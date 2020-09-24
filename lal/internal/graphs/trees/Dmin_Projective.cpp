/*********************************************************************
 *
 *  Linear Arrangement Library - A library that implements a collection
 *  algorithms for linear arrangments of graphs.
 *
 *  Copyright (C) 2019-2020
 *
 *  This file is part of Linear Arrangement Library. To see the full code
 *  visit the webpage:
 *      https://github.com/lluisalemanypuig/linear-arrangement-library.git
 *
 *  Linear Arrangement Library is free software: you can redistribute it
 *  and/or modify it under the terms of the GNU Affero General Public License
 *  as published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  Linear Arrangement Library is distributed in the hope that it will be
 *  useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with Linear Arrangement Library.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contact:
 *
 *      Lluís Alemany Puig (lalemany@cs.upc.edu)
 *          LARCA (Laboratory for Relational Algorithmics, Complexity and Learning)
 *          CQL (Complexity and Quantitative Linguistics Lab)
 *          Jordi Girona St 1-3, Campus Nord UPC, 08034 Barcelona.   CATALONIA, SPAIN
 *          Webpage: https://cqllab.upc.edu/people/lalemany/
 *
 *      Ramon Ferrer i Cancho (rferrericancho@cs.upc.edu)
 *          LARCA (Laboratory for Relational Algorithmics, Complexity and Learning)
 *          CQL (Complexity and Quantitative Linguistics Lab)
 *          Office S124, Omega building
 *          Jordi Girona St 1-3, Campus Nord UPC, 08034 Barcelona.   CATALONIA, SPAIN
 *          Webpage: https://cqllab.upc.edu/people/rferrericancho/
 *
 ********************************************************************/

#include <lal/internal/graphs/trees/Dmin.hpp>

// C++ includes
#include <cassert>
using namespace std;

// lal includes
#include <lal/linarr/D.hpp>
#include <lal/iterators/E_iterator.hpp>
#include <lal/internal/graphs/trees/make_projective_arr.hpp>
#include <lal/internal/sorting/counting_sort.hpp>

typedef std::pair<lal::node,uint32_t> node_size;

namespace lal {
using namespace graphs;
using namespace iterators;

namespace internal {

typedef char place;
#define LEFT_PLACE 0
#define RIGHT_PLACE 1
#define ROOT_PLACE 2

typedef char direction;
#define TO_LEFT 1
#define TO_RIGHT 2

#define right_placed_pos(int_size) (int_size%2 == 1 ? int_size/2 : int_size/2 - 1)
#define left_placed_pos(int_size) (int_size%2 == 1 ? int_size/2 : int_size/2)

#define get_int_size(v) (t.out_degree(v) + 1)

#define get_neighbours(t,u)														\
	(t.get_rooted_tree_type() == rooted_tree::rooted_tree_type::arborescence ?	\
	t.get_out_neighbours(u) : t.get_in_neighbours(u))

constexpr position pos_in_interval(uint32_t int_size, place P) {
	if (int_size == 1) { return 0; }
	switch (P) {
		case LEFT_PLACE: return left_placed_pos(int_size);
		case RIGHT_PLACE: return right_placed_pos(int_size);
	}
	return int_size/2;
}

constexpr direction start_left_right(uint32_t int_size, place P) {
	switch (P) {
		case LEFT_PLACE: return (int_size%2 == 1 ? TO_RIGHT : TO_LEFT);
		case RIGHT_PLACE: return (int_size%2 == 1 ? TO_LEFT : TO_RIGHT);
	}
	return TO_LEFT;
}

/*
 * t: the rooted tree.
 * M: adjacency matrix of the tree with extra information: for each vertex,
 *		attach an integer that represents the size of the subtree rooted
 *		at that vertex. Each adjacency list is sorted INCREASINGLY by that size.
 * r: the vertex root of the subtree whose interval is to be made
 * place: where, respect to its parent, has 'r' been placed in the interval.
 *		LEFT_PLACE, RIGHT_PLACE, ROOT_PLACE
 *		The last value is only valid for the root of the whole tree.
 * data: the interval of every vertex.
 * 		data[v][p] = u <-> vertex 'u' is at position 'p' of vertex 'v's interval
 *
 * Returns the sum of the length of the outgoing edges from vertex 'r' plus
 * the length of the anchor of the edge from 'r' to its parent. Such length
 * is defined as the number of vertices to the left of 'r' if 'r_place'
 * is RIGHT_PLACE, or as the number of vertices to the right of 'r' if
 * 'r_place' is LEFT_PLACE.
 */
uint32_t Dmin_Pr__optimal_interval_of(
	const rooted_tree& t, const vector<vector<node_size>>& M,
	node r, place r_place,
	vector<vector<node>>& data
)
{
	const uint32_t r_int_size = get_int_size(r);

	vector<node>& interval = data[r];
	interval = vector<node>(r_int_size);

	if (r_int_size == 1) {
		data[r][0] = r;
		return 0;
	}

	if (r_int_size == 2) {
		const node vi = get_neighbours(t,r)[0];
		interval[0] = (r_place == LEFT_PLACE ? vi : r);
		interval[1] = (r_place == LEFT_PLACE ? r : vi);
		const place vi_place = (r_place == LEFT_PLACE ? LEFT_PLACE : RIGHT_PLACE);
		const uint32_t D = Dmin_Pr__optimal_interval_of(t, M, vi, vi_place, data);
		return D + 1;
	}

	// sizes of the subtrees
	const auto& children = M[r];

	// choose 'r's position
	const size_t root_pos = pos_in_interval(r_int_size, r_place);

	// and place the root
	interval[root_pos] = r;

	// ------------------------
	// then, place the children

	size_t leftpos = root_pos - 1;
	size_t rightpos = root_pos + 1;

	// left == "start placing children to the left of the root or not"
	direction dir = start_left_right(r_int_size, r_place);

	// size of the intervals from the root to the left end
	uint32_t acc_size_left = 0;
	// size of the intervals from the root to the right end
	uint32_t acc_size_right = 0;

	// total sum of length of edges + the length of the edge from 'r'
	// to its parent (if any)
	uint32_t D = 0;
	// total sum of lengths of edges from 'r' to 'vi'
	uint32_t d = 0;

	// while placing the children calculate the
	// length of the edge from 'r' to vertex 'vi'
	for (const auto& p : children) {
		const node vi = p.first;
		const uint32_t ni = p.second;
		// the place of 'vi' with respect to 'r'
		const place vi_place = (dir == TO_LEFT ? LEFT_PLACE : RIGHT_PLACE);

		// recursive call: make the interval of 'vi'
		D += Dmin_Pr__optimal_interval_of(
			t, M, vi, vi_place, data
		);

		// accumulate size of interval
		d += (dir == TO_LEFT ? acc_size_left : acc_size_right);
		// add length of edge over root 'r'
		d += 1;

		// place vertex vi
		interval[(dir == TO_LEFT ? leftpos : rightpos)] = vi;

		// 1. increase/decrease right/left position
		// 2. accumulate size of subtree rooted at vi
		leftpos -= (dir == TO_LEFT ? 1 : 0);
		acc_size_left += (dir == TO_LEFT ? ni : 0);

		rightpos += (dir == TO_LEFT ? 0 : 1);
		acc_size_right += (dir == TO_LEFT ? 0 : ni);

		// change direction
		dir = (dir == TO_LEFT ? TO_RIGHT : TO_LEFT);
	}

	// accumulate sum of lengths of edges of the subtrees
	D +=
	(r_place == ROOT_PLACE ? 0 :
	 r_place == LEFT_PLACE ? acc_size_right : acc_size_left);

	return D + d;
}

uint32_t Dmin_Pr__optimal_interval_of(
	const rooted_tree& t,
	const vector<vector<pair<node,uint32_t>>>& M,
	node r, vector<vector<node>>& data
)
{
	return Dmin_Pr__optimal_interval_of(t, M, r, ROOT_PLACE, data);
}

pair<uint32_t, linear_arrangement> Dmin_Projective(const rooted_tree& t) {
	assert(t.is_rooted_tree());

	const uint32_t n = t.n_nodes();
	if (n == 1) {
		return make_pair(0, linear_arrangement(0,0));
	}

	typedef pair<edge,uint32_t> edge_size;
	typedef vector<edge_size>::iterator edge_size_t;

	// for every edge (u,v), store the tuple
	//    (n_v, (u,v))
	// at L[u]
	vector<edge_size> L;
	{
	E_iterator Eit(t);
	while (Eit.has_next()) {
		Eit.next();
		const edge e = Eit.get_edge();
		const node v = e.second;
		L.push_back(make_pair(e,t.n_nodes_subtree(v)));
	}
	}

	// sort all tuples in L using the size of the subtree
	internal::counting_sort<edge_size_t, edge_size, true>(
		L.begin(), L.end(), n,
		[](const edge_size& T) -> size_t { return std::get<1>(T); }
	);

	// M[u] : adjacency list of vertex u sorted increasingly according
	// to the sizes of the subtrees.
	vector<vector<node_size>> M(n);
	for (const auto& T : L) {
		const node u = std::get<0>(T).first;
		const node v = std::get<0>(T).second;
		const uint32_t nv = std::get<1>(T);
		M[u].push_back(make_pair(v,nv));
		assert(t.has_edge(u,v));
	}

#if defined DEBUG
	for (node u = 0; u < n; ++u) {
		assert(M[u].size() == t.degree(u));
	}
#endif

	// the optimal intervals
	vector<vector<node>> data(t.n_nodes());

	// construct the optimal intervals
	const uint32_t D = Dmin_Pr__optimal_interval_of(
		t, M, t.get_root(), ROOT_PLACE, data
	);

	// construct the arrangement
	const linear_arrangement arr = internal::put_in_arrangement(t, data);

	return make_pair(D, arr);
}

} // -- namespace internal
} // -- namespace lal
