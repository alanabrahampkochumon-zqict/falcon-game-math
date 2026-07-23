/**
 * @file ReflectionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 09, 2026
 *
 * @brief Verify @ref fgm::Mat3 reflection factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3TestSetup.h"

/**
 * @addtogroup T_FGM_Mat3x3_Transforms
 * @{
 */



template <typename T>
class Mat3Reflection: public ::testing::Test
{
protected:
    fgm::Mat3<T> _expectedReflectionX, _expectedReflectionY, _expectedReflectionZ, _expectedReflectionXY,
        _expectedReflectionYZ, _expectedReflectionZX, _expectedReflectionOrigin;

    void SetUp() override
    {
        _expectedReflectionX = { fgm::Vec3{ T(1), T(0), T(0) }, fgm::Vec3{ T(0), T(-1), T(0) },
                                 fgm::Vec3{ T(0), T(0), T(-1) } };

        _expectedReflectionY = { fgm::Vec3{ T(-1), T(0), T(0) }, fgm::Vec3{ T(0), T(1), T(0) },
                                 fgm::Vec3{ T(0), T(0), T(-1) } };

        _expectedReflectionZ = { fgm::Vec3{ T(-1), T(0), T(0) }, fgm::Vec3{ T(0), T(-1), T(0) },
                                 fgm::Vec3{ T(0), T(0), T(1) } };

        _expectedReflectionXY = { fgm::Vec3{ T(1), T(0), T(0) }, fgm::Vec3{ T(0), T(1), T(0) },
                                  fgm::Vec3{ T(0), T(0), T(-1) } };

        _expectedReflectionYZ = { fgm::Vec3{ T(-1), T(0), T(0) }, fgm::Vec3{ T(0), T(1), T(0) },
                                  fgm::Vec3{ T(0), T(0), T(1) } };

        _expectedReflectionZX = { fgm::Vec3{ T(1), T(0), T(0) }, fgm::Vec3{ T(0), T(-1), T(0) },
                                  fgm::Vec3{ T(0), T(0), T(1) } };

        _expectedReflectionOrigin = { fgm::Vec3{ T(-1), T(0), T(0) }, fgm::Vec3{ T(0), T(-1), T(0) },
                                      fgm::Vec3{ T(0), T(0), T(-1) } };
    }
};
/**
 * @brief Test fixture for @ref fgm::Mat3 reflection along coordinate axis, planes, and the origin
 *        parameterized @ref SupportedSignedArithmeticTypes
 */
TYPED_TEST_SUITE(Mat3Reflection, SupportedSignedArithmeticTypes);

//
// template <typename T>
// class Mat3XAxisReflection: public ::testing::Test
// {
// protected:
//     fgm::Mat3<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vec4{ T(-1), T(0) }, fgm::Vec4{ T(0), T(1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Mat3 reflection along x-axis, parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Mat3XAxisReflection, SupportedSignedArithmeticTypes);


/** @brief Verify that reflection transform factory is available at compile time.  */
namespace
{
    // Reflection across axis
    constexpr auto REFLECTION_MAT_X = fgm::Mat3<int>::makeReflection<fgm::reflect::X>();
    static_assert(REFLECTION_MAT_X(0, 0) == 1);
    static_assert(REFLECTION_MAT_X(0, 1) == 0);
    static_assert(REFLECTION_MAT_X(0, 2) == 0);
    static_assert(REFLECTION_MAT_X(1, 0) == 0);
    static_assert(REFLECTION_MAT_X(1, 1) == -1);
    static_assert(REFLECTION_MAT_X(1, 2) == 0);
    static_assert(REFLECTION_MAT_X(2, 0) == 0);
    static_assert(REFLECTION_MAT_X(2, 1) == 0);
    static_assert(REFLECTION_MAT_X(2, 2) == -1);


    constexpr auto REFLECTION_MAT_Y = fgm::Mat3<int>::makeReflection<fgm::reflect::Y>();
    static_assert(REFLECTION_MAT_Y(0, 0) == -1);
    static_assert(REFLECTION_MAT_Y(0, 1) == 0);
    static_assert(REFLECTION_MAT_Y(0, 2) == 0);
    static_assert(REFLECTION_MAT_Y(1, 0) == 0);
    static_assert(REFLECTION_MAT_Y(1, 1) == 1);
    static_assert(REFLECTION_MAT_Y(1, 2) == 0);
    static_assert(REFLECTION_MAT_Y(2, 0) == 0);
    static_assert(REFLECTION_MAT_Y(2, 1) == 0);
    static_assert(REFLECTION_MAT_Y(2, 2) == -1);


    constexpr auto REFLECTION_MAT_Z = fgm::Mat3<int>::makeReflection<fgm::reflect::Z>();
    static_assert(REFLECTION_MAT_Z(0, 0) == -1);
    static_assert(REFLECTION_MAT_Z(0, 1) == 0);
    static_assert(REFLECTION_MAT_Z(0, 2) == 0);
    static_assert(REFLECTION_MAT_Z(1, 0) == 0);
    static_assert(REFLECTION_MAT_Z(1, 1) == -1);
    static_assert(REFLECTION_MAT_Z(1, 2) == 0);
    static_assert(REFLECTION_MAT_Z(2, 0) == 0);
    static_assert(REFLECTION_MAT_Z(2, 1) == 0);
    static_assert(REFLECTION_MAT_Z(2, 2) == 1);


    // Reflection across plane
    constexpr auto REFLECTION_MAT_XY = fgm::Mat3<int>::makeReflection<fgm::reflect::XY>();
    static_assert(REFLECTION_MAT_XY(0, 0) == 1);
    static_assert(REFLECTION_MAT_XY(0, 1) == 0);
    static_assert(REFLECTION_MAT_XY(0, 2) == 0);
    static_assert(REFLECTION_MAT_XY(1, 0) == 0);
    static_assert(REFLECTION_MAT_XY(1, 1) == 1);
    static_assert(REFLECTION_MAT_XY(1, 2) == 0);
    static_assert(REFLECTION_MAT_XY(2, 0) == 0);
    static_assert(REFLECTION_MAT_XY(2, 1) == 0);
    static_assert(REFLECTION_MAT_XY(2, 2) == -1);


    constexpr auto REFLECTION_MAT_YZ = fgm::Mat3<int>::makeReflection<fgm::reflect::YZ>();
    static_assert(REFLECTION_MAT_YZ(0, 0) == -1);
    static_assert(REFLECTION_MAT_YZ(0, 1) == 0);
    static_assert(REFLECTION_MAT_YZ(0, 2) == 0);
    static_assert(REFLECTION_MAT_YZ(1, 0) == 0);
    static_assert(REFLECTION_MAT_YZ(1, 1) == 1);
    static_assert(REFLECTION_MAT_YZ(1, 2) == 0);
    static_assert(REFLECTION_MAT_YZ(2, 0) == 0);
    static_assert(REFLECTION_MAT_YZ(2, 1) == 0);
    static_assert(REFLECTION_MAT_YZ(2, 2) == 1);


    constexpr auto REFLECTION_MAT_ZX = fgm::Mat3<int>::makeReflection<fgm::reflect::ZX>();
    static_assert(REFLECTION_MAT_ZX(0, 0) == 1);
    static_assert(REFLECTION_MAT_ZX(0, 1) == 0);
    static_assert(REFLECTION_MAT_ZX(0, 2) == 0);
    static_assert(REFLECTION_MAT_ZX(1, 0) == 0);
    static_assert(REFLECTION_MAT_ZX(1, 1) == -1);
    static_assert(REFLECTION_MAT_ZX(1, 2) == 0);
    static_assert(REFLECTION_MAT_ZX(2, 0) == 0);
    static_assert(REFLECTION_MAT_ZX(2, 1) == 0);
    static_assert(REFLECTION_MAT_ZX(2, 2) == 1);

    // Reflect across origin
    constexpr auto REFLECTION_MAT_ORIGIN = fgm::Mat3<int>::makeReflection<fgm::reflect::ORIGIN>();
    static_assert(REFLECTION_MAT_ORIGIN(0, 0) == -1);
    static_assert(REFLECTION_MAT_ORIGIN(0, 1) == 0);
    static_assert(REFLECTION_MAT_ORIGIN(0, 2) == 0);
    static_assert(REFLECTION_MAT_ORIGIN(1, 0) == 0);
    static_assert(REFLECTION_MAT_ORIGIN(1, 1) == -1);
    static_assert(REFLECTION_MAT_ORIGIN(1, 2) == 0);
    static_assert(REFLECTION_MAT_ORIGIN(2, 0) == 0);
    static_assert(REFLECTION_MAT_ORIGIN(2, 1) == 0);
    static_assert(REFLECTION_MAT_ORIGIN(2, 2) == -1);


} // namespace


//
// /**************************************
//  *                                    *
//  *          REFLECTION TESTS          *
//  *                                    *
//  **************************************/


/** @brief Verify that reflection transformation factory for x-axis returns a matrix with negated y and z values. */
TYPED_TEST(Mat3Reflection, X_ReturnsMatrixWithNegatedYZ)
{ EXPECT_MAT_EQ(this->_expectedReflectionX, fgm::Mat3<TypeParam>::template makeReflection<fgm::reflect::X>()); }


/** @brief Verify that reflection transformation factory for y-axis returns a matrix with negated x and z values. */
TYPED_TEST(Mat3Reflection, Y_ReturnsMatrixWithNegatedXZ)
{ EXPECT_MAT_EQ(this->_expectedReflectionY, fgm::Mat3<TypeParam>::template makeReflection<fgm::reflect::Y>()); }


/** @brief Verify that reflection transformation factory for z-axis returns a matrix with negated y and z values. */
TYPED_TEST(Mat3Reflection, Z_ReturnsMatrixWithNegatedXY)
{ EXPECT_MAT_EQ(this->_expectedReflectionZ, fgm::Mat3<TypeParam>::template makeReflection<fgm::reflect::Z>()); }


/** @brief Verify that reflection transformation factory for xy-plane returns a matrix with negated z value. */
TYPED_TEST(Mat3Reflection, XY_ReturnsMatrixWithNegatedZ)
{ EXPECT_MAT_EQ(this->_expectedReflectionXY, fgm::Mat3<TypeParam>::template makeReflection<fgm::reflect::XY>()); }


/** @brief Verify that reflection transformation factory for yz-plane returns a matrix with negated x value. */
TYPED_TEST(Mat3Reflection, YZ_ReturnsMatrixWithNegatedX)
{ EXPECT_MAT_EQ(this->_expectedReflectionYZ, fgm::Mat3<TypeParam>::template makeReflection<fgm::reflect::YZ>()); }


/** @brief Verify that reflection transformation factory for zx-plane returns a matrix with negated y value. */
TYPED_TEST(Mat3Reflection, ZX_ReturnsMatrixWithNegatedY)
{ EXPECT_MAT_EQ(this->_expectedReflectionZX, fgm::Mat3<TypeParam>::template makeReflection<fgm::reflect::ZX>()); }


/** @brief Verify that reflection transformation factory for origin returns a matrix with negated x, y and z values. */
TYPED_TEST(Mat3Reflection, Origin_ReturnsMatrixWithNegatedXYZ)
{
    EXPECT_MAT_EQ(this->_expectedReflectionOrigin,
                  fgm::Mat3<TypeParam>::template makeReflection<fgm::reflect::ORIGIN>());
}


// /** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
// TYPED_TEST(Mat3OriginReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat3<TypeParam>::reflect(true, true)); }
//

/** @} */
