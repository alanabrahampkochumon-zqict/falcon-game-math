/**
 * @file InvolutionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 24, 2026
 *
 * @brief Verifies Mat3 involution transformation factory.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "../Mat3TestSetup.h"


/**
 * @addtogroup T_FGM_Mat3x3_Transforms
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat3 involution factory (Floating Point).
     *
     * @tparam T The floating point scalar type (e.g., float, double) used for the matrix and vectors.
     */
    template <typename T>
    class Mat3InvolutionFactoryFPTests: public testing::Test
    {
    protected:
        fgm::Vec3<T> _norm;
        fgm::Mat3<T> _expectedInvolution;

        void SetUp() override
        {
            _norm = fgm::Vec3{ T(0.3244428422615251), T(0.48666426339228763), T(0.8111071056538127) };

            _expectedInvolution = {
                fgm::Vec3{ T(-0.7894736842105263), T(0.31578947368421056), T(0.5263157894736843) },
                fgm::Vec3{ T(0.31578947368421056), T(-0.5263157894736842), T(0.7894736842105263) },
                fgm::Vec3{ T(0.5263157894736843), T(0.7894736842105263), T(0.3157894736842106) },
            };
        }
    };
    TYPED_TEST_SUITE(Mat3InvolutionFactoryFPTests, SupportedFloatingPointTypes);


    /**
     * @brief Test fixture for @ref fgm::Mat3 involution factory (Integral).
     *
     * @tparam T The signed scalar type (e.g., int32_t, int16_t) used for the matrix and vectors.
     */
    template <typename T>
    class Mat3InvolutionFactoryIntTests: public ::testing::Test
    {
    protected:
        fgm::Vec3<T> _xAxis, _yAxis, _zAxis;
        fgm::Mat3<T> _expectedInvolutionX, _expectedInvolutionY, _expectedInvolutionZ;

        void SetUp() override
        {
            _xAxis = fgm::Vec3{ T(1), T(0), T(0) };
            _yAxis = fgm::Vec3{ T(0), T(1), T(0) };
            _zAxis = fgm::Vec3{ T(0), T(0), T(1) };

            _expectedInvolutionX = { fgm::Vec3{ T(1), T(0), T(0) }, fgm::Vec3{ T(0), T(-1), T(0) },
                                     fgm::Vec3{ T(0), T(0), T(-1) } };

            _expectedInvolutionY = { fgm::Vec3{ T(-1), T(0), T(0) }, fgm::Vec3{ T(0), T(1), T(0) },
                                     fgm::Vec3{ T(0), T(0), T(-1) } };

            _expectedInvolutionZ = { fgm::Vec3{ T(-1), T(0), T(0) }, fgm::Vec3{ T(0), T(-1), T(0) },
                                     fgm::Vec3{ T(0), T(0), T(1) } };
        }
    };
    TYPED_TEST_SUITE(Mat3InvolutionFactoryIntTests, SupportedSignedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that involution matrix transformation factory is available at compile time.
        constexpr auto INVOLUTION_MAT = fgm::Mat3<int>::makeInvolution(fgm::Vec3{ 1, 0, 0 });
        static_assert(INVOLUTION_MAT[0] == fgm::Vec3{ 1, 0, 0});
        static_assert(INVOLUTION_MAT[1] == fgm::Vec3{ 0, -1, 0 });
        static_assert(INVOLUTION_MAT[2] == fgm::Vec3{ 0, 0, -1 });

    } // namespace static_tests

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3InvolutionFactoryFPTests, ArbitraryDirection_ReturnsValidInvolutionMatrix)
{ EXPECT_MAT_EQ(this->_expectedInvolution, fgm::Mat3<TypeParam>::makeInvolution(this->_norm)); }


TYPED_TEST(Mat3InvolutionFactoryIntTests, XAxis_ReturnsIdentityMatrixWithNegatedYAndZ)
{ EXPECT_MAT_EQ(this->_expectedInvolutionX, fgm::Mat3<TypeParam>::makeInvolution(this->_xAxis)); }


TYPED_TEST(Mat3InvolutionFactoryIntTests, YAxis_ReturnsIdentityMatrixWithNegatedZAndX)
{ EXPECT_MAT_EQ(this->_expectedInvolutionY, fgm::Mat3<TypeParam>::makeInvolution(this->_yAxis)); }


TYPED_TEST(Mat3InvolutionFactoryIntTests, ZAxis_IdentityMatrixWithNegatedXAndY)
{ EXPECT_MAT_EQ(this->_expectedInvolutionZ, fgm::Mat3<TypeParam>::makeInvolution(this->_zAxis)); }

/** @} */
