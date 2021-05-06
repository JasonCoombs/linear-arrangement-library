/*********************************************************************
 *
 *  Linear Arrangement Library - A library that implements a collection
 *  algorithms for linear arrangments of graphs.
 *
 *  Copyright (C) 2019 - 2021
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

// C++ includes
#include <random>

// lal includes
#include <lal/graphs/rooted_tree.hpp>
#include <lal/generate/rand_lab_free_trees.hpp>

namespace lal {
namespace generate {

/**
 * @brief Uniformly random generation of labelled rooted trees.
 *
 * <b>Users should refrain from using this class.</b> The generation of random
 * labelled trees should be done using the wrapper class @ref rand_lab_rooted_trees.
 * This class, however, contains the actual code to generate labelled rooted trees
 * uniformly at random.
 *
 * These trees are generated by first generating uniformly at random a free
 * labelled tree. Then, a node of the generated tree is chosen uniformly at random.
 * This node plays the role of the root of the rooted labelled tree. The edges
 * are oriented away from the root.
 */
class _rand_lab_rooted_trees : public _rand_lab_free_trees {
public:
	/* CONSTRUCTORS */

	/**
	 * @brief Constructor with size of tree and seed for the random number generator.
	 *
	 * In case the seed given is '0', a random seed will be generated.
	 * @param n Number of nodes.
	 * @param seed The seed used for the random generator.
	 */
	_rand_lab_rooted_trees(uint32_t n, uint32_t seed = 0) noexcept
		: _rand_lab_free_trees(n, seed) { }
	/**
	 * @brief Copy constructor.
	 * @param Gen Random labelled rooted tree generator.
	 */
	_rand_lab_rooted_trees(const _rand_lab_rooted_trees& Gen) = default;
#ifndef SWIG
	/**
	 * @brief Move constructor.
	 * @param Gen Random labelled rooted tree generator.
	 */
	_rand_lab_rooted_trees(_rand_lab_rooted_trees&& Gen) = default;
#endif
	/// Default destructor.
	~_rand_lab_rooted_trees() = default;

	/* GETTERS */

	/**
	 * @brief Generates uniformly at random a labelled rooted tree.
	 * @returns A labelled tree generated uniformly at random. The
	 * tree is rooted at vertex 0.
	 */
	inline graphs::rooted_tree get_tree() noexcept {
		const graphs::free_tree t = _rand_lab_free_trees::get_tree();
		const node r = m_unif(m_gen);
		return graphs::rooted_tree(t, r);
	}

protected:
	/**
	 * @brief Sets the size of the labelled trees to generate.
	 *
	 * Initialises the random number generator.
	 * @param seed Integer value used to seed the random number generator.
	 */
	inline void init(uint32_t seed = 0) noexcept {
		_rand_lab_free_trees::init(seed);
	}
};

/**
 * @brief Uniformly random generation of labelled rooted trees.
 *
 * This is a wrapper class of @ref _rand_lab_rooted_trees. Users should refrain
 * from using said class. However, users will find the implementation details
 * (as for algorithms and citations) in the documentation of said class.
 *
 * An example of usage of this class is
 * @code
 *		lal::generate::rand_lab_rooted_trees Gen(n);
 *		for (int i = 0; i < 100; ++i) {
 *			const lal::graphs::rooted_tree T = Gen.get_tree();
 *			// ...
 *		}
 * @endcode
 * Equivalently,
 * @code
 *		lal::generate::rand_lab_rooted_trees Gen(n);
 *		for (int i = 0; i < 100; ++i) {
 *			const lal::graphs::rooted_tree T = Gen.yield_tree();
 *			// ...
 *		}
 * @endcode
 */
class rand_lab_rooted_trees : public _tree_generator<graphs::rooted_tree> {
public:
	/* CONSTRUCTORS */

	/**
	 * @brief Constructor with size of tree and seed for the random number generator.
	 *
	 * In case the seed given is '0', a random seed will be generated.
	 * @param n Number of nodes.
	 * @param seed The seed used for the random generator. If the seed is 0 then
	 * a random seed is generated and used.
	 */
	rand_lab_rooted_trees(uint32_t n, uint32_t seed = 0) noexcept
		: _tree_generator<graphs::rooted_tree>(n), m_Gen(n, seed) { }
	/**
	 * @brief Copy constructor.
	 * @param Gen Random labelled rooted tree generator.
	 */
	rand_lab_rooted_trees(const rand_lab_rooted_trees& Gen) = default;
#ifndef SWIG
	/**
	 * @brief Move constructor.
	 * @param Gen Random labelled rooted tree generator.
	 */
	rand_lab_rooted_trees(rand_lab_rooted_trees&& Gen) = default;
#endif
	/// Default destructor.
	~rand_lab_rooted_trees() = default;

	inline graphs::rooted_tree yield_tree() noexcept {
		return get_tree();
	}

protected:
	/**
	 * @brief Returns a labelled rooted tree chosen uniformly at random.
	 *
	 * See @ref _rand_lab_rooted_trees::get_tree for details.
	 * @returns A labelled rooted tree chosen uniformly at random.
	 */
	inline graphs::rooted_tree __get_tree() noexcept { return m_Gen.get_tree(); }

protected:
	/// See @ref _rand_lab_rooted_trees for details.
	_rand_lab_rooted_trees m_Gen;
};

} // -- namespace generate
} // -- namespace lal
