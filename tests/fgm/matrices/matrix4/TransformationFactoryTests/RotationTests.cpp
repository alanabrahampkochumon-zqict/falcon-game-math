/**
 * @file RotationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 08, 2026
 *
 * @brief Verify @ref fgm::Mat4 rotation factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**
 * @addtogroup T_FGM_Mat4x4_Transforms
 * @{
 */

template <typename T>
class Mat4Rotation: public testing::Test
{
protected:
    using FP_T  = T::first_type;  // FP_T -> Floating-point Type
    using COM_T = T::second_type; // COM_T -> Common Type

    FP_T _angle;
    fgm::Mat4<COM_T> _expectedMatX, _expectedMatY, _expectedMatZ, _expectedMatXYZ;


    void SetUp() override
    {
        _angle = fgm::constants::PI<FP_T> / FP_T(2.0);

#ifdef FGM_LEFT_HANDED
        _expectedMatX   = { fgm::Vec4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(0), COM_T(-1), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) }, fgm::Vec4 {
                              COM_T(0),
                              COM_T(0),
                              COM_T(0),
                              COM_T(1)
                          } };
        _expectedMatY   = { fgm::Vec4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                            fgm::Vec4{ COM_T(-1), COM_T(0), COM_T(0), COM_T(0) }, fgm::Vec4 {
                              COM_T(0),
                              COM_T(0),
                              COM_T(0),
                              COM_T(1)
                          } };
        _expectedMatZ   = { fgm::Vec4{ COM_T(0), COM_T(-1), COM_T(0), COM_T(0) },
                            fgm::Vec4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) }, fgm::Vec4 {
                              COM_T(0),
                              COM_T(0),
                              COM_T(0),
                              COM_T(1)
                          } };
        _expectedMatXYZ = { fgm::Vec4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(-1), COM_T(0), COM_T(0) },
                            fgm::Vec4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) }, fgm::Vec4 {
                                COM_T(0),
                                COM_T(0),
                                COM_T(0),
                                COM_T(1)
                            } };
#else
        _expectedMatX   = { fgm::Vec4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(-1), COM_T(0), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };
        _expectedMatY   = { fgm::Vec4{ COM_T(0), COM_T(0), COM_T(-1), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                            fgm::Vec4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };
        _expectedMatZ   = { fgm::Vec4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                            fgm::Vec4{ COM_T(-1), COM_T(0), COM_T(0), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(0), COM_T(1), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };
        _expectedMatXYZ = { fgm::Vec4{ COM_T(0), COM_T(0), COM_T(-1), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(1), COM_T(0), COM_T(0) },
                            fgm::Vec4{ COM_T(1), COM_T(0), COM_T(0), COM_T(0) },
                            fgm::Vec4{ COM_T(0), COM_T(0), COM_T(0), COM_T(1) } };

#endif
    }
};
/**
 * @brief Test fixture for @ref fgm::Mat4 rotation factory, parameterized
 *        @ref SupportedSignedArithmeticFloatingTypePair
 */
TYPED_TEST_SUITE(Mat4Rotation, SupportedSignedArithmeticFloatingTypePair);


template <typename T>
class Mat4FloatRotation: public testing::Test
{
protected:
    T _angle;
    fgm::Vec3<T> _axis;
    fgm::Mat4<T> _expectedMatX, _expectedMatY, _expectedMatZ, _expectedMatXYZ, _expectedAxisRotation;


    void SetUp() override
    {
        _angle = fgm::constants::PI<T> / T(4.0);
        _axis  = fgm::Vec3 { T(0.26726124191242440), T(0.53452248382484879), T(0.80178372573727319) };

#ifdef FGM_LEFT_HANDED
        _expectedMatX = { fgm::Vec4{ T(1.0), T(0.0), T(0.0), T(0.0) },
                          fgm::Vec4{ T(0.0), T(0.70710678118654757), T(-0.70710678118654757), T(0.0) },
                          fgm::Vec4{ T(0.0), T(0.70710678118654757), T(0.70710678118654757), T(0.0) }, fgm::Vec4 {
                              T(0.0),
                              T(0.0),
                              T(0.0),
                              T(1.0)
                          } };

        _expectedMatY = { fgm::Vec4{ T(0.70710678118654757), T(0.0), T(0.70710678118654757), T(0.0) },
                          fgm::Vec4{ T(0.0), T(1.0), T(0.0), T(0.0) },
                          fgm::Vec4{ T(-0.70710678118654757), T(0.0), T(0.70710678118654757), T(0.0) },
                          fgm::Vec4 {
                              T(0.0),
                              T(0.0),
                              T(0.0),
                              T(1.0)
                          } };

        _expectedMatZ = { fgm::Vec4{ T(0.70710678118654757), T(-0.70710678118654757), T(0.0), T(0.0) },
                          fgm::Vec4{ T(0.70710678118654757), T(0.70710678118654757), T(0.0), T(0.0) },
                          fgm::Vec4{ T(0.0), T(0.0), T(1.0), T(0.0) }, fgm::Vec4 {
                              T(0.0),
                              T(0.0),
                              T(0.0),
                              T(1.0)
                          } };

        _expectedMatXYZ = { fgm::Vec4{ T(0.5), T(0.5), T(-0.70710678118654757), T(0.0) },
                            fgm::Vec4{ T(-0.14644660940672627), T(0.85355339059327395), T(0.5), T(0.0) },
                            fgm::Vec4{ T(0.85355339059327395), T(-0.14644660940672627), T(0.5), T(0.0) },
                            fgm::Vec4 {
                                T(0.0),
                                T(0.0),
                                T(0.0),
                                T(1.0)
                            } };

        _expectedAxisRotation = {
            fgm::Vec4{ T(0.72802772538750848), T(0.60878859791576267), T(-0.31520164040634457), T(0.0) },
            fgm::Vec4{ T(-0.52510482111191903), T(0.79079055799039111), T(0.31450790171037896), T(0.0) },
            fgm::Vec4{ T(0.44072730561210993), T(-0.06345657129884830), T(0.89539527899519555), T(0.0) },
            fgm::Vec4 {
                T(0.0),
                T(0.0),
                T(0.0),
                T(1.0)
            }
        };

#else

        _expectedMatX = { fgm::Vec4{ T(1.0), T(0.0), T(0.0), T(0.0) },
                          fgm::Vec4{ T(0.0), T(0.70710678118654757), T(0.70710678118654757), T(0.0) },
                          fgm::Vec4{ T(0.0), T(-0.70710678118654757), T(0.70710678118654757), T(0.0) },
                          fgm::Vec4{ T(0.0), T(0.0), T(0.0), T(1.0) } };

        _expectedMatY = { fgm::Vec4{ T(0.70710678118654757), T(0.0), T(-0.70710678118654757), T(0.0) },
                          fgm::Vec4{ T(0.0), T(1.0), T(0.0), T(0.0) },
                          fgm::Vec4{ T(0.70710678118654757), T(0.0), T(0.70710678118654757), T(0.0) },
                          fgm::Vec4{ T(0.0), T(0.0), T(0.0), T(1.0) } };

        _expectedMatZ = { fgm::Vec4{ T(0.70710678118654757), T(0.70710678118654757), T(0.0), T(0.0) },
                          fgm::Vec4{ T(-0.70710678118654757), T(0.70710678118654757), T(0.0), T(0.0) },
                          fgm::Vec4{ T(0.0), T(0.0), T(1.0), T(0.0) },
                          fgm::Vec4{ T(0.0), T(0.0), T(0.0), T(1.0) } };

        _expectedMatXYZ = { fgm::Vec4{ T(0.5), T(0.5), T(-0.70710678118654757), T(0.0) },
                            fgm::Vec4{ T(-0.14644660940672627), T(0.85355339059327395), T(0.5), T(0.0) },
                            fgm::Vec4{ T(0.85355339059327395), T(-0.14644660940672627), T(0.5), T(0.0) },
                            fgm::Vec4{ T(0.0), T(0.0), T(0.0), T(1.0) } };

        _expectedAxisRotation = {
            fgm::Vec4{ T(0.72802772538750848), T(0.60878859791576267), T(-0.31520164040634457), T(0.0) },
            fgm::Vec4{ T(-0.52510482111191903), T(0.79079055799039111), T(0.31450790171037896), T(0.0) },
            fgm::Vec4{ T(0.44072730561210993), T(-0.06345657129884830), T(0.89539527899519555), T(0.0) },
            fgm::Vec4{ T(0.0), T(0.0), T(0.0), T(1.0) }
        };

#endif
    }
};
/**
 * @brief Test fixture for @ref fgm::Mat4 rotation factory, parameterized
 *        @ref SupportedFloatingPointTypes
 */
TYPED_TEST_SUITE(Mat4FloatRotation, SupportedFloatingPointTypes);


/**************************************
 *                                    *
 *               TESTS                *
 *                                    *
 **************************************/

/** @brief Verify that rotation transformation factory for x returns a rotation matrix. */
TYPED_TEST(Mat4Rotation, X_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatX, fgm::Mat4<typename TypeParam::first_type>::makeRotationX(this->_angle)); }


/**
 * @brief Verify that rotation transformation factory for x returns a rotation matrix for non-integral rotation values.
 */
TYPED_TEST(Mat4FloatRotation, X_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatX, fgm::Mat4<TypeParam>::makeRotationX(this->_angle)); }


/** @brief Verify that rotation transformation factory for y returns a rotation matrix. */
TYPED_TEST(Mat4Rotation, Y_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatY, fgm::Mat4<typename TypeParam::first_type>::makeRotationY(this->_angle)); }


/**
 * @brief Verify that rotation transformation factory for y returns a rotation matrix for non-integral rotation values.
 */
TYPED_TEST(Mat4FloatRotation, Y_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatY, fgm::Mat4<TypeParam>::makeRotationY(this->_angle)); }


/** @brief Verify that rotation transformation factory for y returns a rotation matrix. */
TYPED_TEST(Mat4Rotation, Z_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatZ, fgm::Mat4<typename TypeParam::first_type>::makeRotationZ(this->_angle)); }


/**
 * @brief Verify that rotation transformation factory for z returns a rotation matrix for non-integral rotation values.
 */
TYPED_TEST(Mat4FloatRotation, Z_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMatZ, fgm::Mat4<TypeParam>::makeRotationZ(this->_angle)); }


/**
 * @brief Verify that rotation transformation factory for an axis returns a rotation matrix.
 */
TYPED_TEST(Mat4FloatRotation, AxisAligned_ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedAxisRotation, fgm::Mat4<TypeParam>::makeRotation(this->_angle, this->_axis)); }


/** @} */
