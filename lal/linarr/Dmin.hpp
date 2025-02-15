/*********************************************************************
 *
 *  Linear Arrangement Library - A library that implements a collection
 *  algorithms for linear arrangments of graphs.
 *
 *  Copyright (C) 2019 - 2021
 *
 *  This file is part of Linear Arrangement Library. The full code is available
 *  at:
 *      https://github.com/LAL-project/linear-arrangement-library.git
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
#include <lal/linear_arrangement.hpp>
#include <lal/graphs/free_tree.hpp>
#include <lal/graphs/rooted_tree.hpp>
#include <lal/linarr/algorithms_Dmin_projective.hpp>
#include <lal/linarr/algorithms_Dmin_planar.hpp>
#include <lal/linarr/algorithms_Dmin.hpp>

namespace lal {
namespace linarr {

/**
 * @brief Computes the minimum value of \f$D\f$ in free trees.
 *
 * Calculates the minimum value of \f$D\f$ and returns a linear arrangement
 * yielding this value. Such optimal value of \f$D\f$ depends on the choice
 * of algorithm for its calculation.
 *
 * See the description of the values in @ref lal::linarr::algorithms_Dmin for
 * details on the algorithm implemented and to see references to the papers.
 * @param t Input free tree.
 * @param a The algorithm to use.
 * @returns The minimum value of \f$D\f$ and an optimum arrangement.
 * @pre Input tree @e t must be a valid tree (see @ref lal::graphs::tree::is_tree()).
 * @pre This function has as extra preconditions those specified in the enumeration
 * passed as parameter.
 */
std::pair<uint64_t, linear_arrangement> min_sum_edge_lengths(
	const graphs::free_tree& t,
	const algorithms_Dmin& a = algorithms_Dmin::Shiloach
) noexcept;
/**
 * @brief Computes the minimum value of \f$D\f$ in trees.
 *
 * Calculates the minimum value of \f$D\f$ and returns a linear arrangement
 * yielding this value. Such optimal value of \f$D\f$ depends on the choice
 * of algorithm for its calculation.
 *
 * This function converts the input rooted into a free tree (see @ref
 * lal::graphs::rooted_tree::to_undirected())
 * @param t Input rooted tree.
 * @param a The algorithm to use.
 * @returns The minimum value of \f$D\f$ and an optimum arrangement.
 * @pre Input tree @e t must be a valid tree (see @ref lal::graphs::tree::is_tree()).
 * @pre This function has as extra preconditions those specified in the enumeration
 * passed as parameter.
 */
inline
std::pair<uint64_t, linear_arrangement> min_sum_edge_lengths(
	const graphs::rooted_tree& t,
	const algorithms_Dmin& a = algorithms_Dmin::Shiloach
) noexcept
{
	return min_sum_edge_lengths(t.to_free_tree(), a);
}

/**
 * @brief Computes the minimum value of \f$D\f$ in trees under the planarity
 * constraint.
 *
 * This function implements the algorithm published in \cite Alemany2022a.
 *
 * Computes an optimal planar linear arrangement for free trees. A planar linear
 * arrangement is an arrangement in which there are no edge crossings. This problem
 * was originally tackled by Iordanskii \cite Iordanskii1987a and later by Hochberg
 * and Stallmann \cite Hochberg2003a. See \cite Alemany2022a for a review.
 * @param t Input free tree.
 * @param a The algorithm to use.
 * @returns The minimum value of \f$D\f$ and an optimum arrangement.
 * @pre Input tree @e t must be a valid tree (see @ref lal::graphs::tree::is_tree()).
 */
std::pair<uint64_t, linear_arrangement> min_sum_edge_lengths_planar(
	const graphs::free_tree& t,
	const algorithms_Dmin_planar& a = algorithms_Dmin_planar::AlemanyEstebanFerrer
)
noexcept;
/**
 * @brief Computes the minimum value of \f$D\f$ in trees under the planarity
 * constraint.
 *
 * This function implements the algorithm published in \cite Alemany2022a.
 *
 * Computes an optimal planar linear arrangement for free trees. A planar linear
 * arrangement is an arrangement in which there are no edge crossings. This problem
 * was originally tackled by Iordanskii \cite Iordanskii1987a and later by Hochberg
 * and Stallmann \cite Hochberg2003a. See \cite Alemany2022a for a review.
 *
 * This function converts the input rooted into a free tree (see @ref
 * lal::graphs::rooted_tree::to_undirected())
 * @param t Input rooted tree.
 * @param a The algorithm to use.
 * @returns The minimum value of \f$D\f$ and an optimum arrangement.
 * @pre Input tree @e t must be a valid tree (see @ref lal::graphs::tree::is_tree()).
 */
inline
std::pair<uint64_t, linear_arrangement> min_sum_edge_lengths_planar(
	const graphs::rooted_tree& t,
	const algorithms_Dmin_planar& a = algorithms_Dmin_planar::AlemanyEstebanFerrer
)
noexcept
{
	return min_sum_edge_lengths_planar(t.to_free_tree(), a);
}

/**
 * @brief Computes the minimum value of \f$D\f$ in rooted trees under the projectivity
 * constraint.
 *
 * Computes an optimal projective linear arrangement for rooted trees. A
 * projective linear arrangement is an arrangement in which there are no edge
 * crossings and the root is not covered by any edge.
 *
 * This function implements the algorithm in \cite Alemany2022a. A non-linear
 * time algorithm to solve this problem was oulined in \cite Gildea2007a.
 *
 * @param t Input rooted tree.
 * @param a The algorithm to use.
 * @returns The minimum value of \f$D\f$ and an optimum arrangement.
 * @pre Input tree @e t must be a valid tree (see @ref lal::graphs::tree::is_tree()).
 */
std::pair<uint64_t, linear_arrangement> min_sum_edge_lengths_projective(
	const graphs::rooted_tree& t,
	const algorithms_Dmin_projective& a = algorithms_Dmin_projective::AlemanyEstebanFerrer
)
noexcept;

} // -- namespace linarr
} // -- namespace lal
