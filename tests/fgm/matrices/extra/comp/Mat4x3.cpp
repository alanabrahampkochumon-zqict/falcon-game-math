/**
 * @file Mat4x3.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref fgm::Mat4x3 composition (matrix-matrix Composition) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <fgm/matrices/extra/Comp.h>
#include <gtest/gtest.h>


using namespace testutils;



/**
 * @addtogroup T_FGM_Mat4x3_Comp
 * @{
 */

namespace
{

    /**************************************
     *                                    *
     *               SETUP                *
     *                                    *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat4x3 matrix composition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat4x3Composition: public testing::Test
    {

    protected:
        fgm::Mat3<T> _mat3;
        fgm::Mat3x2<T> _mat3x2;
        fgm::Mat3x4<T> _mat3x4;

        fgm::Mat4<T> _expectedFPMat4, _expectedIntMat4;
        fgm::Mat4x2<T> _expectedFPMat4x2, _expectedIntMat4x2;
        fgm::Mat4x3<T> _mat4x3, _expectedFPMat4x3, _expectedIntMat4x3;


        void SetUp() override
        {
            _mat4x3 = { fgm::Vec4{ T(5.12390421300000032), T(2.01238399999999995), T(5.01238401234000008),
                                   T(3.12343210000000004) },
                        fgm::Vec4{ T(1.01820339999999998), T(2.01234000000000002), T(1.10234800000000011),
                                   T(2.12389900000000020) },
                        fgm::Vec4{ T(5.01238399999999995), T(1.02384019999999998), T(5.01238399999999995),
                                   T(9.10234799999999922) } };


            _mat3 = { fgm::Vec3{ T(5.12390421300000032), T(2.01238399999999995), T(5.01238401234000008) },
                      fgm::Vec3{ T(1.01820339999999998), T(2.01234000000000002), T(1.10234800000000011) },
                      fgm::Vec3{ T(5.01238399999999995), T(1.02384019999999998), T(0.01283400000000000) } };

            _mat3x2 = { fgm::Vec3{ T(1.32194213899999991), T(3.02134123399999988), T(5.10238399999999981) },
                        fgm::Vec3{ T(2.12304122299999998), T(4.01283041000000029), T(6.01238399999999995) } };

            _mat3x4 = { fgm::Vec3{ T(5.12390421300000032), T(2.01234000000000002), T(0.01283400000000000) },
                        fgm::Vec3{ T(1.01820339999999998), T(1.02384019999999998), T(0.25123420000000002) },
                        fgm::Vec3{ T(5.01238399999999995), T(5.01238401234000008), T(1.20830199999999999) },
                        fgm::Vec3{ T(2.01238399999999995), T(1.10234800000000011), T(3.01234499999999983) } };

            _expectedFPMat4x2  = { fgm::Vec4{ T(35.42495273583932658), T(13.96424688331373609), T(35.53175903283557346),
                                             T(56.98969493447862078) },
                                   fgm::Vec4{ T(45.10051479744376479), T(18.50327377280183327), T(45.20141082396263954),
                                             T(69.88083307814204659) } };
            _expectedIntMat4x2 = { fgm::Vec4{ T(33), T(13), T(33), T(54) }, fgm::Vec4{ T(44), T(18), T(44), T(68) } };

            _expectedFPMat4  = { fgm::Vec4{ T(28.36769475021115383), T(14.37391509650059263), T(27.96560346857877377),
                                           T(20.39499334410143661) },
                                 fgm::Vec4{ T(7.51893654798040423), T(4.36655449254844008), T(7.49153692459262999),
                                           T(7.64164347873053984) },
                                 fgm::Vec4{ T(36.84307555021202063), T(21.41057036818867587), T(36.70585852851179709),
                                           T(37.30002376764731764) },
                                 fgm::Vec4{ T(26.53270721783699315), T(9.35214824504499909), T(26.40104238187281993),
                                           T(36.04623308403839843) } };
            _expectedIntMat4 = { fgm::Vec4{ T(27), T(14), T(27), T(19) }, fgm::Vec4{ T(6), T(4), T(6), T(5) },
                                 fgm::Vec4{ T(35), T(21), T(35), T(34) }, fgm::Vec4{ T(26), T(9), T(26), T(35) } };


            _expectedFPMat4x3  = { fgm::Vec4{ T(53.42740404021357392), T(19.49274392400478106), T(53.02531646094359274),
                                             T(65.90273085138041154) },
                                   fgm::Vec4{ T(12.79153959853892530), T(7.22715670329520066), T(12.84731689542222988),
                                             T(17.48825121065313937) },
                                   fgm::Vec4{ T(26.78978200372647223), T(12.16029591665079934), T(26.31695055835441721),
                                             T(17.94719379429820094) } };
            _expectedIntMat4x3 = { fgm::Vec4{ T(52), T(19), T(52), T(64) }, fgm::Vec4{ T(12), T(7), T(12), T(16) },
                                   fgm::Vec4{ T(26), T(12), T(26), T(17) } };
        }
    };
    TYPED_TEST_SUITE(Mat4x3Composition, SupportedArithmeticTypes);


    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr fgm::Mat4x3 MAT4X3(5, 1, 5, 2, 2, 1, 5, 1, 5, 3, 2, 9);
        constexpr fgm::Mat3x2 MAT3X2(1, 2, 3, 4, 5, 6);
        constexpr fgm::Mat3 MAT3(5, 1, 5, 2, 2, 1, 5, 1, 0);
        // constexpr fgm::Mat2x4 MAT2X4(5, 1, 5, 2, 2, 1, 5, 1);
        //


        /// @test Verify that 4x3 matrix times a 3x2 matrix yields a 4x2 matrix at compile time.
        constexpr auto EXP_MAT4X2 = MAT4X3 * MAT3X2;
        static_assert(EXP_MAT4X2[0] == fgm::Vec4{ 33, 13, 33, 54 });
        static_assert(EXP_MAT4X2[1] == fgm::Vec4{ 44, 18, 44, 68 });

        /// @test Verify that 4x3 matrix times a 3x3 matrix yields a 4x3 matrix at compile time.
        constexpr auto EXP_MAT4X3 = MAT4X3 * MAT3;
        static_assert(EXP_MAT4X3[0] == fgm::Vec4{ 52, 19, 52, 64 });
        static_assert(EXP_MAT4X3[1] == fgm::Vec4{ 12, 7, 12, 16 });
        static_assert(EXP_MAT4X3[2] == fgm::Vec4{ 26, 12, 26, 17 });
        //
        // /// @test Verify that 4x2 matrix times a 2x4 matrix yields a 4D matrix at compile time.
        // constexpr auto EXP_MAT4 = MAT4X3 * MAT2X4;
        // static_assert(EXP_MAT4[0] == fgm::Vec4{ 27, 29, 12, 27 });
        // static_assert(EXP_MAT4[1] == fgm::Vec4{ 6, 7, 3, 6 });
        // static_assert(EXP_MAT4[2] == fgm::Vec4{ 30, 35, 15, 30 });
        // static_assert(EXP_MAT4[3] == fgm::Vec4{ 11, 12, 5, 11 });

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

TYPED_TEST(Mat4x3Composition, Mat4x3TimesMat3x2_ReturnsAValid4x2Matrix)
{
    const auto matrixProduct = this->_mat4x3 * this->_mat3x2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat4x2, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat4x2, matrixProduct);
    }
}


TYPED_TEST(Mat4x3Composition, Mat4x3TimesMat3_ReturnsAValid4x3Matrix)
{
    const auto matrixProduct = this->_mat4x3 * this->_mat3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat4x3, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat4x3, matrixProduct);
    }
}


// TYPED_TEST(Mat4x3Composition, Mat4x3TimesMat2x4_ReturnsAValid4DMatrix)
// {
//     const auto matrixProduct = this->_mat4x3 * this->_mat2x4;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_MAT_EQ(this->_expectedFPMat4, matrixProduct);
//     }
//     else
//     {
//         EXPECT_MAT_EQ(this->_expectedIntMat4, matrixProduct);
//     }
// }

/** @} */
