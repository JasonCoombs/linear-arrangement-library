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

// C includes
#include <gmp.h>

// C++ includes
#include <cstdint>
#include <string>

// lal includes
#include <lal/numeric/integer.hpp>

namespace lal {
namespace numeric {

/**
 * @brief Exact rational number.
 *
 * This class wraps the @e mpq_t data structure from GMP with operators for an
 * easy usage.
 */
class rational {
public:
	/* CONSTRUCTORS */

	/// Empty constructor.
	rational() noexcept { mpq_init(m_val); }
	/**
	 * @brief Constructor with numerator and denominator.
	 * @param n Numerator, signed integer (basic type).
	 * @param d Denominator, unsigned integer (basic type).
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	rational(T n, uint64_t d = 1) noexcept
	{ mpq_init(m_val); set_number(n, d); }
	/**
	 * @brief Constructor with numerator and denominator.
	 * @param n Numerator, a @ref lal::numeric::integer.
	 * @param d Denominator, a @ref lal::numeric::integer.
	 */
	rational(const integer& n, const integer& d = 1) noexcept
	{ mpq_init(m_val); set_integer(n, d); }
	/**
	 * @brief Constructor with string.
	 * @param s A string.
	 */
	rational(const std::string& s) noexcept
	{ mpq_init(m_val); set_str(s); }
	/**
	 * @brief Copy constructor.
	 * @param r A @ref lal::numeric::rational.
	 */
	rational(const rational& r) noexcept
	{ mpq_init(m_val); mpq_set(m_val, r.m_val); }
#ifndef SWIG
	/**
	 * @brief Move constructor.
	 * @param v A @ref lal::numeric::integer
	 */
	rational(integer&& v) noexcept;
	/**
	 * @brief Move constructor with numerator and denominator.
	 * @param n Numerator, a @ref lal::numeric::integer.
	 * @param d Denominator, a @ref lal::numeric::integer.
	 */
	rational(integer&& n, integer&& d) noexcept;
	/**
	 * @brief Move constructor.
	 * @param r A @ref lal::numeric::rational.
	 */
	rational(rational&& r) noexcept;
#endif
	/// Destructor.
	~rational() noexcept { mpq_clear(m_val); }

	/* SETTERS */

	/**
	 * @brief Overwrites the value of this rational with \f$n/d\f$.
	 * @param n Numerator, signed integer (basic type).
	 * @param d Denominator, unsigned integer (basic type).
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline void set_number(T n, uint64_t d = 1) noexcept {
		if (not is_initialized()) { mpq_init(m_val); }
		if constexpr (std::is_signed_v<T>) { mpq_set_si(m_val, n, d); }
		else { mpq_set_ui(m_val, n, d); }
		mpq_canonicalize(m_val);
		m_initialized = true;
	}
	/**
	 * @brief Overwrites the value in the string @e s.
	 * @param s A string.
	 */
	inline void set_str(const std::string& s) noexcept {
		if (not is_initialized()) { mpq_init(m_val); }
		mpq_set_str(m_val, s.c_str(), 10);
		mpq_canonicalize(m_val);
		m_initialized = true;
	}
	/**
	 * @brief Overwrites the value of this rational with the value \f$n/d\f$.
	 * @param n Numerator, a @ref lal::numeric::integer.
	 * @param d Denominator, a @ref lal::numeric::integer.
	 */
	inline void set_integer(const integer& n, const integer& d) noexcept {
		if (not is_initialized()) { mpq_init(m_val); }
		mpq_set_num(m_val, n.get_raw_value());
		mpq_set_den(m_val, d.get_raw_value());
		mpq_canonicalize(m_val);
		m_initialized = true;
	}
	/**
	 * @brief Overwrites the value of this rational with the value \f$n/d\f$.
	 * @param r A lal::numeric::rational.
	 */
	inline void set_rational(const rational& r) noexcept {
		if (not is_initialized()) { mpq_init(m_val); }
		mpq_set(m_val, r.m_val);
	}

	/**
	 * @brief Changes numerator and denominator.
	 *
	 * If this rational value was \f$n/d\f$ then after calling this
	 * method it will be \f$d/n\f$.
	 */
	inline void invert() noexcept { mpq_inv(m_val, m_val); }

	/* OPERATORS */

	// -- ASSIGNMENT

	/**
	 * @brief Assignment operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline rational& operator= (T i) noexcept
	{ set_number(i); return *this; }
	/**
	 * @brief Assignment operator.
	 * @param s A string.
	 */
	inline rational& operator= (const std::string& s) noexcept
	{ set_str(s); return *this; }
	/**
	 * @brief Assignment operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline rational& operator= (const integer& i) noexcept
	{ set_integer(i, 1); return *this; }
	/**
	 * @brief Assignment operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline rational& operator= (const rational& r) noexcept
	{ set_rational(r); return *this; }
#ifndef SWIG
	/**
	 * @brief Move assignment operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	rational& operator= (integer&& i) noexcept;
	/**
	 * @brief Move assignment operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	rational& operator= (rational&& r) noexcept;
#endif

	// -- EQUALITY

	/**
	 * @brief Equality operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline bool operator== (T i) const noexcept {
		if constexpr (std::is_signed_v<T>) {
			return mpq_cmp_si(m_val, i, 1) == 0;
		}
		else {
			return mpq_cmp_ui(m_val, i, 1) == 0;
		}
	}
#ifndef SWIG
	/**
	 * @brief Equality operator.
	 * @param i An integer (basic type) number.
	 * @param r A @ref lal::numeric::rational.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline friend bool operator== (T i, const rational& r) noexcept
	{ return r == i; }
#endif
	/**
	 * @brief Equality operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline bool operator== (const integer& i) const noexcept
	{ rational r(i); return mpq_equal(m_val, r.m_val); }
#ifndef SWIG
	/**
	 * @brief Equality operator.
	 * @param i A @ref lal::numeric::integer.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline friend bool operator== (const integer& i, const rational& r) noexcept
	{ return r == i; }
#endif
	/**
	 * @brief Equality operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline bool operator== (const rational& r) const noexcept {
		// this function returns non-zero if parameters are equal!
		return mpq_equal(m_val, r.m_val);
	}

	// -- NON-EQUALITY

	/**
	 * @brief Non-equality operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline bool operator!= (T i) const noexcept
	{ return not (*this == i); }
#ifndef SWIG
	/**
	 * @brief Non-equality operator.
	 * @param i An integer (basic type) number.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline friend bool operator!= (int64_t i, const rational& r) noexcept
	{ return r != i; }
#endif
	/**
	 * @brief Non-equality operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline bool operator!= (const integer& i) const noexcept
	{ return not (*this == i); }
#ifndef SWIG
	/**
	 * @brief Non-equality operator.
	 * @param i A @ref lal::numeric::integer.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline friend bool operator!= (const integer& i, const rational& r) noexcept
	{ return r != i; }
#endif
	/**
	 * @brief Non-equality operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline bool operator!= (const rational& r) const noexcept
	{ return not (*this == r); }

	// -- LESS THAN

	/**
	 * @brief Less than operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline bool operator< (T i) const noexcept {
		if constexpr (std::is_signed_v<T>) {
			return mpq_cmp_si(m_val, i, 1) < 0;
		}
		else {
			return mpq_cmp_ui(m_val, i, 1) < 0;
		}
	}
#ifndef SWIG
	/**
	 * @brief Less than operator.
	 * @param i An integer (basic type) number.
	 * @param r A @ref lal::numeric::rational.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline friend bool operator< (T i, const rational& r) noexcept
	{ return r > i; }
#endif
	/**
	 * @brief Less than operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline bool operator< (const integer& i) const noexcept
	{ rational r(i); return mpq_cmp(m_val, r.m_val) < 0; }
#ifndef SWIG
	/**
	 * @brief Less than operator.
	 * @param i A @ref lal::numeric::integer.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline friend bool operator< (const integer& i, const rational& r) noexcept
	{ return r > i; }
#endif
	/**
	 * @brief Less than operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline bool operator< (const rational& r) const noexcept
	{ return mpq_cmp(m_val, r.m_val) < 0; }

	// -- LESS THAN OR EQUAL TO

	/**
	 * @brief Less than or equal to operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline bool operator<= (T i) const noexcept {
		if constexpr (std::is_signed_v<T>) {
			return mpq_cmp_si(m_val, i, 1) <= 0;
		}
		else {
			return mpq_cmp_ui(m_val, i, 1) <= 0;
		}
	}
#ifndef SWIG
	/**
	 * @brief Less than or equal to operator.
	 * @param i An integer (basic type) number.
	 * @param r A @ref lal::numeric::rational.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline friend bool operator<= (T i, const rational& r) noexcept
	{ return r >= i; }
#endif
	/**
	 * @brief Less than or equal to operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline bool operator<= (const integer& i) const noexcept
	{ rational r(i); return mpq_cmp(m_val, r.m_val) <= 0; }
#ifndef SWIG
	/**
	 * @brief Less than or equal to operator.
	 * @param i A @ref lal::numeric::integer.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline friend bool operator<= (const integer& i, const rational& r) noexcept
	{ return r >= i; }
#endif
	/**
	 * @brief Less than or equal to operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline bool operator<= (const rational& r) const noexcept
	{ return mpq_cmp(m_val, r.m_val) <= 0; }

	// -- GREATER THAN

	/**
	 * @brief Greater than operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline bool operator> (T i) const noexcept {
		if constexpr (std::is_signed_v<T>) {
			return mpq_cmp_si(m_val, i, 1) > 0;
		}
		else {
			return mpq_cmp_ui(m_val, i, 1) > 0;
		}
	}
#ifndef SWIG
	/**
	 * @brief Greater than operator.
	 * @param i An integer (basic type) number.
	 * @param r A @ref lal::numeric::rational.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline friend bool operator> (T i, const rational& r) noexcept
	{ return r < i; }
#endif
	/**
	 * @brief Greater than operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline bool operator> (const integer& i) const noexcept
	{ rational r(i); return mpq_cmp(m_val, r.m_val) > 0; }
#ifndef SWIG
	/**
	 * @brief Greater than operator.
	 * @param i A @ref lal::numeric::integer.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline friend bool operator> (const integer& i, const rational& r) noexcept
	{ return r < i; }
#endif
	/**
	 * @brief Greater than operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline bool operator> (const rational& r) const noexcept
	{ return mpq_cmp(m_val, r.m_val) > 0; }

	// -- GREATER THAN OR EQUAL TO

	/**
	 * @brief Greater than or equal to operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline bool operator>= (T i) const noexcept {
		if constexpr (std::is_signed_v<T>) {
			return mpq_cmp_si(m_val, i, 1) >= 0;
		}
		else {
			return mpq_cmp_ui(m_val, i, 1) >= 0;
		}
	}
#ifndef SWIG
	/**
	 * @brief Greater than or equal to operator.
	 * @param i An integer (basic type) number.
	 * @param r A @ref lal::numeric::rational.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline friend bool operator>= (T i, const rational& r) noexcept
	{ return r <= i; }
#endif
	/**
	 * @brief Greater than or equal to operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline bool operator>= (const integer& i) const noexcept
	{ rational r(i); return mpq_cmp(m_val, r.m_val) >= 0; }
#ifndef SWIG
	/**
	 * @brief Greater than or equal to operator.
	 * @param i A @ref lal::numeric::integer.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline friend bool operator>= (const integer& i, const rational& r) noexcept
	{ return r <= i; }
#endif
	/**
	 * @brief Greater than or equal to operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline bool operator>= (const rational& r) const noexcept
	{ return mpq_cmp(m_val, r.m_val) >= 0; }

	// -- ADDITION

	/**
	 * @brief Addition operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline rational operator+ (T i) const noexcept
	{ rational r(*this); r += i; return r; }
#ifndef SWIG
	/**
	 * @brief Addition operator.
	 * @param i An integer (basic type) number.
	 * @param r A @ref lal::numeric::rational.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline friend rational operator+ (T i, const rational& r) noexcept
	{ return r + i; }
#endif
	/**
	 * @brief Addition operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline rational operator+ (const integer& i) const noexcept
	{ rational r(*this); r += i; return r; }
#ifndef SWIG
	/**
	 * @brief Addition operator.
	 * @param i A @ref lal::numeric::integer.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline friend rational operator+ (const integer& i, const rational& r) noexcept
	{ return r + i; }
#endif
	/**
	 * @brief Addition operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline rational operator+ (const rational& r) const noexcept
	{ rational k(*this); k += r; return k; }

	/**
	 * @brief Addition operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline rational& operator+= (T i) noexcept
	{ rational r(i); mpq_add(m_val, m_val, r.m_val); return *this; }
	/**
	 * @brief Addition operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline rational& operator+= (const integer& i) noexcept
	{ rational r(i); mpq_add(m_val, m_val, r.m_val); return *this; }
	/**
	 * @brief Addition operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline rational& operator+= (const rational& r) noexcept
	{ mpq_add(m_val, m_val, r.m_val); return *this; }

	// -- SUBSTRACTION

	/// Substraction unary operator.
	inline rational operator- () const noexcept
	{ rational r(*this); mpq_neg(r.m_val, r.m_val); return r; }
	/**
	 * @brief Substraction operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline rational operator- (T i) const noexcept
	{ rational r(*this); r -= i; return r; }
#ifndef SWIG
	/**
	 * @brief Substraction operator.
	 * @param i An integer (basic type) number.
	 * @param r A @ref lal::numeric::rational.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline friend rational operator- (T i, const rational& r) noexcept
	{ return -r + i; }
#endif
	/**
	 * @brief Substraction operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline rational operator- (const integer& i) const noexcept
	{ rational r(*this); r -= i; return r; }
#ifndef SWIG
	/**
	 * @brief Substraction operator.
	 * @param i A @ref lal::numeric::integer.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline friend rational operator- (const integer& i, const rational& r) noexcept
	{ return -r + i; }
#endif
	/**
	 * @brief Substraction operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline rational operator- (const rational& r) const noexcept
	{ rational k(*this); k -= r; return k; }

	/**
	 * @brief Substraction operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline rational& operator-= (T i) noexcept
	{ rational r(i); mpq_sub(m_val, m_val, r.m_val); return *this; }
	/**
	 * @brief Substraction operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline rational& operator-= (const integer& i) noexcept
	{ rational r(i); mpq_sub(m_val, m_val, r.m_val); return *this; }
	/**
	 * @brief Substraction operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline rational& operator-= (const rational& r) noexcept
	{ mpq_sub(m_val, m_val, r.m_val); return *this; }

	// -- MULTIPLICATION

	/**
	 * @brief Multiplication operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline rational operator* (T i) const noexcept
	{ rational r(*this); r *= i; return r; }
#ifndef SWIG
	/**
	 * @brief Multiplication operator.
	 * @param i An integer (basic type) number.
	 * @param r A @ref lal::numeric::rational.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline friend rational operator* (T i, const rational& r) noexcept
	{ return r*i; }
#endif
	/**
	 * @brief Multiplication operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline rational operator* (const integer& i) const noexcept
	{ rational r(*this); r *= i; return r; }
#ifndef SWIG
	/**
	 * @brief Multiplication operator.
	 * @param i A @ref lal::numeric::integer.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline friend rational operator* (const integer& i, const rational& r) noexcept
	{ return r*i; }
#endif
	/**
	 * @brief Multiplication operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline rational operator* (const rational& r) const noexcept
	{ rational k(*this); k *= r; return k; }

	/**
	 * @brief Multiplication operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline rational& operator*= (T i) noexcept
	{ rational r(i); mpq_mul(m_val, m_val, r.m_val); return *this; }
	/**
	 * @brief Multiplication operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline rational& operator*= (const integer& i) noexcept
	{ rational r(i); mpq_mul(m_val, m_val, r.m_val); return *this; }
	/**
	 * @brief Multiplication operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline rational& operator*= (const rational& r) noexcept
	{ mpq_mul(m_val, m_val, r.m_val); return *this; }

	// -- DIVISION

	/**
	 * @brief Division operator.
	 * @param i An integer (basic type) number.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline rational operator/ (T i) const noexcept
	{ rational r(*this); r /= i; return r; }
#ifndef SWIG
	/**
	 * @brief Division operator.
	 * @param i An integer (basic type) number.
	 * @param r Rational value.
	 */
	template<typename T,std::enable_if_t<std::is_integral_v<T>, bool> = true>
	inline friend rational operator/ (T i, const rational& r) noexcept
	{ rational inv(r); inv.invert(); return inv*i; }
#endif

	/**
	 * @brief Division operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	inline rational operator/ (const integer& i) const noexcept
	{ rational r(*this); r /= i; return r; }
	/**
	 * @brief Division operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	inline rational operator/ (const rational& r) const noexcept
	{ rational k(*this); k /= r; return k; }

	/**
	 * @brief Division operator.
	 * @param i An integer (basic type) number.
	 */
	rational& operator/= (int64_t i) noexcept;
	/**
	 * @brief Division operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	rational& operator/= (const integer& i) noexcept;
	/**
	 * @brief Division operator.
	 * @param r A @ref lal::numeric::rational.
	 */
	rational& operator/= (const rational& r) noexcept;

	// -- EXPONENTIATION

	/**
	 * @brief Exponentiation operator.
	 * @param i An unsigned integer (basic type).
	 */
	rational pow(uint64_t i) const noexcept;
	/**
	 * @brief Exponentiation operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	rational pow(const integer& i) const noexcept;

	/**
	 * @brief Exponentiation operator.
	 * @param i An unsigned integer (basic type).
	 */
	rational& powt(uint64_t i) noexcept;
	/**
	 * @brief Exponentiation operator.
	 * @param i A @ref lal::numeric::integer.
	 */
	rational& powt(const integer& i) noexcept;

	/* GETTERS */

	/// Returns whether this object is initialised or not.
	inline bool is_initialized() const noexcept { return m_initialized; }
	/// Returns the sign of this rational.
	inline int64_t get_sign() const noexcept { return mpq_sgn(m_val); }

	/// Returns the amount of bytes this integer occupies.
	size_t bytes() const noexcept;

	/* CONVERTERS */

	/**
	 * @brief Converts this rational to an integer value.
	 *
	 * This function returns \f$\left\lfloor n/d \right\rfloor\f$ where
	 * \f$n,d\f$ are, respectively, the numerator and denominator.
	 * @returns The floor of this rational.
	 */
	inline integer to_integer() const noexcept {
		integer i;
		as_integer(i);
		return i;
	}
	/**
	 * @brief Converts this rational to an integer value.
	 *
	 * This function returns \f$\left\lfloor n/d \right\rfloor\f$ where
	 * \f$n,d\f$ are, respectively, the numerator and denominator.
	 * @returns The floor of this rational.
	 */
	void as_integer(integer& i) const noexcept;

	/// Converts this rational to a double-precision floating-point value.
	inline double to_double() const noexcept { return mpq_get_d(m_val); }
	/// Converts this rational to a double-precision floating-point value.
	inline void as_double(double& d) const noexcept { d = mpq_get_d(m_val); }

	/// Converts this integer to a string.
	inline std::string to_string() const noexcept {
		std::string k;
		as_string(k);
		return k;
	}
	/// Converts this integer to a string.
	inline void as_string(std::string& s) const noexcept {
		char *buf = nullptr;
		buf = mpq_get_str(buf, 10, m_val);
		s = std::string(buf);
		free(buf);
	}

	/// Returns the numerator of this rational number
	inline integer get_numerator() const noexcept {
		mpz_t numerator;
		mpz_init(numerator);
		mpq_get_num(numerator, m_val);
		return integer(std::move(numerator));
	}

	/// Returns the denominator of this rational number
	inline integer get_denominator() const noexcept {
		mpz_t denominator;
		mpz_init(denominator);
		mpq_get_den(denominator, m_val);
		return integer(std::move(denominator));
	}

	/* OTHERS */

	/**
	 * @brief Swaps the value of this rational with rational @e r's value.
	 *
	 * - If none of the rationals is initialised, it does nothing.
	 * - If only one of the rationals is initialised, moves the contents
	 * of the initialised rational to the other. At the end, one of the two
	 * rationals is left uninitiliased.
	 * - If both rationals are initialised, swaps the values they contain.
	 */
	void swap(rational& r) noexcept { mpq_swap(m_val, r.m_val); }

#ifndef SWIG
	/**
	 * @brief Swaps two rationals.
	 * @param r1 Input rational.
	 * @param r2 Input rational.
	 */
	friend void swap(rational& r1, rational& r2) noexcept { r1.swap(r2); }
#endif

private:
	/// Structure from GMP storing the rational's value.
	mpq_t m_val;
	/// Is this rational initialised?
	bool m_initialized = true;
};

} // -- namespace numeric
} // -- namespace lal
