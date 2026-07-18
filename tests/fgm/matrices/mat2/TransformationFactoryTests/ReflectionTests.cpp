/**
 * @file ReflectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 09, 2026
 *
 * @brief Verify @ref fgm::Mat3 reflection factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"



/**
 * @addtogroup T_FGM_Mat2x2_Transforms
 * @{
 */

template <typename T>
class Mat2NoReflection: public ::testing::Test
{
protected:
    fgm::Mat2<T> _expectedMat;

    void SetUp() override { _expectedMat = { fgm::Vec2{ T(1), T(0) }, fgm::Vec2{ T(0), T(1) } }; }
};
/**
 * @brief Test fixture for @ref fgm::Mat2 reflection along x-axis, parameterized
 *        @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Mat2NoReflection, SupportedSignedArithmeticTypes);


template <typename T>
class Mat2XAxisReflection: public ::testing::Test
{
protected:
    fgm::Mat2<T> _expectedMat;

    void SetUp() override { _expectedMat = { fgm::Vec2{ T(-1), T(0) }, fgm::Vec2{ T(0), T(1) } }; }
};
/**
 * @brief Test fixture for @ref fgm::Mat2 reflection along x-axis, parameterized
 *        @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Mat2XAxisReflection, SupportedSignedArithmeticTypes);


template <typename T>
class Mat2YAxisReflection: public ::testing::Test
{
protected:
    fgm::Mat2<T> _expectedMat;

    void SetUp() override { _expectedMat = { fgm::Vec2{ T(1), T(0) }, fgm::Vec2{ T(0), T(-1) } }; }
};
/**
 * @brief Test fixture for @ref fgm::Mat2 reflection along y-axis, parameterized
 *        @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Mat2YAxisReflection, SupportedSignedArithmeticTypes);


template <typename T>
class Mat2OriginReflection: public ::testing::Test
{
protected:
    fgm::Mat2<T> _expectedMat;

    void SetUp() override { _expectedMat = { fgm::Vec2{ T(-1), T(0) }, fgm::Vec2{ T(0), T(-1) } }; }
};
/**
 * @brief Test fixture for @ref fgm::Mat2 reflection along the origin(0, 0), parameterized
 *        @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Mat2OriginReflection, SupportedSignedArithmeticTypes);



/** @brief Verify that reflection transform factory is available at compile time.  */
namespace
{
    // Reflection through origin
    constexpr auto REFLECTION_MAT = fgm::Mat2<int>::makeReflection(true, true);
    static_assert(REFLECTION_MAT(0, 0) == -1);
    static_assert(REFLECTION_MAT(0, 1) == 0);
    static_assert(REFLECTION_MAT(1, 0) == 0);
    static_assert(REFLECTION_MAT(1, 1) == -1);

} // namespace



/**
 * @brief Verify that reflection transformation factory for no reflection along any axis
 *        returns a reflection matrix.
 */
TYPED_TEST(Mat2NoReflection, ReturnsReflectionMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat2<TypeParam>::makeReflection(false, false));
}


/** @brief Verify that reflection transformation factory for x-axis returns a reflection matrix. */
TYPED_TEST(Mat2XAxisReflection, ReturnsReflectionMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat2<TypeParam>::makeReflection(true, false));
}


/** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
TYPED_TEST(Mat2YAxisReflection, ReturnsReflectionMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat2<TypeParam>::makeReflection(false, true));
}


/** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
TYPED_TEST(Mat2OriginReflection, ReturnsReflectionMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat2<TypeParam>::makeReflection(true, true));
}

/** @} */
