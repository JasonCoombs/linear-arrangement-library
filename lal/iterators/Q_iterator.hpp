/*********************************************************************
 *
 *  Linear Arrangement Library - A library that implements a collection
 *  algorithms for linear arrangments of graphs.
 *
 *  Copyright (C) 2019-2020
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
#include <tuple>

// lal includes
#include <lal/graphs/graph.hpp>

namespace lal {
namespace iterators {

/**
 * @brief Iterator over the set \f$Q\f$ of a graph.
 *
 * This class is used to easily iterate over the elements of the set \f$Q\f$
 * of a graph.
 *
 * This class iterates over the independent pairs of edges of a graph. For
 * undirected graphs, the edges of the pair returned are edges \f$(u,v)\f$
 * so that the inequality \f$u < v\f$ always holds. For directed graphs, this
 * is not always true, since the edges returned always has left-to-right direction.
 *
 * Bear in mind, however, that this class does not modify in any way the
 * graph it is initialised with.
 *
 * The correct usage of this class is
 * @code
 *		Q_iterator it(g); // g is a graph
 *		while (it.has_next()) {
 *			it.next();
 *			edge_pair q = it.get_pair();
 *			// ...
 *		}
 * @endcode
 */
class Q_iterator {
	public:
		/**
		 * @brief Constructor
		 * @param g Constant reference to the graph over which we iterate.
		 */
		Q_iterator(const graphs::graph& g);
		/// Destructor.
		~Q_iterator();

		/// Returns true if there are pairs of independent edges left to be iterated over.
		bool has_next() const;

		/// Moves the iterator to the next pair, if there is any.
		void next();

		/// Returns the current edge pair.
		edge_pair get_pair() const;

		/**
		 * @brief Sets the iterator at the beginning of the set of edges.
		 * @post The next call to method @ref next() returns the first edge
		 * of the graph.
		 */
		void reset();

	private:
		typedef std::pair<node,std::size_t> E_pointer;

	private:
		/// Graph we are iterating on
		const graphs::graph& m_G;

		/// Current pointers to the first edge.
		E_pointer m_cur1 = E_pointer(0,0);
		/// Current pointers to the second edge.
		E_pointer m_cur2 = E_pointer(0,0);

		/// Is there a next pair of independent edges?
		bool m_exists_next = true;
		/// Current pair of independent edges.
		edge_pair m_cur_pair = edge_pair(edge(0,0),edge(0,0));

	private:
		/// Returns the pair of independent edges pointed by @ref m_cur1 and @ref m_cur2.
		edge_pair make_current_pair() const;

};

} // -- namespace iterators
} // -- namespace lal
