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
 * @brief Algorithm to calculate optimal projective arrangements of rooted trees.
 *
 * Computes an optimal projective linear arrangement for rooted trees.
 * A projective linear arrangement is an arrangement in which there are
 * no edge crossings and the root is not covered by any edge.
 *
 * This function implements Gildea and Temperley's algorithm published in \cite Gildea2007a.
 *
 * @param t Input rooted tree.
 * @pre The object @e t must be a valid rooted tree (see @ref graphs::rtree::is_rooted_tree).
 * @pre The tree must have the size of its subtrees calculated (see
 * @ref graphs::rtree::need_recalc_size_subtrees).
 */
std::pair<uint32_t, linear_arrangement> Dmin_Projective
(const graphs::rooted_tree& t);

/**
 * @brief Algorithm to calculate unconstrained optimal linearization of free trees.
 *
 * Computes an unconstrained optimal linear arrangement of a free tree and
 * the value of its cost, i.e., the sum of the lengths of the edges.
 *
 * This function implements Yossi Shiloach's algorithm published in \cite Shiloach1979a.
 * The implementation of this algorithm uses the corrections published
 * in \cite Esteban2017a.
 *
 * @pre The object must be a tree (see @ref graphs::rtree::is_tree).
 */
std::pair<uint32_t, linear_arrangement> Dmin_Unconstrained_YS
(const graphs::free_tree& t);

/**
 * @brief Algorithm to calculate unconstrained optimal linearization of free trees.
 *
 * Computes an unconstrained optimal linear arrangement of a free tree and
 * the value of its cost, i.e., the sum of the lengths of the edges.
 *
 * This function implements Fan Chung's algorithm published in \cite Chung1984a.
 *
 * @pre The object must be a tree (see @ref graphs::rtree::is_tree).
 */
std::pair<uint32_t, linear_arrangement> Dmin_Unconstrained_FC
(const graphs::free_tree& t);

/* -------------------------------------------------------------------------- */

/**
 * @brief Computes the minimum value of \f$D\f$ in rooted trees.
 *
 * Calculates the minimum value of \f$D\f$ and returns a linear arrangement
 * yielding this value. Such optimal value of \f$D\f$ depends on the choice
 * of algorithm for its calculation.
 * @param t Input tree.
 * @param a The algorithm to be chosen.
 * @pre The preconditions of this function have to meet the preconditions of
 * the function that is called:
 * - if @e a is @ref algorithms_Dmin::Projective the function called is
 * @ref compute_Dmin_Projective.
 * @return Returns the minimum value of \f$D\f$ and an optimum arrangement.
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
 * @pre The preconditions of this function have to meet the preconditions of
 * the function that is called:
 * - if @e a is @ref algorithms_Dmin::Unconstrained_YS the function called is
 * @ref compute_Dmin_Unconstrained_YS.
 * - if @e a is @ref algorithms_Dmin::Unconstrained_FC the function called is
 * @ref compute_Dmin_Unconstrained_FC.
 * @return Returns the minimum value of \f$D\f$ and an optimum arrangement.
 */
std::pair<uint32_t, linear_arrangement> Dmin
(const graphs::free_tree& t, const algorithms_Dmin& a);

} // -- namespace linarr
} // -- namespace lal
