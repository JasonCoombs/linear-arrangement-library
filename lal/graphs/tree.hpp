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

#pragma once

// lal includes
#include <lal/graphs/graph.hpp>

namespace lal {
namespace graphs {

/**
 * @brief Tree graph class.
 *
 * This class is just a class that inherits from @ref graph so as to allow
 * passing classes that inherit from this class to functions that only accept
 * attributes of type @ref graph.
 *
 * Tree-like data structures that might be useful for the user are:
 * - @ref utree
 * - @ref dtree
 * - @ref urtree
 * - @ref drtree
 */
class tree : virtual public graph {
	public:
		tree();
		virtual ~tree();

		/**
		 * @brief Returns whether this graph is an actual tree or not.
		 *
		 * Returns true if the number of edges is one less than the
		 * number of vertices. Note that this would not really be true if the
		 * addition of edges was not constrained. Since it is constrained in a
		 * way that no cycles can be produced (see @ref utree::add_edge,
		 * @ref utree::add_edges, @ref dtree::add_edge, @ref dtree::add_edges),
		 * then we only need to check for the number of edges.
		 *
		 * For further characterisations of a tree, see \cite Tree_Wikipedia.
		 */
		bool is_tree() const;

		/// Returns whether this tree is a rooted tree.
		virtual bool is_rooted() const = 0;
};

} // -- namespace graphs
} // -- namespace lal
