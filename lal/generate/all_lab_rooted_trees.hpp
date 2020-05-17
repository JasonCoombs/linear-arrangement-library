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
#include <lal/generate/all_lab_free_trees.hpp>
#include <lal/graphs/rtree.hpp>

namespace lal {
namespace generate {

/**
 * @brief Exhaustive labelled rooted tree generator.
 *
 * This class is based on the labelled free trees generator (see
 * @ref all_lab_free_trees).
 *
 * The correct usage of this class is
 * @code
 *		all_lab_rooted_trees TreeGen(n);
 *		while (TreeGen.has_next()) {
 *			TreeGen.next();
 *			lal::graphs::rtree T = TreeGen.get_tree();
 *			// ...
 *		}
 * @endcode
 */
class all_lab_rooted_trees {
	public:
		/**
		 * @brief Default constructor.
		 *
		 * When constructed this way, the class needs to be initialised.
		 * See @ref init(uint32_t).
		 */
		all_lab_rooted_trees();
		/// Constructor with number of nodes.
		all_lab_rooted_trees(uint32_t n);
		/// Default destructor.
		~all_lab_rooted_trees();

		/**
		 * @brief Initialises the generator.
		 *
		 * Initialises the internal state of this generator
		 * so that method @ref next can be called safely.
		 *
		 * Initialising this class already allows the user
		 * to retrieve the first tree via method @ref get_tree.
		 *
		 * It is allowed to call this method two or more times,
		 * and with different values for parameter @e n.
		 * @param n The number of nodes of the trees to be
		 * generated.
		 */
		void init(uint32_t n);

		/**
		 * @brief Returns whether there are more trees to generate.
		 * @return Returns true if there are still more trees
		 * to generate. Returns false if all trees have been
		 * generated (there are no more unique trees of this
		 * size that were not generated before).
		 * @pre The generator must have been initialised.
		 */
		bool has_next() const;

		/**
		 * @brief Generates next tree.
		 *
		 * Modifies the internal state so that the next tree
		 * can be retrieved using method @ref get_tree().
		 * @pre The generator must have been initialised.
		 */
		void next();

		/**
		 * @brief Constructs the current tree.
		 * @pre The generator must have been initialised, and method
		 * @ref next must have been called at least once.
		 * @return Returns the tree generated with method @ref next().
		 */
		graphs::rtree get_tree() const;

	private:
		/// Number of nodes of the generated trees.
		uint32_t m_n;
		/// Does exist a next labelled rooted tree?
		bool m_has_next;

		/// Labelled free tree generator.
		all_lab_free_trees m_lab_free_tree_gen;
		/// Current labelled free tree.
		graphs::ftree m_cur_ftree;
		/// Current root.
		node m_cur_root;
};

} // -- namespace generate
} // -- namespace lal
