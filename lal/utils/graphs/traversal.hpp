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

// C++ includes
#include <functional>
#include <vector>
#include <queue>
#include <stack>

// lal includes
#include <lal/definitions.hpp>
#include <lal/graphs/dgraph.hpp>
#include <lal/graphs/ugraph.hpp>

namespace lal {
namespace utils {

/* This class implements an abstract graph traversal traversal. It can be
 * instantiated with std::queue<> or with std::stack<> in order to obtain a
 * Breadth-First Search (BFS) or a Depth-First Search (DFS).
 *
 * NOTE: we can say that the DFS is a "forward" DFS, i.e., processing the vertices
 * and the edges can only be done when exploring a branch "forwards". Unlike
 * in a custom recursion, for example,
 * void f(node u) {
 *		// do stuff (1)
 *		for (node v : neighbours(u)) {
 *			f(u);
 *			// do stuff (2)
 *		}
 * }
 * the DFS traversal only allows for (1).
 *
 * Users of this class can control the traversal by setting custom control-flow
 * functions. The user can set:
 * - a function used for early termination of the traversal
 * (see @ref set_terminate),
 * - a function that processes the current node in the traversal
 * (see @ref set_process_current),
 * - a function that processes the current edge in the traversal
 * (see @ref set_process_neighbour),
 * - a function that can decide when to add another node to the queue of the
 * traversal (see @ref set_node_add).
 *
 * This graph_traversal traversal can also use "reversed edges" when doing traversals on
 * directed graphs. A back edge in a directed graph of a node u is a node
 * that points to u, namely, the directed edge is of the form (v,u), for another
 * node v of the graph. This can be set via the @ref set_use_back_edges method.
 */
template<class S, class G, typename node = typename lal::node>
class GR_TR {
	public:
		typedef std::function<void (const GR_TR<S,G>&, node)> graph_traversal_process_one;
		typedef std::function<void (const GR_TR<S,G>&, node, node, bool)> graph_traversal_process_two;
		typedef std::function<bool (const GR_TR<S,G>&, node)> graph_traversal_bool_function;

	public:
		// Constructor
		GR_TR(const G& g) : m_G(g) {
			m_vis = std::vector<bool>(g.n_nodes());
			reset();
		}
		// Destructor
		virtual ~GR_TR() { }

		// Set the graph_traversal to its default state.
		void reset() {
			reset_visited();
			clear_structure();

			set_use_rev_edges(false);
			set_process_visited_neighbours(false);

			set_terminate_default();
			set_process_current_default();
			set_process_neighbour_default();
			set_node_add_default();
		}

		void start_at(node source) {
			m_X.push(source);
			m_vis[source] = true;
			do_traversal();
		}

		void start_at(const std::vector<node>& sources) {
			for (const node& u : sources) {
				m_X.push(u);
				m_vis[u] = true;
			}
			do_traversal();
		}

		/* SETTERS */

		// set whether the traversal can use reversed edges
		void set_use_rev_edges(bool use) { m_use_rev_edges = use; }

		// see @ref m_term
		void set_terminate_default()
		{ m_term = [](const GR_TR<S,G>&, const node) -> bool { return false; }; }
		void set_terminate(const graph_traversal_bool_function& f)
		{ m_term = f; }

		// see @ref m_proc_cur
		void set_process_current_default()
		{ m_proc_cur = [](const GR_TR<S,G>&, const node) -> void { }; }
		void set_process_current(const graph_traversal_process_one& f)
		{ m_proc_cur = f; }

		// see @ref m_proc_neigh
		void set_process_neighbour_default()
		{ m_proc_neigh = [](const GR_TR<S,G>&, const node, const node, bool) -> void { }; }
		void set_process_neighbour(const graph_traversal_process_two& f)
		{ m_proc_neigh = f; }

		// see @ref m_add_node
		void set_node_add_default()
		{ m_add_node = [](const GR_TR<S,G>&, const node) -> bool { return true; }; }
		void set_node_add(const graph_traversal_bool_function& f)
		{ m_add_node = f; }

		/*
		 * @brief Should the algorithm call the neighbour processing function
		 * for already visited neighbours?
		 * @param v Either true or false.
		 */
		void set_process_visited_neighbours(bool v) { m_proc_vis_neighs = v; }

		// Sets all nodes to not visited.
		void reset_visited() {
			std::fill(m_vis.begin(), m_vis.end(), false);
		}

		// Empties the structure used for the traversal.
		template<class SS = S,
		typename std::enable_if<std::is_same<SS, std::stack<node>>::value, int >::type = 0
		>
		void clear_structure() { std::stack<node> s; m_X.swap(s); }

		template<class SS = S,
		typename std::enable_if<std::is_same<SS, std::queue<node>>::value, int >::type = 0
		>
		void clear_structure() { std::queue<node> q; m_X.swap(q); }

		// Set node @e u as visited.
		void set_visited(node u, bool vis = true) { m_vis[u] = vis; }

		/* GETTERS */

		// Returns the set of visited nodes.
		bool node_was_visited(node u) const { return m_vis[u]; }

		// have all nodes been visited?
		bool all_visited() const {
			return find(m_vis.begin(), m_vis.end(), false) == m_vis.end();
		}

		// returns the graph
		const G& get_graph() const { return m_G; }

		// Return visited nodes information
		const std::vector<bool>& get_visited() const { return m_vis; }

	protected:
		void deal_with_neighbour(node s, node t, bool ltr) {
			// Process the neighbour 't' of 's'.
			if ((m_vis[t] and m_proc_vis_neighs) or not m_vis[t]) {
				m_proc_neigh(*this, s, t, ltr);
			}

			if (not m_vis[t] and m_add_node(*this, t)) {
				m_X.push(t);
				// set node as visited
				m_vis[t] = true;
			}
		}

		// process neighbours
		//     when the graph is an undirected graph
		template<class GG = G,
		typename std::enable_if<std::is_base_of<graphs::ugraph, GG>::value, int>::type = 0
		>
		void process_neighbours(node s) {
			for (const node& t : m_G.get_neighbours(s)) {
				deal_with_neighbour(s, t, true);
			}
		}
		//     when the graph is a directed graph
		template<class GG = G,
		typename std::enable_if<std::is_base_of<graphs::dgraph, GG>::value, int>::type = 0
		>
		void process_neighbours(node s) {
			for (const node& t : m_G.get_neighbours(s)) {
				deal_with_neighbour(s, t, true);
			}
			// process in-neighbours whenever appropriate
			if (m_use_rev_edges) {
				for (const node& t : m_G.get_in_neighbours(s)) {
					deal_with_neighbour(s, t, false);
				}
			}
		}

		// Returns the next node to be processed.
		// This means we have to access m_X but each structure has different
		// methods.
		template<class SS = S,
		typename std::enable_if<std::is_same<SS, std::stack<node>>::value, int >::type = 0
		>
		node next_node() const { return m_X.top(); }

		template<class SS = S,
		typename std::enable_if<std::is_same<SS, std::queue<node>>::value, int >::type = 0
		>
		node next_node() const { return m_X.front(); }

		/* The graph_traversal traversal is implemented as follows:
		 *
		 * <pre>
		 * ProcessNeighbourhood(graph, u, Nv):
		 *	 1. for each w in Nv do
		 *   2.		if w has not been visited before, or it has been but
		 *	 3.			already-visited nodes have to be processed
		 *	 4.		then
		 *	 5.			proc_neigh(u,w)
		 *	 6.		endif
		 *	 7.
		 *	 8.		if w not visited before and node_add(w) then
		 *	 9.			push w into X
		 *	10.			mark w as visited in vis
		 *	11.		endif
		 *	12.	endfor
		 * </pre>
		 *
		 * <pre>
		 * graph_traversal(graph, source):
		 *	 1.	vis = {false}	// set of |V(graph)| bits set to false
		 *	 2.	X = {source}	// structure of the traversal,
		 *	   					// initialised with the source,
		 *						// either a stack or a queue.
		 *	 3.	while X is not empty do
		 *	 4.		v = X.front or X.top
		 *	 5.		remove X's top
		 *	 6.		proc_curr(v)
		 *	 7.		if terminate(v) then Finish traversal
		 *	 8.		else
		 *	 9.			Nv = out-neighbourhood of v
		 *	10.			ProcessNeighbourhood(graph, v, Nv)
		 *	11.			If graph is directed and process reverse edges then
		 *	12.				Nv = in-neighbourhood of v
		 *	13.				ProcessNeighbourhood(graph, v, Nv)
		 *	14.			endif
		 *	15.		endif
		 *	16.	endwhile
		 * </pre>
		 *
		 * Note that lines (...) extend the neighbourhood of a node "Nv"
		 * depending of the type of graph. If the graph is directed and
		 * the user wants to process "reversed edges", then the neighbourhood
		 * is not limited to "out-neighbours", but also to "in-neighbours".
		 */
		void do_traversal() {
			while (not m_X.empty()) {
				const node s = next_node();
				m_X.pop();

				// process current node
				m_proc_cur(*this, s);

				// check user-defined early termination condition
				if (m_term(*this, s)) { break; }

				process_neighbours(s);
			}
		}

	protected:
		// Constant reference to the graph.
		const G& m_G;
		// The structure of the traversal (either a queue or a stack).
		S m_X;
		// The set of visited nodes.
		std::vector<bool> m_vis;
		// Should we process already visitied neighbours?
		bool m_proc_vis_neighs = false;
		// Use back edges in directed graphs.
		bool m_use_rev_edges = false;

	protected:
		/*
		 * @brief graph_traversal early terminating function.
		 *
		 * Returns true if the @ref graph_traversal algorithm should terminate.
		 *
		 * For more details on when this function is called see @ref do_traversal.
		 * @param graph_traversal The object containing the traversal. This also contains
		 * several attributes that might be useful to guide the traversal.
		 * @param s The node at the front of the queue of the algorithm.
		 */
		graph_traversal_bool_function m_term;

		/*
		 * @brief graph_traversal node processing function.
		 *
		 * Processes the current node visited.
		 *
		 * For more details on when this function is called see @ref do_traversal.
		 * @param graph_traversal The object containing the traversal. This also contains
		 * several attributes that might be useful to guide the traversal.
		 * @param s The node at the front of the queue of the algorithm.
		 */
		graph_traversal_process_one m_proc_cur;

		/*
		 * @brief graph_traversal neighbour node processing function.
		 *
		 * Processes the next visited node. The direction of the nodes
		 * visited passed as parameters is given by the boolean parameter. If
		 * it is true then the edge is s -> t. If it is false then the edge is
		 * t -> s.
		 *
		 * For more details on when this function is called see @ref do_traversal.
		 * @param graph_traversal The object containing the traversal. This also contains
		 * several attributes that might be useful to guide the traversal.
		 * @param s The node at the front of the queue of the algorithm.
		 * @param t The node neighbour of @e u visited by the algorithm.
		 */
		graph_traversal_process_two m_proc_neigh;

		/*
		 * @brief graph_traversal node addition function.
		 *
		 * Determines whether a node @e s should be added to the queue or not.
		 *
		 * For more details on when this function is called see @ref do_traversal.
		 * @param graph_traversal The object containing the traversal. This also contains
		 * several attributes that might be useful to guide the traversal.
		 * @param s The node candidate for addition.
		 */
		graph_traversal_bool_function m_add_node;
};

template<class G, typename node = typename lal::node>
using BFS = GR_TR<std::queue<node>, G, node>;

template<class G, typename node = typename lal::node>
using DFS = GR_TR<std::stack<node>, G, node>;

} // -- namespace utils
} // -- namespace lal
