/*********************************************************************
 *
 *  Linear Arrangement Library - A library that implements a collection
 *  algorithms for linear arrangments of graphs.
 *
 *  Copyright (C) 2019
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
 
#include <lal/io/treebank_reader.hpp>

// C includes
#include <sys/types.h>
#include <sys/stat.h>

// C++ includes
#include <sstream>
using namespace std;

// lal includes
#include <lal/utils/conversions.hpp>

namespace lal {
using namespace graphs;

namespace io {

// TREEBANK_READER

treebank_reader::treebank_reader() {}
treebank_reader::~treebank_reader() {}

// MODIFIERS

dataset_error treebank_reader::init(const string& file, const string& lang) {
	m_treebank.close();
	m_language = lang;
	m_num_trees = 0;

	m_treebank_file = file;
	m_treebank.open(m_treebank_file.c_str());

	if (not m_treebank.is_open()) {
		return dataset_error::no_treebank_file;
	}
	return dataset_error::no_error;
}

bool treebank_reader::has_tree() const {
	return not m_treebank.eof();
}

dataset_error treebank_reader::next_tree() {
	getline(m_treebank, m_file_line);
	if (m_file_line.length() == 1) {
		// line is probably empty...
		if (not ('0' <= m_file_line[0] and m_file_line[0] <= '9')) {
			// line is certainly empty
			return dataset_error::empty_line;
		}
	}

	++m_num_trees;

	// this peek is needed so that treebank.eof()
	// returns true when it has to.
	m_treebank.peek();

	return dataset_error::no_error;
}

// GETTERS

size_t treebank_reader::get_num_trees() const {
	return m_num_trees;
}

const string& treebank_reader::what_language() const {
	return m_language;
}

const string& treebank_reader::get_treebank_filename() const {
	return m_treebank_file;
}

ugraph treebank_reader::get_tree() const {
	// parse tree in line
	stringstream ss(m_file_line);

	// parent of each node
	vector<node> L;
	// add a dummy value so that conversion
	// code can be made more readable
	L.push_back(0);
	node k;
	while (ss >> k) {
		L.push_back(k);
	}

	uint32_t n = static_cast<uint32_t>(L.size()) - 1;
	return utils::linear_sequence_to_tree(L, n);
}

} // -- namespace io
} // -- namespace lal
