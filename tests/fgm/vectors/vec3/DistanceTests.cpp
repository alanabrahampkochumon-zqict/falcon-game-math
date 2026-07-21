/**
 * @file DistanceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 28, 2026
 *
 * @brief Verify @ref fgm::Vec3 distance (L1, L2, L3) calculation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "CommonSetup.h"
#include "Vec3TestSetup.h"

#include <numbers>



template <typename T>
class Vec3Distance: public testing::Test
{
protected:
    fgm::Vec3<T> _vecA, _vecB;
    fgm::Magnitude<T> _dist;
    T _distSq, _distManhattan, _distChebyshev;


    void SetUp() override
    {
        _vecA = { T(2), T(7), T(2) };
        _vecB = { T(5), T(3), T(5) };

        _dist          = fgm::Magnitude<T>(5.830951894845301);
        _distSq        = T(34);
        _distManhattan = T(10);
        _distChebyshev = T(4);
    }
};
/** @brief Test fixture for @ref fgm::Vec3 distance calculations, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vec3Distance, SupportedArithmeticTypes);


template <typename T>
class Vec3DistanceSigned: public testing::Test
{
protected:
    fgm::Vec3<T> _vecA, _vecB;
    fgm::Magnitude<T> _dist;
    T _distSq, _distManhattan, _distChebyshev;


    void SetUp() override
    {
        _vecA = { T(1), T(2), T(-1) };
        _vecB = { T(-2), T(3), T(-3) };

        _dist          = fgm::Magnitude<T>(3.7416573867739413);
        _distSq        = T(14);
        _distManhattan = T(6);
        _distChebyshev = T(3);
    }
};
/**
 * @brief Test fixture for @ref fgm::Vec3 distance calculations,
 *        parameterized by @ref SupportedSignedArithmeticTypes.
 */
TYPED_TEST_SUITE(Vec3DistanceSigned, SupportedSignedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Dist
 * @{
 */

/** @brief Verify that @ref fgm::Vec3 distance calculations are available at compile time. */
namespace
{
    // TODO: Add back after creating fgm::sqrt
    constexpr fgm::Vec3 vectorA(1, 2, 3);
    constexpr fgm::Vec3 vectorB(3, 8, 6);

    // Euclidean Distance
    // static_assert(vectorA.dist(vectorB) == 7);
    // static_assert(fgm::Vec3<int>::dist(vectorA, vectorB) == 7);

    // Euclidean Distance Square
    static_assert(vectorA.distSq(vectorB) == 49);
    static_assert(fgm::Vec3<int>::distSq(vectorA, vectorB) == 49);

    // Manhattan Distance
    static_assert(vectorA.manhattanDist(vectorB) == 11);
    static_assert(fgm::Vec3<int>::manhattanDist(vectorA, vectorB) == 11);

    // Chebyshev Distance Square
    static_assert(vectorA.chebyshevDist(vectorB) == 6);
    static_assert(fgm::Vec3<int>::chebyshevDist(vectorA, vectorB) == 6);

} // namespace



/**************************************
 *                                    *
 *        EUCLIDEAN DISTANCE          *
 *                                    *
 **************************************/

/** @brief Verify that the @ref fgm::Vec3::dist function returns the Euclidean distance. */
TYPED_TEST(Vec3Distance, Dist_ReturnsEuclideanDistance) { EXPECT_MAG_EQ(this->_dist, this->_vecA.dist(this->_vecB)); }


/** @brief Verify that the @ref fgm::Vec3::dist function maintains precision for irrational numbers. */
TYPED_TEST(Vec3Distance, Dist_IrrationalDistanceMaintainsPrecision)
{
    using T = TypeParam;
    const fgm::Vec3 v1{ T(0), T(0), T(0) };
    const fgm::Vec3 v2{ T(1), T(1), T(0) };

    using P                         = fgm::Magnitude<T>;
    constexpr auto expectedDistance = P(std::numbers::sqrt2);

    const auto distance = v1.dist(v2);
    EXPECT_MAG_EQ(expectedDistance, distance);
}


/** @brief Verify that the @ref fgm::Vec3::dist function returns zero for the same vector. */
TYPED_TEST(Vec3Distance, Dist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = fgm::Magnitude<TypeParam>(0);
    const auto distance = this->_vecA.dist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the @ref fgm::Vec3::dist function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSigned, Dist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.dist(this->_vecB);
    EXPECT_MAG_EQ(this->_dist, distance);
}


/** @brief Verify that the @ref fgm::Vec3::dist function always return a floating-point value. */
TYPED_TEST(Vec3Distance, Dist_AlwaysReturnFloatingPointValue)
{
    [[maybe_unused]] const auto distance = this->_vecA.dist(this->_vecB);
    static_assert(std::is_floating_point_v<decltype(distance)>);
}


/** @brief Verify that the static variant of  @ref fgm::Vec3::dist function returns the Euclidean distance. */
TYPED_TEST(Vec3Distance, StaticWrapper_Dist_ReturnsEuclideanDistance)
{
    EXPECT_MAG_EQ(this->_dist, fgm::Vec3<TypeParam>::dist(this->_vecA, this->_vecB));
}


/**
 * @brief Verify that the static variant of @ref fgm::Vec3::dist function maintains precision
 *        for irrational numbers.
 */
TYPED_TEST(Vec3Distance, StaticWrapper_Dist_IrrationalDistanceMaintainsPrecision)
{
    using T = TypeParam;
    const fgm::Vec3 v1{ T(0), T(0), T(0) };
    const fgm::Vec3 v2{ T(1), T(1), T(0) };

    using P                         = fgm::Magnitude<T>;
    constexpr auto expectedDistance = P(std::numbers::sqrt2);

    const auto distance = fgm::Vec3<T>::dist(v1, v2);

    EXPECT_MAG_EQ(expectedDistance, distance);
}


/** @brief Verify that the @ref fgm::Vec3::dist function returns zero for the same vector. */
TYPED_TEST(Vec3Distance, StaticWrapper_Dist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = fgm::Magnitude<TypeParam>(0);
    const auto distance = fgm::Vec3<TypeParam>::dist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the static variant of @ref fgm::Vec3::dist function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSigned, StaticWrapper_Dist_HandlesNegativeNumbers)
{
    const auto distance = fgm::Vec3<TypeParam>::dist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_dist, distance);
}


/** @brief Verify that the static variant of @ref fgm::Vec3::dist function always return a floating-point value. */
TYPED_TEST(Vec3Distance, StaticWrapper_Dist_AlwaysReturnFloatingPointValue)
{
    [[maybe_unused]] const auto distance = this->_vecA.dist(this->_vecB);
    static_assert(std::is_floating_point_v<decltype(distance)>);
}



/**************************************
 *                                    *
 *    EUCLIDEAN DISTANCE (SQUARED)    *
 *                                    *
 **************************************/

/** @brief Verify that the @ref fgm::Vec3::distSq function returns the Euclidean distance (squared). */
TYPED_TEST(Vec3Distance, DistSq_ReturnsSquaredEuclideanDistance)
{
    EXPECT_MAG_EQ(this->_distSq, this->_vecA.distSq(this->_vecB));
}


/** @brief Verify that the @ref fgm::Vec3::distSq function returns zero for the same vector. */
TYPED_TEST(Vec3Distance, DistSq_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.distSq(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the @ref fgm::Vec3::distSq function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSigned, DistSq_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.distSq(this->_vecB);
    EXPECT_MAG_EQ(this->_distSq, distance);
}


/**
 * @brief Verify that the static variant of  @ref fgm::Vec3::distSq function
 *        returns the Euclidean distance (squared).
 */
TYPED_TEST(Vec3Distance, StaticWrapper_DistSq_ReturnsSquaredEuclideanDistance)
{
    EXPECT_MAG_EQ(this->_distSq, fgm::Vec3<TypeParam>::distSq(this->_vecA, this->_vecB));
}


/** @brief Verify that the @ref fgm::Vec3::distSq function returns zero for the same vector. */
TYPED_TEST(Vec3Distance, StaticWrapper_DistSq_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = fgm::Vec3<TypeParam>::distSq(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the static variant of @ref fgm::Vec3::distSq function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSigned, StaticWrapper_DistSq_HandlesNegativeNumbers)
{
    const auto distance = fgm::Vec3<TypeParam>::distSq(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distSq, distance);
}


/**************************************
 *                                    *
 *        MANHATTAN DISTANCE          *
 *                                    *
 **************************************/

/** @brief Verify that the @ref fgm::Vec3::manhattanDist function returns the Manhattan. */
TYPED_TEST(Vec3Distance, ManhattanDist_ReturnsManhattanDistance)
{
    EXPECT_MAG_EQ(this->_distManhattan, this->_vecA.manhattanDist(this->_vecB));
}


/** @brief Verify that the @ref fgm::Vec3::manhattanDist function returns zero for the same vector. */
TYPED_TEST(Vec3Distance, ManhattanDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.manhattanDist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the @ref fgm::Vec3::manhattanDist function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSigned, ManhattanDist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.manhattanDist(this->_vecB);
    EXPECT_MAG_EQ(this->_distManhattan, distance);
}


/**
 * @brief Verify that the static variant of  @ref fgm::Vec3::manhattanDist function
 *        returns the Manhattan distance.
 */
TYPED_TEST(Vec3Distance, StaticWrapper_ManhattanDist_ReturnsManhattanDistance)
{
    EXPECT_MAG_EQ(this->_distManhattan, fgm::Vec3<TypeParam>::manhattanDist(this->_vecA, this->_vecB));
}


/** @brief Verify that the @ref fgm::Vec3::manhattanDist function returns zero for the same vector. */
TYPED_TEST(Vec3Distance, StaticWrapper_ManhattanDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = fgm::Vec3<TypeParam>::manhattanDist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the static variant of @ref fgm::Vec3::manhattanDist function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSigned, StaticWrapper_ManhattanDist_HandlesNegativeNumbers)
{
    const auto distance = fgm::Vec3<TypeParam>::manhattanDist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distManhattan, distance);
}


/**************************************
 *                                    *
 *        CHEBYSHEV DISTANCE          *
 *                                    *
 **************************************/


/** @brief Verify that the @ref fgm::Vec3::chebyshevDist function returns the Chebyshev distance. */
TYPED_TEST(Vec3Distance, ChebyshevDist_ReturnsChebyshevDistance)
{
    EXPECT_MAG_EQ(this->_distChebyshev, this->_vecA.chebyshevDist(this->_vecB));
}


/** @brief Verify that the @ref fgm::Vec3::chebyshevDist function returns zero for the same vector. */
TYPED_TEST(Vec3Distance, ChebyshevDist_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = this->_vecA.chebyshevDist(this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the @ref fgm::Vec3::chebyshevDist function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSigned, ChebyshevDist_HandlesNegativeNumbers)
{
    const auto distance = this->_vecA.chebyshevDist(this->_vecB);
    EXPECT_MAG_EQ(this->_distChebyshev, distance);
}


/**
 * @brief Verify that the static variant of  @ref fgm::Vec3::chebyshevDist function
 *        returns the Chebyshev distance.
 */
TYPED_TEST(Vec3Distance, StaticWrapper_Chebyshev_ReturnsChebyshevDistance)
{
    EXPECT_MAG_EQ(this->_distChebyshev, fgm::Vec3<TypeParam>::chebyshevDist(this->_vecA, this->_vecB));
}


/** @brief Verify that the @ref fgm::Vec3::chebyshevDist function returns zero for the same vector. */
TYPED_TEST(Vec3Distance, StaticWrapper_Chebyshev_BetweenSameVectorReturnsZero)
{
    constexpr auto zero = TypeParam(0);
    const auto distance = fgm::Vec3<TypeParam>::chebyshevDist(this->_vecA, this->_vecA);
    EXPECT_MAG_EQ(zero, distance);
}


/** @brief Verify that the static variant of @ref fgm::Vec3::chebyshevDist function handles negative coordinates. */
TYPED_TEST(Vec3DistanceSigned, StaticWrapper_Chebyshev_HandlesNegativeNumbers)
{
    const auto distance = fgm::Vec3<TypeParam>::chebyshevDist(this->_vecA, this->_vecB);
    EXPECT_MAG_EQ(this->_distChebyshev, distance);
}

/** @} */
