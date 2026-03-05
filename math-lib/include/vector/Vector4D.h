#pragma once
#pragma once

#include "Vector2D.h"
#include "Vector3D.h"

#include <cstddef>

// NOTE: To manually turn off SIMD support use `FORCE_NO_SIMD` macro


namespace math
{
	template<Arithmetic T>
	struct Vector4D
	{
		using value_type = T;

		static constexpr std::size_t dimension = 4;

		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			struct { T s, t, p, q; };

			T elements[dimension];
		};


		/*************************************
		 *                                   *
		 *            INITIALIZERS           *
		 *                                   *
		 *************************************/

		Vector4D();
		Vector4D(T v1, T v2, T v3, T v4);
		Vector4D(Vector2D<T> vec1, Vector2D<T> vec2);
		Vector4D(Vector3D<T> vec, T v);

		template<Arithmetic U>
		Vector4D(const Vector4D<U>& other);


		/*************************************
		 *                                   *
		 *            ACCESSORS              *
		 *                                   *
		 *************************************/

		T& operator[](std::size_t i);
		const T& operator[](std::size_t i) const;

		/***************************************
		 *                                     *
		 *            COMPARISONS              *
		 *                                     *
		 ***************************************/
		template <Arithmetic U>
		bool equals(const Vector4D<U>& other, double epsilon = (std::is_same_v<T, double> && std::is_same_v<U, double>) ? DOUBLE_EPSILON: FLOAT_EPSILON) const;

		template <Arithmetic U>
		static bool equals(const Vector4D& vecA, const Vector4D<U>& vecB, double epsilon = (std::is_same_v<T, double> && std::is_same_v<U, double>) ? DOUBLE_EPSILON : FLOAT_EPSILON);

		template <Arithmetic U>
		bool operator==(const Vector4D<U>& other) const;

		template <Arithmetic U>
		bool operator!=(const Vector4D<U>& other) const;

		// NOTE: All comparison operator expect equality and inequality performs element-wise comparison
		template <StrictArithmetic U>
		Vector4D<bool> greaterThan(const Vector4D<U>& other) const requires StrictArithmetic<T>;

		template <StrictArithmetic U>
		static Vector4D<bool> greaterThan(const Vector4D& vecA, const Vector4D<U>& vecB) requires StrictArithmetic<T>;

		template <StrictArithmetic U>
		Vector4D<bool> operator>(const Vector4D<U>& other) const requires StrictArithmetic<T>;

		template <StrictArithmetic U>
		Vector4D<bool> greaterThanOrEqual(const Vector4D<U>& other) const requires StrictArithmetic<T>;

		template <StrictArithmetic U>
		static Vector4D<bool> greaterThanOrEqual(const Vector4D& vecA, const Vector4D<U>& vecB) requires StrictArithmetic<T>;

		template <StrictArithmetic U>
		Vector4D<bool> operator>=(const Vector4D<U>& other) const requires StrictArithmetic<T>;

		/*************************************
		 *                                   *
		 *      ARITHMETIC OPERATORS         *
		 *                                   *
		 *************************************/

		template<StrictArithmetic U>
		auto operator+(const Vector4D<U>& other) const->Vector4D<std::common_type_t<T, U>> requires StrictArithmetic<T>;

		template<StrictArithmetic U>
		Vector4D& operator+=(const Vector4D<U>& other) requires StrictArithmetic<T>;

		template<StrictArithmetic U>
		auto operator-(const Vector4D<U>& other) const->Vector4D<std::common_type_t<T, U>> requires StrictArithmetic<T>;
		template<StrictArithmetic U>
		Vector4D& operator-=(const Vector4D<U>& other) requires StrictArithmetic<T>;

		template <StrictArithmetic S>
		auto operator*(S scalar) const->Vector4D<std::common_type_t<T, S>> requires StrictArithmetic<T>;

		template <StrictArithmetic S>
		Vector4D& operator*=(S scalar) requires StrictArithmetic<T>;

		template<StrictArithmetic S>
		auto operator/(S scalar) const->Vector4D<std::common_type_t<T, S>> requires StrictArithmetic<T>;

		template<StrictArithmetic S>
		Vector4D& operator/=(S scalar) requires StrictArithmetic<T>;


		/*************************************
		 *                                   *
		 *        VECTOR DOT PRODUCT         *
		 *                                   *
		 *************************************/

		template<StrictArithmetic U>
		auto dot(const Vector4D<U>& other) const -> std::common_type_t<T, U> requires StrictArithmetic<T>;

		template<StrictArithmetic U>
		static auto dot(const Vector4D& vecA, const Vector4D<U>& vecB) -> std::common_type_t<T, U> requires StrictArithmetic<T>;


		/*************************************
		 *                                   *
		 *         VECTOR MAGNITUDE          *
		 *                                   *
		 *************************************/

		 /*
		  * Returns the magnitude of the vector.
		  * @return If the type of T float, then a float is returned, else a float.
		  */
		Magnitude<T> mag() const requires StrictArithmetic<T>;
		static Magnitude<T> mag(const Vector4D& vec) requires StrictArithmetic<T>;


		/*************************************
		 *                                   *
		 *       VECTOR NORMALIZATION        *
		 *                                   *
		 *************************************/

		 /*
		  * Returns a normalized vector.
		  * Special Note: Vector will be type promoted to math::Magnitude's type.
		  * @return normalized floating point vector.
		  */
		Vector4D<Magnitude<T>> normalize() const requires StrictArithmetic<T>;
		static Vector4D<Magnitude<T>> normalize(const Vector4D& vec) requires StrictArithmetic<T>;


		/*************************************
		 *                                   *
		 *        VECTOR PROJECTION          *
		 *                                   *
		 *************************************/

		 /**
		  * Projects the current vector onto to the `onto` vector.
		  * @tparam U Type of the vector to be projected on to (b).
		  * @param onto Vector to be projected onto.
		  * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
		  * @return Projected vector.
		  */
		template<StrictArithmetic U>
		auto project(const Vector4D<U>& onto, bool ontoNormalized = false) const -> Vector4D<std::common_type_t<T, U>> requires StrictArithmetic<T>;

		/**
		 * Static wrapper for vector projection.
		 * @tparam U Type of the vector to be projected to.
		 * @param vector Vector to project.
		 * @param onto Vector to be projected onto.
		 * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
		 * @return Projected vector.
		 */
		template<StrictArithmetic U>
		static auto project(const Vector4D& vector, const Vector4D<U>& onto, bool ontoNormalized = false) -> Vector4D<std::common_type_t<T, U>> requires StrictArithmetic<T>;


		/*************************************
		 *                                   *
		 *         VECTOR REJECTION          *
		 *                                   *
		 *************************************/

		 /**
		  * Returns the perpendicular component for the current vector after projection to the `onto` vector.
		  * @tparam U Type of the vector to be vector projected onto.
		  * @param onto Vector to be projected onto.
		  * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
		  * @return Projected vector.
		  */
		template<StrictArithmetic U>
		auto reject(const Vector4D<U>& onto, bool ontoNormalized = false) const -> Vector4D<std::common_type_t<T, U>> requires StrictArithmetic<T>;


		/**
		 * Returns the perpendicular component for the current vector after projection to the `onto` vector.
		 * @tparam U Type of the vector to be vector projected onto.
		 * @param vector whose rejection(perpendicular) component on to `onto` we need to find.
		 * @param onto Vector to be projected onto.
		 * @param ontoNormalized A flag for optimizing the by ignoring the division, given the vector that is projected onto is normalized.
		 * @return Projected vector.
		 */
		template<StrictArithmetic U>
		static auto reject(const Vector4D& vector, const Vector4D<U>& onto, bool ontoNormalized = false) -> Vector4D<std::common_type_t<T, U>> requires StrictArithmetic<T>;

	};


	/*************************************
	 *                                   *
	 *       NON-MEMBER FUNCTIONS        *
	 *                                   *
	 *************************************/
	template<StrictArithmetic T, StrictArithmetic S>
	auto operator*(S scalar, const Vector4D<T>& vector) -> Vector4D<std::common_type_t<T, S>> requires StrictArithmetic<T>;


	/*************************************
	 *                                   *
	 *             ALIASES               *
	 *                                   *
	 *************************************/
	using bVec4 = Vector4D<bool>;
	using iVec4 = Vector4D<int>;
	using uVec4 = Vector4D<unsigned int>;
	using vec4 = Vector4D<float>;
	using lVec4 = Vector4D<long long>;
	using dVec4 = Vector4D<double>;
	using ulVec4 = Vector4D<unsigned long long>;


	// TODO: Add &&, ||, ==, !=, ! for bool vectors
}

#include "Vector4D.tpp"