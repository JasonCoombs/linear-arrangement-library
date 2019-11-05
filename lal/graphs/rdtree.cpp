/*********************************************************************
 *
 *  Linear Arrangement Library - A library that implements a collection
 *  algorithms for linear arrangments of graphs.
 *
 *  Copyright (C) 2019
 *
 *  This file is part of Linear Arrangement Library.
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
 *          Research Gate: https://www.researchgate.net/profile/Lluis_Alemany-Puig
 *
 *      Ramon Ferrer i Cancho (rferrericancho@cs.upc.edu)
 *          LARCA (Laboratory for Relational Algorithmics, Complexity and Learning)
 *          CQL (Complexity and Quantitative Linguistics Lab)
 *          Office S124, Omega building
 *          Jordi Girona St 1-3, Campus Nord UPC, 08034 Barcelona.   CATALONIA, SPAIN
 *          Webpage: https://www.cs.upc.edu/~rferrericancho/
 *          Research Gate: https://www.researchgate.net/profile/Ramon_Ferrer-i-Cancho
 *
 ********************************************************************/

#include <lal/graphs/rdtree.hpp>

// C includes
#include <assert.h>

// C++ includes
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// lal includes
#include <lal/utils/bfs.hpp>

namespace lal {
using namespace utils;

namespace graphs {

rdtree::rdtree() : dgraph() { }
rdtree::rdtree(uint32_t n) : dgraph(n) { }
rdtree::rdtree(const ugraph& g, node r) : dgraph() {
	init_rooted(g, r);
}
rdtree::~rdtree() { }

void rdtree::init_rooted(const ugraph& g, node r) {
	// assert(is_tree(g));
	if (g.n_nodes() == 0) {
		init(0);
		m_r = 0;
		return;
	}

	// build list of directed edges out of 'g' ...
	vector<edge> dir_edges(g.n_edges());
	auto it_dir_edges = dir_edges.begin();

	BFS<ugraph,node> bfs(g);
	bfs.start_at(
		r,
		[](const ugraph&, node, const vector<bool>&, const queue<node>&) -> bool { return false; },
		[](const ugraph&, node, const vector<bool>&, const queue<node>&) -> void { },
		[&](const ugraph&, node s, node t, const vector<bool>&, const queue<node>&) -> void {
			*it_dir_edges = edge(s,t);
			++it_dir_edges;
		}
	);

	// construct rooted directed tree
	init(g.n_nodes());
	add_edges(dir_edges);
	m_r = r;
}

/* MODIFIERS */

void rdtree::disjoint_union(const graph& ) { }

/* SETTERS */

void rdtree::set_root(node r) {
	assert(has_node(r));
	m_r = r;
}
node rdtree::get_root() const { return m_r; }

bool rdtree::is_root(node r) const {
	assert(has_node(r));
	return m_in_degree[r];
}

/* PRIVATE */

} // -- namespace graphs
} // -- namespace lal
