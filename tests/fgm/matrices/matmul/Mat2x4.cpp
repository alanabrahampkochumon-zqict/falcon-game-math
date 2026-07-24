/**
 * @file Mat2x4.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 24, 2026
 *
 * @brief Verify @ref fgm::Mat2x4 vector and matrix multiplication logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"
#include "utils/VectorUtils.h"

#include <fgm/matrices/MatMul.h>
#include <gtest/gtest.h>

using namespace testutils;



/**
 * @addtogroup T_FGM_Mat2x4_MatVec_Multiplication
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
     * @brief Test fixture for @ref fgm::Mat2x4 matrix and vector multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrix and vectors.
     */
    template <typename T>
    class Mat2x4Multiplication: public ::testing::Test
    {

    protected:
        fgm::Vec2<T> _vec2, _expectedFPVec2, _expectedIntVec2;
        fgm::Vec4<T> _vec4, _expectedFPVec4, _expectedIntVec4;

        fgm::Mat2<T> _expectedFPMat2, _expectedIntMat2;
        fgm::Mat2x3<T> _expectedFPMat2x3, _expectedIntMat2x3;
        fgm::Mat2x4<T> _mat2x4, _expectedFPMat2x4, _expectedIntMat2x4;

        fgm::Mat4<T> _mat4;
        fgm::Mat4x2<T> _mat4x2;
        fgm::Mat4x3<T> _mat4x3;

        void SetUp() override
        {

            _vec2            = fgm::Vec2{ T(1.23412341000000003), T(2.23412341000000003) };
            _expectedFPVec2  = fgm::Vec2{ T(79.76909769345732570), T(124.92017191745732418) };
            _expectedIntVec2 = fgm::Vec2{ T(70), T(110) };

            _vec4            = fgm::Vec4{ T(1.32194213899999991), T(2.32194213899999991), T(3.32194213899999991),
                               T(4.32194213899999991) };
            _expectedFPVec4  = fgm::Vec4{ T(26.70745813272185387), T(30.17570495272185127), T(33.64395177272185578),
                                         T(37.11219859272185317) };
            _expectedIntVec4 = fgm::Vec4{ T(23), T(26), T(29), T(32) };


            _expectedFPMat2  = { fgm::Vec2{ T(225.24785336999659080), T(355.23032077799655326) },
                                 fgm::Vec2{ T(251.74347022199657431), T(397.72593762999656519) } };
            _expectedIntMat2 = { fgm::Vec2{ T(218), T(346) }, fgm::Vec2{ T(244), T(388) } };

            _expectedFPMat2x3  = { fgm::Vec2{ T(269.99127864799658028), T(423.97374605599657116) },
                                   fgm::Vec2{ T(296.48689549999659221), T(466.46936290799658309) },
                                   fgm::Vec2{ T(322.98251235199654730), T(508.96497975999648133) } };
            _expectedIntMat2x3 = { fgm::Vec2{ T(262), T(414) }, fgm::Vec2{ T(288), T(456) },
                                   fgm::Vec2{ T(314), T(498) } };


            _mat2x4            = { fgm::Vec2{ T(5.12390421300000032), T(9.12390421299999943) },
                                   fgm::Vec2{ T(6.12390421300000032), T(10.12390421299999943) },
                                   fgm::Vec2{ T(7.12390421300000032), T(11.12390421299999943) },
                                   fgm::Vec2{ T(8.12390421299999943), T(12.12390421299999943) } };
            _expectedFPMat2x4  = { fgm::Vec2{ T(314.73470392599654133), T(492.71717133399658906) },
                                   fgm::Vec2{ T(341.23032077799655326), T(535.21278818599660099) },
                                   fgm::Vec2{ T(367.72593762999656519), T(577.70840503799649923) },
                                   fgm::Vec2{ T(394.22155448199657712), T(620.20402188999651116) } };
            _expectedIntMat2x4 = { fgm::Vec2{ T(306), T(482) }, fgm::Vec2{ T(332), T(524) },
                                   fgm::Vec2{ T(358), T(566) }, fgm::Vec2{ T(384), T(608) } };


            _mat4 = { fgm::Vec4{ T(5.12390421300000032), T(9.12390421299999943), T(13.12390421299999943),
                                 T(17.12390421299999943) },
                      fgm::Vec4{ T(6.12390421300000032), T(10.12390421299999943), T(14.12390421299999943),
                                 T(18.12390421299999943) },
                      fgm::Vec4{ T(7.12390421300000032), T(11.12390421299999943), T(15.12390421299999943),
                                 T(19.12390421299999943) },
                      fgm::Vec4{ T(8.12390421299999943), T(12.12390421299999943), T(16.12390421299999943),
                                 T(20.12390421299999943) } };

            _mat4x2 = { fgm::Vec4{ T(5.12390421300000032), T(7.12390421300000032), T(9.12390421299999943),
                                   T(11.12390421299999943) },
                        fgm::Vec4{ T(6.12390421300000032), T(8.12390421299999943), T(10.12390421299999943),
                                   T(12.12390421299999943) } };

            _mat4x3 = { fgm::Vec4{ T(5.12390421300000032), T(8.12390421299999943), T(11.12390421299999943),
                                   T(14.12390421299999943) },
                        fgm::Vec4{ T(6.12390421300000032), T(9.12390421299999943), T(12.12390421299999943),
                                   T(15.12390421299999943) },
                        fgm::Vec4{ T(7.12390421300000032), T(10.12390421299999943), T(13.12390421299999943),
                                   T(16.12390421299999943) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x4Multiplication, SupportedArithmeticTypes);


    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr fgm::Vec2 VEC2(1, 2);
        constexpr fgm::Vec4 VEC4(1, 2, 3, 4);

        constexpr fgm::Mat2x4 MAT2X4(5, 6, 7, 8, 9, 10, 11, 12);

        constexpr fgm::Mat4 MAT4(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
        constexpr fgm::Mat4x2 MAT4X2(5, 6, 7, 8, 9, 10, 11, 12);
        constexpr fgm::Mat4x3 MAT4X3(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);


        /// @test Verify that 2x4 matrix times a 4D column vector yields a 2D column vector at compile time.
        constexpr auto EXP_VEC2 = MAT2X4 * VEC4;
        static_assert(EXP_VEC2.x() == 70);
        static_assert(EXP_VEC2.y() == 110);

        /// @test Verify that 2x4 matrix times a 4x2 matrix yields a 2x2 matrix at compile time.
        constexpr auto EXP_MAT2 = MAT2X4 * MAT4X2;
        static_assert(EXP_MAT2[0] == fgm::Vec2{ 218, 346 });
        static_assert(EXP_MAT2[1] == fgm::Vec2{ 244, 388 });

        /// @test Verify that 2x4 matrix times a 4x3 matrix yields a 2x3 matrix at compile time.
        constexpr auto EXP_MAT_2X3 = MAT2X4 * MAT4X3;
        static_assert(EXP_MAT_2X3[0] == fgm::Vec2{ 262, 414 });
        static_assert(EXP_MAT_2X3[1] == fgm::Vec2{ 288, 456 });
        static_assert(EXP_MAT_2X3[2] == fgm::Vec2{ 314, 498 });


        /// @test Verify that 2x4 matrix times a 4x4 matrix yields a 2x4 matrix at compile time.
        constexpr auto EXP_MAT_2x4 = MAT2X4 * MAT4;
        static_assert(EXP_MAT_2x4[0] == fgm::Vec2{ 306, 482 });
        static_assert(EXP_MAT_2x4[1] == fgm::Vec2{ 332, 524 });
        static_assert(EXP_MAT_2x4[2] == fgm::Vec2{ 358, 566 });
        static_assert(EXP_MAT_2x4[3] == fgm::Vec2{ 384, 608 });


        /// @test Verify that 2D row vector times a 2x4 matrix yields a 4D row vector at compile time.
        constexpr auto EXP_VEC4 = VEC2 * MAT2X4;
        static_assert(EXP_VEC4.x() == 23);
        static_assert(EXP_VEC4.y() == 26);
        static_assert(EXP_VEC4.z() == 29);
        static_assert(EXP_VEC4.w() == 32);

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

TYPED_TEST(Mat2x4Multiplication, Mat2x4Times4DVector_ReturnsAValid2DVector)
{
    const auto expectedVector = this->_mat2x4 * this->_vec4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec2, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec2, expectedVector);
    }
}


TYPED_TEST(Mat2x4Multiplication, Mat2x4TimesMat4x2_ReturnsAValid2DMatrix)
{
    const auto matrixProduct = this->_mat2x4 * this->_mat4x2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2, matrixProduct);
    }
}


TYPED_TEST(Mat2x4Multiplication, Mat2x4TimesMat4_ReturnsAValid2x4Matrix)
{
    const auto matrixProduct = this->_mat2x4 * this->_mat4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2x4, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2x4, matrixProduct);
    }
}


TYPED_TEST(Mat2x4Multiplication, Mat2x4TimesMat4x3_ReturnsAValid2x3Matrix)
{
    const auto matrixProduct = this->_mat2x4 * this->_mat4x3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2x3, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2x3, matrixProduct);
    }
}


TYPED_TEST(Mat2x4Multiplication, 2DRowVectorTimesMat2x4_ReturnsAValid4DRowVector)
{
    const auto expectedVector = this->_vec2 * this->_mat2x4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec4, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec4, expectedVector);
    }
}

/** @} */
