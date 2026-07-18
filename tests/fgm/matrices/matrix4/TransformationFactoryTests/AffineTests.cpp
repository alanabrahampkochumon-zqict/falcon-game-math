/**
 * @file AffineTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 08, 2026
 *
 * @brief Verify @ref fgm::Mat4 affine transformation factory logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "MatrixTestSetup.h"

/**
 * @addtogroup T_FGM_Mat4x4_Transforms
 * @{
 */

template <typename T>
class Mat4Affine: public testing::Test
{
protected:
    fgm::Mat3<T> _linearTransform;
    fgm::Vec3<T> _translation;
    fgm::Mat4<T> _expectedMat;

    void SetUp() override
    {
        _linearTransform = { fgm::Vec3{ T(1.2341234), T(2.31419123), T(3.10234212) },
                             fgm::Vec3{ T(15.123949182), T(0.93819231), T(3.10234212) },
                             fgm::Vec3{ T(5.8329141), T(12.2319382), T(8.34232112) } };
        _translation     = { T(1.2398412349), T(12.1234892134), T(35.012342380) };

        _expectedMat = { fgm::Vec4{ T(1.2341234), T(2.31419123), T(3.10234212), T(0) },
                         fgm::Vec4{ T(15.123949182), T(0.93819231), T(3.10234212), T(0) },
                         fgm::Vec4{ T(5.8329141), T(12.2319382), T(8.34232112), T(0) },
                         fgm::Vec4{ T(1.2398412349), T(12.1234892134), T(35.012342380), T(1) } };
    }
};
/**
 * @brief Test fixture for @ref fgm::Mat4 affine factory, parameterized
 *        @ref SupportedArithmeticTypes
 */
TYPED_TEST_SUITE(Mat4Affine, SupportedArithmeticTypes);

/** @brief Verify that fgm::Mat4::makeAffine is available at compile time. */
namespace
{
    // Make Affine
    constexpr fgm::Mat3 LIN_TRANSFORM{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    constexpr fgm::Vec3 TRANSLATION3D{ 11, 12, 13 };
    constexpr auto AFFINE4D = fgm::Mat4<int>::makeAffine(LIN_TRANSFORM, TRANSLATION3D);
    static_assert(AFFINE4D(0, 0) == 1);
    static_assert(AFFINE4D(0, 1) == 2);
    static_assert(AFFINE4D(0, 2) == 3);
    static_assert(AFFINE4D(0, 3) == 11);
    static_assert(AFFINE4D(1, 0) == 4);
    static_assert(AFFINE4D(1, 1) == 5);
    static_assert(AFFINE4D(1, 2) == 6);
    static_assert(AFFINE4D(1, 3) == 12);
    static_assert(AFFINE4D(2, 0) == 7);
    static_assert(AFFINE4D(2, 1) == 8);
    static_assert(AFFINE4D(2, 2) == 9);
    static_assert(AFFINE4D(2, 3) == 13);
    static_assert(AFFINE4D(3, 0) == 0);
    static_assert(AFFINE4D(3, 1) == 0);
    static_assert(AFFINE4D(3, 2) == 0);
    static_assert(AFFINE4D(3, 3) == 1);
} // namespace


/** @brief Verify that makeAffine returns a matrix with combined linear transform and translation vector. */
TYPED_TEST(Mat4Affine, ReturnsCombinedLinearTransformAndTranslation)
{
    EXPECT_MAT_EQ(this->_expectedMat, fgm::Mat4<TypeParam>::makeAffine(this->_linearTransform, this->_translation));
}

/** @} */
