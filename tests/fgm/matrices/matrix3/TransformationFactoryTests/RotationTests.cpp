/**
 * @file RotationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 08, 2026
 *
 * @brief Verify @ref fgm::Matrix3 rotation factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**
 * @addtogroup T_FGM_Mat3x3_Transforms
 * @{
 */


template <typename T>
class Matrix3Rotation: public testing::Test
{
protected:
    using FP_T  = T::first_type;  // FP_T -> Floating-point Type
    using COM_T = T::second_type; // COM_T -> Common Type

    FP_T _angle;
    fgm::Matrix3<COM_T> _expectedMatX, _expectedMatY, _expectedMatZ;


    void SetUp() override
    {
        _angle = fgm::constants::PI<FP_T> / FP_T(2.0);
#ifdef FGM_LEFT_HANDED
        _expectedMatX = { fgm::Vec3{ COM_T(1), COM_T(0), COM_T(0) }, fgm::Vec3{ COM_T(0), COM_T(0), COM_T(-1) },
                          fgm::Vec3 {
                              COM_T(0),
                              COM_T(1),
                              COM_T(0)
                          } };
        _expectedMatY = { fgm::Vec3{ COM_T(0), COM_T(0), COM_T(1) }, fgm::Vec3{ COM_T(0), COM_T(1), COM_T(0) },
                          fgm::Vec3 {
                              COM_T(-1),
                              COM_T(0),
                              COM_T(0)
                          } };
        _expectedMatZ = { fgm::Vec3{ COM_T(0), COM_T(-1), COM_T(0) }, fgm::Vec3{ COM_T(1), COM_T(0), COM_T(0) },
                          fgm::Vec3 {
                              COM_T(0),
                              COM_T(0),
                              COM_T(1)
                          } };
#else
        _expectedMatX = { fgm::Vec3{ COM_T(1), COM_T(0), COM_T(0) }, fgm::Vec3{ COM_T(0), COM_T(0), COM_T(1) },
                          fgm::Vec3{ COM_T(0), COM_T(-1), COM_T(0) } };
        _expectedMatY = { fgm::Vec3{ COM_T(0), COM_T(0), COM_T(-1) }, fgm::Vec3{ COM_T(0), COM_T(1), COM_T(0) },
                          fgm::Vec3{ COM_T(1), COM_T(0), COM_T(0) } };
        _expectedMatZ = { fgm::Vec3{ COM_T(0), COM_T(1), COM_T(0) }, fgm::Vec3{ COM_T(-1), COM_T(0), COM_T(0) },
                          fgm::Vec3{ COM_T(0), COM_T(0), COM_T(1) } };

#endif
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix3 rotation factory, parameterized
 *        @ref SupportedSignedArithmeticFloatingTypePair
 */
TYPED_TEST_SUITE(Matrix3Rotation, SupportedSignedArithmeticFloatingTypePair);



template <typename T>
class Matrix3FloatRotation: public testing::Test
{
protected:
    T _angle;
    fgm::Matrix3<T> _expectedMatX, _expectedMatY, _expectedMatZ, _expectedMatXYZ;


    void SetUp() override
    {
        _angle = fgm::constants::PI<T> / T(4.0);

#ifdef FGM_LEFT_HANDED
        _expectedMatX = { fgm::Vec3{ T(1.0), T(0.0), T(0.0) },
                          fgm::Vec3{ T(0.0), T(0.70710678118654757), T(-0.70710678118654757) }, fgm::Vec3 {
                              T(0.0),
                              T(0.70710678118654757),
                              T(0.70710678118654757)
                          } };

        _expectedMatY = { fgm::Vec3{ T(0.70710678118654757), T(0.0), T(0.70710678118654757) },
                          fgm::Vec3{ T(0.0), T(1.0), T(0.0) }, fgm::Vec3 {
                              T(-0.70710678118654757),
                              T(0.0),
                              T(0.70710678118654757)
                          } };

        _expectedMatZ = { fgm::Vec3{ T(0.70710678118654757), T(-0.70710678118654757), T(0.0) },
                          fgm::Vec3{ T(0.70710678118654757), T(0.70710678118654757), T(0.0) }, fgm::Vec3 {
                              T(0.0),
                              T(0.0),
                              T(1.0)
                          } };

        _expectedMatXYZ = { fgm::Vec3{ T(0.5), T(0.5), T(-0.70710678118654757) },
                            fgm::Vec3{ T(-0.14644660940672627), T(0.85355339059327395), T(0.5) }, fgm::Vec3 {
                                T(0.85355339059327395),
                                T(-0.14644660940672627),
                                T(0.5)
                            } };

#else

        _expectedMatX = { fgm::Vec3{ T(1.0), T(0.0), T(0.0) },
                          fgm::Vec3{ T(0.0), T(0.70710678118654757), T(0.70710678118654757) },
                          fgm::Vec3{ T(0.0), T(-0.70710678118654757), T(0.70710678118654757) } };

        _expectedMatY = { fgm::Vec3{ T(0.70710678118654757), T(0.0), T(-0.70710678118654757) },
                          fgm::Vec3{ T(0.0), T(1.0), T(0.0) },
                          fgm::Vec3{ T(0.70710678118654757), T(0.0), T(0.70710678118654757) } };

        _expectedMatZ = { fgm::Vec3{ T(0.70710678118654757), T(0.70710678118654757), T(0.0) },
                          fgm::Vec3{ T(-0.70710678118654757), T(0.70710678118654757), T(0.0) },
                          fgm::Vec3{ T(0.0), T(0.0), T(1.0) } };

        _expectedMatXYZ = { fgm::Vec3{ T(0.5), T(0.5), T(-0.70710678118654757) },
                            fgm::Vec3{ T(-0.14644660940672627), T(0.85355339059327395), T(0.5) },
                            fgm::Vec3{ T(0.85355339059327395), T(-0.14644660940672627), T(0.5) } };

#endif
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix3 rotation factory, parameterized
 *        @ref SupportedFloatingPointTypes
 */
TYPED_TEST_SUITE(Matrix3FloatRotation, SupportedFloatingPointTypes);

namespace
{
// TODO: Add static tests after making trig functions constexpr
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


/**************************************
 *                                    *
 *               TESTS                *
 *                                    *
 **************************************/

/** @brief Verify that rotation transformation factory for x returns a rotation matrix. */
TYPED_TEST(Matrix3Rotation, X_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatX, fgm::Matrix3<typename TypeParam::first_type>::makeRotationX(this->_angle)); }


/** @brief Verify that rotation transformation factory for x returns a rotation matrix for non-integral values. */
TYPED_TEST(Matrix3FloatRotation, X_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatX, fgm::Matrix3<TypeParam>::makeRotationX(this->_angle)); }


/** @brief Verify that rotation transformation factory for y returns a rotation matrix. */
TYPED_TEST(Matrix3Rotation, Y_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatY, fgm::Matrix3<typename TypeParam::first_type>::makeRotationY(this->_angle)); }


/** @brief Verify that rotation transformation factory for y returns a rotation matrix for non-integral values. */
TYPED_TEST(Matrix3FloatRotation, Y_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatY, fgm::Matrix3<TypeParam>::makeRotationY(this->_angle)); }


/** @brief Verify that rotation transformation factory for z returns a rotation matrix. */
TYPED_TEST(Matrix3Rotation, Z_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatZ, fgm::Matrix3<typename TypeParam::first_type>::makeRotationZ(this->_angle)); }


/** @brief Verify that rotation transformation factory for z returns a rotation matrix for non-integral values. */
TYPED_TEST(Matrix3FloatRotation, Z_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatZ, fgm::Matrix3<TypeParam>::makeRotationZ(this->_angle)); }

/** @} */
