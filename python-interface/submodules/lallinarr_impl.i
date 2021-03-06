
%include documentation.i

%{
#include <lal/graphs.hpp>
#include <lal/linarr.hpp>
%}

%include "../lal/linarr/1level.hpp"
%include "../lal/linarr/2level.hpp"
%include "../lal/linarr/C.hpp"
%include "../lal/linarr/D.hpp"
%include "../lal/linarr/Dmin.hpp"
%include "../lal/linarr/headedness.hpp"

%include "../lal/linarr/dependency_flux.hpp"
namespace std {
	%template(__list_dependency_flux) vector<lal::linarr::dependency_flux>;
}
%include "../lal/linarr/flux.hpp"

namespace std {
	%template(__array_of_bools_tree_structure_type) array<bool, lal::linarr::__tree_structure_type_size>;
}
%include "../lal/linarr/classify_syntactic_dependency_structure.hpp"

// --------------------------------
// Extendind the function templates

%template(__MDD_1level_rational_undirected_graph)	lal::linarr::mean_dependency_distance_1level_rational<lal::graphs::undirected_graph>;
%template(__MDD_1level_rational_directed_graph)		lal::linarr::mean_dependency_distance_1level_rational<lal::graphs::directed_graph>;
%template(__MDD_1level_rational_free_tree)			lal::linarr::mean_dependency_distance_1level_rational<lal::graphs::free_tree>;
%template(__MDD_1level_rational_rooted_tree)		lal::linarr::mean_dependency_distance_1level_rational<lal::graphs::rooted_tree>;

%template(__MDD_1level_undirected_graph)			lal::linarr::mean_dependency_distance_1level<lal::graphs::undirected_graph>;
%template(__MDD_1level_directed_graph)				lal::linarr::mean_dependency_distance_1level<lal::graphs::directed_graph>;
%template(__MDD_1level_free_tree)					lal::linarr::mean_dependency_distance_1level<lal::graphs::free_tree>;
%template(__MDD_1level_rooted_tree)					lal::linarr::mean_dependency_distance_1level<lal::graphs::rooted_tree>;

%template(__MDD_2level_rational_undirected_graph)	lal::linarr::mean_dependency_distance_2level_rational<lal::graphs::undirected_graph>;
%template(__MDD_2level_rational_directed_graph)		lal::linarr::mean_dependency_distance_2level_rational<lal::graphs::directed_graph>;
%template(__MDD_2level_rational_free_tree)			lal::linarr::mean_dependency_distance_2level_rational<lal::graphs::free_tree>;
%template(__MDD_2level_rational_rooted_tree)		lal::linarr::mean_dependency_distance_2level_rational<lal::graphs::rooted_tree>;

%template(__MDD_2level_undirected_graph)			lal::linarr::mean_dependency_distance_2level<lal::graphs::undirected_graph>;
%template(__MDD_2level_directed_graph)				lal::linarr::mean_dependency_distance_2level<lal::graphs::directed_graph>;
%template(__MDD_2level_free_tree)					lal::linarr::mean_dependency_distance_2level<lal::graphs::free_tree>;
%template(__MDD_2level_rooted_tree)					lal::linarr::mean_dependency_distance_2level<lal::graphs::rooted_tree>;

%pythoncode %{
def mean_dependency_distance_1level_rational(L, P):
	r"""
	1-level mean dependency distance of a list of graphs `L`.
	
	Given a list of graphs :math:`L` and a list of linear arrangements for each of them, :math:`P`, computes the 1-level Mean Dependency Distance as the quotient of :math:`D`, the sum of all the edge lengths of each graph, and of :math:`M` the sum of the number of edges of all the graphs.

	Formally, given a list of linear arrangements :math:`\P = \{\pi_i\}_{i=1}^k` and a list of graphs :math:`L = \{L_i\}_{i=1}^k`, computes :math:`D/M`, where
	
	- :math:`D = \sum_{i=1}^k D(L_i, \pi_i)` is the sum of edge lengths of all graphs.
	- :math:`M = \sum_{i=1}^k |E(L_i)|` is the sum of the number of edges of all graphs.
	
	Parameters
	----------
	* `L` :
		List of input graphs.
	* `P` :
		List of linear arrangements of the nodes :math:`P = \{\pi_i\}_{i=1}^k`. When omitted, :math:`\pi_I` is used for every graph.
	
	Returns
	-------
	Jing's and Liu's 1-level :math:`MDD` for an ensemble of graphs as an exact rational value.
	"""
	__type_graph = str(type(L[0]))[len("<class 'lalgraphs."):-2]
	return globals()[ "__MDD_1level_rational_" + __type_graph ](L, P)

def mean_dependency_distance_1level(L, P):
	r"""
	1-level mean dependency distance of a list of graphs `L`.
	
	Given a list of graphs :math:`L` and a list of linear arrangements for each of them, :math:`P`, computes the 1-level Mean Dependency Distance as the quotient of :math:`D`, the sum of all the edge lengths of each graph, and of :math:`M` the sum of the number of edges of all the graphs.

	Formally, given a list of linear arrangements :math:`\P = \{\pi_i\}_{i=1}^k` and a list of graphs :math:`L = \{L_i\}_{i=1}^k`, computes :math:`D/M`, where
	
	- :math:`D = \sum_{i=1}^k D(L_i, \pi_i)` is the sum of edge lengths of all graphs.
	- :math:`M = \sum_{i=1}^k |E(L_i)|` is the sum of the number of edges of all graphs.
	
	Parameters
	----------
	* `L` :
		List of input graphs.
	* `P` :
		List of linear arrangements of the nodes :math:`P = \{\pi_i\}_{i=1}^k`. When omitted, :math:`\pi_I` is used for every graph.
	
	Returns
	-------
	Jing's and Liu's 1-level :math:`MDD` for an ensemble of graphs as a floating point value.
	"""
	__type_graph = str(type(L[0]))[len("<class 'lalgraphs."):-2]
	return globals()[ "__MDD_1level_" + __type_graph ](L, P)

def mean_dependency_distance_2level_rational(L, P):
	r"""
	2-level Mean Dependency Distance :math:`MDD` over an ensemble of graphs.
	
	Given a list of graphs :math:`L` and a list of linear arrangements of the nodes for each of them, :math:`P`, computes the 2-level Mean Dependency Distance, i.e., it computes the average Mean Dependency Distance of the graphs in the list.

	Formally, given a list of graphs :math:`L = \{L_i\}_{i=1}^k` and a list of linear arrangements :math:`P = \{\pi_i\}_{i=1}^k`, computes :math:`(1/k)S_{<d>}`, where :math:`S_{<d>} = \sum_{i=1}^k MDD(L_i, \pi_i)` is the sum of the mean dependency distances of every graph (see ``mean_dependency_distance_rational`` for details on the definition of the Mean Dependency Distance).
	
	Parameters
	----------
	* `L` :
		List of input graphs.
	* `P` :
		List of linear arrangements of the nodes :math:`P = \{\pi_i\}_{i=1}^k`. When omitted, :math:`\pi_I` is used for every graph.

	Returns
	-------
	Jing's and Liu's 2-level :math:`MDD` for an ensemble of graphs as an exact rational value.
	"""
	__type_graph = str(type(L[0]))[len("<class 'lalgraphs."):-2]
	return globals()[ "__MDD_2level_rational_" + __type_graph ](L, P)

def mean_dependency_distance_2level(L, P):
	r"""
	2-level Mean Dependency Distance :math:`MDD` over an ensemble of graphs.
	
	Given a list of graphs :math:`L` and a list of linear arrangements of the nodes for each of them, :math:`P`, computes the 2-level Mean Dependency Distance, i.e., it computes the average Mean Dependency Distance of the graphs in the list.

	Formally, given a list of graphs :math:`L = \{L_i\}_{i=1}^k` and a list of linear arrangements :math:`P = \{\pi_i\}_{i=1}^k`, computes :math:`(1/k)S_{<d>}`, where :math:`S_{<d>} = \sum_{i=1}^k MDD(L_i, \pi_i)` is the sum of the mean dependency distances of every graph (see ``mean_dependency_distance_rational`` for details on the definition of the Mean Dependency Distance).
	
	Parameters
	----------
	* `L` :
		List of input graphs.
	* `P` :
		List of linear arrangements of the nodes :math:`P = \{\pi_i\}_{i=1}^k`. When omitted, :math:`\pi_I` is used for every graph.

	Returns
	-------
	Jing's and Liu's 2-level :math:`MDD` for an ensemble of graphs as a floating point value.
	"""
	__type_graph = str(type(L[0]))[len("<class 'lalgraphs."):-2]
	return globals()[ "__MDD_2level_" + __type_graph ](L, P)
%}
