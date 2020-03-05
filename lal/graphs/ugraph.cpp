/*********************************************************************
 *
 *  Linear Arrangement Library - A library that implements a collection
 *  algorithms for linear arrangments of graphs.
 *
 *  Copyright (C) 2019-2020
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
 
#include <lal/graphs/ugraph.hpp>

// C++ includes
#include <algorithm>
//#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

// lal includes
#include <lal/properties/Q.hpp>
#include <lal/utils/sort_integers.hpp>

namespace lal {
namespace graphs {

/* PUBLIC */

ugraph::ugraph() : graph() { }
ugraph::ugraph(uint32_t n) {
	init(n);
}
ugraph::~ugraph() { }

/* OPERATORS */

/* MODIFIERS */

ugraph& ugraph::add_edge(node u, node v, bool to_norm) {
	assert(not has_edge(u,v));
	assert(u != v);
	assert(has_node(u));
	assert(has_node(v));

	neighbourhood& nu = m_adjacency_list[u];
	neighbourhood& nv = m_adjacency_list[v];
	nu.push_back(v);
	nv.push_back(u);
	++m_num_edges;

	if (m_normalised) {
		// the graph was normalised
		if (to_norm) {
			// keep it normalised. Insertion sort
			// applied to the last nodes added
			utils::sort_1_n_inc(nu.begin(), nu.end());
			utils::sort_1_n_inc(nv.begin(), nv.end());
		}
		else {
			// Even though we have not been asked to normalise the
			// graph, it may still be so... This means we have to
			// check whether the graph is still normalised. We may
			// be lucky....
			const auto su = nu.size();
			const auto sv = nv.size();
			if (su > 1 and sv > 1) {
				m_normalised = nu[su - 2] < nu[su - 1] and nv[sv - 2] < nv[sv - 1];
			}
			else if (su > 1) {
				m_normalised = nu[su - 2] < nu[su - 1];
			}
			else if (sv > 1) {
				m_normalised = nv[sv - 2] < nv[sv - 1];
			}
		}
	}
	else if (to_norm) {
		// the graph needs to be normalised,
		// from a non-normalised state
		normalise();
	}

	return *this;
}

ugraph& ugraph::add_edges(const vector<edge>& edges, bool to_norm) {
	for (const edge& e : edges) {
		const node u = e.first;
		const node v = e.second;
		assert(not has_edge(u,v));
		assert(u != v);

		m_adjacency_list[u].push_back(v);
		m_adjacency_list[v].push_back(u);
		++m_num_edges;
	}

	if (to_norm) {
		// normalise directly, it might save us time
		normalise();
	}
	else {
		// only check
		check_normalised();
	}

	return *this;
}

/* SETTERS */

/* GETTERS */

std::vector<edge_pair> ugraph::Q() const {
	return graph::Q(properties::size_Q(*this));
}

const neighbourhood& ugraph::get_neighbours(node u) const {
	assert(has_node(u));
	return m_adjacency_list[u];
}

uint32_t ugraph::degree(node u) const {
	assert(has_node(u));
	return static_cast<uint32_t>(m_adjacency_list[u].size());
}

bool ugraph::has_edge(node u, node v) const {
	assert(has_node(u));
	assert(has_node(v));

	const neighbourhood& nu = m_adjacency_list[u];
	const neighbourhood& nv = m_adjacency_list[v];

	if (is_normalised() and std::min(nu.size(), nv.size()) >= 64) {
		return (nu.size() <= nv.size() ?
			binary_search(nu.begin(), nu.end(), v) :
			binary_search(nv.begin(), nv.end(), u)
		);
	}
	return (nu.size() <= nv.size() ?
		find(nu.begin(), nu.end(), v) != nu.end() :
		find(nv.begin(), nv.end(), u) != nv.end()
	);
}

bool ugraph::is_directed() const { return false; }
bool ugraph::is_undirected() const { return true; }

/* PROTECTED */

void ugraph::_init(uint32_t n) {
	//cout << "ugraph::_init(uint32_t)" << endl;
	graph::_init(n);
}

void ugraph::_clear() {
	//cout << "ugraph::_clear()" << endl;
	graph::_clear();
}

/* PRIVATE */

} // -- namespace graphs
} // -- namespace lal

