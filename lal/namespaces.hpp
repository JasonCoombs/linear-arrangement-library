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
 *      Lluís Alemany-Puig (lalemany@cs.upc.edu)
 *          LARCA (Laboratory for Relational Algorithmics, Complexity and Learning)
 *          CQL (Complexity and Quantitative Linguistics Lab)
 *          Jordi Girona St 1-3, Campus Nord UPC, 08034 Barcelona.   CATALONIA, SPAIN
 *          Webpages:
 *              https://cqllab.upc.edu/people/lalemany/
 *              https://www.researchgate.net/profile/Lluis_Alemany-Puig
 *
 *     Juan Luis Esteban (esteban@cs.upc.edu)
 *          Office 110, Omega building
 *          Jordi Girona St 1-3, Campus Nord UPC, 08034 Barcelona.   CATALONIA, SPAIN
 *          Webpages:
 *              https://www.cs.upc.edu/~esteban/
 *              https://www.researchgate.net/profile/Juan_Esteban13
 * 
 *      Ramon Ferrer-i-Cancho (rferrericancho@cs.upc.edu)
 *          LARCA (Laboratory for Relational Algorithmics, Complexity and Learning)
 *          CQL (Complexity and Quantitative Linguistics Lab)
 *          Office S124, Omega building
 *          Jordi Girona St 1-3, Campus Nord UPC, 08034 Barcelona.   CATALONIA, SPAIN
 *          Webpages:
 *              https://cqllab.upc.edu/people/rferrericancho/
 *              https://www.researchgate.net/profile/Ramon_Ferrer-i-Cancho
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
 * This library offers a variety of algorithms related to linear arrangements of graphs so as to provide researchers in the field of Quantitative Linguistics with a toolset with which they can perform statistical analyses on different corpora of treebanks efficiently and effectively. Therefore, this library implements several state-of-the-art algorithms and offers a variety of functionalities. While most of the functions have been generalised to be applicable to general graphs, we also provide specialised functions for trees, which are more efficient than their more general counterparts.
 * 
 * The main goal of this library is to provide algorithms with which the library's users can use to do statistical studies. One of the most attractive features offered in this library is that of treebank collection processing. This library offers a class that automatically processes a collection and computes several metrics based on the capabilities of the library. See class @ref lal::io::treebank_collection_processor and @ref lal::io::treebank_processor for details. We also provide classes for custom processing of treebanks (see @ref lal::io::treebank_collection_reader and @ref lal::io::treebank_reader).
 * 
 * All the features of syntactic dependency trees that can be calculated with the algorithms in this library are gathered in the namespaces @ref lal::linarr and in @ref lal::properties. These features include, but are not limited to,
 * - the sum of edge lengths \f$D\f$ (see @ref lal::linarr::sum_edge_lengths), and the expectation and variance of the sum of edge lengths (see @ref lal::properties::exp_sum_edge_lengths and lal::properties::var_sum_edge_lengths),
 * - the computation of optimal arrangements: unconstrained minimum arrangements with respect to the sum of edge lengths (see @ref lal::linarr::min_sum_edge_lengths), with free choice on the algorithm to be used (see @ref lal::linarr::algorithms_Dmin), and the computation of minimum planar arrangements (see @ref lal::linarr::min_sum_edge_lengths_planar) and of minimum projective arrangements (see @ref lal::linarr::min_sum_edge_lengths_projective).
 * - the number of crossings (see @ref lal::linarr::num_crossings), and the expectation and variance of the number of crossings (see @ref lal::properties::exp_num_crossings and lal::properties::var_num_crossings),
 * - any moment of the degree of the vertices of a graph (see @ref lal::properties::moment_degree and its variants),
 * - the mean dependency distance (see @ref lal::linarr::mean_dependency_distance),
 * - the mean dependency distance over ensembles of graphs (see @ref lal::linarr::mean_dependency_distance_1level and @ref lal::linarr::mean_dependency_distance_2level),
 * - the mean hierarchical distance (see @ref lal::properties::mean_hierarchical_distance),
 * - the headedness of a tree (see @ref lal::linarr::head_initial),
 * - the type of syntactic dependency trees according to their projectivity (see @ref lal::linarr::syntactic_dependency_structure_class).
 * - calculation of the centre of a tree (see @ref lal::properties::tree_centre), the centroid of a tree (see @ref lal::properties::tree_centroid), a tree's diameter (see @ref lal::properties::tree_diameter).
 * 
 * As extra features, useful for experimentation, are the generation of different types of trees, all of which are available in the @ref lal::generate namespace. We have implemented existing techniques (cited accordingly) or made or own to enumerate
 * - all labelled/unlabelled free trees,
 * - all labelled/unlabelled rooted trees,
 * - all projective arrangements of rooted trees,
 * 
 * and to generate uniformly at random
 * - labelled/unlabelled free/rooted trees,
 * - projective arrangements of rooted trees.
 * 
 * The documentation of each class includes usage examples.
 * 
 * This library implements several types of graphs that can be found in the @ref lal::graphs namespace.
 * 
 * \section s1 The basic data structures in this library
 * 
 * In order to be able to use the library comfortably, its users must take good note of the different data structures that are the library's core.
 * 
 * With LAL, most metrics can be calculated as exact rational numbers (see @ref lal::numeric::rational), but also as floating point values of double precision. For the former, add the suffix '_rational' at the end of the function name. For example, the function @ref lal::properties::var_num_crossings returns the variance of the number of crossings 'C' as a floating point value. By adding the suffix, i.e., @ref lal::properties::var_num_crossings_rational, we obtain said variance as an exact rational value. To see what a rational value is in the context of this library, see the documentation of the namespace @ref lal::numeric.
 * 
 * \subsection ss1_s1 Exact integer and rational arithmetic
 * 
 * Most operations in this library are done using exact integer and rational arithmetic. Such arithmetic is powered by the GMP library (see \cite GMP_library). We have wrapped their C structures into the classes @ref lal::numeric::integer and @ref lal::numeric::rational.
 * 
 * \subsection ss3_s1 The different types of graphs
 * 
 * As it should be expected, this library offers a number of different graph abstractions: undirected graphs (see @ref lal::graphs::undirected_graph), directed graphs (see @ref lal::graphs::directed_graph), free trees (see @ref lal::graphs::free_tree) and roted trees (see @ref lal::graphs::rooted_tree), all of which can be found within the @ref lal::graphs namespace.
 * 
 * \subsubsection sss1_ss3_s1 The internal structure of graphs
 * 
 * Although all graphs should be regarded as unlabelled, each node carries an implicit labelling. Such labelling has a most trivial nature since each node is labelled with a number between 0 and the total number of vertices minus one.
 * 
 * Due to most graphs being sparse, the data structure of choice are adjacency lists where each vertex has a list of neighbouring nodes, or simply neighbours, associated to it. The user can affect the order of appearance of neighbours in multiple ways. One of them is, evidently, the order in which edges are added. Another way is via the @ref lal::graphs::graph::normalise function, which sorts every list of neighbours increasingly by index. By default, the addition of edges is normalising, namely the following code
 * @code
 * lal::graphs::free_tree t(4);
 * t.add_edge(0,1,false,false).add_edge(0,3,false,false).add_edge(0,2,false,false);
 * t.normalise();
 * cout << t << endl;
 * @endcode
 * produces the same output as
 * @code
 * lal::graphs::free_tree t(4);
 * t.add_edge(0,1).add_edge(0,3).add_edge(0,2);
 * cout << t << endl;
 * @endcode
 * which is
@verbatim
0: 1 2 3
1: 0
2: 0
3: 0
@endverbatim
 * The output is easy to interpret: the first line indicates the nodes are incident to vertex 0, the second line indicates the nodes incident to vertex 1, and so on. Without normalisation (neither the call to @ref lal::graphs::free_tree::normalise, and using 'false' in the optional parameters), the output is
@verbatim
0: 1 3 2
1: 0
2: 0
3: 0
@endverbatim
 * where only the first line changes.
 * 
 * Such normalisation is required by some of the algorithms in this library. Without proper normalisation, the algorithms are not likely to compute correct values. The parameter that governs the graphs' normalisation is called the normalisation parameter.
 * 
 * The adjacency list structure has been extended to directed graphs in a way that the user can query them for in-degree (see @ref lal::graphs::directed_graph::get_in_degree) and in-neighbours (see @ref lal::graphs::directed_graph::get_in_neighbours).
 * 
 * \section s2 Basic terminology and notation
 * 
 * Users will note, after browsing through the library's documentation, that several concepts are quite ubiquitous. The @ref lal::node type is simply a typedef of an unsigned integer type, and the @ref lal::edge type is simply a STL's pair of nodes. Moreover, users need to have a deep understanding of what a head vector is (see @ref lal::head_vector), which is what allows users to easily read trees from files and process a file containing a large collection of trees (see @ref lal::io namespace).
 * 
 * A more advanced concept is that of linear arrangement (see @ref lal::linear_arrangement). In this library, a linear arrangement is viewed as a function that relates each node to a position in a linear sequence. Due to the properties of such functions, a linear arrangement is implemented with the STL's vector. Note that the concept of linear arrangement has been detached from that of trees, and the pair of a linear arrangement and a tree forms, in the context of the library, a syntactic dependency tree (this is why this class is not implemented). The symbol of choice for representing a linear arrangement in the library is the greek letter for the number pi \f$\pi\f$.
 * 
 * Now, many functions (see those fuctions within the @ref lal::linarr namespace) admit a linear arrangement which can be empty. Whenever it is empty, i.e., the value of the parameter is an empty vector, the positions of the nodes of the graphs in question are given by their implicit label. Such empty arrangement is called, in the context of the library, the identity arrangement symbolised with \f$\pi_I\f$. Therefore, the following measurement of the sum of the lengths of the edges are equivalent
 * @code
 * lal::graphs::free_tree t(4);
 * t.add_edges({lal::edge(0,1), lal::edge(1,2), lal::edge(2,3)});
 * uint32_t D1 = lal::linarr::sum_edge_lengths(t);
 * uint32_t D2 = lal::linarr::sum_edge_lengths(t, {0,1,2,3});
 * @endcode
 * The possibility of expliciting a linear arrangement increases the flexibility of the library. For example, for the purposes of illustration, one can calculate the expected sum of the length of the edges as follows
 * @code
 * lal::graphs::free_tree t(4);
 * t.add_edges({lal::edge(0,1), lal::edge(1,2), lal::edge(2,3)});
 * lal::numeric::rational Dt = 0;
 * lal::linearrgmnt arr = {0,1,2,3};
 * do {
 * 		Dt += lal::linarr::sum_edge_lengths(t, arr);
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
 * One the one hand, the wrong choice of operation can affect the library's performance gravely. For example, the addition/deletion of edges to/from graphs is slower when it is done edge by edge than when it is done in bulk. Users are highly encouraged to add/delete them in bulk using the appropriate functions (see, for example, @ref lal::graphs::undirected_graph::add_edges and @ref lal::graphs::undirected_graph::remove_edges). Although correct, the following code is discouraged
 * @code
 * lal::graphs::free_tree t(10);
 * lal::node u, v;
 * for (int i = 0; i < 9; ++i) {
 * 		cin >> u >> v;
 * 		t.add_edge(u,v);
 * }
 * @endcode
 * while the next piece of code is strongly encouraged whenever possible
 * @code
 * lal::graphs::free_tree t(10);
 * vector<lal::edge> e(9);
 * for (int i = 0; i < 9; ++i) {
 * 		cin >> e[i].first >> e[i].second;
 * }
 * t.set_edges(e);
 * @endcode
 * A similar reasoning should be applied to the deletion of edges.
 * 
 * Furthermore, graphs are seldom required to be normalised. For example, when calculating the variance of \f$C\f$ (see @ref lal::properties::var_num_crossings), it is mandatory that the graph be normalised, namely, the function has a precondition that requires the graph to be normalised. If such a function is to be called eventually then add all edges in bulk and with normalisation, or read the graph from disk also with normalisation. However, if such functions will never be called then the users are encouraged to set the normalisation parameter to false. For example, if the variance of \f$C\f$ is to be calculated,
 * @code
 * const string filename = "..."; // a valid name of a file
 * const lal::graphs::free_tree t = *lal::io::read_edge_list(filename);
 * double var_C = lal::properties::var_num_crossings(t);
 * @endcode
 * but if not
 * @code
 * const string filename = "..."; // a valid name of a file
 * const lal::graphs::free_tree t = *lal::io::read_edge_list(filename, false);
 * // ...
 * @endcode
 */

/**
 * @brief Main namespace of the library.
 *
 * This namespace groups all namespaces of the library. Each namespace classifies the classes and functions in categories.
 */
namespace lal {

/**
 * @brief Generation of different classes of objects.
 * 
 * This namespace contains algorithms for the generation of trees and of arrangements.
 *
 * \section gen_trees Generating trees
 *
 * The classes that generate trees have a self-explanatory format:
 *
 * @verbatim
1_2_3_trees
   @endverbatim
 *
 * The numbers are placeholders for the following:
 *
 * - 3: rooted/free -- Generate rooted or free trees.
 *
 * - 2: lab/ulab -- Generate labelled or unlabelled free/rooted trees.
 *
 * - 1: rand/all -- Indicates whether the generation is to be random (rand) or exhaustive (all). An exhaustive generation will enumerate all lab/ulab rooted/free trees whereas random generation generate trees unformly at random.
 *
 * Therefore, the class @ref lal::generate::rand_lab_rooted_trees generates random labelled rooted trees uniformly at random, and the class @ref lal::generate::all_ulab_free_trees should be used to enumerate all unlabelled free trees.
 *
 * All classes for tree generation return trees that are preprocessed. This preprocessing varies depending on whether the tree is rooted or free. The full preprocessing details can be checked in class @ref lal::generate::tree_generator, from which all these classes inherit.
 *
 * Using these classes is straightforward. To generate trees uniformly at random:
 * @code
 *		lal::generate::rand_2_3_trees TreeGen(n);
 *		for (int i = 0; i < 100; ++i) {
 *			const lal::graphs::3_tree T = TreeGen.get_tree();
 *			// ...
 *		}
 * @endcode
 * To enumerate all trees:
 * @code
 *		lal::generate::all_2_3_trees TreeGen(n);
 *		while (TreeGen.has_next()) {
 *			TreeGen.next();
 *			const lal::graphs::3_tree T = TreeGen.get_tree();
 *			// ...
 *		}
 * @endcode
 * (remember to replace the numbers in the actual code!).
 *
 * \remark In this documentation you will find 8 classes for random generation of trees. Users should refrain from using those starting with '__' as the trees returned by these classes are not preprocessed. However, if one wishes to know the implementation details (as for algorithms implemented, and the papers cited), please, read the documentation of said classes.
 *
 * \section gen_arrangements Generating arrangements
 *
 * This namespace contains classes for the generation of arrangements <b>of a given tree</b>. Depending on the type of arrangements, the given tree should be free or rooted accordingly.
 *
 * Again, the names for these classes are also self-explanatory:
 * @verbatim
1_2_arrangement
   @endverbatim
 *
 * The numbers are placeholders for the following:
 *
 * - 2: projective -- Indicates whether the generated arrangements should be
 * projective.
 *
 * - 1: rand/all -- As before, this indicates whether the generation is to be random (rand) or exhaustive (all). An exhaustive generation will enumerate all arrangements
 *
 * Therefore, the class @ref lal::generate::rand_projective_arrangements generates random projective arrangements of a tree, and the class @ref lal::generate::all_projective_arrangements should be used to enumerate all projective arrangements of a tree.
 *
 * Using these classes is straightforward. To generate trees uniformly at random:
 * @code
 *		// given a tree T (of the appropriate type -- indicated with the '2')
 *		lal::generate::rand_2_arrangements ArrGen(T);
 *		for (int i = 0; i < 100; ++i) {
 *			const lal::linear_arrangement arr = ArrGen.make_rand_arrgmnt();
 *			// ...
 *		}
 * @endcode
 * To enumerate all arrangements:
 * @code
 *		// given a tree T (of the appropriate type -- indicated with the '2')
 *		lal::generate::all_2_arrangements ArrGen(T);
 *		while (ArrGen.has_next()) {
 *			ArrGen.next();
 *			const lal::linearrgmnt arr = ArrGen.get_arrangement();
 *			// ...
 *		}
 * @endcode
 * (remember to replace the numbers in the actual code!).
 *
 * \remark In all cases, the arrangements generated are considered to be labelled, i.e., there are no symmetries taken into account when it comes to enumerating or generating uniformly at random said arrangements. For example, for any \f$n\f$-vertex star tree, the class @ref lal::generate::all_projective_arrangements will enumerate \f$n!\f$ arrangements.
 */
namespace generate {}

/**
 * @brief Namespace for the graphs data structures.
 * 
 * This namespace contains the data structures that implement graphs. Note that, although we do not support labelled graphs, the nodes of these graphs carry a label, a number between \f$0\f$ and \f$n-1\f$, where \f$n\f$ is the number of nodes of the graph.
 * 
 * The functions (in other namespaces) that return a @ref lal::node will always use a value greater than or equal to \f$n\f$ to denote that the node index is invalid.
 */
namespace graphs {}

/**
 * @brief Input/Output functions and processing of treebanks.
 * 
 * This namespace contains the functions for input/output operations.
 * 
 * The most basic operations read a graph from a file. The formats supported for reading are:
 * - Edge list. See @ref lal::io::read_edge_list functions.
 * - Head vector (see @ref lal::head_vector for details). See @ref lal::io::read_head_vector functions.
 * 
 * Users can also process collection of trees (called treebank files), and collections of treebank files (obviously, a treebank collection). One can process automatically a treebank file (see @ref lal::io::treebank_processor) or a treebank collection (see @ref lal::io::treebank_collection_processor), and iterate through the trees of a treebank file (see @ref lal::io::treebank_reader) and through the treebank files within a treebank collection (see @ref lal::io::treebank_collection_reader).
 * 
 * A treebank file is a file containing only head vectors of trees. Such head vectors may not be formatted correctly (from the standpoint of this library), and so users of the library are also provided with function to check the correctess of such files (see @ref lal::io::check_correctness_treebank and @ref lal::io::check_correctness_treebank_collection). Users are encouraged to read the documentation of these classes to know more about treebank files and collection of treebanks and how to process them with the library.
 */
namespace io {}

/**
 * @brief Iterators namespace.
 * 
 * This namespace contains classes useful for iterating through the graph. These classes iterate
 * - over the set of edges (see @ref lal::iterators::E_iterator).
 * - over the set of pairs of independent edges \f$Q\f$ (see @ref lal::iterators::Q_iterator).
 */
namespace iterators {}

/**
 * @brief Namespace for all linear-arrangement-dependent algorithms.
 * 
 * This namespace contains functions to calculate properties of graphs that depend on a linear arrangement. Said arrangement van be given explicitly, i.e., by constructing a @ref lal::linear_arrangement object, or by omitting it in the functions to let these use the labelling of the graph. For example, given a graph
 * @code
 *		lal::graphs::undirected_graph g;
 * @endcode
 * we can calculate the sum of length of the edges using function @ref lal::linarr::sum_edge_lengths in two different ways. The first is by omitting the arrangement:
 * @code
 *		lal::linarr::sum_edge_lengths(g);
 * @endcode
 * or by giving one explicitly
 * @code
 *		lal::linarr::sum_edge_lengths(g, {...});
 * @endcode
 *
 * A linear arrangement object is a vector whose size is equal to the number of nodes of its corresponding graph. Note, however, that a linear arrangement has no associated graph; it is just a vector. Throughout this namespace we use the symbol for the number pi, \f$\pi\f$ to denote a linear arrangement, as is usually done in the scientific literature.
 *
 * The contents of a @ref lal::linear_arrangement object are as follows: if \f$\pi\f$ is a linear arrangement then the @e u-th position of \f$\pi\f$ contains the position of that node in the arrangement. Formally, \f$\pi[u] = p\f$ if, and only if, node @e u is at position @e p in the linear arrangement.
 *
 * The identity arrangement \f$\pi_I\f$ is a special case of linear arrangement used in many functions. Such an arrangement is one that maps each node into the position corresponding to their label, i.e., \f$ \pi_I(u) = u\f$. When omitting the arrangement in the functions of this namespace, the user should consider that the arrangement used is the identity arrangement.
 */
namespace linarr {}

/**
 * @brief Numeric namespace.
 *
 * This namespace contains the data structures that wrap the basic structures of the GMP library for integers of arbitrary precision (see @ref lal::numeric::integer) and exact rational numbers (see @ref lal::numeric::rational).
 */
namespace numeric {}

/**
 * @brief Namespace for all linear-arrangement-independent algorithms.
 * 
 * This namespace contains functions to calculate properties of graphs that do not depend, whether implicitly or explicitly, on a linear arrangement.
 */
namespace properties {}

/**
 * @brief Set of utilities.
 *
 * This namespace contains several utilities for the library, useful for experimentation. This includes the following functions:
 * - Isomorphism tests. For free trees (see @ref lal::utilities::are_trees_isomorphic(const lal::graphs::free_tree&,const lal::graphs::free_tree&)) and for rooted trees (see @ref lal::utilities::are_trees_isomorphic(const lal::graphs::rooted_tree&,const graphs::rooted_tree&)).
 */
namespace utilities {}

} // -- namespace lal
