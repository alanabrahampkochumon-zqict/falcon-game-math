/**
 * @file DistanceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 28, 2026
 *
 * @brief Verify @ref fgm::Vector4D distance (L1, L2, L3) calculation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "CommonSetup.h"
#include "Vector4DTestSetup.h"

#include <numbers>



template <typename T>
class Vector4DDistance: public testing::Test
{
protected:
    fgm::Vector4D<T> _vecA, _vecB;
    fgm::Magnitude<T> _dist;
    T _distSq, _distManhattan, _distChebyshev;


    void SetUp() override
    {
        _vecA = { T(2), T(7), T(2), T(3) };
        _vecB = { T(5), T(3), T(5), T(1) };

        _dist          = fgm::Magnitude<T>(6.164414002968976);
        _distSq        = T(38);
        _distManhattan = T(12);
        _distChebyshev = T(4);
    }
};
/** @brief Test fixture for @ref fgm::Vector4D distance calculations, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DDistance, SupportedArithmeticTypes);


template <typename T>
class Vector4DDistanceSigned: public testing::Test
{
protected:
    fgm::Vector4D<T> _vecA, _vecB;
    fgm::Magnitude<T> _dist;
    T _distSq, _distManhattan, _distChebyshev;


    void SetUp() override
    {
        _vecA = { T(1), T(2), T(-1), T(2) };
        _vecB = { T(-2), T(3), T(-3), T(1) };

        _dist          = fgm::Magnitude<T>(3.872983346207417);
        _distSq        = T(15);
        _distManhattan = T(7);
        _distChebyshev = T(3);
    }
};
/**
 * @brief Test fixture for @ref fgm::Vector4D distance calculations,
 *        parameterized by @ref SupportedSignedArithmeticTypes.
 */
TYPED_TEST_SUITE(Vector4DDistanceSigned, SupportedSignedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Dist
 * @{
 */

/** @brief Verify that @ref fgm::Vector4D distance calculations are available at compile time. */
namespace
{
    // TODO: Add back after creating fgm::sqrt
    constexpr fgm::Vector4D vectorA(1, 1, 2, 1);
    constexpr fgm::Vector4D vectorB(3, 3, 4, 3);

    // Euclidean Distance
    // static_assert(vectorA.dist(vectorB) == 4);
    // static_assert(fgm::Vector4D<int>::dist(vectorA, vectorB) == 4);

    // Euclidean Distance Square
    static_assert(vectorA.distSq(vectorB) == 16);
    static_assert(fgm::Vector4D<int>::distSq(vectorA, vectorB) == 16);

    // Manhattan Distance
    static_assert(vectorA.manhattanDist(vectorB) == 8);
    static_assert(fgm::Vector4D<int>::manhattanDist(vectorA, vectorB) == 8);

    // // Chebyshev Distance Square
    // static_assert(vectorA.chebyshevDist(vectorB) == 6);
    // static_assert(fgm::Vector4D<int>::chebyshevDist(vectorA, vectorB) == 6);

} // namespace



/**************************************
 *                                    *
 *        EUCLIDEAN DISTANCE          *
 *                                    *
 **************************************/

/** @brief Verify that the @ref fgm::Vector4D::dist function returns the Euclidean distance. */
TYPED_TEST(Vector4DDistance, Dist_ReturnsEuclideanDistance)
{ EXPECT_MAG_EQ(this->_dist, this->_vecA.dist(this->_vecB)); }


/** @brief Verify that the @ref fgm::Vector4D::dist function maintains precision for irrational numbers. */
TYPED_TEST(Vector4DDistance, Dist_IrrationalDistanceMaintainsPrecision)
{
    using T = TypeParam;
    const fgm::Vector4D v1{ T(0), T(0), T(0), T(0) };
    const fgm::Vector4D v2{ T(1), T(1), T(0), T(0) };

    using P                         = fgm::Magnitude<T>;
    constexpr auto expectedDistance = P(std::numbers::sqrt2);

    const auto distance = v1.dist(v2);
    EXPECT_MAG_EQ(expectedDistance, distance);
}


/** @brief Verify that the @ref fgm::Vector4D::dist function returns zero for the same vector. */
TYPED_TEST(Vector4DDistance, Dist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = fgm::Magnitude<TypeParam>(0);
    const auto distance = this->_vecA.dist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the @ref fgm::Vector4D::dist function handles negative coordinates. */
TYPED_TEST(Vector4DDistanceSigned, Dist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.dist(this->_vecB);
    EXPECT_MAG_EQ(this->_dist, distance);
}


/** @brief Verify that the @ref fgm::Vector4D::dist function always return a floating-point value. */
TYPED_TEST(Vector4DDistance, Dist_AlwaysReturnFloatingPointValue)
{
    [[maybe_unused]] const auto distance = this->_vecA.dist(this->_vecB);
    static_assert(std::is_floating_point_v<decltype(distance)>);
}


/** @brief Verify that the static variant of  @ref fgm::Vector4D::dist function returns the Euclidean distance. */
TYPED_TEST(Vector4DDistance, StaticWrapper_Dist_ReturnsEuclideanDistance)
{ EXPECT_MAG_EQ(this->_dist, fgm::Vector4D<TypeParam>::dist(this->_vecA, this->_vecB)); }


/**
 * @brief Verify that the static variant of @ref fgm::Vector4D::dist function maintains precision
 *        for irrational numbers.
 */
TYPED_TEST(Vector4DDistance, StaticWrapper_Dist_IrrationalDistanceMaintainsPrecision)
{
    using T = TypeParam;
    const fgm::Vector4D v1{ T(0), T(0), T(0), T(0) };
    const fgm::Vector4D v2{ T(1), T(1), T(0), T(0) };

    using P                         = fgm::Magnitude<T>;
    constexpr auto expectedDistance = P(std::numbers::sqrt2);

    const auto distance = fgm::Vector4D<T>::dist(v1, v2);

    EXPECT_MAG_EQ(expectedDistance, distance);
}


/** @brief Verify that the @ref fgm::Vector4D::dist function returns zero for the same vector. */
TYPED_TEST(Vector4DDistance, StaticWrapper_Dist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = fgm::Magnitude<TypeParam>(0);
    const auto distance = fgm::Vector4D<TypeParam>::dist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the static variant of @ref fgm::Vector4D::dist function handles negative coordinates. */
TYPED_TEST(Vector4DDistanceSigned, StaticWrapper_Dist_HandlesNegativeNumbers)
{
    const auto distance = fgm::Vector4D<TypeParam>::dist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_dist, distance);
}


/** @brief Verify that the static variant of @ref fgm::Vector4D::dist function always return a floating-point value. */
TYPED_TEST(Vector4DDistance, StaticWrapper_Dist_AlwaysReturnFloatingPointValue)
{
    [[maybe_unused]] const auto distance = this->_vecA.dist(this->_vecB);
    static_assert(std::is_floating_point_v<decltype(distance)>);
}



/**************************************
 *                                    *
 *    EUCLIDEAN DISTANCE (SQUARED)    *
 *                                    *
 **************************************/

/** @brief Verify that the @ref fgm::Vector4D::distSq function returns the Euclidean distance (squared). */
TYPED_TEST(Vector4DDistance, DistSq_ReturnsSquaredEuclideanDistance)
{ EXPECT_MAG_EQ(this->_distSq, this->_vecA.distSq(this->_vecB)); }


/** @brief Verify that the @ref fgm::Vector4D::distSq function returns zero for the same vector. */
TYPED_TEST(Vector4DDistance, DistSq_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.distSq(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the @ref fgm::Vector4D::distSq function handles negative coordinates. */
TYPED_TEST(Vector4DDistanceSigned, DistSq_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.distSq(this->_vecB);
    EXPECT_MAG_EQ(this->_distSq, distance);
}


/**
 * @brief Verify that the static variant of  @ref fgm::Vector4D::distSq function
 *        returns the Euclidean distance (squared).
 */
TYPED_TEST(Vector4DDistance, StaticWrapper_DistSq_ReturnsSquaredEuclideanDistance)
{ EXPECT_MAG_EQ(this->_distSq, fgm::Vector4D<TypeParam>::distSq(this->_vecA, this->_vecB)); }


/** @brief Verify that the @ref fgm::Vector4D::distSq function returns zero for the same vector. */
TYPED_TEST(Vector4DDistance, StaticWrapper_DistSq_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = fgm::Vector4D<TypeParam>::distSq(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the static variant of @ref fgm::Vector4D::distSq function handles negative coordinates. */
TYPED_TEST(Vector4DDistanceSigned, StaticWrapper_DistSq_HandlesNegativeNumbers)
{
    const auto distance = fgm::Vector4D<TypeParam>::distSq(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distSq, distance);
}


/**************************************
 *                                    *
 *        MANHATTAN DISTANCE          *
 *                                    *
 **************************************/

// /** @brief Verify that the @ref fgm::Vector4D::manhattanDist function returns the Manhattan. */
// TYPED_TEST(Vector4DDistance, ManhattanDist_ReturnsManhattanDistance)
// { EXPECT_MAG_EQ(this->_distManhattan, this->_vecA.manhattanDist(this->_vecB)); }
//
//
// /** @brief Verify that the @ref fgm::Vector4D::manhattanDist function returns zero for the same vector. */
// TYPED_TEST(Vector4DDistance, ManhattanDist_BetweenSameVectorReturnsZero)
// {
//     constexpr auto zero = TypeParam(0);
//     const auto distance = this->_vecA.manhattanDist(this->_vecA);
//     EXPECT_MAG_EQ(zero, distance);
// }
//
//
// /** @brief Verify that the @ref fgm::Vector4D::manhattanDist function handles negative coordinates. */
// TYPED_TEST(Vector4DDistanceSigned, ManhattanDist_HandlesNegativeNumbers)
// {
//     const auto distance = this->_vecA.manhattanDist(this->_vecB);
//     EXPECT_MAG_EQ(this->_distManhattan, distance);
// }
//
//
// /**
//  * @brief Verify that the static variant of  @ref fgm::Vector4D::manhattanDist function
//  *        returns the Manhattan distance.
//  */
// TYPED_TEST(Vector4DDistance, StaticWrapper_ManhattanDist_ReturnsManhattanDistance)
// { EXPECT_MAG_EQ(this->_distManhattan, fgm::Vector4D<TypeParam>::manhattanDist(this->_vecA, this->_vecB)); }
//
//
// /** @brief Verify that the @ref fgm::Vector4D::manhattanDist function returns zero for the same vector. */
// TYPED_TEST(Vector4DDistance, StaticWrapper_ManhattanDist_BetweenSameVectorReturnsZero)
// {
//     constexpr auto zero = TypeParam(0);
//     const auto distance = fgm::Vector4D<TypeParam>::manhattanDist(this->_vecA, this->_vecA);
//     EXPECT_MAG_EQ(zero, distance);
// }
//
//
// /** @brief Verify that the static variant of @ref fgm::Vector4D::manhattanDist function handles negative coordinates. */
// TYPED_TEST(Vector4DDistanceSigned, StaticWrapper_ManhattanDist_HandlesNegativeNumbers)
// {
//     const auto distance = fgm::Vector4D<TypeParam>::manhattanDist(this->_vecA, this->_vecB);
//     EXPECT_MAG_EQ(this->_distManhattan, distance);
// }
//
//
// /**************************************
//  *                                    *
//  *        CHEBYSHEV DISTANCE          *
//  *                                    *
//  **************************************/
//
//
// /** @brief Verify that the @ref fgm::Vector4D::chebyshevDist function returns the Chebyshev distance. */
// TYPED_TEST(Vector4DDistance, ChebyshevDist_ReturnsChebyshevDistance)
// { EXPECT_MAG_EQ(this->_distChebyshev, this->_vecA.chebyshevDist(this->_vecB)); }
//
//
// /** @brief Verify that the @ref fgm::Vector4D::chebyshevDist function returns zero for the same vector. */
// TYPED_TEST(Vector4DDistance, ChebyshevDist_BetweenSameVectorReturnsZero)
// {
//     constexpr auto zero = TypeParam(0);
//     const auto distance = this->_vecA.chebyshevDist(this->_vecA);
//     EXPECT_MAG_EQ(zero, distance);
// }
//
//
// /** @brief Verify that the @ref fgm::Vector4D::chebyshevDist function handles negative coordinates. */
// TYPED_TEST(Vector4DDistanceSigned, ChebyshevDist_HandlesNegativeNumbers)
// {
//     const auto distance = this->_vecA.chebyshevDist(this->_vecB);
//     EXPECT_MAG_EQ(this->_distChebyshev, distance);
// }
//
//
// /**
//  * @brief Verify that the static variant of  @ref fgm::Vector4D::chebyshevDist function
//  *        returns the Chebyshev distance.
//  */
// TYPED_TEST(Vector4DDistance, StaticWrapper_Chebyshev_ReturnsChebyshevDistance)
// { EXPECT_MAG_EQ(this->_distChebyshev, fgm::Vector4D<TypeParam>::chebyshevDist(this->_vecA, this->_vecB)); }
//
//
// /** @brief Verify that the @ref fgm::Vector4D::chebyshevDist function returns zero for the same vector. */
// TYPED_TEST(Vector4DDistance, StaticWrapper_Chebyshev_BetweenSameVectorReturnsZero)
// {
//     constexpr auto zero = TypeParam(0);
//     const auto distance = fgm::Vector4D<TypeParam>::chebyshevDist(this->_vecA, this->_vecA);
//     EXPECT_MAG_EQ(zero, distance);
// }
//
//
// /** @brief Verify that the static variant of @ref fgm::Vector4D::chebyshevDist function handles negative coordinates. */
// TYPED_TEST(Vector4DDistanceSigned, StaticWrapper_Chebyshev_HandlesNegativeNumbers)
// {
//     const auto distance = fgm::Vector4D<TypeParam>::chebyshevDist(this->_vecA, this->_vecB);
//     EXPECT_MAG_EQ(this->_distChebyshev, distance);
// }

/** @} */
