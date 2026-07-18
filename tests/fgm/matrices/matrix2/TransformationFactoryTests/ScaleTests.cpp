/**
 * @file ScaleTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 09, 2026
 *
 * @brief Verify @ref fgm::Mat2 scale factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "MatrixTestSetup.h"


/**
 * @addtogroup T_FGM_Mat2x2_Transforms
 * @{
 */

template <typename T>
class Mat2UniformScale: public ::testing::Test
{
protected:
    fgm::Mat2<T> _expectedMat;
    T _scale;

    void SetUp() override
    {
        _expectedMat = { fgm::Vec2{ T(5.3821839321), T(0) }, fgm::Vec2{ T(0), T(5.3821839321) } };
        _scale       = T(5.3821839321);
    }
};
/**
 * @brief Test fixture for @ref fgm::Mat2 uniform scale factory, parameterized
 *        @ref SupportedArithmeticTypes
 */
TYPED_TEST_SUITE(Mat2UniformScale, SupportedArithmeticTypes);


template <typename T>
class Mat2NonUniformScale: public ::testing::Test
{
protected:
    fgm::Mat2<T> _expectedMat;
    T _scaleX, _scaleY;

    void SetUp() override
    {
        _expectedMat = { fgm::Vec2{ T(5.3821839321), T(0) }, fgm::Vec2{ T(0), T(8.1234921348) } };
        _scaleX      = T(5.3821839321);
        _scaleY      = T(8.1234921348);
    }
};
/**
 * @brief Test fixture for @ref fgm::Mat2 non-uniform scale factory, parameterized
 *        @ref SupportedArithmeticTypes
 */
TYPED_TEST_SUITE(Mat2NonUniformScale, SupportedArithmeticTypes);


/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that scale transform factory is available at compile time.  */
namespace
{
    // Uniform scale
    constexpr auto U_SCALE_MAT = fgm::Mat2<int>::makeScale(2);
    static_assert(U_SCALE_MAT(0, 0) == 2);
    static_assert(U_SCALE_MAT(0, 1) == 0);
    static_assert(U_SCALE_MAT(1, 0) == 0);
    static_assert(U_SCALE_MAT(1, 1) == 2);

    // Non-uniform scale
    constexpr auto SCALE_MAT = fgm::Mat2<int>::makeScale(2, 3);
    static_assert(SCALE_MAT(0, 0) == 2);
    static_assert(SCALE_MAT(0, 1) == 0);
    static_assert(SCALE_MAT(1, 0) == 0);
    static_assert(SCALE_MAT(1, 1) == 3);

} // namespace


/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that uniform scale transformation factory returns a scale matrix. */
TYPED_TEST(Mat2UniformScale, ReturnsScaleMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat2<TypeParam>::makeScale(this->_scale));
}


/** @brief Verify that non-uniform scale transformation factory returns a non-uniform scale matrix. */
TYPED_TEST(Mat2NonUniformScale, ReturnsScaleMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat2<TypeParam>::makeScale(this->_scaleX, this->_scaleY));
}


/** @} */
