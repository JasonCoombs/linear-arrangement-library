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
 *          Resarch Gate: https://www.researchgate.net/profile/Ramon_Ferrer-i-Cancho
 *
 ********************************************************************/
 
#include <lal/linarr/D.hpp>

// C includes
#include <assert.h>
#include <stdlib.h>

// C++ includes
#include <numeric>
using namespace std;

// lal includes
#include <lal/utils/macros.hpp>
#include <lal/edge_iterator.hpp>

namespace lal {
namespace linarr {

uint32_t __sum_length_edges(const ugraph& g, const vector<node>& arr) {
	const node n = g.n_nodes();

	// translation table:
	// T[u] = p <-> node u is at position p
	uint32_t *T = static_cast<uint32_t *>( malloc(n*sizeof(uint32_t)) );
	for (uint32_t i = 0; i < n; ++i) {
		T[ arr[i] ] = i;
	}

	// sum of lengths
	uint32_t l = 0;

	edge_iterator e_it(g);
	while (e_it.has_next()) {
		const edge e = e_it.next();
		const node u = e.first;
		const node v = e.second;

		// accumulate length of edge
		l += (T[u] >= T[v] ? T[u] - T[v] : T[v] - T[u]);
	}
	free(T);
	return l;
}

uint32_t sum_length_edges(const ugraph& g, const vector<node>& arr) {
	return macros::call_with_empty_arrangement(__sum_length_edges, g, arr);
}

} // -- namespace linarr
} // -- namespace lal
