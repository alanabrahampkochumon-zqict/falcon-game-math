/**
 * @file TransformationFactoryTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 04, 2026
 *
 * @brief Verify @ref fgm::Matrix4 transformation factory function (E.g: MakeRotation, MakeScale, etc.) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix4Rotation: public testing::Test
{
protected:
    using FP_T  = T::first_type;  // FP_T -> Floating-point Type
    using COM_T = T::second_type; // COM_T -> Common Type

    FP_T _angle;
    fgm::Matrix4<COM_T> _expectedMatX, _expectedMatY, _expectedMatZ;


    void SetUp() override
    {
        _angle = fgm::constants::PI<FP_T> / FP_T(2.0);

#ifdef FMG_LEFT_HANDED
        _expectedMatX = { fgm::Vector4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                          fgm::Vector4{ COM_T(0), COM_T(0), COM_T(-1), COM_T(0) },
                          fgm::Vector4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) }, fgm::Vector4 {
                              COM_T(0),
                              COM_T(0),
                              COM_T(0),
                              COM_T(1)
                          } };
        _expectedMatY = { fgm::Vector4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                          fgm::Vector4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                          fgm::Vector4{ COM_T(-1), COM_T(0), COM_T(0), COM_T(0) }, fgm::Vector4 {
                              COM_T(0),
                              COM_T(0),
                              COM_T(0),
                              COM_T(1)
                          } };
        _expectedMatZ = { fgm::Vector4{ COM_T(0), COM_T(-1), COM_T(0), COM_T(0) },
                          fgm::Vector4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                          fgm::Vector4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) }, fgm::Vector4 {
                              COM_T(0),
                              COM_T(0),
                              COM_T(0),
                              COM_T(1)
                          } };
#else
        _expectedMatX = { fgm::Vector4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                          fgm::Vector4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                          fgm::Vector4{ COM_T(0), COM_T(-1), COM_T(0), COM_T(0) },
                          fgm::Vector4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };
        _expectedMatY = { fgm::Vector4{ COM_T(0), COM_T(0), COM_T(-1), COM_T(0) },
                          fgm::Vector4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                          fgm::Vector4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                          fgm::Vector4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };
        _expectedMatZ = { fgm::Vector4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                          fgm::Vector4{ COM_T(-1), COM_T(0), COM_T(0), COM_T(0) },
                          fgm::Vector4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                          fgm::Vector4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };

#endif
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix4 rotation factory, parameterized
 *        @ref SupportedSignedArithmeticFloatingTypePair
 */
TYPED_TEST_SUITE(Matrix4Rotation, SupportedSignedArithmeticFloatingTypePair);


template <typename T>
class Matrix4UniformScale: public testing::Test
{
protected:
    fgm::Matrix4<T> _expectedMat;
    T _scale;

    void SetUp() override
    {
        _expectedMat = { fgm::Vector4{ T(5.3821839321), T(0), T(0), T(0) },
                         fgm::Vector4{ T(0), T(5.3821839321), T(0), T(0) },
                         fgm::Vector4{ T(0), T(0), T(5.3821839321), T(0) }, fgm::Vector4{ T(0), T(0), T(0), T(1) } };
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
        _expectedMat = { fgm::Vector4{ T(5.3821839321), T(0), T(0), T(0) },
                         fgm::Vector4{ T(0), T(8.1234921348), T(0), T(0) },
                         fgm::Vector4{ T(0), T(0), T(0.12348921340), T(0) }, fgm::Vector4{ T(0), T(0), T(0), T(1) } };
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


// template <typename T>
// class Matrix4NoReflection: public ::testing::Test
// {
// protected:
//     fgm::Matrix4<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vector4{ T(1), T(0) }, fgm::Vector4{ T(0), T(1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix4 reflection along x-axis, parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Matrix4NoReflection, SupportedSignedArithmeticTypes);
//
//
// template <typename T>
// class Matrix4XAxisReflection: public ::testing::Test
// {
// protected:
//     fgm::Matrix4<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vector4{ T(-1), T(0) }, fgm::Vector4{ T(0), T(1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix4 reflection along x-axis, parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Matrix4XAxisReflection, SupportedSignedArithmeticTypes);
//
//
// template <typename T>
// class Matrix4YAxisReflection: public ::testing::Test
// {
// protected:
//     fgm::Matrix4<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vector4{ T(1), T(0) }, fgm::Vector4{ T(0), T(-1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix4 reflection along y-axis, parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Matrix4YAxisReflection, SupportedSignedArithmeticTypes);
//
//
// template <typename T>
// class Matrix4OriginReflection: public ::testing::Test
// {
// protected:
//     fgm::Matrix4<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vector4{ T(-1), T(0) }, fgm::Vector4{ T(0), T(-1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix4 reflection along the origin(0, 0), parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Matrix4OriginReflection, SupportedSignedArithmeticTypes);
//

template <typename T>
class Matrix4Affine: public testing::Test
{
protected:
    fgm::Matrix3<T> _linearTransform;
    fgm::Vector3<T> _translation;
    fgm::Matrix4<T> _expectedMat;

    void SetUp() override
    {
        _linearTransform = { fgm::Vector3{ T(1.2341234), T(2.31419123), T(3.10234212) },
                             fgm::Vector3{ T(15.123949182), T(0.93819231), T(3.10234212) },
                             fgm::Vector3{ T(5.8329141), T(12.2319382), T(8.34232112) } };
        _translation     = { T(1.2398412349), T(12.1234892134), T(35.012342380) };

        _expectedMat = { fgm::Vector4{ T(1.2341234), T(2.31419123), T(3.10234212), T(0) },
                         fgm::Vector4{ T(15.123949182), T(0.93819231), T(3.10234212), T(0) },
                         fgm::Vector4{ T(5.8329141), T(12.2319382), T(8.34232112), T(0) },
                         fgm::Vector4{ T(1.2398412349), T(12.1234892134), T(35.012342380), T(1) } };
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix4 affine factory, parameterized
 *        @ref SupportedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix4Affine, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Mat4x4_Transforms
 * @{
 */

/**************************************
 *                                    *
 *           STATIC TESTS             *
 *                                    *
 **************************************/

namespace
{
    /**
     * @brief Verify that rotation transform factory is available at compile time.
     *         Only available for **C++26 and above** since trigonometric functions
     *         are constexpr starting from C++26.
     */
    namespace
    {
#if __cplusplus >= 202603L // TODO: Add static tests after making trig functions constexpr
        // Rotation matrix for 180° or 2π radians
        constexpr auto ROTATION_MAT = fgm::Matrix4<int>::rotate(fgm::constants::PI<float>);
        static_assert(ROTATION_MAT(0, 0) == 1);
        static_assert(ROTATION_MAT(0, 1) == 0);
        static_assert(ROTATION_MAT(0, 2) == 0);
        static_assert(ROTATION_MAT(1, 0) == 0);
        static_assert(ROTATION_MAT(1, 1) == -1);
        static_assert(ROTATION_MAT(1, 2) == 0);
        static_assert(ROTATION_MAT(2, 0) == 0);
        static_assert(ROTATION_MAT(2, 1) == 0);
        static_assert(ROTATION_MAT(2, 2) == -1);
#endif

    } // namespace


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


    // /** @brief Verify that reflection transform factory is available at compile time.  */
    // namespace
    // {
    //     // Reflection through origin
    //     constexpr auto REFLECTION_MAT = fgm::Matrix4<int>::reflect(true, true);
    //     static_assert(REFLECTION_MAT(0, 0) == -1);
    //     static_assert(REFLECTION_MAT(0, 1) == 0);
    //     static_assert(REFLECTION_MAT(1, 0) == 0);
    //     static_assert(REFLECTION_MAT(1, 1) == -1);

    // } // namespace
} // namespace



/**************************************
 *                                    *
 *           ROTATION TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that rotation transformation factory for x returns a rotation matrix. */
TYPED_TEST(Matrix4Rotation, X_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatX, fgm::Matrix4<typename TypeParam::first_type>::makeRotationX(this->_angle)); }


/** @brief Verify that rotation transformation factory for y returns a rotation matrix. */
TYPED_TEST(Matrix4Rotation, Y_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatY, fgm::Matrix4<typename TypeParam::first_type>::makeRotationY(this->_angle)); }


/** @brief Verify that rotation transformation factory for y returns a rotation matrix. */
TYPED_TEST(Matrix4Rotation, Z_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatZ, fgm::Matrix4<typename TypeParam::first_type>::makeRotationZ(this->_angle)); }


/**************************************
 *                                    *
 *            SCALE TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that uniform scale transformation factory returns a scale matrix. */
TYPED_TEST(Matrix4UniformScale, ReturnsScaleMatrix)
{ EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix4<TypeParam>::makeScale(this->_scale)); }


/** @brief Verify that non-uniform scale transformation factory returns a non-uniform scale matrix. */
TYPED_TEST(Matrix4NonUniformScale, ReturnsScaleMatrix)
{ EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix4<TypeParam>::makeScale(this->_scaleX, this->_scaleY, this->_scaleZ)); }



/**************************************
 *                                    *
 *            AFFINE TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that makeAffine returns a matrix with combined linear transform and translation vector. */
TYPED_TEST(Matrix4Affine, ReturnsCombinedLinearTransformAndTranslation)
{ EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix4<TypeParam>::makeAffine(this->_linearTransform, this->_translation)); }


//
// /**************************************
//  *                                    *
//  *          REFLECTION TESTS          *
//  *                                    *
//  **************************************/
//
// /**
//  * @brief Verify that reflection transformation factory for no reflection along any axis
//  *        returns a reflection matrix.
//  */
// TYPED_TEST(Matrix4NoReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix4<TypeParam>::reflect(false, false)); }
//
//
// /** @brief Verify that reflection transformation factory for x-axis returns a reflection matrix. */
// TYPED_TEST(Matrix4XAxisReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix4<TypeParam>::reflect(true, false)); }
//
//
// /** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
// TYPED_TEST(Matrix4YAxisReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix4<TypeParam>::reflect(false, true)); }
//
//
// /** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
// TYPED_TEST(Matrix4OriginReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix4<TypeParam>::reflect(true, true)); }
//
// /** @} */
