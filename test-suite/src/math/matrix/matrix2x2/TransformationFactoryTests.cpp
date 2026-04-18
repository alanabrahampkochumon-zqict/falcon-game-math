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
    fgm::Matrix2D<COM_T> _expectedMat;


    void SetUp() override
    {
        _angle = fgm::constants::PI<FP_T> / FP_T(2.0);
#ifdef FMG_LEFT_HANDED
        _expectedMat = { fgm::Vector2D{ COM_T(0), COM_T(-1) }, fgm::Vector2D { COM_T(1), COM_T(0) } };
#else
        _expectedMat = { fgm::Vector2D{ COM_T(0), COM_T(1) }, fgm::Vector2D{ COM_T(-1), COM_T(0) } };
#endif
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2D rotation factory, parameterized
 *        @ref SupportedSignedArithmeticFloatingTypePair
 */
TYPED_TEST_SUITE(Matrix2DRotation, SupportedSignedArithmeticFloatingTypePair);


template <typename T>
class Matrix2DUniformScale: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _mat, _expectedMat;
    T _scale;

    void SetUp() override
    {
        _mat = { fgm::Vector2D{ T(4.12349891123), T(5.12343214891234) },
                 fgm::Vector2D{ T(3.12819385912319), T(5.8238991932838) } };
        _expectedMat = { fgm::Vector2D{ T(5.3821839321), T(0) }, fgm::Vector2D{ T(0), T(5.3821839321) } };
        _scale = T(5.3821839321);
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix2D scale factory, parameterized
 *        @ref SupportedSignedArithmeticFloatingTypePair
 */
TYPED_TEST_SUITE(Matrix2DUniformScale, SupportedArithmeticTypes);



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
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2D<typename TypeParam::first_type>::makeRotation(this->_angle));
}

/** @brief Verify that uniform scale transformation factory returns a scale matrix. */
TYPED_TEST(Matrix2DUniformScale, ReturnsExpectedRotationMatrix)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix2D<TypeParam>::makeScale(this->_scale));
}

/** @} */
