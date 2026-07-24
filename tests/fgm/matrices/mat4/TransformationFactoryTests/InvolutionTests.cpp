/**
 * @file InvolutionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 24, 2026
 *
 * @brief Verifies Mat4 involution transformation factory.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "Mat4TestSetup.h"


/**
 * @addtogroup T_FGM_Mat4x4_Transforms
 * @{
 */

namespace
{
    /**************************************
     *                                    *
     *            TEST SETUP              *
     *                                    *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat4 involution factory (Floating Point).
     *
     * @tparam T The floating point scalar type (e.g., float, double) used for the matrix and vectors.
     */
    template <typename T>
    class Mat4InvolutionFactoryFP: public testing::Test
    {
    protected:
        fgm::Vec3<T> _norm;
        fgm::Mat4<T> _expectedInvolution;

        void SetUp() override
        {
            _norm = fgm::Vec3{ T(0.3244428422615251), T(0.48666426339228763), T(0.8111071056538127) };

            _expectedInvolution = {
                fgm::Vec4{ T(-0.7894736842105263), T(0.31578947368421056), T(0.5263157894736843), T(0) },
                fgm::Vec4{ T(0.31578947368421056), T(-0.5263157894736842), T(0.7894736842105263), T(0) },
                fgm::Vec4{ T(0.5263157894736843), T(0.7894736842105263), T(0.3157894736842106), T(0) },
                fgm::Vec4{ T(0), T(0), T(0), T(1) }
            };
        }
    };
    TYPED_TEST_SUITE(Mat4InvolutionFactoryFP, SupportedFloatingPointTypes);


    /**
     * @brief Test fixture for @ref fgm::Mat4 involution factory (Integral).
     *
     * @tparam T The signed scalar type (e.g., int32_t, int16_t) used for the matrix and vectors.
     */
    template <typename T>
    class Mat4InvolutionFactoryInt: public ::testing::Test
    {
    protected:
        fgm::Vec3<T> _xAxis, _yAxis, _zAxis;
        fgm::Mat4<T> _expectedInvolutionX, _expectedInvolutionY, _expectedInvolutionZ;

        void SetUp() override
        {
            _xAxis = fgm::Vec3{ T(1), T(0), T(0) };
            _yAxis = fgm::Vec3{ T(0), T(1), T(0) };
            _zAxis = fgm::Vec3{ T(0), T(0), T(1) };

            _expectedInvolutionX = { fgm::Vec4{ T(1), T(0), T(0), T(0) }, fgm::Vec4{ T(0), T(-1), T(0), T(0) },
                                     fgm::Vec4{ T(0), T(0), T(-1), T(0) }, fgm::Vec4{ T(0), T(0), T(0), T(1) } };

            _expectedInvolutionY = { fgm::Vec4{ T(-1), T(0), T(0), T(0) }, fgm::Vec4{ T(0), T(1), T(0), T(0) },
                                     fgm::Vec4{ T(0), T(0), T(-1), T(0) }, fgm::Vec4{ T(0), T(0), T(0), T(1) } };

            _expectedInvolutionZ = { fgm::Vec4{ T(-1), T(0), T(0), T(0) }, fgm::Vec4{ T(0), T(-1), T(0), T(0) },
                                     fgm::Vec4{ T(0), T(0), T(1), T(0) }, fgm::Vec4{ T(0), T(0), T(0), T(1) } };
        }
    };
    TYPED_TEST_SUITE(Mat4InvolutionFactoryInt, SupportedSignedArithmeticTypes);



    /**************************************
     *                                    *
     *           STATIC TESTS             *
     *                                    *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that involution matrix transformation factory is available at compile time.
        constexpr auto INVOLUTION_MAT = fgm::Mat4<int>::makeInvolution(fgm::Vec3{ 1, 0, 0 });
        static_assert(INVOLUTION_MAT[0] == fgm::Vec4{ 1, 0, 0, 0 });
        static_assert(INVOLUTION_MAT[1] == fgm::Vec4{ 0, -1, 0, 0 });
        static_assert(INVOLUTION_MAT[2] == fgm::Vec4{ 0, 0, -1, 0 });
        static_assert(INVOLUTION_MAT[3] == fgm::Vec4{ 0, 0, 0, 1 });

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

TYPED_TEST(Mat4InvolutionFactoryFP, ArbitraryDirection_ReturnsValidInvolutionMatrix)
{ EXPECT_MAT_EQ(this->_expectedInvolution, fgm::Mat4<TypeParam>::makeInvolution(this->_norm)); }


TYPED_TEST(Mat4InvolutionFactoryInt, XAxis_ReturnsIdentityMatrixWithNegatedYAndZ)
{ EXPECT_MAT_EQ(this->_expectedInvolutionX, fgm::Mat4<TypeParam>::makeInvolution(this->_xAxis)); }


TYPED_TEST(Mat4InvolutionFactoryInt, YAxis_ReturnsIdentityMatrixWithNegatedZAndX)
{ EXPECT_MAT_EQ(this->_expectedInvolutionY, fgm::Mat4<TypeParam>::makeInvolution(this->_yAxis)); }


TYPED_TEST(Mat4InvolutionFactoryInt, ZAxis_IdentityMatrixWithNegatedXAndY)
{ EXPECT_MAT_EQ(this->_expectedInvolutionZ, fgm::Mat4<TypeParam>::makeInvolution(this->_zAxis)); }

/** @} */
