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

// C++ includes
#include <functional>
#include <queue>

// lal includes
#include <lal/basic_types.hpp>
#include <lal/graphs/directed_graph.hpp>
#include <lal/graphs/undirected_graph.hpp>
#include <lal/detail/data_array.hpp>

namespace lal {
namespace detail {

/**
 * @brief Abstract graph Breadth-First Search traversal.
 *
 * The traversal can be controlled by setting custom control-flow functions:
 * - a function used for early termination of the traversal
 * (see @ref set_terminate),
 * - a function that processes the current node in the traversal
 * (see @ref set_process_current),
 * - a function that processes the current edge in the traversal
 * (see @ref set_process_neighbour),
 *
 * This graph_traversal traversal can also use "reversed edges" when doing traversals on
 * directed graphs. A back edge in a directed graph of a node u is a node
 * that points to u, namely, the directed edge is of the form (v,u), for another
 * node v of the graph. This can be set via the @ref set_use_rev_edges method.
 *
 * An example of usage is as follows:
 @code
 detail::BFS<graphs::undirected_graph> bfs(g); // 'g' is an undirected graph
 bfs.set_terminate( ... ); // assign a function to decide when to terminate the search.
 bfs.set_process_neighbour( ... ); // assign a function to process neighbours
 bfs.start_at(0); // start the traversal now at node 0.
 @endcode
 *
 * @tparam graph_t Type of graph.
 */
template<
	class graph_t,
	bool is_directed = std::is_base_of_v<graphs::directed_graph, graph_t>,
	std::enable_if_t< std::is_base_of_v<graphs::graph, graph_t>, bool > = true
>
class BFS {
public:
	typedef std::function<void (const BFS<graph_t>&, node)> BFS_process_one;
	typedef std::function<void (const BFS<graph_t>&, node, node, bool)> BFS_process_two;
	typedef std::function<bool (const BFS<graph_t>&, node)> BFS_bool_one;
	typedef std::function<bool (const BFS<graph_t>&, node, node)> BFS_bool_two;

public:
	/// Constructor
	BFS(const graph_t& g) noexcept : m_G(g), m_vis(m_G.get_num_nodes()) {
		reset();
	}
	/// Destructor
	~BFS() noexcept { }

	/// Set the graph_traversal to its default state.
	void reset() noexcept {
		reset_visited();
		clear_structure();

		set_use_rev_edges(false);
		set_process_visited_neighbours(false);

		set_terminate_default();
		set_process_current_default();
		set_process_neighbour_default();
		set_node_add_default();
	}

	/**
	 * @brief Start traversal at a given node.
	 * @param source Node.
	 */
	void start_at(node source) noexcept {
		m_queue.push(source);
		m_vis[source] = 1;
		do_traversal();
	}

	/**
	 * @brief Start the traversal at every given node.
	 * @param sources List of node.
	 */
	void start_at(const std::vector<node>& sources) noexcept {
		for (const node& u : sources) {
			m_queue.push(u);
			m_vis[u] = 1;
		}
		do_traversal();
	}

	/* SETTERS */

	/// Set whether the traversal can use reversed edges
	void set_use_rev_edges(bool use) noexcept { m_use_rev_edges = use; }

	/// Set the default value of @ref m_term.
	void set_terminate_default() noexcept
	{ m_term = [](const BFS<graph_t>&, const node) -> bool { return false; }; }
	/// Set the function that controls the termination of the loop.
	void set_terminate(const BFS_bool_one& f) noexcept
	{ m_term = f; }

	/// Set the default value of @ref m_proc_cur.
	void set_process_current_default() noexcept
	{ m_proc_cur = [](const BFS<graph_t>&, const node) -> void { }; }
	/// Set the function that controls the processing of the current node.
	void set_process_current(const BFS_process_one& f) noexcept
	{ m_proc_cur = f; }

	/// Set the default value of @ref m_proc_neigh.
	void set_process_neighbour_default() noexcept
	{ m_proc_neigh = [](const BFS<graph_t>&, const node, const node, bool) -> void { }; }
	/// Set the function that controls the processing of the current neighbour.
	void set_process_neighbour(const BFS_process_two& f) noexcept
	{ m_proc_neigh = f; }

	// see @ref m_add_node
	void set_node_add_default() noexcept
	{ m_add_node = [](const BFS<graph_t>&, const node, const node) -> bool { return true; }; }
	void set_node_add(const BFS_bool_two& f) noexcept
	{ m_add_node = f; }

	/**
	 * @brief Should the algorithm call the neighbour processing function
	 * for already visited neighbours?
	 * @param v Either true or false.
	 */
	void set_process_visited_neighbours(bool v) noexcept
	{ m_proc_vis_neighs = v; }

	/// Sets all nodes to not visited.
	void reset_visited() noexcept { m_vis.fill(0); }

	/// Clear the memory allocated for this structure.
	void clear_structure() noexcept { std::queue<node> q; m_queue.swap(q); }

	/// Set node @e u as visited or not.
	void set_visited(node u, char vis) noexcept { m_vis[u] = vis; }

	/* GETTERS */

	/// Returns whether or not node @e u has been visited.
	bool node_was_visited(node u) const noexcept { return m_vis[u]; }

	/// Have all nodes been visited?
	bool all_visited() const noexcept {
		return std::all_of(m_vis.begin(), m_vis.end(), [](auto x){return x == 1;});
	}

	/// Returns a constant reference to the graph
	const graph_t& get_graph() const noexcept { return m_G; }

	/// Return visited nodes information
	const data_array<char>& get_visited() const noexcept { return m_vis; }

protected:
	// ltr: is the 'natural' orientation of the vertices "s -> t"?
	//      If true, then the edge in the graph is (s,t)
	//      If false, the edge in the graph is (t,s)
	void deal_with_neighbour(node s, node t, bool ltr) noexcept {
		// Process the neighbour 't' of 's'.
		if ((m_vis[t] and m_proc_vis_neighs) or not m_vis[t]) {
			m_proc_neigh(*this, s, t, ltr);
		}

		if (not m_vis[t] and m_add_node(*this, s, t)) {
			m_queue.push(t);
			// set node as visited
			m_vis[t] = true;
		}
	}

	/// Process the neighbours of node @e s in an undirected graph.
	template<
		class GG = graph_t,
		std::enable_if_t<
			std::is_base_of_v<graphs::undirected_graph, GG>, bool
		> = true
	>
	void process_neighbours(node s) noexcept {
		for (const node& t : m_G.get_neighbours(s)) {
			// Edges are processed in the direction "s -> t".
			// This is also the 'natural' orientation of the edge,
			// so this explains the 'true'.
			deal_with_neighbour(s, t, true);
		}
	}

	/// Process the neighbours of node @e s in an directed graph.
	template<
		class GG = graph_t,
		std::enable_if_t<
			std::is_base_of_v<graphs::directed_graph, GG>, bool
		> = true
	>
	void process_neighbours(node s) noexcept {
		for (const node& t : m_G.get_out_neighbours(s)) {
			// Edges are processed in the direction "s -> t".
			// This is also the 'natural' orientation of the edge,
			// hence the 'true'.
			deal_with_neighbour(s, t, true);
		}
		// process in-neighbours whenever appropriate
		if (m_use_rev_edges) {
			for (const node& t : m_G.get_in_neighbours(s)) {
				// Edges are processed in the direction "s -> t".
				// However, the 'natural' orientation of the edge
				// is "t -> s", hence the 'false'.
				deal_with_neighbour(s, t, false);
			}
		}
	}

	/// Return the next node in line.
	node next_node() const noexcept { return m_queue.front(); }

	/**
	 * @brief Traversal through the graph's vertices.
	 *
	 * The graph_traversal traversal is implemented as follows:
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
	 *    .	// set of |V(graph)| bits set to false
	 *	 1.	vis = {false}
	 *    .	// structure of the traversal, initialised with the source,
	 *	  .	// either a stack or a queue.
	 *	 2.	X = {source}
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
	void do_traversal() noexcept {
		while (not m_queue.empty()) {
			const node s = next_node();
			m_queue.pop();

			// process current node
			m_proc_cur(*this, s);

			// check user-defined early termination condition
			if (m_term(*this, s)) { break; }

			process_neighbours(s);
		}
	}

protected:
	/// Constant reference to the graph.
	const graph_t& m_G;
	/// The structure of the traversal.
	std::queue<node> m_queue;
	/// The set of visited nodes.
	data_array<char> m_vis;
	/// Should we process already visitied neighbours?
	bool m_proc_vis_neighs = false;
	/// Use back edges in directed graphs.
	bool m_use_rev_edges = false;

protected:
	/**
	 * @brief graph_traversal early terminating function.
	 *
	 * Returns true if the graph_traversal algorithm should terminate.
	 *
	 * For more details on when this function is called see @ref do_traversal.
	 * @param graph_traversal The object containing the traversal. This also contains
	 * several attributes that might be useful to guide the traversal.
	 * @param s The node at the front of the queue of the algorithm.
	 */
	BFS_bool_one m_term;

	/**
	 * @brief graph_traversal node processing function.
	 *
	 * Processes the current node visited.
	 *
	 * For more details on when this function is called see @ref do_traversal.
	 * @param graph_traversal The object containing the traversal. This also contains
	 * several attributes that might be useful to guide the traversal.
	 * @param s The node at the front of the queue of the algorithm.
	 */
	BFS_process_one m_proc_cur;

	/**
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
	BFS_process_two m_proc_neigh;

	/**
	 * @brief graph_traversal node addition function.
	 *
	 * Determines whether a node @e s should be added to the queue or not.
	 *
	 * For more details on when this function is called see @ref do_traversal.
	 * @param graph_traversal The object containing the traversal. This also contains
	 * several attributes that might be useful to guide the traversal.
	 * @param s The node candidate for addition.
	 */
	BFS_bool_two m_add_node;
};

} // -- namespace detail
} // -- namespace lal
