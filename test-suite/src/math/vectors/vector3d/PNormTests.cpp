/**
 * @file PNormTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 22, 2026
 *
 * @brief Verify the @ref fgm::Vector3D p-Norm length logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vector3DTestSetup.h"



template <typename T>
class Vector3DManhattanNorm: public testing::Test
{
protected:
    fgm::Vector3D<T> _vec;
    T _norm;

    void SetUp() override
    {
        _vec  = { T(1), T(2), T(4) };
        _norm = T(7);
    }
};
/** @brief Test fixture for @ref fgm::Vector3D manhattan norm, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector3DManhattanNorm, SupportedArithmeticTypes);


template <typename T>
class Vector3DChebyshevNorm: public testing::Test
{
protected:
    fgm::Vector3D<T> _vec;
    T _norm;

    void SetUp() override
    {
        _vec  = { T(1), T(2), T(4) };
        _norm = T(4);
    }
};
/** @brief Test fixture for @ref fgm::Vector3D chebyshev norm, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector3DChebyshevNorm, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec3_Norm
 * @{
 */

/** @brief Verify that pNorm (Manhattan and Chebyshev length) operations are available at compile time. */
namespace
{
    constexpr fgm::Vector3D vector(1, -2, 4);

    // L1 Norm (Manhattan Norm)
    static_assert(vector.manhattanNorm() == 7);
    static_assert(fgm::Vector3D<int>::manhattanNorm(vector) == 7);

    // L∞ Norm (Chebyshev Norm)
    //static_assert(vector.chebyshevNorm() == 2);
    //static_assert(fgm::Vector3D<int>::chebyshevNorm(vector) == 2);

} // namespace


/**************************************
 *                                    *
 *           MANHATTAN NORM           *
 *                                    *
 **************************************/

/** @brief Verify that taking the manhattan norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vector3DManhattanNorm, ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = this->_vec.manhattanNorm();

    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @brief Verify that taking the manhattan norm of a non-unit vector using static variant of
 *        @ref fgm::Vector3D::manhattanNorm returns non-unit scalar.
 */
TYPED_TEST(Vector3DManhattanNorm, StaticWrapper_ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = fgm::Vector3D<TypeParam>::manhattanNorm(this->_vec);

    EXPECT_MAG_EQ(this->_norm, magnitude);
}



/**************************************
 *                                    *
 *           CHEBYSHEV NORM           *
 *                                    *
 **************************************/

/** @brief Verify that taking the chebyshev norm of a non-unit vector returns non-unit scalar. */
//TYPED_TEST(Vector3DChebyshevNorm, ReturnsLongestAbsoluteComponent)
//{
//    const auto magnitude = this->_vec.chebyshevNorm();
//
//    EXPECT_MAG_EQ(this->_norm, magnitude);
//}
//
//
///**
// * @brief Verify that taking the chebyshev norm of a non-unit vector using static variant of
// *        @ref fgm::Vector3D::chebyshevNorm returns non-unit scalar.
// */
//TYPED_TEST(Vector3DChebyshevNorm, StaticWrapper_ReturnsLongestAbsoluteComponent)
//{
//    const auto magnitude = fgm::Vector3D<TypeParam>::chebyshevNorm(this->_vec);
//
//    EXPECT_MAG_EQ(this->_norm, magnitude);
//}

/** @} */
