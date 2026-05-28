/**
 * @file DistanceTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 28, 2026
 *
 * @brief Verify @ref fgm::Vector distance (L1, L2, L3) calculation logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "CommonSetup.h"
#include "Vector2DTestSetup.h"



template <typename T>
class Vector2DDistance: public testing::Test
{
protected:
    fgm::Vector2D<T> _vecA, _vecB;
    fgm::Magnitude<T> _dist;
    T _distSq, _distManhattan, _distChebyshev;


    void SetUp() override
    {
        _vecA = { T(2), T(3) };
        _vecB = { T(5), T(7) };

        _dist          = 5;
        _distSq        = 25;
        _distManhattan = 7;
        _distChebyshev = 4;
    }
};
/** @brief Test fixture for @ref fgm::Vector2D distance calculations, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector2DDistance, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec2_Dist
 * @{
 */

/** @brief Verify that @ref fgm::Vector2D distance calculations are available at compile time. */
namespace
{
    // TODO: Add back after creating fgm::sqrt
    // constexpr fgm::Vector2D vectorA(2, 3);
    // constexpr fgm::Vector2D vectorB(5, 7);

    // static_assert(vectorA.dist(vectorB) == 5);
    // static_assert(fgm::Vector2D<int>::dist(vectorA, vectorB) == 5);

} // namespace



/**************************************
 *                                    *
 *           L2 DISTANCE              *
 *                                    *
 **************************************/

/** @brief Verify that the @ref fgm::Vector2D::dist function returns the Euclidean distance. */
TYPED_TEST(Vector2DDistance, Dist_ReturnsEuclideanDistance) { EXPECT_EQ(this->_vecA.dist(this->_vecB), this->_dist); }


/** @brief Verify that the static variant of  @ref fgm::Vector2D::dist function returns the Euclidean distance. */
TYPED_TEST(Vector2DDistance, StaticWrapper_Dist_ReturnsEuclideanDistance)
{
    EXPECT_EQ(fgm::Vector2D<TypeParam>::dist(this->_vecA, this->_vecB), this->_dist);
}


/** @brief Verify that the @ref fgm::Vector2D::dist function always return a floating-point value. */
TYPED_TEST(Vector2DDistance, Dist_AlwaysReturnFloatingPointValue)
{
    [[maybe_unused]] const auto distance = this->_vecA.dist(this->_vecB);
    static_assert(std::is_floating_point_v<decltype(distance)>);
}


/** @brief Verify that the static variant of @ref fgm::Vector2D::dist function always return a floating-point value. */
TYPED_TEST(Vector2DDistance, StaticWrapper_Dist_AlwaysReturnFloatingPointValue)
{
    [[maybe_unused]] const auto distance = this->_vecA.dist(this->_vecB);
    static_assert(std::is_floating_point_v<decltype(distance)>);
}

/** @} */
