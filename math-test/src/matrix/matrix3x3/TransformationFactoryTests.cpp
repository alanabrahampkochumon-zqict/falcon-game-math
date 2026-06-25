/**
 * @file TransformationFactoryTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: June 25, 2026
 *
 * @brief Verify @ref fgm::Matrix3 transformation factory function (E.g: MakeRotation, MakeScale, etc.) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



template <typename T>
class Matrix3Rotation: public testing::Test
{
protected:
    using FP_T  = T::first_type;  // FP_T -> Floating-point Type
    using COM_T = T::second_type; // COM_T -> Common Type

    FP_T _angle;
    fgm::Matrix3<COM_T> _expectedMatX, _expectedMatY;


    void SetUp() override
    {
        _angle = fgm::constants::PI<FP_T> / FP_T(2.0);
#ifdef FMG_LEFT_HANDED
        _expectedMatX = { fgm::Vector3{ COM_T(1), COM_T(0), COM_T(0) }, fgm::Vector3{ COM_T(0), COM_T(0), COM_T(-1) },
                         fgm::Vector3 {
                             COM_T(0),
                             COM_T(1),
                             COM_T(0)
                         } };
        _expectedMatY = { fgm::Vector3{ COM_T(0), COM_T(0), COM_T(1) }, fgm::Vector3{ COM_T(0), COM_T(1), COM_T(0) },
                         fgm::Vector3{ COM_T(-1), COM_T(0), COM_T(0) } };
#else
        _expectedMatX = { fgm::Vector3{ COM_T(1), COM_T(0), COM_T(0) }, fgm::Vector3{ COM_T(0), COM_T(0), COM_T(1) },
            fgm::Vector3{ COM_T(0), COM_T(-1), COM_T(0) } };
        _expectedMatY = { fgm::Vector3{ COM_T(0), COM_T(0), COM_T(-1) }, fgm::Vector3{ COM_T(0), COM_T(1), COM_T(0) },
                         fgm::Vector3{ COM_T(1), COM_T(0), COM_T(0) } };

#endif
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix3 rotation factory, parameterized
 *        @ref SupportedSignedArithmeticFloatingTypePair
 */
TYPED_TEST_SUITE(Matrix3Rotation, SupportedSignedArithmeticFloatingTypePair);


template <typename T>
class Matrix3UniformScale: public testing::Test
{
protected:
    fgm::Matrix3<T> _expectedMat;
    T _scale;

    void SetUp() override
    {
        _expectedMat = { fgm::Vector3{ T(5.3821839321), T(0), T(0) }, fgm::Vector3{ T(0), T(5.3821839321), T(0) },
                         fgm::Vector3{ T(0), T(0), T(5.3821839321) } };
        _scale       = T(5.3821839321);
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix3 uniform scale factory, parameterized
 *        @ref SupportedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix3UniformScale, SupportedArithmeticTypes);


template <typename T>
class Matrix3NonUniformScale: public ::testing::Test
{
protected:
    fgm::Matrix3<T> _expectedMat;
    T _scaleX, _scaleY, _scaleZ;

    void SetUp() override
    {
        _expectedMat = { fgm::Vector3{ T(5.3821839321), T(0), T(0) }, fgm::Vector3{ T(0), T(8.1234921348), T(0) },
                         fgm::Vector3{ T(0), T(0), T(0.12348921340) } };
        _scaleX      = T(5.3821839321);
        _scaleY      = T(8.1234921348);
        _scaleZ      = T(0.12348921340);
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix3 non-uniform scale factory, parameterized
 *        @ref SupportedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix3NonUniformScale, SupportedArithmeticTypes);


// template <typename T>
// class Matrix3NoReflection: public ::testing::Test
// {
// protected:
//     fgm::Matrix3<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vector3{ T(1), T(0) }, fgm::Vector3{ T(0), T(1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix3 reflection along x-axis, parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Matrix3NoReflection, SupportedSignedArithmeticTypes);
//
//
// template <typename T>
// class Matrix3XAxisReflection: public ::testing::Test
// {
// protected:
//     fgm::Matrix3<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vector3{ T(-1), T(0) }, fgm::Vector3{ T(0), T(1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix3 reflection along x-axis, parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Matrix3XAxisReflection, SupportedSignedArithmeticTypes);
//
//
// template <typename T>
// class Matrix3YAxisReflection: public ::testing::Test
// {
// protected:
//     fgm::Matrix3<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vector3{ T(1), T(0) }, fgm::Vector3{ T(0), T(-1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix3 reflection along y-axis, parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Matrix3YAxisReflection, SupportedSignedArithmeticTypes);
//
//
// template <typename T>
// class Matrix3OriginReflection: public ::testing::Test
// {
// protected:
//     fgm::Matrix3<T> _expectedMat;
//
//     void SetUp() override { _expectedMat = { fgm::Vector3{ T(-1), T(0) }, fgm::Vector3{ T(0), T(-1) } }; }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix3 reflection along the origin(0, 0), parameterized
//  *        @ref SupportedSignedArithmeticTypes
//  */
// TYPED_TEST_SUITE(Matrix3OriginReflection, SupportedSignedArithmeticTypes);
//


/**
 * @addtogroup T_FGM_Mat3x3_Transforms
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
        constexpr auto ROTATION_MAT = fgm::Matrix3<int>::rotate(fgm::constants::PI<float>);
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
        constexpr auto U_SCALE_MAT = fgm::Matrix3<int>::makeScale(2);
        static_assert(U_SCALE_MAT(0, 0) == 2);
        static_assert(U_SCALE_MAT(0, 1) == 0);
        static_assert(U_SCALE_MAT(0, 2) == 0);
        static_assert(U_SCALE_MAT(1, 0) == 0);
        static_assert(U_SCALE_MAT(1, 1) == 2);
        static_assert(U_SCALE_MAT(1, 2) == 0);
        static_assert(U_SCALE_MAT(2, 0) == 0);
        static_assert(U_SCALE_MAT(2, 1) == 0);
        static_assert(U_SCALE_MAT(2, 2) == 2);

        // Non-uniform scale
        constexpr auto SCALE_MAT = fgm::Matrix3<int>::makeScale(2, 3, 4);
        static_assert(SCALE_MAT(0, 0) == 2);
        static_assert(SCALE_MAT(0, 1) == 0);
        static_assert(SCALE_MAT(0, 2) == 0);
        static_assert(SCALE_MAT(1, 0) == 0);
        static_assert(SCALE_MAT(1, 1) == 3);
        static_assert(SCALE_MAT(1, 2) == 0);
        static_assert(SCALE_MAT(2, 0) == 0);
        static_assert(SCALE_MAT(2, 1) == 0);
        static_assert(SCALE_MAT(2, 2) == 4);
    } // namespace


    // /** @brief Verify that reflection transform factory is available at compile time.  */
    // namespace
    // {
    //     // Reflection through origin
    //     constexpr auto REFLECTION_MAT = fgm::Matrix3<int>::reflect(true, true);
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
TYPED_TEST(Matrix3Rotation, X_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatX, fgm::Matrix3<typename TypeParam::first_type>::makeRotationX(this->_angle)); }


/** @brief Verify that rotation transformation factory for y returns a rotation matrix. */
TYPED_TEST(Matrix3Rotation, Y_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatY, fgm::Matrix3<typename TypeParam::first_type>::makeRotationY(this->_angle)); }


/**************************************
 *                                    *
 *            SCALE TESTS             *
 *                                    *
 **************************************/

/** @brief Verify that uniform scale transformation factory returns a scale matrix. */
TYPED_TEST(Matrix3UniformScale, ReturnsScaleMatrix)
{ EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix3<TypeParam>::makeScale(this->_scale)); }


/** @brief Verify that non-uniform scale transformation factory returns a non-uniform scale matrix. */
TYPED_TEST(Matrix3NonUniformScale, ReturnsScaleMatrix)
{ EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix3<TypeParam>::makeScale(this->_scaleX, this->_scaleY, this->_scaleZ)); }


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
// TYPED_TEST(Matrix3NoReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix3<TypeParam>::reflect(false, false)); }
//
//
// /** @brief Verify that reflection transformation factory for x-axis returns a reflection matrix. */
// TYPED_TEST(Matrix3XAxisReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix3<TypeParam>::reflect(true, false)); }
//
//
// /** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
// TYPED_TEST(Matrix3YAxisReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix3<TypeParam>::reflect(false, true)); }
//
//
// /** @brief Verify that reflection transformation factory for y-axis returns a reflection matrix. */
// TYPED_TEST(Matrix3OriginReflection, ReturnsReflectionMatrix)
// { EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix3<TypeParam>::reflect(true, true)); }
//
// /** @} */
