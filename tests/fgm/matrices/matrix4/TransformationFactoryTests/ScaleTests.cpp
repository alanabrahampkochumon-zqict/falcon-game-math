/**
 * @file ScaleTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 08, 2026
 *
 * @brief Verify @ref fgm::Matrix4 scale factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "MatrixTestSetup.h"


/**
 * @addtogroup T_FGM_Mat4x4_Transforms
 * @{
 */


template <typename T>
class Matrix4UniformScale: public testing::Test
{
protected:
    fgm::Matrix4<T> _expectedMat;
    T _scale;

    void SetUp() override
    {
        _expectedMat = { fgm::Vec4{ T(5.3821839321), T(0), T(0), T(0) },
                         fgm::Vec4{ T(0), T(5.3821839321), T(0), T(0) },
                         fgm::Vec4{ T(0), T(0), T(5.3821839321), T(0) }, fgm::Vec4{ T(0), T(0), T(0), T(1) } };
        _scale       = T(5.3821839321);
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix4 uniform scale factory, parameterized
 *        @ref SupportedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix4UniformScale, SupportedArithmeticTypes);


template <typename T>
class Matrix4NonUniformScale: public testing::Test
{
protected:
    fgm::Matrix4<T> _expectedMat;
    T _scaleX, _scaleY, _scaleZ;

    void SetUp() override
    {
        _expectedMat = { fgm::Vec4{ T(5.3821839321), T(0), T(0), T(0) },
                         fgm::Vec4{ T(0), T(8.1234921348), T(0), T(0) },
                         fgm::Vec4{ T(0), T(0), T(0.12348921340), T(0) }, fgm::Vec4{ T(0), T(0), T(0), T(1) } };
        _scaleX      = T(5.3821839321);
        _scaleY      = T(8.1234921348);
        _scaleZ      = T(0.12348921340);
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix4 non-uniform scale factory, parameterized
 *        @ref SupportedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix4NonUniformScale, SupportedArithmeticTypes);



/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that scale transform factory is available at compile time.  */
namespace
{
    // Uniform scale
    constexpr auto U_SCALE_MAT = fgm::Matrix4<int>::makeScale(2);
    static_assert(U_SCALE_MAT(0, 0) == 2);
    static_assert(U_SCALE_MAT(0, 1) == 0);
    static_assert(U_SCALE_MAT(0, 2) == 0);
    static_assert(U_SCALE_MAT(0, 3) == 0);
    static_assert(U_SCALE_MAT(1, 0) == 0);
    static_assert(U_SCALE_MAT(1, 1) == 2);
    static_assert(U_SCALE_MAT(1, 2) == 0);
    static_assert(U_SCALE_MAT(1, 3) == 0);
    static_assert(U_SCALE_MAT(2, 0) == 0);
    static_assert(U_SCALE_MAT(2, 1) == 0);
    static_assert(U_SCALE_MAT(2, 2) == 2);
    static_assert(U_SCALE_MAT(2, 3) == 0);
    static_assert(U_SCALE_MAT(3, 0) == 0);
    static_assert(U_SCALE_MAT(3, 1) == 0);
    static_assert(U_SCALE_MAT(3, 2) == 0);
    static_assert(U_SCALE_MAT(3, 3) == 1);

    // Non-uniform scale
    constexpr auto SCALE_MAT = fgm::Matrix4<int>::makeScale(2, 3, 4);
    static_assert(SCALE_MAT(0, 0) == 2);
    static_assert(SCALE_MAT(0, 1) == 0);
    static_assert(SCALE_MAT(0, 2) == 0);
    static_assert(SCALE_MAT(0, 3) == 0);
    static_assert(SCALE_MAT(1, 0) == 0);
    static_assert(SCALE_MAT(1, 1) == 3);
    static_assert(SCALE_MAT(1, 2) == 0);
    static_assert(SCALE_MAT(1, 3) == 0);
    static_assert(SCALE_MAT(2, 0) == 0);
    static_assert(SCALE_MAT(2, 1) == 0);
    static_assert(SCALE_MAT(2, 2) == 4);
    static_assert(SCALE_MAT(2, 3) == 0);
    static_assert(SCALE_MAT(3, 0) == 0);
    static_assert(SCALE_MAT(3, 1) == 0);
    static_assert(SCALE_MAT(3, 2) == 0);
    static_assert(SCALE_MAT(3, 3) == 1);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that uniform scale transformation factory returns a scale matrix. */
TYPED_TEST(Matrix4UniformScale, ReturnsScaleMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix4<TypeParam>::makeScale(this->_scale));
}


/** @brief Verify that non-uniform scale transformation factory returns a non-uniform scale matrix. */
TYPED_TEST(Matrix4NonUniformScale, ReturnsScaleMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix4<TypeParam>::makeScale(this->_scaleX, this->_scaleY, this->_scaleZ));
}

/** @} */
