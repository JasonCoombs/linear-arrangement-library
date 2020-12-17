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

#include <lal/graphs/directed_graph.hpp>

// C++ includes
#include <algorithm>
#include <cassert>
#include <cmath>
using namespace std;

// lal includes
#include <lal/internal/sorting/bit_sort.hpp>
#include <lal/iterators/E_iterator.hpp>
#include <lal/properties/Q.hpp>

namespace lal {
namespace graphs {

/* CONSTRUCTORS */

directed_graph::directed_graph() : graph() { }
directed_graph::directed_graph(uint32_t n) {
	init(n);
}
directed_graph::directed_graph(const directed_graph& d) : graph() {
	copy_full_directed_graph(d);
}
directed_graph::directed_graph(directed_graph&& d) {
	move_full_directed_graph(std::move(d));
}
directed_graph::~directed_graph() { }

/* OPERATORS */

directed_graph& directed_graph::operator= (const directed_graph& d) {
	copy_full_directed_graph(d);
	return *this;
}

directed_graph& directed_graph::operator= (directed_graph&& d) {
	move_full_directed_graph(std::move(d));
	return *this;
}

/* MODIFIERS */

void directed_graph::normalise() {
	char *mem = new char[n_nodes()]{0};
	for (node u = 0; u < n_nodes(); ++u) {
		neighbourhood& out_nu = m_adjacency_list[u];
		if (not is_sorted(out_nu.begin(), out_nu.end())) {
			internal::bit_sort_mem(out_nu.begin(), out_nu.end(), out_nu.size(), mem);
		}
		neighbourhood& in_nu = m_in_adjacency_list[u];
		if (not is_sorted(in_nu.begin(), in_nu.end())) {
			internal::bit_sort_mem(in_nu.begin(), in_nu.end(), in_nu.size(), mem);
		}
	}
	m_normalised = true;
	delete[] mem;
}

bool directed_graph::check_normalised() {
	if (not graph::check_normalised()) { return false; }

	// check that every adjacency list is sorted
	for (node u = 0; u < n_nodes(); ++u) {
		const neighbourhood& out_nu = m_adjacency_list[u];
		if (not is_sorted(out_nu.begin(), out_nu.end())) {
			// if some is not then the graph is not normalised
			m_normalised = false;
			return false;
		}

		const neighbourhood& in_nu = m_in_adjacency_list[u];
		if (not is_sorted(in_nu.begin(), in_nu.end())) {
			// if some is not then the graph is not normalised
			m_normalised = false;
			return false;
		}
	}
	// all adjacency lists are sorted so
	// the graph is normalised
	m_normalised = true;
	return true;
}

directed_graph& directed_graph::add_edge(
	node u, node v, bool to_norm, bool check_norm
)
{
	assert(not has_edge(u,v));

	neighbourhood& out_u = m_adjacency_list[u];
	out_u.push_back(v);
	neighbourhood& in_v = m_in_adjacency_list[v];
	in_v.push_back(u);
	++m_num_edges;

	// do the extra work!
	extra_work_per_edge_add(u, v);

	if (is_normalised()) {
		// the graph was normalised
		if (to_norm) {
			// keep it normalised
			internal::bit_sort(out_u.begin(), out_u.end(), out_u.size());
			internal::bit_sort(in_v.begin(), in_v.end(), in_v.size());
		}
		else if (check_norm) {
			// Even though we have not been asked to normalise the
			// graph, it may still be so... This means we have to
			// check whether the graph is still normalised. We might
			// be lucky....
			const size_t out_u_s = out_u.size();
			const bool out_u_norm =
				(out_u_s <= 1 ? m_normalised : out_u[out_u_s - 2] < out_u[out_u_s - 1]);
			const size_t in_v_s = in_v.size();
			const bool in_v_norm =
				(in_v_s <= 1 ? m_normalised : in_v[in_v_s - 2] < in_v[in_v_s - 1]);
			m_normalised = m_normalised and out_u_norm and in_v_norm;
			/*if (su > 1) {
				m_normalised = nu[su - 2] < nu[su - 1];
			}*/
		}
		else {
			m_normalised = false;
		}
	}
	else {
		// the graph was not normalised.

		if (to_norm) {
			// the graph needs to be normalised,
			// from a non-normalised state
			normalise();
		}
		else if (check_norm) {
			// the graph is certainly not normalised --
			// no need to check anything
		}
		else {
			// not 'to_norm' and not 'check_norm' --
			m_normalised = false;
		}
	}

	return *this;
}

directed_graph& directed_graph::add_edges(
	const vector<edge>& edges, bool to_norm, bool check_norm
)
{
	for (const edge& e : edges) {
		const node u = e.first;
		const node v = e.second;
		assert(not has_edge(u,v));

		m_adjacency_list[u].push_back(v);
		m_in_adjacency_list[v].push_back(u);
		++m_num_edges;

		// do the extra work!
		extra_work_per_edge_add(u, v);
	}

	if (to_norm) {
		// normalise directly, it might save us time
		normalise();
	}
	else if (check_norm) {
		// only check
		check_normalised();
	}
	else {
		// not 'to_norm' and not 'check_norm' --
		m_normalised = false;
	}

	return *this;
}

directed_graph& directed_graph::set_edges(
	const vector<edge>& edges, bool to_norm, bool check_norm
)
{
	{
	const uint32_t n = n_nodes();
	clear(); init(n);
	}

	for (const edge& e : edges) {
		const node u = e.first;
		const node v = e.second;
		assert(not has_edge(u,v));

		m_adjacency_list[u].push_back(v);
		m_in_adjacency_list[v].push_back(u);
	}
	m_num_edges = static_cast<uint32_t>(edges.size());

	if (to_norm) {
		// normalise directly, it might save us time
		normalise();
	}
	else if (check_norm) {
		// only check
		check_normalised();
	}
	else {
		// not 'to_norm' and not 'check_norm' --
		m_normalised = false;
	}
	return *this;
}

directed_graph& directed_graph::remove_edge(
	node u, node v, bool norm, bool check_norm
)
{
	assert(has_edge(u,v));
	--m_num_edges;

	neighbourhood& out_u = m_adjacency_list[u];
	neighbourhood& in_v = m_in_adjacency_list[v];
	remove_single_edge(u,v, out_u, in_v);

	// if (is_normalised()) {
	//		Removing an edge does not change normalisation
	// }
	// if (not is_normalised()) {
	//		Since the graph was not normalised, we need to do something about it now.
	//      if (norm)     ... NORMALISE THE GRAPH
	//      if (not norm) ... the result of deleting edges is certainly
	//                        not normalised since the deletion of edges
	//                        keeps the normalisation invariant. No need
	//                        to check.
	// }

	if (not is_normalised()) {
		if (norm) {
			normalise();
		}
		else if (check_norm) {
			// we might have been lucky...
			check_normalised();
		}
		else {
			// not 'to_norm' and not 'check_norm' --
			m_normalised = false;
		}
	}
	return *this;
}

directed_graph& directed_graph::remove_edges(
	const vector<edge>& edges, bool norm, bool check_norm
)
{
	for (const edge& e : edges) {
		const node u = e.first;
		const node v = e.second;
		assert(has_edge(u,v));
		--m_num_edges;

		neighbourhood& out_u = m_adjacency_list[u];
		neighbourhood& in_v = m_in_adjacency_list[v];
		remove_single_edge(u,v, out_u, in_v);
	}

	// see comments in method ugraph::remove_edge for details

	if (not is_normalised()) {
		if (norm) {
			normalise();
		}
		else if (check_norm) {
			// we might have been lucky...
			check_normalised();
		}
		else {
			// not 'to_norm' and not 'check_norm' --
			m_normalised = false;
		}
	}
	return *this;
}

void directed_graph::disjoint_union(const directed_graph& g) {
	// number of vertices before adding the out-neighbours
	const uint32_t n = n_nodes();

	// this call updates the out-neighbours adjacency list,
	// as well as the number of edges and the graph's normalisation
	graph::__disjoint_union(g);

	// update the in-neighbours adjacency list
	for (node u = 0; u < g.n_nodes(); ++u) {
		// add new edges by appending all the neighbours of 'u' in 'g'
		m_in_adjacency_list.push_back( g.get_in_neighbours(u) );
		// relabel the nodes
		for (node& v : m_in_adjacency_list.back()) {
			v += n;
		}
	}
}

/* SETTERS */

/* GETTERS */

vector<edge_pair> directed_graph::Q() const {
	return graph::Q(properties::size_Q(*this));
}

bool directed_graph::has_edge(node u, node v) const {
	assert(u != v);
	assert(has_node(u));
	assert(has_node(v));

	const neighbourhood& out_u = m_adjacency_list[u];
	const neighbourhood& in_v = m_in_adjacency_list[v];

	if (is_normalised() and min(out_u.size(), in_v.size()) >= 64) {
		return (out_u.size() <= in_v.size() ?
			binary_search(out_u.begin(), out_u.end(), v) :
			binary_search(in_v.begin(), in_v.end(), u)
		);
	}
	return (out_u.size() <= in_v.size() ?
		find(out_u.begin(), out_u.end(), v) != out_u.end() :
		find(in_v.begin(), in_v.end(), u) != in_v.end()
	);
}

undirected_graph directed_graph::to_undirected() const {
	undirected_graph g(n_nodes());

	vector<edge> my_edges;
	my_edges.reserve(n_edges());

	// add edges so that none are repeated
	iterators::E_iterator it(*this);
	while (it.has_next()) {
		it.next();
		const edge e = it.get_edge();
		const edge se = e.first < e.second ? e : edge(e.second, e.first);

		if (not std::binary_search(my_edges.begin(), my_edges.end(), se)) {
			my_edges.push_back(se);
		}
	}

	g.set_edges(my_edges);
	return g;
}

/* PROTECTED */

void directed_graph::_init(uint32_t n) {
	graph::_init(n);
	m_in_adjacency_list = vector<neighbourhood>(n);
}

void directed_graph::_clear() {
	graph::_clear();
	m_in_adjacency_list.clear();
}

void directed_graph::copy_full_directed_graph(const directed_graph& d) {
	// copy parent class
	copy_full_graph(d);

	// copy this class' members
	m_in_adjacency_list = d.m_in_adjacency_list;
}

void directed_graph::move_full_directed_graph(directed_graph&& d) {
	// move-assign parent class
	move_full_graph(std::move(d));

	// move-assign this class' members
	m_in_adjacency_list = std::move(d.m_in_adjacency_list);
}

/* PRIVATE */

void directed_graph::remove_single_edge(
	node u, node v, neighbourhood& out_u, neighbourhood& in_v
)
{
	// it_v: pointer to node v in out_u
	// it_u: pointer to node u in in_v
	vector<node>::iterator it_v, it_u;

	// find the nodes in the lists
	if (is_normalised()) {
		it_v = lower_bound(out_u.begin(), out_u.end(), v);
		it_u = lower_bound(in_v.begin(), in_v.end(), u);
	}
	else {
		it_v = find(out_u.begin(), out_u.end(), v);
		it_u = find(in_v.begin(), in_v.end(), u);
	}

	// check that the iterators point to the correct value
	assert(*it_v == v);
	assert(*it_u == u);

	// remove edges from the lists
	out_u.erase(it_v);
	in_v.erase(it_u);

	// do the extra work!
	extra_work_per_edge_remove(u, v);
}

} // -- namespace graphs
} // -- namespace lal
