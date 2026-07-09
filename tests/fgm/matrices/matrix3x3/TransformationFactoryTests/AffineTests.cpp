/**
 * @file AffineTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 09, 2026
 *
 * @brief Verify @ref fgm::Matrix3 affine transformation factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "MatrixTestSetup.h"

/**
 * @addtogroup T_FGM_Mat3x3_Transforms
 * @{
 */

template <typename T>
class Matrix3Affine: public testing::Test
{
protected:
    fgm::Matrix2<T> _linearTransform;
    fgm::Vector2<T> _translation;
    fgm::Matrix3<T> _expectedMat;

    void SetUp() override
    {
        _linearTransform = { fgm::Vector2{ T(1.2341234), T(2.31419123) },
                             fgm::Vector2{ T(15.123949182), T(0.93819231) } };
        _translation     = { T(1.2398412349), T(12.1234892134) };

        _expectedMat = { fgm::Vector3{ T(1.2341234), T(2.31419123), T(0) },
                         fgm::Vector3{ T(15.123949182), T(0.93819231), T(0) },
                         fgm::Vector3{ T(1.2398412349), T(12.1234892134), T(1) } };
    }
};
/**
 * @brief Test fixture for @ref fgm::Matrix3 affine factory, parameterized
 *        @ref SupportedArithmeticTypes
 */
TYPED_TEST_SUITE(Matrix3Affine, SupportedArithmeticTypes);


/** @brief Verify that fgm::Matrix3::makeAffine is available at compile time. */
namespace
{
    // Make Affine
    constexpr fgm::Matrix2 LIN_TRANSFORM{ 1, 2, 3, 4 };
    constexpr fgm::Vector2 TRANSLATION3D{ 11, 12 };
    constexpr auto AFFINE3D = fgm::Matrix3<int>::makeAffine(LIN_TRANSFORM, TRANSLATION3D);
    static_assert(AFFINE3D(0, 0) == 1);
    static_assert(AFFINE3D(0, 1) == 2);
    static_assert(AFFINE3D(0, 2) == 11);
    static_assert(AFFINE3D(1, 0) == 3);
    static_assert(AFFINE3D(1, 1) == 4);
    static_assert(AFFINE3D(1, 2) == 12);
    static_assert(AFFINE3D(2, 0) == 0);
    static_assert(AFFINE3D(2, 1) == 0);
    static_assert(AFFINE3D(2, 2) == 1);

} // namespace


/** @brief Verify that makeAffine returns a matrix with combined linear transform and translation vector. */
TYPED_TEST(Matrix3Affine, ReturnsCombinedLinearTransformAndTranslation)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Matrix3<TypeParam>::makeAffine(this->_linearTransform, this->_translation));
}

/** @} */
