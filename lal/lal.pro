TEMPLATE = lib

VERSION_MAJOR = 99.99
VERSION_BUILD = 99
VERSION = $${VERSION_MAJOR}.$${VERSION_BUILD}

CONFIG -= app_bundle
QT	 -= core gui

CONFIG(release, debug|release) {
TARGET = lal
}
CONFIG(debug, debug|release) {
TARGET = laldebug
}

QMAKE_CXXFLAGS += -std=c++17 -fPIC -fopenmp
QMAKE_CXXFLAGS_DEBUG += -O3 -DDEBUG -D_GLIBCXX_DEBUG
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3 -UDEBUG -DNDEBUG -fstrict-aliasing

# uncomment when doing actual profiling
#QMAKE_CXXFLAGS_RELEASE += -pg
#QMAKE_LFLAGS += -pg

# libraries
LIBS += -lgmp -fopenmp -lpthread

isEmpty(ENVIR) {
	ENVIR = "HOME"
}

# configure home
equals(ENVIR, "HOME") {

}

# configure cluster
equals(ENVIR, "CLUSTER") {
	QMAKE_CXX = /home/soft/gcc-11.2.0/bin/g++
	QMAKE_LINK = /home/soft/gcc-11.2.0/bin/g++
}

QMAKE_CXXFLAGS +=			\
	-Wall					\
	-Wextra					\ # reasonable and standard
	-Wshadow				\ # warn if a variable declaration shadows one from
							\ # a parent context
	-Wnon-virtual-dtor		\ # warn if a class with virtual functions has
							\ # non-virtual destructors
	-Wold-style-cast		\ # warn for c-style casts
	-Wcast-align			\ # warn for potential performance problem casts
	-Wunused				\ # warn on anything being unused
	-Woverloaded-virtual	\ # warn if a virtual is overloaded (not overridden)
	-Wpedantic				\ # warn if non-standard C++ is used
	-Wconversion			\ # warn on type conversions that may lose data
	-Wsign-conversion		\ # warn on sign conversions
	-Wnull-dereference		\ # warn if a null dereference is detected
	-Wdouble-promotion		\ # warn if float is implicitly promoted to double
	-Wformat=2				\ # warn on security issues around functions that
							\ # format output
	-Wduplicated-cond		\ # warn if if-then-else chan has duplicated conditions
	-Wduplicated-branches	\ # warn if if-then-else have duplicated code
	-Wlogical-op			\ # warn about logical operations being used where
							\ # bitwise were probably prefered
	-Wuseless-cast			\ # warn if you perform a cast to the same type
	-Wrestrict

INCLUDEPATH += ..

# -------------
# PROJECT FILES
HEADERS += \
    basic_types.hpp \
    detail/data_array.hpp \
	detail/avl.hpp \
    detail/macros/integer_convert.hpp \
	detail/make_array.hpp \
	detail/graphs/conversions.hpp \
	detail/graphs/enumerate_sets.hpp \
	detail/graphs/is_tree.hpp \
	detail/graphs/make_arrangement.hpp \
	detail/graphs/retrieve_subtrees.hpp \
	detail/graphs/size_subtrees.hpp \
	detail/graphs/tree_classification.hpp \
	detail/graphs/tree_type.hpp \
	detail/io/check_correctness.hpp \
	detail/linarr/C_brute_force.hpp \
	detail/linarr/C_dyn_prog.hpp \
	detail/linarr/C_ladder.hpp \
	detail/linarr/Dmin_Planar_AEF.hpp \
	detail/linarr/Dmin_Planar_HS.hpp \
	detail/linarr/Dmin_Projective_AEF.hpp \
	detail/linarr/Dmin_Projective_HS.hpp \
	detail/linarr/Dmin_utils.hpp \
	detail/linarr/algorithms_crossings.hpp \
	detail/linarr/C_stack_based.hpp \
	detail/linarr/Dmin_Unconstrained_FC.hpp \
	detail/linarr/Dmin_Unconstrained_YS.hpp \
	detail/linarr/syntactic_dependency_structure.hpp \
	detail/numeric/utils.hpp \
    detail/macros/call_with_empty_arr.hpp \
    detail/macros/is_pointer_iterator.hpp \
    detail/pairs_utils.hpp \
	detail/properties/tree_centre.hpp \
	detail/properties/tree_centroid.hpp \
	detail/properties/tree_diameter.hpp \
	detail/sorted_vector.hpp \
	detail/sorting/bit_sort.hpp \
	detail/sorting/counting_sort.hpp \
	detail/sorting/insertion_sort.hpp \
	detail/graphs/union_find.hpp \
	detail/graphs/utils.hpp \
	detail/graphs/cycles.hpp \
	detail/graphs/reachability.hpp \
	detail/graphs/traversal.hpp \
	detail/utilities/tree_isomorphism.hpp \
	generate.hpp \
	generate/all_arrangements.hpp \
	generate/all_lab_free_trees.hpp \
	generate/all_planar_arrangements.hpp \
	generate/all_ulab_free_trees.hpp \
	generate/all_ulab_rooted_trees.hpp \
	generate/all_lab_rooted_trees.hpp \
	generate/all_projective_arrangements.hpp \
	generate/rand_arrangements.hpp \
	generate/rand_lab_free_trees.hpp \
	generate/rand_lab_rooted_trees.hpp \
	generate/rand_planar_arrangements.hpp \
	generate/rand_ulab_free_trees.hpp \
	generate/rand_ulab_rooted_trees.hpp \
	generate/rand_projective_arrangements.hpp \
	generate/tree_generator.hpp \
	generate/tree_generator_type.hpp \
	graphs.hpp \
	graphs/conversions.hpp \
	graphs/graph.hpp \
	graphs/output.hpp \
	graphs/tree.hpp \
	graphs/directed_graph.hpp \
	graphs/free_tree.hpp \
	graphs/rooted_tree.hpp \
	graphs/tree_type.hpp \
	graphs/undirected_graph.hpp \
	io/check_correctness.hpp \
	io/edge_list.hpp \
	io.hpp \
	io/basic_output.hpp \
	io/head_vector.hpp \
	io/process_treebank_base.hpp \
	io/report_correctness.hpp \
	io/treebank_collection_processor.hpp \
	io/treebank_collection_reader.hpp \
	io/treebank_error.hpp \
	io/treebank_error_type.hpp \
	io/treebank_processor.hpp \
	io/treebank_reader.hpp \
	io/treebank_feature.hpp \
	iterators.hpp \
	iterators/E_iterator.hpp \
	iterators/Q_iterator.hpp \
	linarr.hpp \
	C.hpp \
	D.hpp \
	linarr/Dmin.hpp \
	linarr/algorithms_C.hpp \
	linarr/algorithms_Dmin.hpp \
	linarr/1level.hpp \
	linarr/2level.hpp \
	linarr/algorithms_Dmin_planar.hpp \
	linarr/algorithms_Dmin_projective.hpp \
	linarr/classify_syntactic_dependency_structure.hpp \
	linarr/dependency_flux.hpp \
	linarr/flux.hpp \
	linarr/C.hpp \
	linarr/D.hpp \
	linarr/formal_constraints.hpp \
	linarr/head_initial.hpp \
	linarr/syntactic_dependency_structure.hpp \
    linear_arrangement.hpp \
	numeric.hpp \
	numeric/integer.hpp \
	numeric/integer_output.hpp \
	numeric/output.hpp \
	numeric/rational.hpp \
	numeric/rational_output.hpp \
	properties.hpp \
	properties/Q.hpp \
	properties/D_rla.hpp \
	properties/C_rla.hpp \
	properties/degrees.hpp \
    properties/hierarchical_distance.hpp \
	properties/tree_centre.hpp \
	properties/tree_centroid.hpp \
	properties/tree_diameter.hpp \
	utilities.hpp \
	utilities/tree_isomorphism.hpp \
	lal_version.hpp

SOURCES += \
	generate/all_lab_free_trees.cpp \
	generate/all_planar_arrangements.cpp \
	generate/all_projective_arrangements.cpp \
	generate/all_ulab_free_trees.cpp \
	generate/all_ulab_rooted_trees.cpp \
	generate/rand_lab_free_trees.cpp \
	generate/rand_planar_arrangements.cpp \
	generate/rand_projective_arrangements.cpp \
	generate/rand_ulab_free_trees.cpp \
	generate/rand_ulab_rooted_trees.cpp \
	graphs/conversions.cpp \
	graphs/directed_graph.cpp \
	graphs/free_tree.cpp \
	graphs/graph.cpp \
	graphs/rooted_tree.cpp \
	graphs/tree.cpp \
	graphs/undirected_graph.cpp \
	io/check_correctness.cpp \
	io/edge_list.cpp \
	io/head_vector.cpp \
	io/treebank_collection_processor.cpp \
	io/treebank_collection_reader.cpp \
	io/treebank_processor.cpp \
	io/treebank_reader.cpp \
	linarr/C.cpp \
	linarr/Dmin.cpp \
	linarr/classify_syntactic_dependency_structure.cpp \
	linarr/flux.cpp \
	linarr/D.cpp \
	linarr/head_initial.cpp \
	linarr/predicted_C.cpp \
	numeric/integer.cpp \
	numeric/rational.cpp \
	properties/Q.cpp \
	properties/hierarchical_distance.cpp \
	properties/tree_centre.cpp \
	properties/tree_centroid.cpp \
	properties/tree_diameter.cpp \
	properties/variance_C_gen_graphs.cpp \
	properties/variance_C_forests.cpp \
	properties/D_rla.cpp \
	properties/C_rla.cpp \
	utilities/tree_isomorphism.cpp
