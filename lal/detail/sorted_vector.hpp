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
#if defined DEBUG
#include <cassert>
#endif
#include <algorithm>
#include <vector>

namespace lal {
namespace detail {

/**
 * @brief Sorted vector class
 *
 * This class inherits from std::vector to implement a vector-like container
 * whose elements are always sorted lexicographically non-decreasing.
 *
 * @tparam T type of data.
 * @tparam unique Whether or not the elements inserted should be unique.
 */
template<class T, bool unique>
class sorted_vector : public std::vector<T> {
public:
	/// Empty constructor
	sorted_vector() noexcept : std::vector<T>() { }
	/// Constructor with number of elements
	sorted_vector(std::size_t n) noexcept : std::vector<T>(n) { }
	/// Constructor with number of elements and initial element
	sorted_vector(std::size_t n, const T& x) noexcept : std::vector<T>(n, x) { }

	/// Copy constructor
	sorted_vector(const sorted_vector& v) noexcept : std::vector<T>(v) { }
	/// Move constructor
	sorted_vector(sorted_vector&& v) noexcept : std::vector<T>(std::move(v)) { }

	/// Copy-assignment operator
	sorted_vector& operator= (const sorted_vector& v) noexcept { *this = v; }
	/// Move-assignment operator
	sorted_vector& operator= (sorted_vector&& v) noexcept { *this = std::move(v); }

	/// Empty destructor
	~sorted_vector() noexcept { }

	/**
	 * @brief Insert an element to the vector.
	 * @param x Element to be inserted.
	 * @returns An iterator to the inserted element.
	 */
	inline typename std::vector<T>::iterator
	insert_sorted(const T& x) noexcept {
		if constexpr (not unique) {
			const auto it = std::upper_bound(this->begin(), this->end(), x);
			return this->insert(it, x);
		}
		else {
			if (this->size() == 0) {
				this->push_back(x);
				return this->begin();
			}

			const auto it = upper_bound(this->begin(), this->end(), x);
			const auto pre_it = it == this->begin() ? it : it - 1;
			if (*pre_it != x) {
				return this->insert(it, x);
			}
			return it;
		}
	}
	/**
	 * @brief Insert an element to the vector.
	 * @param x Element to be inserted.
	 * @returns An iterator to the inserted element.
	 */
	inline typename std::vector<T>::iterator
	insert_sorted(T&& x) noexcept {
		if constexpr (not unique) {
			const auto it = std::upper_bound(this->begin(), this->end(), x);
			return this->insert(it, std::move(x));
		}
		else {
			if (this->size() == 0) {
				this->push_back(std::move(x));
				return this->begin();
			}

			const auto it = std::upper_bound(this->begin(), this->end(), x);
			const auto pre_it = it == this->begin() ? it : it - 1;
			if (*pre_it != x) {
				return this->insert(it, std::move(x));
			}
			return it;
		}
	}

	/**
	 * @brief Remove an element from the vector.
	 * @param x Element to be removed.
	 * @returns An iterator to the previous element in the original vector.
	 */
	inline typename std::vector<T>::iterator
	remove_sorted(const T& x) noexcept {
#if defined DEBUG
		assert(contains(x));
#endif
		const auto i1 = std::lower_bound(this->begin(), this->end(), x);
		return this->erase(i1);
	}

	/**
	 * @brief Query whether an element is in the vector or not.
	 *
	 * Has the same complexity as std::binary_search.
	 * @param x The element to look for.
	 * @returns True or false telling if the element is in the vector or not.
	 */
	inline bool contains(const T& x) const noexcept {
		return std::binary_search(this->begin(), this->end(), x);
	}

	/**
	 * @brief Find the position of an element in the vector.
	 * @param x The element to be searched.
	 * @returns An iterator to the element, or std::vector::end() if it does not
	 * exist.
	 */
	inline typename std::vector<T>::iterator
	find_sorted(const T& x) noexcept {
		const auto i = std::lower_bound(this->begin(), this->end(), x);
		if (i == this->end()) { return this->end(); }

		if (*i == x) { return i; }
		return this->end();
	}
};

} // -- namespace detail
} // -- namespace lal
