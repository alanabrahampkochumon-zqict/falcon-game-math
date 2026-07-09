/**
 * @file RotationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 08, 2026
 *
 * @brief Verify @ref fgm::Matrix2 rotation factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**
 * @addtogroup T_FGM_Mat2x2_Transforms
 * @{
 */

template <typename T>
class Matrix2Rotation: public ::testing::Test
{
protected:
    using FP_T  = T::first_type;  // FP_T -> Floating-point Type
    using COM_T = T::second_type; // COM_T -> Common Type

    FP_T _angle;
    fgm::Matrix2<COM_T> _expectedMat;


    void SetUp() override
    {
        _angle = fgm::constants::PI<FP_T> / FP_T(2.0);
        #ifdef FGM_LEFT_HANDED
        _expectedMat = { fgm::Vector2{ COM_T(0), COM_T(-1) }, fgm::Vector2 { COM_T(1), COM_T(0) } };
        #else
        _expectedMat = { fgm::Vector2{ COM_T(0), COM_T(1) }, fgm::Vector2{ COM_T(-1), COM_T(0) } };
        #endif
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2 rotation factory, parameterized
 *        @ref SupportedSignedArithmeticFloatingTypePair
 */
TYPED_TEST_SUITE(Matrix2Rotation, SupportedSignedArithmeticFloatingTypePair);



// template <typename T>
// class Matrix2FloatRotation: public testing::Test
// {
// protected:
//     T _angle;
//     fgm::Matrix2<T> _expectedMatX, _expectedMatY, _expectedMatZ, _expectedMatXYZ;
//
//
//     void SetUp() override
//     {
//         _angle = fgm::constants::PI<T> / T(4.0);
//
// #ifdef FGM_LEFT_HANDED
//         _expectedMatX = { fgm::Vector4{ T(1.0), T(0.0), T(0.0), T(0.0) },
//                           fgm::Vector4{ T(0.0), T(0.70710678118654757), T(-0.70710678118654757), T(0.0) },
//                           fgm::Vector4{ T(0.0), T(0.70710678118654757), T(0.70710678118654757), T(0.0) }, fgm::Vector4 {
//                               T(0.0),
//                               T(0.0),
//                               T(0.0),
//                               T(1.0)
//                           } };
//
//         _expectedMatY = { fgm::Vector4{ T(0.70710678118654757), T(0.0), T(0.70710678118654757), T(0.0) },
//                           fgm::Vector4{ T(0.0), T(1.0), T(0.0), T(0.0) },
//                           fgm::Vector4{ T(-0.70710678118654757), T(0.0), T(0.70710678118654757), T(0.0) },
//                           fgm::Vector4 {
//                               T(0.0),
//                               T(0.0),
//                               T(0.0),
//                               T(1.0)
//                           } };
//
//         _expectedMatZ = { fgm::Vector4{ T(0.70710678118654757), T(-0.70710678118654757), T(0.0), T(0.0) },
//                           fgm::Vector4{ T(0.70710678118654757), T(0.70710678118654757), T(0.0), T(0.0) },
//                           fgm::Vector4{ T(0.0), T(0.0), T(1.0), T(0.0) },
//                           fgm::Vector4 {
//                               T(0.0),
//                               T(0.0),
//                               T(0.0),
//                               T(1.0)
//                           } };
//
//         _expectedMatXYZ = { fgm::Vector4{ T(0.5), T(0.5), T(-0.70710678118654757), T(0.0) },
//                             fgm::Vector4{ T(-0.14644660940672627), T(0.85355339059327395), T(0.5), T(0.0) },
//                             fgm::Vector4{ T(0.85355339059327395), T(-0.14644660940672627), T(0.5), T(0.0) },
//                             fgm::Vector4 {
//                                 T(0.0),
//                                 T(0.0),
//                                 T(0.0),
//                                 T(1.0)
//                             } };
//
// #else
//
//         _expectedMatX = { fgm::Vector4{ T(1.0), T(0.0), T(0.0), T(0.0) },
//                           fgm::Vector4{ T(0.0), T(0.70710678118654757), T(0.70710678118654757), T(0.0) },
//                           fgm::Vector4{ T(0.0), T(-0.70710678118654757), T(0.70710678118654757), T(0.0) },
//                           fgm::Vector4{ T(0.0), T(0.0), T(0.0), T(1.0) } };
//
//         _expectedMatY = { fgm::Vector4{ T(0.70710678118654757), T(0.0), T(-0.70710678118654757), T(0.0) },
//                           fgm::Vector4{ T(0.0), T(1.0), T(0.0), T(0.0) },
//                           fgm::Vector4{ T(0.70710678118654757), T(0.0), T(0.70710678118654757), T(0.0) },
//                           fgm::Vector4{ T(0.0), T(0.0), T(0.0), T(1.0) } };
//
//         _expectedMatZ = { fgm::Vector4{ T(0.70710678118654757), T(0.70710678118654757), T(0.0), T(0.0) },
//                           fgm::Vector4{ T(-0.70710678118654757), T(0.70710678118654757), T(0.0), T(0.0) },
//                           fgm::Vector4{ T(0.0), T(0.0), T(1.0), T(0.0) },
//                           fgm::Vector4{ T(0.0), T(0.0), T(0.0), T(1.0) } };
//
//         _expectedMatXYZ = { fgm::Vector4{ T(0.5), T(0.5), T(-0.70710678118654757), T(0.0) },
//                             fgm::Vector4{ T(-0.14644660940672627), T(0.85355339059327395), T(0.5), T(0.0) },
//                             fgm::Vector4{ T(0.85355339059327395), T(-0.14644660940672627), T(0.5), T(0.0) },
//                             fgm::Vector4{ T(0.0), T(0.0), T(0.0), T(1.0) } };
//
// #endif
//     }
// };
// /**
//  * @brief Test fixture for @ref fgm::Matrix2 rotation factory, parameterized
//  *        @ref SupportedFloatingPointTypes
//  */
// TYPED_TEST_SUITE(Matrix2FloatRotation, SupportedFloatingPointTypes);

namespace
{
    // TODO: Add static tests
    #if __cplusplus >= 202603L
    // Rotation matrix for 180° or 2π radians
    constexpr auto ROTATION_MAT = fgm::Matrix2<int>::makeRotation(fgm::constants::PI<float>);
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
TYPED_TEST(Matrix2Rotation, ReturnsRotationMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2<typename TypeParam::first_type>::makeRotation(this->_angle));
}


/** @} */
