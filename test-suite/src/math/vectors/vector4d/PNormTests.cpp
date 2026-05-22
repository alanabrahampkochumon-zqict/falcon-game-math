/**
 * @file PNormTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 22, 2026
 *
 * @brief Verify the @ref fgm::Vector4D p-Norm length logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "Vector4DTestSetup.h"



template <typename T>
class Vector4DManhattanNorm: public testing::Test
{
protected:
    fgm::Vector4D<T> _vec;
    T _norm;

    void SetUp() override
    {
        _vec  = { T(1), T(2), T(3), T(4) };
        _norm = T(10);
    }
};
/** @brief Test fixture for @ref fgm::Vector4D manhattan norm, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DManhattanNorm, SupportedArithmeticTypes);


template <typename T>
class Vector4DChebyshevNorm: public testing::Test
{
protected:
    fgm::Vector4D<T> _vec;
    T _norm;

    void SetUp() override
    {
        _vec  = { T(1), T(2), T(3), T(4) };
        _norm = T(4);
    }
};
/** @brief Test fixture for @ref fgm::Vector4D chebyshev norm, parameterized by @ref SupportedArithmeticTypes. */
TYPED_TEST_SUITE(Vector4DChebyshevNorm, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Vec4_Norm
 * @{
 */

/** @brief Verify that pNorm (Manhattan and Chebyshev length) operations are available at compile time. */
namespace
{
    constexpr fgm::Vector4D vector(1, -2, 3, -4);

    // L1 Norm (Manhattan Norm)
    static_assert(vector.manhattanNorm() == 10);
    static_assert(fgm::Vector4D<int>::manhattanNorm(vector) == 10);

    //// L∞ Norm (Chebyshev Norm)
    //static_assert(vector.chebyshevNorm() == 4);
    //static_assert(fgm::Vector4D<int>::chebyshevNorm(vector) == 4);

} // namespace


/**************************************
 *                                    *
 *           MANHATTAN NORM           *
 *                                    *
 **************************************/

/** @brief Verify that taking the manhattan norm of a non-unit vector returns non-unit scalar. */
TYPED_TEST(Vector4DManhattanNorm, ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = this->_vec.manhattanNorm();

    EXPECT_MAG_EQ(this->_norm, magnitude);
}


/**
 * @brief Verify that taking the manhattan norm of a non-unit vector using static variant of
 *        @ref fgm::Vector4D::manhattanNorm returns non-unit scalar.
 */
TYPED_TEST(Vector4DManhattanNorm, StaticWrapper_ReturnsSumOfAbsoluteValueOfComponents)
{
    const auto magnitude = fgm::Vector4D<TypeParam>::manhattanNorm(this->_vec);

    EXPECT_MAG_EQ(this->_norm, magnitude);
}



/**************************************
 *                                    *
 *           CHEBYSHEV NORM           *
 *                                    *
 **************************************/

///** @brief Verify that taking the chebyshev norm of a non-unit vector returns non-unit scalar. */
//TYPED_TEST(Vector4DChebyshevNorm, ReturnsLongestAbsoluteComponent)
//{
//    const auto magnitude = this->_vec.chebyshevNorm();
//
//    EXPECT_MAG_EQ(this->_norm, magnitude);
//}
//
//
///**
// * @brief Verify that taking the chebyshev norm of a non-unit vector using static variant of
// *        @ref fgm::Vector4D::chebyshevNorm returns non-unit scalar.
// */
//TYPED_TEST(Vector4DChebyshevNorm, StaticWrapper_ReturnsLongestAbsoluteComponent)
//{
//    const auto magnitude = fgm::Vector4D<TypeParam>::chebyshevNorm(this->_vec);
//
//    EXPECT_MAG_EQ(this->_norm, magnitude);
//}

/** @} */
