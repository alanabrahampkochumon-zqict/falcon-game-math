/**
 * @file Mat4x2.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref fgm::Mat4x2 vector and matrix multiplication logic.
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
 * @addtogroup T_FGM_Mat4x2_MatVec_Multiplication
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
     * @brief Test fixture for @ref fgm::Mat4x2 matrix and vector multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrix and vectors.
     */
    template <typename T>
    class Mat4x2Multiplication: public testing::Test
    {

    protected:
        fgm::Vec2<T> _vec2, _expectedFPVec2, _expectedIntVec2;
        fgm::Vec4<T> _vec4, _expectedFPVec4, _expectedIntVec4;

        fgm::Mat2<T> _mat2;
        fgm::Mat2x3<T> _mat2x3;
        fgm::Mat2x4<T> _mat2x4;

        fgm::Mat3x2<T> _mat3x2;

        fgm::Mat4<T> _expectedFPMat4, _expectedIntMat4;
        fgm::Mat4x2<T> _mat4x2, _expectedFPMat4x2, _expectedIntMat4x2;
        fgm::Mat4x3<T> _expectedFPMat4x3, _expectedIntMat4x3;


        void SetUp() override
        {

            _vec2            = fgm::Vec2{ T(1.23412341000000003), T(2.21341324399999984) };
            _expectedFPVec2  = fgm::Vec2{ T(43.60881556301329454), T(13.13528635912819098) };
            _expectedIntVec2 = fgm::Vec2{ T(41), T(12) };


            _vec4            = fgm::Vec4{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988),
                               T(4.01283041000000029) };
            _expectedFPVec4  = { fgm::Vec4{ T(8.57723503050675617), T(10.64013783192313589), T(4.74965736129900851),
                                           T(8.62585211223543524) } };
            _expectedIntVec4 = { fgm::Vec4{ T(7), T(9), T(4), T(7) } };


            _mat2 = { fgm::Vec2{ T(1.32194213899999991), T(3.02134123399999988) },
                      fgm::Vec2{ T(2.12304122299999998), T(4.01283041000000029) } };

            _mat2x3 = { fgm::Vec2{ T(1.32194213899999991), T(4.01283041000000029) },
                        fgm::Vec2{ T(2.12304122299999998), T(5.10238399999999981) },
                        fgm::Vec2{ T(3.02134123399999988), T(6.01238399999999995) } };

            _mat2x4 = { fgm::Vec2{ T(5.12390421300000032), T(2.01234000000000002) },
                        fgm::Vec2{ T(1.01820339999999998), T(1.02384019999999998) },
                        fgm::Vec2{ T(5.01238399999999995), T(5.01238401234000008) },
                        fgm::Vec2{ T(2.01238399999999995), T(1.10234800000000011) } };


            _mat3x2 = { fgm::Vec3{ T(1.32194213899999991), T(3.02134123399999988), T(5.10238399999999981) },
                        fgm::Vec3{ T(2.12304122299999998), T(4.01283041000000029), T(6.01238399999999995) } };

            _mat4x2 = { fgm::Vec4{ T(5.12390421300000032), T(5.01238399999999995), T(2.01234000000000002),
                                   T(5.01238401234000008) },
                        fgm::Vec4{ T(1.01820339999999998), T(2.01238399999999995), T(1.02384019999999998),
                                   T(1.10234800000000011) } };

            _expectedFPMat4x2  = { fgm::Vec4{ T(9.84984481238332776), T(12.70618038429122976), T(5.75356765728206643),
                                             T(9.95665110937957465) },
                                   fgm::Vec4{ T(14.96413743398776930), T(18.71685356930307265), T(8.38077786423230364),
                                             T(15.06503346050664049) } };
            _expectedIntMat4x2 = { fgm::Vec4{ T(8), T(11), T(5), T(8) }, fgm::Vec4{ T(14), T(18), T(8), T(14) } };

            _expectedFPMat4x3  = { fgm::Vec4{ T(10.85938246244972660), T(14.70143733824681576), T(6.76869413353574245),
                                             T(11.04961721956482279) },
                                   fgm::Vec4{ T(16.07352460380797510), T(20.90945378096163054), T(9.49630662972862005),
                                             T(16.26610068133595988) },
                                   fgm::Vec4{ T(21.60289290870881729), T(27.24334782329785298), T(12.23568625586436021),
                                             T(21.77186197475720775) } };
            _expectedIntMat4x3 = { fgm::Vec4{ T(9), T(13), T(6), T(9) }, fgm::Vec4{ T(15), T(20), T(9), T(15) },
                                   fgm::Vec4{ T(21), T(27), T(12), T(21) } };

            _expectedFPMat4  = { fgm::Vec4{ T(28.30336581395515338), T(29.73257631333379436), T(12.37135199205641989),
                                           T(27.90127453232277333) },
                                 fgm::Vec4{ T(6.25965426364760447), T(7.16398606794239967), T(3.09722018509204000),
                                           T(6.23225464025983023) },
                                 fgm::Vec4{ T(30.78660193824402214), T(35.21083475174481237), T(15.21850106823098869),
                                           T(30.64938491654379504) },
                                 fgm::Vec4{ T(11.43367733735699332), T(12.30518884108800037), T(5.17822901534960067),
                                           T(11.30201250139281832) } };
            _expectedIntMat4 = { fgm::Vec4{ T(27), T(29), T(12), T(27) }, fgm::Vec4{ T(6), T(7), T(3), T(6) },
                                 fgm::Vec4{ T(30), T(35), T(15), T(30) }, fgm::Vec4{ T(11), T(12), T(5), T(11) } };
        }
    };
    TYPED_TEST_SUITE(Mat4x2Multiplication, SupportedArithmeticTypes);


    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr fgm::Vec2 VEC2(1, 2);
        // constexpr fgm::Vec3 ROW_VEC3(1, 2, 3);

        constexpr fgm::Mat2 MAT2(1, 2, 3, 4);
        // constexpr fgm::Mat2x3 MAT2X3(1, 2, 3, 4, 5, 6);
        // constexpr fgm::Mat2x4 MAT2X4(5, 1, 5, 2, 2, 1, 5, 1);

        constexpr fgm::Mat4x2 MAT4X2(5, 1, 5, 2, 2, 1, 5, 1);


        /// @test Verify that 4x2 matrix times a 2D column vector yields a 4D column vector at compile time.
        constexpr auto EXP_VEC4 = MAT4X2 * VEC2;
        static_assert(EXP_VEC4.x() == 7);
        static_assert(EXP_VEC4.y() == 9);
        static_assert(EXP_VEC4.z() == 4);
        static_assert(EXP_VEC4.w() == 7);

        /// @test Verify that 4x2 matrix times a 2D matrix yields a 4x2 matrix at compile time.
        constexpr auto EXP_MAT4X2 = MAT4X2 * MAT2;
        static_assert(EXP_MAT4X2[0] == fgm::Vec4{ 8, 11, 5, 8 });
        static_assert(EXP_MAT4X2[1] == fgm::Vec4{ 14, 18, 8, 14 });

        // /// @test Verify that 3x2 matrix times a 2x3 matrix yields a 3x3 matrix at compile time.
        // constexpr auto EXP_MAT3 = MAT3X2 * MAT2X3;
        // static_assert(EXP_MAT3[0] == fgm::Vec3{ 9, 19, 29 });
        // static_assert(EXP_MAT3[1] == fgm::Vec3{ 12, 26, 40 });
        // static_assert(EXP_MAT3[2] == fgm::Vec3{ 15, 33, 51 });
        //
        // /// @test Verify that 3x2 matrix times a 2x4 matrix yields a 3x4 matrix at compile time.
        // constexpr auto EXP_MAT3X4 = MAT3X2 * MAT2X4;
        // static_assert(EXP_MAT3X4[0] == fgm::Vec3{ 9, 23, 37 });
        // static_assert(EXP_MAT3X4[1] == fgm::Vec3{ 3, 7, 11 });
        // static_assert(EXP_MAT3X4[2] == fgm::Vec3{ 15, 35, 55 });
        // static_assert(EXP_MAT3X4[3] == fgm::Vec3{ 4, 10, 16 });
        //
        // /// @test Verify that 3D row vector times a 3x2 matrix yields a 2D row vector at compile time.
        // constexpr auto EXP_ROW_VEC2 = ROW_VEC3 * MAT3X2;
        // static_assert(EXP_ROW_VEC2.x() == 22);
        // static_assert(EXP_ROW_VEC2.y() == 28);

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

TYPED_TEST(Mat4x2Multiplication, Mat4x2Times2DVector_ReturnsAValid4DVector)
{
    const auto expectedVector = this->_mat4x2 * this->_vec2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec4, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec4, expectedVector);
    }
}


TYPED_TEST(Mat4x2Multiplication, Mat4x2TimesMat2_ReturnsAValid4x2Matrix)
{
    const auto matrixProduct = this->_mat4x2 * this->_mat2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat4x2, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat4x2, matrixProduct);
    }
}


// TYPED_TEST(Mat4x2Multiplication, Mat4x2TimesMat2x3_ReturnsAValid3DMatrix)
// {
//     const auto matrixProduct = this->_mat4x2 * this->_mat2x3;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_MAT_EQ(this->_expectedFPMat3, matrixProduct);
//     }
//     else
//     {
//         EXPECT_MAT_EQ(this->_expectedIntMat3, matrixProduct);
//     }
// }
//
//
// TYPED_TEST(Mat4x2Multiplication, Mat4x2TimesMat2x4_ReturnsAValid3x4Matrix)
// {
//     const auto matrixProduct = this->_mat4x2 * this->_mat2x4;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_MAT_EQ(this->_expectedFPMat3x4, matrixProduct);
//     }
//     else
//     {
//         EXPECT_MAT_EQ(this->_expectedIntMat3x4, matrixProduct);
//     }
// }
//
//
// TYPED_TEST(Mat4x2Multiplication, 3DRowVectorTimesMat4x2_ReturnsAValid2DRowVector)
// {
//     const auto expectedVector = this->_vec3 * this->_mat4x2;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_VEC_EQ(this->_expectedFPVec2, expectedVector);
//     }
//     else
//     {
//         EXPECT_VEC_EQ(this->_expectedIntVec2, expectedVector);
//     }
// }

/** @} */
