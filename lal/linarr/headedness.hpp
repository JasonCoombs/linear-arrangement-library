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

#pragma once

// C++ includes
#include <vector>

// lal includes
#include <lal/dgraph.hpp>
#include <lal/numeric/rational.hpp>

namespace lal {
namespace linarr {

/**
 * @brief Computes headedness of a directed graph as an exact rational number.
 *
 * Given a graph and a permutation of its vertices, computes the ratio of
 * right-branching edges over the total amount of edges.
 *
 * A value of 0 indicates perfect left branching, and a value of 1 indicates
 * perfect right-branching.
 * @param g Input graph.
 * @param arr Permutation of the vertices. If @e pi[u] = p then
 * node @e u is placed in position @e p of the arrangement.
 * @return Returns \f$\frac{# right-branching edges}{# edges}\f$ as an exact
 * rational number.
 */
numeric::rational headedness_rational
(const dgraph& g, const std::vector<node>& pi = {});

/**
 * @brief Computes headedness of a directed graph.
 *
 * Given a graph and a permutation of its vertices, computes the ratio of
 * right-branching edges over the total amount of edges.
 *
 * A value of 0 indicates perfect left branching, and a value of 1 indicates
 * perfect right-branching.
 * @param g Input graph.
 * @param arr Permutation of the vertices. If @e pi[u] = p then
 * node @e u is placed in position @e p of the arrangement.
 * @return Returns \f$\frac{# right-branching edges}{# edges}\f$.
 */
double headedness
(const dgraph& g, const std::vector<node>& pi = {});

} // -- namespace linarr
} // -- namespace lal
