/**
 * @file Mat2x3.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref fgm::Mat2x3 vector and matrix multiplication logic.
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
 * @addtogroup T_FGM_Mat2x3_MatVec_Multiplication
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
     * @brief Test fixture for @ref fgm::Mat2x3 matrix and vector multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrix and vectors.
     */
    template <typename T>
    class Mat2x3Multiplication: public ::testing::Test
    {

    protected:
        fgm::Vec2<T> _vec2, _expectedFPVec2, _expectedIntVec2;
        fgm::Vec3<T> _vec3, _expectedFPVec3, _expectedIntVec3;

        fgm::Mat2<T> _expectedFPMat2, _expectedIntMat2;
        fgm::Mat2x3<T> _mat2x3, _expectedFPMat2x3, _expectedIntMat2x3;
        fgm::Mat2x4<T> _expectedFPMat2x4, _expectedIntMat2x4;

        fgm::Mat3x2<T> _mat3x2;
        fgm::Mat3<T> _mat3;
        fgm::Mat3x4<T> _mat3x4;


        void SetUp() override
        {
            _vec2            = fgm::Vec2{ T(1.23412341000000003), T(2.23412341000000003) };
            _expectedFPVec2  = fgm::Vec2{ T(44.65805374209299572), T(99.77319165909298704) };
            _expectedIntVec2 = fgm::Vec2{ T(38), T(92) };


            _vec3            = fgm::Vec3{ T(5.12390421300000032), T(6.12390421300000032), T(7.12390421300000032) };
            _expectedFPVec3  = fgm::Vec3{ T(11.28719184981074797), T(14.75543866981074714), T(18.22368548981074809) };
            _expectedIntVec3 = fgm::Vec3{ T(9), T(12), T(15) };


            _expectedFPMat2  = { fgm::Vec2{ T(53.62388015909299099), T(117.73901807609298942) },
                                 fgm::Vec2{ T(60.58970657609299337), T(133.70484449309299180) } };
            _expectedIntMat2 = { fgm::Vec2{ T(46), T(109) }, fgm::Vec2{ T(52), T(124) } };


            _mat2x3            = { fgm::Vec2{ T(1.32194213899999991), T(4.32194213899999991) },
                                   fgm::Vec2{ T(2.32194213899999991), T(5.32194213899999991) },
                                   fgm::Vec2{ T(3.32194213899999991), T(6.32194213899999991) } };
            _expectedFPMat2x3  = { fgm::Vec2{ T(62.58970657609299337), T(135.70484449309299180) },
                                   fgm::Vec2{ T(69.55553299309298154), T(151.67067091009300839) },
                                   fgm::Vec2{ T(76.52135941009299813), T(167.63649732709299656) } };
            _expectedIntMat2x3 = { fgm::Vec2{ T(54), T(126) }, fgm::Vec2{ T(60), T(141) }, fgm::Vec2{ T(66), T(156) } };


            _expectedFPMat2x4  = { fgm::Vec2{ T(71.55553299309299575), T(153.67067091009300839) },
                                   fgm::Vec2{ T(78.52135941009299813), T(169.63649732709299656) },
                                   fgm::Vec2{ T(85.48718582709298630), T(185.60232374409298473) },
                                   fgm::Vec2{ T(92.45301224409298868), T(201.56815016109297289) } };
            _expectedIntMat2x4 = { fgm::Vec2{ T(62), T(143) }, fgm::Vec2{ T(68), T(158) }, fgm::Vec2{ T(74), T(173) },
                                   fgm::Vec2{ T(80), T(188) } };


            _mat3x2 = { fgm::Vec3{ T(5.12390421300000032), T(7.12390421300000032), T(9.12390421299999943) },
                        fgm::Vec3{ T(6.12390421300000032), T(8.12390421299999943), T(10.12390421299999943) } };


            _mat3 = { fgm::Vec3{ T(5.12390421300000032), T(8.12390421299999943), T(11.12390421299999943) },
                      fgm::Vec3{ T(6.12390421300000032), T(9.12390421299999943), T(12.12390421299999943) },
                      fgm::Vec3{ T(7.12390421300000032), T(10.12390421299999943), T(13.12390421299999943) } };


            _mat3x4 = { fgm::Vec3{ T(5.12390421300000032), T(9.12390421299999943), T(13.12390421299999943) },
                        fgm::Vec3{ T(6.12390421300000032), T(10.12390421299999943), T(14.12390421299999943) },
                        fgm::Vec3{ T(7.12390421300000032), T(11.12390421299999943), T(15.12390421299999943) },
                        fgm::Vec3{ T(8.12390421299999943), T(12.12390421299999943), T(16.12390421299999943) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x3Multiplication, SupportedArithmeticTypes);



    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr fgm::Vec2 VEC2(1, 2);
        constexpr fgm::Vec3 VEC3(5, 6, 7);

        constexpr fgm::Mat2x3 MAT2X3(1, 2, 3, 4, 5, 6);

        constexpr fgm::Mat3 MAT3X3(5, 6, 7, 8, 9, 10, 11, 12, 13);
        constexpr fgm::Mat3x2 MAT3X2(5, 6, 7, 8, 9, 10);
        constexpr fgm::Mat3x4 MAT3X4(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);


        /// @test Verify that 2x3 matrix times a 3D column vector yields a 2D column vector at compile time.
        constexpr auto EXP_VEC2 = MAT2X3 * VEC3;
        static_assert(EXP_VEC2.x() == 38);
        static_assert(EXP_VEC2.y() == 92);

        /// @test Verify that 2x3 matrix times a 3x2 matrix yields a 2x2 matrix at compile time.
        constexpr auto EXP_MAT2 = MAT2X3 * MAT3X2;
        static_assert(EXP_MAT2[0] == fgm::Vec2{ 46, 109 });
        static_assert(EXP_MAT2[1] == fgm::Vec2{ 52, 124 });

        /// @test Verify that 2x3 matrix times a 3x3 matrix yields a 2x3 matrix at compile time.
        constexpr auto EXP_MAT_2X3 = MAT2X3 * MAT3X3;
        static_assert(EXP_MAT_2X3[0] == fgm::Vec2{ 54, 126 });
        static_assert(EXP_MAT_2X3[1] == fgm::Vec2{ 60, 141 });
        static_assert(EXP_MAT_2X3[2] == fgm::Vec2{ 66, 156 });

        /// @test Verify that 2x3 matrix times a 3x4 matrix yields a 2x4 matrix at compile time.
        constexpr auto EXP_MAT_2X4 = MAT2X3 * MAT3X4;
        static_assert(EXP_MAT_2X4[0] == fgm::Vec2{ 62, 143 });
        static_assert(EXP_MAT_2X4[1] == fgm::Vec2{ 68, 158 });
        static_assert(EXP_MAT_2X4[2] == fgm::Vec2{ 74, 173 });
        static_assert(EXP_MAT_2X4[3] == fgm::Vec2{ 80, 188 });

        /// @test Verify that 2D row vector times a 2x3 matrix yields a 3D row vector at compile time.
        constexpr auto EXP_VEC3 = VEC2 * MAT2X3;
        static_assert(EXP_VEC3.x() == 9);
        static_assert(EXP_VEC3.y() == 12);
        static_assert(EXP_VEC3.z() == 15);

    } // namespace static_tests

} // namespace

/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

TYPED_TEST(Mat2x3Multiplication, Mat2x3Times3DVector_ReturnsAValid2DVector)
{
    const auto expectedVector = this->_mat2x3 * this->_vec3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec2, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec2, expectedVector);
    }
}


TYPED_TEST(Mat2x3Multiplication, Mat2x3TimesMat3x2_ReturnsAValid2DMatrix)
{
    const auto matrixProduct = this->_mat2x3 * this->_mat3x2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2, matrixProduct);
    }
}


TYPED_TEST(Mat2x3Multiplication, Mat2x3TimesMat3_ReturnsAValid2x3Matrix)
{
    const auto matrixProduct = this->_mat2x3 * this->_mat3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2x3, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2x3, matrixProduct);
    }
}


TYPED_TEST(Mat2x3Multiplication, Mat2x3TimesMat3x4_ReturnsAValid2x4Matrix)
{
    const auto matrixProduct = this->_mat2x3 * this->_mat3x4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2x4, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2x4, matrixProduct);
    }
}


TYPED_TEST(Mat2x3Multiplication, 2DRowVectorTimeMat2x3_ReturnsAValid3DRowVector)
{
    const auto expectedVector = this->_vec2 * this->_mat2x3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec3, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec3, expectedVector);
    }
}

/** @} */
