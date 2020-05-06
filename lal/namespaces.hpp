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
 *          Resarch Gate: https://www.researchgate.net/profile/Ramon_Ferrer-i-Cancho
 *
 ********************************************************************/

/* In this file are declared all namespaces of the LAL library. Moreover,
 * we include the information that should appear in the main page of the
 * documentation.
 * 
 * This is done for documentation purposes only.
 */
 
 /** \mainpage Documentation of LAL, the Linear Arrangement Library
 * 
 * This library offers a variety of algorithms related to linear arrangements of graphs so as to provide to researchers in the field of Quantitative Linguistics a toolset with which they can perform statistical analyses on different corpora of languages efficiently and effectively. Therefore, this library implements several state-of-the-art algorithms and offers a variety of functionalities. While most of the functions have been generalised to be applicable to graphs, we also provide specialised functions for trees, which are more efficient than they more general counterparts.
 * 
 * The main goal of this library is to provide algorithms with which the library's users can use to do statistical studies. One of the most attractive features offered in this library is that of treebank dataset processing. We offer a class that automatically processes a dataset and computes several metrics based on the capabilities of the library. See class @ref lal::io::treebank_processor for details. We also provide classes for custom processing of treebanks (see @ref lal::io::treebank_dataset and @ref lal::io::treebank_reader).
 * 
 * All the features of syntactic dependency trees that can be calculated with the algorithms in this library are gathered in the namespaces @ref lal::linarr and in @ref lal::properties. These features include
 * - the sum of edge lengths (see @ref lal::linarr::sum_length_edges), and the expectation and variance of the sum of edge lengths (see @ref lal::properties::expectation_D and lal::properties::variance_D),
 * - the number of crossings (see @ref lal::linarr::n_crossings), and the expectation and variance of the number of crossings (see @ref lal::properties::expectation_C and lal::properties::variance_C),
 * - any moment of the degree of the vertices of a graph (@ref lal::properties::mmt_degree),
 * - the mean dependency distance (see @ref lal::linarr::MDD),
 * - the mean dependency distance over ensembles of graphs (see @ref lal::linarr::MDD_1level and @ref lal::linarr::MDD_2level),
 * - the mean hierarchical distance (see @ref lal::properties::MHD),
 * - the headedness of a tree (see @ref lal::linarr::headedness),
 * - the type of syntactic dependency trees according the their projectivity (see @ref lal::linarr::get_tree_structure_type).
 * 
 * Other algorithms, also gathered in the same namespaces, offer the computation of optimal arrangements. For example, it is offered
 * - the computation of the minimal arrangements with respect to the sum of edge lengths (see @ref lal::linarr::compute_Dmin), with free choice on the algorithm to be used (see @ref lal::linarr::algorithms_Dmin).
 * 
 * As extra features, useful for experimentation, are the generation of different types of trees, all of which are available in the @ref lal::generate namespace. We have implemented existing techniques for enumerating all
 * - labelled/unlabelled free trees,
 * - unlabelled rooted trees,
 * 
 * for generating uniformly at random,
 * 
 * - labelled/unlabelled free/rooted trees.
 * 
 * The documentation of each class include usage examples.
 * 
 * \section s1 The basic data structures in this library
 * 
 * In order to be able to use the library comfortably, its users must take good note of the different data structures that are the library's core.
 * 
 * \subsection ss1_s1 Exact integer and rational arithmetic
 * 
 * Most operations in this library are done using exact integer and rational arithmetic. Such arithmetic is powered by the GMP library (see \cite GMP_library). We have wrapped their C structures into the classes @ref lal::numeric::integer and @ref lal::numeric::rational.
 * 
 * \subsection ss3_s1 The different types of graphs
 * 
 * As it should be expected, this library offers a number of different graph abstractions: undirected graphs (see @ref lal::graphs::ugraph), directed graphs (see @ref lal::graphs::dgraph), free trees (see @ref lal::graphs::ftree) and roted trees (see @ref lal::graphs::rtree), all of which can be found within the @ref lal::graphs namespace.
 * 
 * \subsubsection sss1_ss3_s1 The internal structure of graphs
 * 
 * Although all graphs should be regarded as unlabelled, each node carries an implicit labelling. Such labelling has a most trivial nature since each node is labelled with a number between 0 and the total number of vertices minus 1.
 * 
 * Due to most graphs being sparse, the data structure of choice are adjacency lists where each vertex has a list of neighbouring nodes, or simply neighbours, associated to it. The user can affect the order of appearance of neighbours in multiple ways. One of them is, evidently, the order in which edges are added. Another way is via the @ref lal::graphs::graph::normalise function, which sorts every list of neighbours increasingly. By default, the addition of edges is normalising, namely the following code
 * @code
 * lal::graphs::ftree t(4);
 * t.add_edge(0,1,false).add_edge(0,3,false).add_edge(0,2,false);
 * t.normalise();
 * cout << t << endl;
 * @endcode
 * produces the same output as
 * @code
 * lal::graphs::ftree t(4);
 * t.add_edge(0,1).add_edge(0,3).add_edge(0,2);
 * cout << t << endl;
 * @endcode
 * Such normalisation is required by some of the algorithms in this library. Without proper normalisation, the algorithms are not likely to compute correct values. The parameter that governs the graphs' normalisation is called the normalisation parameter.
 * 
 * The adjacency list structure has been extended to directed graphs in a way that the user can query them for in-degree (see @ref lal::graphs::dgraph::in_degree) and in-neighbours (see @ref lal::graphs::dgraph::get_in_neighbours).
 * 
 * \section s2 Basic terminology and notation
 * 
 * The user will note, after browsing through the capabilities of the library, that several concepts are quite ubiquitous. The @ref lal::node type is simply a typedef of an unsigned integer type, and the @ref lal::edge type is simply a STL's pair of nodes.
 * 
 * A more advanced concept is that of linear arrangement (see @ref lal::linearrgmnt). In this library, a linear arrangement is viewed as a function that relates each node to a position in a linear sequence. Due to the properties of such functions, a linear arrangement is implemented with the STL's vector. Note that the concept of linear arrangement has been detached from that of trees, and the pair of a linear arrangement and a tree forms, in the context of the library, a syntactic dependency tree (this is why this class is not implemented). The symbol of choice for representing a linear arrangement in the library is the greek letter for the number pi \f$\pi\f$.
 * 
 * Now, many functions (see those fuctions within the @ref lal::linarr namespace) admit a linear arrangement which can be empty. Whenever it is empty, i.e., the value of the parameter is an empty vector, the positions of the nodes of the graphs in question are given by their implicit label. Such empty arrangement is called, in the context of the library, the identity arrangement symbolised with \f$\pi_I\f$. Therefore, the following measurement of the sum of the lengths of the edges are equivalent
 * @code
 * lal::graphs::ftree t(4);
 * t.add_edges({edge(0,1), edge(1,2), edge(2,3)});
 * uint32_t D1 = linarr::sum_length_edges(t);
 * uint32_t D2 = linarr::sum_length_edges(t, {0,1,2,3});
 * @endcode
 * The possibility of expliciting a linear arrangement increases the flexibility of the library. For example, for the purposes of illustration, one can calculate the expected sum of the length of the edges as follows
 * @code
 * lal::graphs::ftree t(4);
 * t.add_edges({edge(0,1), edge(1,2), edge(2,3)});
 * lal::numeric::rational Dt = 0;
 * lal::linearrgmnt arr = {0,1,2,3};
 * do {
 * 		Dt += linarr::sum_length_edges(t, arr);
 * }
 * while (std::next_permutation(arr.begin(), arr.end());
 * Dt /= 24;
 * @endcode
 * 
 * Throughout the library we refer to the sum of length of edges with a capital D, \f$D\f$, and we refer to the number of crossings with a capital C, \f$C\f$.
 * 
 * \section s3 Using the library effectively
 * 
 * As a rule of the thumb, the user is encouraged not to change the default value of the parameters whenever they are given. However, certain operations can be less efficient than others, and sometimes it is even desirable to use values different from the default ones.
 * 
 * One the one hand, the wrong choice of operation can affect the library's performance gravely. For example, the addition/deletion of edges to/from graphs is slower when it is done edge by edge. Users are highly encouraged to add/delete them in bulk using the appropriate functions (see, for example, @ref lal::graphs::ugraph::add_edges and @ref lal::graphs::ugraph::remove_edges). The following code is discouraged
 * @code
 * lal::graphs::utree t(10);
 * node u, v;
 * for (int i = 0; i < 9; ++i) {
 * 		cin >> u >> v;
 * 		t.add_edge(u,v);
 * }
 * @endcode
 * while the next piece of code is strongly encouraged whenever possible
 * @code
 * lal::graphs::utree t(10);
 * vector<edge> e(9);
 * for (int i = 0; i < 9; ++i) {
 * 		cin >> e[i].first >> e[i].second;
 * }
 * t.add_edges(e);
 * @endcode
 * Similar reasoning should be applied to the deletion of edges.
 * 
 * On the other hand, graphs are seldom required to be normalised. For example, when calculating the variance of \f$C\f$ (see @ref lal::properties::variance_C), it is mandatory that the graph be normalised, namely, the function has a precondition that requires the graph to be normalised. If such a function is to be called eventually then add all edges in bulk and with normalisation, or read the graph from disk also with normalisation. However, if such functions will never be called then the users are encouraged to set the normalisation parameter to false. For example, if the variance of \f$C\f$ is to be calculated,
 * @code
 * lal::graphs::ftree t;
 * lal::io::read_edge_list(t);
 * double var_C = lal::properties::variance_C(t);
 * @endcode
 * but if not
 * @code
 * lal::graphs::ftree t;
 * lal::io::read_edge_list(t, false);
 * // ...
 * @endcode
 */

/**
 * @brief Main namespace of the library.
 *
 * This namespace groups all namespaces of the library. Each namespace
 * classifies the classes and functions in categories.
 */
namespace lal {

/**
 * @brief Namespace for the generation of different types of graphs.
 * 
 * This namespace contains algorithms for the generation of
 * certain types of graphs, for example: all unique unlabelled free trees.
 */
namespace generate {}

/**
 * @brief Namespace for the graphs data structures.
 * 
 * This namespace contains the data structures that implement graphs. Note that,
 * although we do not support labelled graphs, the nodes of these graphs
 * carry a label, a number between 0 and \f$n-1\f$, where \f$n\f$ is the number
 * of nodes of the graph.
 */
namespace graphs {}

/**
 * @brief Input/Output functions.
 * 
 * This namespace contains the functions for input/output operations.
 * 
 * This includes reading a graph (or collection of graphs) from
 * a file. The formats supported for reading are:
 * - Edge list. See functions @ref read_edge_list(const std::string&, graphs::ugraph&, bool)
 * and @ref read_edge_list(const std::string&, graphs::dgraph&, bool).
 * 
 * Other features contained in this namespace are:
 * - Processing of whole corpora of treebanks automatically (see @ref io::treebank_processor)
 * - Custom processing of whole coropora of treebanks (see @ref io::treebank_dataset)
 * - Custom processing of single treebank files (see @ref io::treebank_reader)
 */
namespace io {}

/**
 * @brief Iterators namespace.
 * 
 * This namespace contains classes useful for iterating through the graph.
 * These classes iterate
 * - over the set of edges (see @ref E_iterator).
 * - over the set of pairs of independent edges \f$Q\f$ (see @ref Q_iterator).
 */
namespace iterators {}

/**
 * @brief Linear arrangements namespace.
 * 
 * This namespace contains all operations related to linear arrangements.
 * 
 * All linear arrangements are vectors of as many nodes as the
 * corresponding graph has. If \f$\pi\f$ is a linear arrangement then
 * the @e u-th position of \f$\pi\f$ contains the position of that node in
 * the arrangement. Formally, \f$\pi[u] = p\f$ if, and only if, node @e u
 * is at position @e p in the linear arrangement.
 *
 * The identity arrangement \f$\pi_I\f$ is a special case of linear arrangement
 * used in many functions. Such an arrangement is one that maps each node
 * into the position corresponding to their label, i.e., \f$ \pi_I(u) = u\f$.
 * 
 * This namespace contains the computation of:
 * - the number of crossings \f$C\f$ (see @ref n_crossings).
 * - the sum of the length of edges \f$D\f$ (see @ref sum_length_edges).
 * - the headedness of directed graphs (see @ref headedness).
 * - the Mean Dependency Distance for single trees (see @ref MDD).
 * 
 * It also contains methods for the classification of trees into projective
 * classes (see @ref tree_structure for the supported classes and see function
 * @ref get_tree_structure_type to know how to classify the trees).
 */
namespace linarr {}

/**
 * @brief Numeric namespace.
 *
 * This namespace contains the data structures that wrap the basic structures
 * of the GMP library for integers of arbitrary precision (see @ref integer)
 * and exact rational numbers (see @ref rational).
 */
namespace numeric {

	/**
	 * @brief GMP utils.
	 *
	 * This namespace contains a collection of useful algorithms
	 * for manipulating the basic data structures of the GMP library.
	 */
	namespace gmp_utils {}
}

/**
 * @brief Properties of graphs.
 * 
 * This namespace contains basic properties of graphs including, but
 * not limited to:
 * - hubiness (see @ref hubiness),
 * - Mean Hierarchical Distance (see @ref MHD),
 * - computation of the moments of:
 * 		- degree about zero \f$ \langle k^p \rangle\f$ (see @ref mmt_degree),
 * 		- in-degree about zero \f$ \langle k_{in}^p \rangle\f$ (see @ref mmt_in_degree),
 * 		- out-degree about zero \f$ \langle k_{out}^p \rangle\f$ (see @ref mmt_out_degree),
 * - computation of the amount of pairs of independent edges \f$Q\f$ (see @ref size_Q),
 * - computation of the variance of \f$V_{rla}[D]\f$ (see @ref variance_D),
 * - computation of \f$V_{rla}[C]\f$:
 * 		- in general graphs (see @ref variance_C),
 * 		- in forests (see @ref variance_C_forest),
 * 		- in trees (see @ref variance_C_tree).
 * 
 * All calculations can be retrieved as exact rational numbers
 * (see @ref numeric::rational), but also as floating point values of
 * double precision.
 */
namespace properties {}

} // -- namespace lal
