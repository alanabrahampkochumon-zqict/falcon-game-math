/**
 * @file RotationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 08, 2026
 *
 * @brief Verify @ref fgm::Matrix4 rotation factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**
 * @addtogroup T_FGM_Mat4x4_Transforms
 * @{
 */

template <typename T>
class Matrix4Rotation: public testing::Test
{
protected:
    using FP_T  = T::first_type;  // FP_T -> Floating-point Type
    using COM_T = T::second_type; // COM_T -> Common Type

    FP_T _angle;
    fgm::Matrix4<COM_T> _expectedMatX, _expectedMatY, _expectedMatZ, _expectedMatXYZ;


    void SetUp() override
    {
        _angle = fgm::constants::PI<FP_T> / FP_T(2.0);

#ifdef FMG_LEFT_HANDED
        _expectedMatX   = { fgm::Vector4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                            fgm::Vector4{ COM_T(0), COM_T(0), COM_T(-1), COM_T(0) },
                            fgm::Vector4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) }, fgm::Vector4 {
                              COM_T(0),
                              COM_T(0),
                              COM_T(0),
                              COM_T(1)
                          } };
        _expectedMatY   = { fgm::Vector4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                            fgm::Vector4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                            fgm::Vector4{ COM_T(-1), COM_T(0), COM_T(0), COM_T(0) }, fgm::Vector4 {
                              COM_T(0),
                              COM_T(0),
                              COM_T(0),
                              COM_T(1)
                          } };
        _expectedMatZ   = { fgm::Vector4{ COM_T(0), COM_T(-1), COM_T(0), COM_T(0) },
                            fgm::Vector4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                            fgm::Vector4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) }, fgm::Vector4 {
                              COM_T(0),
                              COM_T(0),
                              COM_T(0),
                              COM_T(1)
                          } };
        _expectedMatXYZ = { fgm::Vector4{ COM_T(0), COM_T(0), COM_T(-1), COM_T(0) },
                            fgm::Vector4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                            fgm::Vector4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) }, fgm::Vector4 {
                                COM_T(0),
                                COM_T(0),
                                COM_T(0),
                                COM_T(1)
                            } };
#else
        _expectedMatX   = { fgm::Vector4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                            fgm::Vector4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                            fgm::Vector4{ COM_T(0), COM_T(-1), COM_T(0), COM_T(0) },
                            fgm::Vector4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };
        _expectedMatY   = { fgm::Vector4{ COM_T(0), COM_T(0), COM_T(-1), COM_T(0) },
                            fgm::Vector4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                            fgm::Vector4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                            fgm::Vector4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };
        _expectedMatZ   = { fgm::Vector4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                            fgm::Vector4{ COM_T(-1), COM_T(0), COM_T(0), COM_T(0) },
                            fgm::Vector4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                            fgm::Vector4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };
        _expectedMatXYZ = { fgm::Vector4{ COM_T(0), COM_T(0), COM_T(-1), COM_T(0) },
                            fgm::Vector4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                            fgm::Vector4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
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
class Matrix4FloatRotation: public testing::Test
{
protected:
    T _angle;
    fgm::Matrix4<T> _expectedMatX, _expectedMatY, _expectedMatZ, _expectedMatXYZ;


    void SetUp() override
    {
        _angle = fgm::constants::PI<T> / T(4.0);

#ifdef FMG_LEFT_HANDED
        _expectedMatX   = { fgm::Vector4{ T(1.00000000000000000), T(0.00000000000000000), T(0.00000000000000000),
                                        T(0.00000000000000000) },

                            fgm::Vector4{ T(0.00000000000000000), T(0.70710678118654757), T(0.70710678118654757),
                                        T(0.00000000000000000) },

                            fgm::Vector4{ T(0.00000000000000000), T(-0.70710678118654757), T(0.70710678118654757),
                                        T(0.00000000000000000) },
                            fgm::Vector4 {
                              T(0.00000000000000000),
                              T(0.00000000000000000),
                              T(0.00000000000000000),
                              T(1.00000000000000000)
                          } };
        _expectedMatY   = { fgm::Vector4{ T(0.70710678118654757), T(0.00000000000000000), T(-0.70710678118654757),
                                        T(0.00000000000000000) },
                            fgm::Vector4{ T(0.00000000000000000), T(1.00000000000000000), T(0.00000000000000000),
                                        T(0.00000000000000000) },

                            fgm::Vector4{ T(0.70710678118654757), T(0.00000000000000000), T(0.70710678118654757),
                                        T(0.00000000000000000) },

                            fgm::Vector4 {
                              T(0.00000000000000000),
                              T(0.00000000000000000),
                              T(0.00000000000000000),
                              T(1.00000000000000000)
                          } };
        _expectedMatZ   = { fgm::Vector4{ T(0.70710678118654757), T(0.70710678118654757), T(0.00000000000000000),
                                        T(0.00000000000000000) },

                            fgm::Vector4{ T(-0.70710678118654757), T(0.70710678118654757), T(0.00000000000000000),
                                        T(0.00000000000000000) },
                            fgm::Vector4{ T(0.00000000000000000), T(0.00000000000000000), T(1.00000000000000000),
                                        T(0.00000000000000000) },

                            fgm::Vector4 {
                              T(0.00000000000000000),
                              T(0.00000000000000000),
                              T(0.00000000000000000),
                              T(1.00000000000000000)
                          } };
        _expectedMatXYZ = { fgm::Vector4{ T(0.50000000000000011), T(0.50000000000000011), T(-0.70710678118654757),
                                          T(0.00000000000000000) },
                            fgm::Vector4{ T(-0.14644660940672627), T(0.85355339059327395), T(0.50000000000000011),
                                          T(0.00000000000000000) },
                            fgm::Vector4{ T(0.85355339059327395), T(-0.14644660940672627), T(0.50000000000000011),
                                          T(0.00000000000000000) },
                            fgm::Vector4 {
                                T(0.00000000000000000),
                                T(0.00000000000000000),
                                T(0.00000000000000000),
                                T(1.00000000000000000)
                            } };
        ;
#else

        _expectedMatX = { fgm::Vector4{ T(1.00000000000000000), T(0.00000000000000000), T(0.00000000000000000),
                                        T(0.00000000000000000) },

                          fgm::Vector4{ T(0.00000000000000000), T(0.70710678118654757), T(0.70710678118654757),
                                        T(0.00000000000000000) },

                          fgm::Vector4{ T(0.00000000000000000), T(-0.70710678118654757), T(0.70710678118654757),
                                        T(0.00000000000000000) },
                          fgm::Vector4{ T(0.00000000000000000), T(0.00000000000000000), T(0.00000000000000000),
                                        T(1.00000000000000000) } };

        _expectedMatY   = { fgm::Vector4{ T(0.70710678118654757), T(0.00000000000000000), T(-0.70710678118654757),
                                        T(0.00000000000000000) },
                            fgm::Vector4{ T(0.00000000000000000), T(1.00000000000000000), T(0.00000000000000000),
                                        T(0.00000000000000000) },

                            fgm::Vector4{ T(0.70710678118654757), T(0.00000000000000000), T(0.70710678118654757),
                                        T(0.00000000000000000) },

                            fgm::Vector4{ T(0.00000000000000000), T(0.00000000000000000), T(0.00000000000000000),
                                        T(1.00000000000000000) } };
        _expectedMatZ   = { fgm::Vector4{ T(0.70710678118654757), T(0.70710678118654757), T(0.00000000000000000),
                                        T(0.00000000000000000) },

                            fgm::Vector4{ T(-0.70710678118654757), T(0.70710678118654757), T(0.00000000000000000),
                                        T(0.00000000000000000) },
                            fgm::Vector4{ T(0.00000000000000000), T(0.00000000000000000), T(1.00000000000000000),
                                        T(0.00000000000000000) },

                            fgm::Vector4{ T(0.00000000000000000), T(0.00000000000000000), T(0.00000000000000000),
                                        T(1.00000000000000000) } };
        _expectedMatXYZ = { fgm::Vector4{ T(0.50000000000000011), T(0.50000000000000011), T(-0.70710678118654757),
                                          T(0.00000000000000000) },
                            fgm::Vector4{ T(-0.14644660940672627), T(0.85355339059327395), T(0.50000000000000011),
                                          T(0.00000000000000000) },
                            fgm::Vector4{ T(0.85355339059327395), T(-0.14644660940672627), T(0.50000000000000011),
                                          T(0.00000000000000000) },
                            fgm::Vector4{ T(0.00000000000000000), T(0.00000000000000000), T(0.00000000000000000),
                                          T(1.00000000000000000) } };

#endif
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix4 rotation factory, parameterized
 *        @ref SupportedFloatingPointTypes
 */
TYPED_TEST_SUITE(Matrix4FloatRotation, SupportedFloatingPointTypes);


/**************************************
 *                                    *
 *               TESTS                *
 *                                    *
 **************************************/

/** @brief Verify that rotation transformation factory for x returns a rotation matrix. */
TYPED_TEST(Matrix4Rotation, X_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatX, fgm::Matrix4<typename TypeParam::first_type>::makeRotationX(this->_angle)); }


/** @brief Verify that rotation transformation factory for x returns a rotation matrix for non-integral rotation values.
 */
TYPED_TEST(Matrix4FloatRotation, X_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatX, fgm::Matrix4<TypeParam>::makeRotationX(this->_angle)); }


/** @brief Verify that rotation transformation factory for y returns a rotation matrix. */
TYPED_TEST(Matrix4Rotation, Y_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatY, fgm::Matrix4<typename TypeParam::first_type>::makeRotationY(this->_angle)); }


/** @brief Verify that rotation transformation factory for y returns a rotation matrix for non-integral rotation values.
 */
TYPED_TEST(Matrix4FloatRotation, Y_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatY, fgm::Matrix4<TypeParam>::makeRotationY(this->_angle)); }


/** @brief Verify that rotation transformation factory for y returns a rotation matrix. */
TYPED_TEST(Matrix4Rotation, Z_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatZ, fgm::Matrix4<typename TypeParam::first_type>::makeRotationZ(this->_angle)); }


/** @brief Verify that rotation transformation factory for z returns a rotation matrix for non-integral rotation values.
 */
TYPED_TEST(Matrix4FloatRotation, Z_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatZ, fgm::Matrix4<TypeParam>::makeRotationZ(this->_angle)); }

/** @} */
