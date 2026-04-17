/**
 * @file TransformationFactoryTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 17, 2026
 *
 * @brief Verify @ref fgm::Matrix2D transformation factory function (E.g: MakeRotation, MakeScale, etc.) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"
#include "utility"



template <typename T>
class Matrix2DRotation: public ::testing::Test
{
protected:
    using FP_T = T::first_type;   // FP_T -> Floating-point Type
    using COM_T = T::second_type; // COM_T -> Common Type

    FP_T _angle;
    fgm::Matrix2D<COM_T> _expectedMatrix;


    void SetUp() override
    {
        _angle = fgm::constants::PI<FP_T> / FP_T(2.0);
#ifdef FMG_LEFT_HANDED
        _expectedMatrix = { fgm::Vector2D{ COM_T(0), COM_T(-1) }, fgm::Vector2D { COM_T(1), COM_T(0) } };
#else
        _expectedMatrix = { fgm::Vector2D{ COM_T(0), COM_T(1) }, fgm::Vector2D{ COM_T(-1), COM_T(0) } };
#endif
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2D rotation factory, parameterized
 *        @ref SupportedSignedArithmeticFloatingTypePair
 */
TYPED_TEST_SUITE(Matrix2DRotation, SupportedSignedArithmeticFloatingTypePair);



/**
 * @addtogroup T_FGM_Mat2x2_Transforms
 * @{
 */

/**************************************
 *                                    *
 *         COMPILE TIME TESTS         *
 *                                    *
 **************************************/
namespace
{
    // TODO: Add tests
}



/**************************************
 *                                    *
 *           ROTATION TESTS           *
 *                                    *
 **************************************/

/** @brief Verify that rotation transformation factory returns a rotation matrix. */
TYPED_TEST(Matrix2DRotation, ReturnsExpectedRotationMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMatrix, fgm::Matrix2D<typename TypeParam::first_type>::makeRotation(this->_angle));
}

/** @} */
