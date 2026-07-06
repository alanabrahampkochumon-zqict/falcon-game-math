/**
 * @file DistanceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 28, 2026
 *
 * @brief Verify @ref fgm::Vector4 distance (L1, L2, L3) calculation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "CommonSetup.h"
#include "Vector4TestSetup.h"

#include <numbers>



template <typename T>
class Vector4Distance: public testing::Test
{
protected:
    fgm::Vector4<T> _vecA, _vecB;
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
/** @brief Test fixture for @ref fgm::Vector4 distance calculations, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4Distance, SupportedArithmeticTypes);


template <typename T>
class Vector4DistanceSigned: public testing::Test
{
protected:
    fgm::Vector4<T> _vecA, _vecB;
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
 * @brief Test fixture for @ref fgm::Vector4 distance calculations,
 *        parameterized by @ref SupportedSignedArithmeticTypes.
 */
TYPED_TEST_SUITE(Vector4DistanceSigned, SupportedSignedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Dist
 * @{
 */

/** @brief Verify that @ref fgm::Vector4 distance calculations are available at compile time. */
namespace
{
    // TODO: Add back after creating fgm::sqrt
    constexpr fgm::Vector4 vectorA(1, 1, 2, 1);
    constexpr fgm::Vector4 vectorB(3, 3, 4, 3);

    // Euclidean Distance
    // static_assert(vectorA.dist(vectorB) == 4);
    // static_assert(fgm::Vector4<int>::dist(vectorA, vectorB) == 4);

    // Euclidean Distance Square
    static_assert(vectorA.distSq(vectorB) == 16);
    static_assert(fgm::Vector4<int>::distSq(vectorA, vectorB) == 16);

    // Manhattan Distance
    static_assert(vectorA.manhattanDist(vectorB) == 8);
    static_assert(fgm::Vector4<int>::manhattanDist(vectorA, vectorB) == 8);

    // Chebyshev Distance Square
    static_assert(vectorA.chebyshevDist(vectorB) == 2);
    static_assert(fgm::Vector4<int>::chebyshevDist(vectorA, vectorB) == 2);

} // namespace



/**************************************
 *                                    *
 *        EUCLIDEAN DISTANCE          *
 *                                    *
 **************************************/

/** @brief Verify that the @ref fgm::Vector4::dist function returns the Euclidean distance. */
TYPED_TEST(Vector4Distance, Dist_ReturnsEuclideanDistance)
{ EXPECT_MAG_EQ(this->_dist, this->_vecA.dist(this->_vecB)); }


/** @brief Verify that the @ref fgm::Vector4::dist function maintains precision for irrational numbers. */
TYPED_TEST(Vector4Distance, Dist_IrrationalDistanceMaintainsPrecision)
{
    using T = TypeParam;
    const fgm::Vector4 v1{ T(0), T(0), T(0), T(0) };
    const fgm::Vector4 v2{ T(1), T(1), T(0), T(0) };

    using P                         = fgm::Magnitude<T>;
    constexpr auto expectedDistance = P(std::numbers::sqrt2);

    const auto distance = v1.dist(v2);
    EXPECT_MAG_EQ(expectedDistance, distance);
}


/** @brief Verify that the @ref fgm::Vector4::dist function returns zero for the same vector. */
TYPED_TEST(Vector4Distance, Dist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = fgm::Magnitude<TypeParam>(0);
    const auto distance = this->_vecA.dist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the @ref fgm::Vector4::dist function handles negative coordinates. */
TYPED_TEST(Vector4DistanceSigned, Dist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.dist(this->_vecB);
    EXPECT_MAG_EQ(this->_dist, distance);
}


/** @brief Verify that the @ref fgm::Vector4::dist function always return a floating-point value. */
TYPED_TEST(Vector4Distance, Dist_AlwaysReturnFloatingPointValue)
{
    [[maybe_unused]] const auto distance = this->_vecA.dist(this->_vecB);
    static_assert(std::is_floating_point_v<decltype(distance)>);
}


/** @brief Verify that the static variant of  @ref fgm::Vector4::dist function returns the Euclidean distance. */
TYPED_TEST(Vector4Distance, StaticWrapper_Dist_ReturnsEuclideanDistance)
{ EXPECT_MAG_EQ(this->_dist, fgm::Vector4<TypeParam>::dist(this->_vecA, this->_vecB)); }


/**
 * @brief Verify that the static variant of @ref fgm::Vector4::dist function maintains precision
 *        for irrational numbers.
 */
TYPED_TEST(Vector4Distance, StaticWrapper_Dist_IrrationalDistanceMaintainsPrecision)
{
    using T = TypeParam;
    const fgm::Vector4 v1{ T(0), T(0), T(0), T(0) };
    const fgm::Vector4 v2{ T(1), T(1), T(0), T(0) };

    using P                         = fgm::Magnitude<T>;
    constexpr auto expectedDistance = P(std::numbers::sqrt2);

    const auto distance = fgm::Vector4<T>::dist(v1, v2);

    EXPECT_MAG_EQ(expectedDistance, distance);
}


/** @brief Verify that the @ref fgm::Vector4::dist function returns zero for the same vector. */
TYPED_TEST(Vector4Distance, StaticWrapper_Dist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = fgm::Magnitude<TypeParam>(0);
    const auto distance = fgm::Vector4<TypeParam>::dist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the static variant of @ref fgm::Vector4::dist function handles negative coordinates. */
TYPED_TEST(Vector4DistanceSigned, StaticWrapper_Dist_HandlesNegativeNumbers)
{
    const auto distance = fgm::Vector4<TypeParam>::dist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_dist, distance);
}


/** @brief Verify that the static variant of @ref fgm::Vector4::dist function always return a floating-point value. */
TYPED_TEST(Vector4Distance, StaticWrapper_Dist_AlwaysReturnFloatingPointValue)
{
    [[maybe_unused]] const auto distance = this->_vecA.dist(this->_vecB);
    static_assert(std::is_floating_point_v<decltype(distance)>);
}



/**************************************
 *                                    *
 *    EUCLIDEAN DISTANCE (SQUARED)    *
 *                                    *
 **************************************/

/** @brief Verify that the @ref fgm::Vector4::distSq function returns the Euclidean distance (squared). */
TYPED_TEST(Vector4Distance, DistSq_ReturnsSquaredEuclideanDistance)
{ EXPECT_MAG_EQ(this->_distSq, this->_vecA.distSq(this->_vecB)); }


/** @brief Verify that the @ref fgm::Vector4::distSq function returns zero for the same vector. */
TYPED_TEST(Vector4Distance, DistSq_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.distSq(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the @ref fgm::Vector4::distSq function handles negative coordinates. */
TYPED_TEST(Vector4DistanceSigned, DistSq_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.distSq(this->_vecB);
    EXPECT_MAG_EQ(this->_distSq, distance);
}


/**
 * @brief Verify that the static variant of  @ref fgm::Vector4::distSq function
 *        returns the Euclidean distance (squared).
 */
TYPED_TEST(Vector4Distance, StaticWrapper_DistSq_ReturnsSquaredEuclideanDistance)
{ EXPECT_MAG_EQ(this->_distSq, fgm::Vector4<TypeParam>::distSq(this->_vecA, this->_vecB)); }


/** @brief Verify that the @ref fgm::Vector4::distSq function returns zero for the same vector. */
TYPED_TEST(Vector4Distance, StaticWrapper_DistSq_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = fgm::Vector4<TypeParam>::distSq(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the static variant of @ref fgm::Vector4::distSq function handles negative coordinates. */
TYPED_TEST(Vector4DistanceSigned, StaticWrapper_DistSq_HandlesNegativeNumbers)
{
    const auto distance = fgm::Vector4<TypeParam>::distSq(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distSq, distance);
}


/**************************************
 *                                    *
 *        MANHATTAN DISTANCE          *
 *                                    *
 **************************************/

/** @brief Verify that the @ref fgm::Vector4::manhattanDist function returns the Manhattan. */
TYPED_TEST(Vector4Distance, ManhattanDist_ReturnsManhattanDistance)
{ EXPECT_MAG_EQ(this->_distManhattan, this->_vecA.manhattanDist(this->_vecB)); }


/** @brief Verify that the @ref fgm::Vector4::manhattanDist function returns zero for the same vector. */
TYPED_TEST(Vector4Distance, ManhattanDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.manhattanDist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the @ref fgm::Vector4::manhattanDist function handles negative coordinates. */
TYPED_TEST(Vector4DistanceSigned, ManhattanDist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.manhattanDist(this->_vecB);
    EXPECT_MAG_EQ(this->_distManhattan, distance);
}


/**
 * @brief Verify that the static variant of  @ref fgm::Vector4::manhattanDist function
 *        returns the Manhattan distance.
 */
TYPED_TEST(Vector4Distance, StaticWrapper_ManhattanDist_ReturnsManhattanDistance)
{ EXPECT_MAG_EQ(this->_distManhattan, fgm::Vector4<TypeParam>::manhattanDist(this->_vecA, this->_vecB)); }


/** @brief Verify that the @ref fgm::Vector4::manhattanDist function returns zero for the same vector. */
TYPED_TEST(Vector4Distance, StaticWrapper_ManhattanDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = fgm::Vector4<TypeParam>::manhattanDist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the static variant of @ref fgm::Vector4::manhattanDist function handles negative coordinates. */
TYPED_TEST(Vector4DistanceSigned, StaticWrapper_ManhattanDist_HandlesNegativeNumbers)
{
    const auto distance = fgm::Vector4<TypeParam>::manhattanDist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distManhattan, distance);
}


/**************************************
 *                                    *
 *        CHEBYSHEV DISTANCE          *
 *                                    *
 **************************************/


/** @brief Verify that the @ref fgm::Vector4::chebyshevDist function returns the Chebyshev distance. */
TYPED_TEST(Vector4Distance, ChebyshevDist_ReturnsChebyshevDistance)
{ EXPECT_MAG_EQ(this->_distChebyshev, this->_vecA.chebyshevDist(this->_vecB)); }


/** @brief Verify that the @ref fgm::Vector4::chebyshevDist function returns zero for the same vector. */
TYPED_TEST(Vector4Distance, ChebyshevDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.chebyshevDist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the @ref fgm::Vector4::chebyshevDist function handles negative coordinates. */
TYPED_TEST(Vector4DistanceSigned, ChebyshevDist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.chebyshevDist(this->_vecB);
    EXPECT_MAG_EQ(this->_distChebyshev, distance);
}


/**
 * @brief Verify that the static variant of  @ref fgm::Vector4::chebyshevDist function
 *        returns the Chebyshev distance.
 */
TYPED_TEST(Vector4Distance, StaticWrapper_Chebyshev_ReturnsChebyshevDistance)
{ EXPECT_MAG_EQ(this->_distChebyshev, fgm::Vector4<TypeParam>::chebyshevDist(this->_vecA, this->_vecB)); }


/** @brief Verify that the @ref fgm::Vector4::chebyshevDist function returns zero for the same vector. */
TYPED_TEST(Vector4Distance, StaticWrapper_Chebyshev_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = fgm::Vector4<TypeParam>::chebyshevDist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the static variant of @ref fgm::Vector4::chebyshevDist function handles negative coordinates. */
TYPED_TEST(Vector4DistanceSigned, StaticWrapper_Chebyshev_HandlesNegativeNumbers)
{
    const auto distance = fgm::Vector4<TypeParam>::chebyshevDist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distChebyshev, distance);
}

/** @} */
