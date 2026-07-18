/**
 * @file ReflectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 09, 2026
 *
 * @brief Verify @ref fgm::Matrix3 reflection factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**
 * @addtogroup T_FGM_Mat2x2_Transforms
 * @{
 */

template <typename T>
class Matrix2NoReflection: public ::testing::Test
{
protected:
    fgm::Matrix2<T> _expectedMat;

    void SetUp() override { _expectedMat = { fgm::Vec2{ T(1), T(0) }, fgm::Vec2{ T(0), T(1) } }; }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2 reflection along x-axis, parameterized
 *        @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix2NoReflection, SupportedSignedArithmeticTypes);


template <typename T>
class Matrix2XAxisReflection: public ::testing::Test
{
protected:
    fgm::Matrix2<T> _expectedMat;

    void SetUp() override { _expectedMat = { fgm::Vec2{ T(-1), T(0) }, fgm::Vec2{ T(0), T(1) } }; }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2 reflection along x-axis, parameterized
 *        @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix2XAxisReflection, SupportedSignedArithmeticTypes);


template <typename T>
class Matrix2YAxisReflection: public ::testing::Test
{
protected:
    fgm::Matrix2<T> _expectedMat;

    void SetUp() override { _expectedMat = { fgm::Vec2{ T(1), T(0) }, fgm::Vec2{ T(0), T(-1) } }; }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2 reflection along y-axis, parameterized
 *        @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix2YAxisReflection, SupportedSignedArithmeticTypes);


template <typename T>
class Matrix2OriginReflection: public ::testing::Test
{
protected:
    fgm::Matrix2<T> _expectedMat;

    void SetUp() override { _expectedMat = { fgm::Vec2{ T(-1), T(0) }, fgm::Vec2{ T(0), T(-1) } }; }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2 reflection along the origin(0, 0), parameterized
 *        @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix2OriginReflection, SupportedSignedArithmeticTypes);



/** @brief Verify that reflection transform factory is available at compile time.  */
namespace
{
    // Reflection through origin
    constexpr auto REFLECTION_MAT = fgm::Matrix2<int>::makeReflection(true, true);
    static_assert(REFLECTION_MAT(0, 0) == -1);
    static_assert(REFLECTION_MAT(0, 1) == 0);
    static_assert(REFLECTION_MAT(1, 0) == 0);
    static_assert(REFLECTION_MAT(1, 1) == -1);

} // namespace



/**
 * @brief Verify that reflection transformation factory for no reflection along any axis
 *        returns a reflection matrix.
 */
TYPED_TEST(Matrix2NoReflection, ReturnsReflectionMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2<TypeParam>::makeReflection(false, false));
}


/** @brief Verify that reflection transformation factory for x-axis returns a reflection matrix. */
TYPED_TEST(Matrix2XAxisReflection, ReturnsReflectionMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2<TypeParam>::makeReflection(true, false));
}


/** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
TYPED_TEST(Matrix2YAxisReflection, ReturnsReflectionMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2<TypeParam>::makeReflection(false, true));
}


/** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
TYPED_TEST(Matrix2OriginReflection, ReturnsReflectionMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2<TypeParam>::makeReflection(true, true));
}

/** @} */
