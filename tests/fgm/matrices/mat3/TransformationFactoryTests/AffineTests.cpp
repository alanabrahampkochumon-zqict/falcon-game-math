/**
 * @file AffineTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 09, 2026
 *
 * @brief Verify @ref fgm::Mat3 affine transformation factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "Mat2TestSetup.h"
#include "Mat3TestSetup.h"

/**
 * @addtogroup T_FGM_Mat3x3_Transforms
 * @{
 */

template <typename T>
class Mat3Affine: public testing::Test
{
protected:
    fgm::Mat2<T> _linearTransform;
    fgm::Vec2<T> _translation;
    fgm::Mat3<T> _expectedMat;

    void SetUp() override
    {
        _linearTransform = { fgm::Vec2{ T(1.2341234), T(2.31419123) }, fgm::Vec2{ T(15.123949182), T(0.93819231) } };
        _translation     = { T(1.2398412349), T(12.1234892134) };

        _expectedMat = { fgm::Vec3{ T(1.2341234), T(2.31419123), T(0) },
                         fgm::Vec3{ T(15.123949182), T(0.93819231), T(0) },
                         fgm::Vec3{ T(1.2398412349), T(12.1234892134), T(1) } };
    }
};
/**
 * @brief Test fixture for @ref fgm::Mat3 affine factory, parameterized
 *        @ref SupportedArithmeticTypes
 */
TYPED_TEST_SUITE(Mat3Affine, SupportedArithmeticTypes);


/** @brief Verify that fgm::Mat3::makeAffine is available at compile time. */
namespace
{
    // Make Affine
    constexpr fgm::Mat2 LIN_TRANSFORM{ 1, 2, 3, 4 };
    constexpr fgm::Vec2 TRANSLATION3D{ 11, 12 };
    constexpr auto AFFINE3D = fgm::Mat3<int>::makeAffine(LIN_TRANSFORM, TRANSLATION3D);
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
TYPED_TEST(Mat3Affine, ReturnsCombinedLinearTransformAndTranslation)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat3<TypeParam>::makeAffine(this->_linearTransform, this->_translation));
}

/** @} */
