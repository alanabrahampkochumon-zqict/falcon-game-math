/**
 * @file RotationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 08, 2026
 *
 * @brief Verify @ref fgm::Mat2 rotation factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat2TestSetup.h"



/**
 * @addtogroup T_FGM_Mat2x2_Transforms
 * @{
 */

template <typename T>
class Mat2Rotation: public ::testing::Test
{
protected:
    using FP_T  = T::first_type;  // FP_T -> Floating-point Type
    using COM_T = T::second_type; // COM_T -> Common Type

    FP_T _angle;
    fgm::Mat2<COM_T> _expectedMat;


    void SetUp() override
    {
        _angle = fgm::constants::PI<FP_T> / FP_T(2.0);
#ifdef FGM_LEFT_HANDED
        _expectedMat = { fgm::Vec2{ COM_T(0), COM_T(-1) }, fgm::Vec2 { COM_T(1), COM_T(0) } };
#else
        _expectedMat = { fgm::Vec2{ COM_T(0), COM_T(1) }, fgm::Vec2{ COM_T(-1), COM_T(0) } };
#endif
    }
};
/**
 * @brief Test fixture for @ref fgm::Mat2 rotation factory, parameterized
 *        @ref SupportedSignedArithmeticFloatingTypePair
 */
TYPED_TEST_SUITE(Mat2Rotation, SupportedSignedArithmeticFloatingTypePair);


template <typename T>
class Mat2FloatRotation: public testing::Test
{
protected:
    T _angle;
    fgm::Mat2<T> _expectedMat;


    void SetUp() override
    {
        _angle = fgm::constants::PI<T> / T(4.0);

#ifdef FGM_LEFT_HANDED
        _expectedMat = {
            fgm::Vec2{ T(0.70710678118654757), T(-0.70710678118654757) },
            fgm::Vec2{ T(0.70710678118654757), T(0.70710678118654757) },
        };

#else
        _expectedMat = { fgm::Vec2{ T(0.70710678118654757), T(0.70710678118654757) },
                         fgm::Vec2{ T(-0.70710678118654757), T(0.70710678118654757) } };

#endif
    }
};
/**
 * @brief Test fixture for @ref fgm::Mat2 rotation factory, parameterized
 *        @ref SupportedFloatingPointTypes
 */
TYPED_TEST_SUITE(Mat2FloatRotation, SupportedFloatingPointTypes);

namespace
{
// TODO: Add static tests
#if __cplusplus >= 202603L
    // Rotation matrix for 180° or 2π radians
    constexpr auto ROTATION_MAT = fgm::Mat2<int>::makeRotation(fgm::constants::PI<float>);
    static_assert(ROTATION_MAT(0, 0) == 0);
    static_assert(ROTATION_MAT(0, 1) == -1);
    static_assert(ROTATION_MAT(1, 0) == 1);
    static_assert(ROTATION_MAT(1, 1) == 0);
#endif

} // namespace

/**************************************
 *                                    *
 *               TESTS                *
 *                                    *
 **************************************/

/** @brief Verify that rotation transformation factory returns a rotation matrix. */
TYPED_TEST(Mat2Rotation, ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat2<typename TypeParam::first_type>::makeRotation(this->_angle)); }


/** @brief Verify that rotation transformation factory returns a rotation matrix with non-integral values. */
TYPED_TEST(Mat2FloatRotation, ReturnsRotationMatrix)
{ EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat2<TypeParam>::makeRotation(this->_angle)); }


/** @} */
