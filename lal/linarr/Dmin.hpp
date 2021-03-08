/*********************************************************************
 *
 *  Linear Arrangement Library - A library that implements a collection
 *  algorithms for linear arrangments of graphs.
 *
 *  Copyright (C) 2019
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

#pragma once

// lal includes
#include <lal/graphs/free_tree.hpp>
#include <lal/graphs/rooted_tree.hpp>
#include <lal/linarr/algorithms_Dmin.hpp>

namespace lal {
namespace linarr {

/**
 * @brief Computes the minimum value of \f$D\f$ in rooted trees.
 *
 * Calculates the minimum value of \f$D\f$ and returns a linear arrangement
 * yielding this value. Such optimal value of \f$D\f$ depends on the choice
 * of algorithm for its calculation.
 * @param t Input tree.
 * @param a The algorithm to be chosen.
 * @returns The minimum value of \f$D\f$ and an optimum arrangement.
 * @pre Input tree @e t must be a valid tree (see @ref lal::graphs::tree::is_tree()).
 * @pre This function has as extra preconditions those specified in the enumeration
 * passed as parameter.
 */
std::pair<uint32_t, linear_arrangement> Dmin
(const graphs::rooted_tree& t, const algorithms_Dmin& a);

/**
 * @brief Computes the minimum value of \f$D\f$ in free trees.
 *
 * Calculates the minimum value of \f$D\f$ and returns a linear arrangement
 * yielding this value. Such optimal value of \f$D\f$ depends on the choice
 * of algorithm for its calculation.
 * @param t Input tree.
 * @param a The algorithm to be chosen.
 * @returns The minimum value of \f$D\f$ and an optimum arrangement.
 * @pre Input tree @e t must be a valid tree (see @ref lal::graphs::tree::is_tree()).
 * @pre This function has as extra preconditions those specified in the enumeration
 * passed as parameter.
 */
std::pair<uint32_t, linear_arrangement> Dmin
(const graphs::free_tree& t, const algorithms_Dmin& a);

} // -- namespace linarr
} // -- namespace lal
