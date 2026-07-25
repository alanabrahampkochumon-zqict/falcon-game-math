/**
 * @file Mat3x2.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref fgm::Mat3x2 vector and matrix multiplication logic.
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
 * @addtogroup T_FGM_Mat3x2_MatVec_Multiplication
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
     * @brief Test fixture for @ref fgm::Mat3x2 matrix and vector multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrix and vectors.
     */
    template <typename T>
    class Mat3x2Multiplication: public testing::Test
    {

    protected:
        fgm::Vec2<T> _vec2, _expectedFPVec2, _expectedIntVec2;
        fgm::Vec3<T> _vec3, _expectedFPVec3, _expectedIntVec3;

        fgm::Mat2<T> _mat2;
        fgm::Mat2x3<T> _mat2x3;
        fgm::Mat3<T> _expectedFPMat3, _expectedIntMat3;
        fgm::Mat3x2<T> _mat3x2, _expectedFPMat3x2, _expectedIntMat3x2;

        fgm::Mat2x4<T> _mat2x4;
        fgm::Mat3x4<T> _expectedFPMat3x4, _expectedIntMat3x4;

        void SetUp() override
        {
            _vec2            = fgm::Vec2{ T(1.23412341000000003), T(2.21341324399999984) };
            _expectedFPVec2  = fgm::Vec2{ T(23.57800617829743928), T(29.49140573069764315) };
            _expectedIntVec2 = fgm::Vec2{ T(22), T(28) };

            _vec3            = fgm::Vec3{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988) };
            _expectedFPVec3  = fgm::Vec3{ T(6.33060730095153090), T(12.61075992189763717), T(19.60486191482313600) };
            _expectedIntVec3 = fgm::Vec3{ T(5), T(11), T(17) };

            _mat2 = { fgm::Vec2{ T(1.32194213899999991), T(3.02134123399999988) },
                      fgm::Vec2{ T(2.12304122299999998), T(4.01283041000000029) } };

            _mat3x2 = { fgm::Vec3{ T(1.32194213899999991), T(3.02134123399999988), T(5.10238399999999981) },
                        fgm::Vec3{ T(2.12304122299999998), T(4.01283041000000029), T(6.01238399999999995) } };


            _expectedFPMat3x2 = { fgm::Vec3{ T(8.16196300739558467), T(16.11816827630498494), T(24.91052011280122969) },
                                  fgm::Vec3{ T(11.32594203685578726), T(22.51723988795246001),
                                             T(34.95924891937306711) } };
            _expectedIntMat3x2 = { fgm::Vec3{ T(7), T(15), T(23) }, fgm::Vec3{ T(10), T(22), T(34) } };

            _mat2x3 = { fgm::Vec2{ T(1.32194213899999991), T(4.01283041000000029) },
                        fgm::Vec2{ T(2.12304122299999998), T(5.10238399999999981) },
                        fgm::Vec2{ T(3.02134123399999988), T(6.01238399999999995) } };

            _expectedFPMat3  = { fgm::Vec3{ T(10.26693540020188777), T(20.09684619294363017), T(30.87173377075681557) },
                                 fgm::Vec3{ T(13.63910922309342588), T(26.88943366722913098), T(41.51006349103163018) },
                                 fgm::Vec3{ T(16.75857737402849068), T(33.25518020406607889),
                                           T(51.56480453435784739) } };
            _expectedIntMat3 = { fgm::Vec3{ T(9), T(19), T(29) }, fgm::Vec3{ T(12), T(26), T(40) },
                                 fgm::Vec3{ T(15), T(33), T(51) } };

            _mat2x4 = { fgm::Vec2{ T(5.12390421300000032), T(2.01234000000000002) },
                        fgm::Vec2{ T(1.01820339999999998), T(1.02384019999999998) },
                        fgm::Vec2{ T(5.01238399999999995), T(5.01238401234000008) },
                        fgm::Vec2{ T(2.01238399999999995), T(1.10234800000000011) } };

            _expectedFPMat3x4 = {
                fgm::Vec3{ T(11.04578567005615142), T(23.55624222506261845), T(38.24308769250379214) },
                fgm::Vec3{ T(3.51966093089763676), T(7.18483700655947821), T(11.35098517394239970) },
                fgm::Vec3{ T(17.26757951015333603), T(35.25796945115762071), T(55.71148536110482041) },
                fgm::Vec3{ T(5.00058545554098011), T(10.50363433464453600), T(16.89569540108799828) }
            };
            _expectedIntMat3x4 = { fgm::Vec3{ T(9), T(23), T(37) }, fgm::Vec3{ T(3), T(7), T(11) },
                                   fgm::Vec3{ T(15), T(35), T(55) }, fgm::Vec3{ T(4), T(10), T(16) } };
        }
    };
    TYPED_TEST_SUITE(Mat3x2Multiplication, SupportedArithmeticTypes);


    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr fgm::Vec2 VEC2(1, 2);
        // constexpr fgm::Vec4 VEC4(1, 2, 3, 4);
        //
        constexpr fgm::Mat2 MAT2(1, 2, 3, 4);
        constexpr fgm::Mat3x2 MAT3X2(1, 2, 3, 4, 5, 6);
        //
        // constexpr fgm::Mat4 MAT4(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
        // constexpr fgm::Mat4x2 MAT4X2(5, 6, 7, 8, 9, 10, 11, 12);
        // constexpr fgm::Mat4x3 MAT4X3(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        //
        //
        /// @test Verify that 3x2 matrix times a 2D column vector yields a 3D column vector at compile time.
        constexpr auto EXP_VEC3 = MAT3X2 * VEC2;
        static_assert(EXP_VEC3.x() == 5);
        static_assert(EXP_VEC3.y() == 11);
        static_assert(EXP_VEC3.z() == 17);

        /// @test Verify that 3x2 matrix times a 2D matrix yields a 3x2 matrix at compile time.
        constexpr auto EXP_MAT2 = MAT3X2 * MAT2;
        static_assert(EXP_MAT2[0] == fgm::Vec3{ 7, 15, 23 });
        static_assert(EXP_MAT2[1] == fgm::Vec3{ 10, 22, 34 });

        // /// @test Verify that 3x2 matrix times a 4x3 matrix yields a 2x3 matrix at compile time.
        // constexpr auto EXP_MAT_2X3 = MAT2X4 * MAT4X3;
        // static_assert(EXP_MAT_2X3[0] == fgm::Vec2{ 262, 414 });
        // static_assert(EXP_MAT_2X3[1] == fgm::Vec2{ 288, 456 });
        // static_assert(EXP_MAT_2X3[2] == fgm::Vec2{ 314, 498 });
        //
        //
        // /// @test Verify that 3x2 matrix times a 4x4 matrix yields a 2x4 matrix at compile time.
        // constexpr auto EXP_MAT_2X4 = MAT2X4 * MAT4;
        // static_assert(EXP_MAT_2X4[0] == fgm::Vec2{ 306, 482 });
        // static_assert(EXP_MAT_2X4[1] == fgm::Vec2{ 332, 524 });
        // static_assert(EXP_MAT_2X4[2] == fgm::Vec2{ 358, 566 });
        // static_assert(EXP_MAT_2X4[3] == fgm::Vec2{ 384, 608 });
        //
        //
        // /// @test Verify that 2D row vector times a 3x2 matrix yields a 4D row vector at compile time.
        // constexpr auto EXP_VEC4 = VEC2 * MAT2X4;
        // static_assert(EXP_VEC4.x() == 23);
        // static_assert(EXP_VEC4.y() == 26);
        // static_assert(EXP_VEC4.z() == 29);
        // static_assert(EXP_VEC4.w() == 32);

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

TYPED_TEST(Mat3x2Multiplication, Mat3x2Times2DVector_ReturnsAValid3DVector)
{
    const auto expectedVector = this->_mat3x2 * this->_vec2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec3, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec3, expectedVector);
    }
}


TYPED_TEST(Mat3x2Multiplication, Mat3x2TimesMat2x3_ReturnsAValid3DMatrix)
{
    const auto matrixProduct = this->_mat3x2 * this->_mat2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat3x2, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat3x2, matrixProduct);
    }
}


// TYPED_TEST(Mat3x2Multiplication, Mat3x2TimesMat4_ReturnsAValid2x4Matrix)
// {
//     const auto matrixProduct = this->_mat3x2 * this->_mat4;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_MAT_EQ(this->_expectedFPMat3x2, matrixProduct);
//     }
//     else
//     {
//         EXPECT_MAT_EQ(this->_expectedIntMat3x2, matrixProduct);
//     }
// }
//
//
// TYPED_TEST(Mat3x2Multiplication, Mat3x2TimesMat4x3_ReturnsAValid2x3Matrix)
// {
//     const auto matrixProduct = this->_mat3x2 * this->_mat4x3;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_MAT_EQ(this->_expectedFPMat2x3, matrixProduct);
//     }
//     else
//     {
//         EXPECT_MAT_EQ(this->_expectedIntMat2x3, matrixProduct);
//     }
// }
//
//
// TYPED_TEST(Mat3x2Multiplication, 2DRowVectorTimesMat3x2_ReturnsAValid4DRowVector)
// {
//     const auto expectedVector = this->_vec2 * this->_mat3x2;
//     if constexpr (std::is_floating_point_v<TypeParam>)
//     {
//         EXPECT_VEC_EQ(this->_expectedFPVec4, expectedVector);
//     }
//     else
//     {
//         EXPECT_VEC_EQ(this->_expectedIntVec4, expectedVector);
//     }
// }

/** @} */
