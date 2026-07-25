/**
 * @file Mat3x4.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 25, 2026
 *
 * @brief Verify @ref fgm::Mat3x4 vector and matrix multiplication logic.
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
 * @addtogroup T_FGM_Mat3x4_MatVec_Multiplication
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
     * @brief Test fixture for @ref fgm::Mat3x4 matrix and vector multiplication.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrix and vectors.
     */
    template <typename T>
    class Mat3x4Multiplication: public testing::Test
    {

    protected:
        fgm::Vec3<T> _vec3, _expectedFPVec3, _expectedIntVec3;
        fgm::Vec4<T> _vec4, _expectedFPVec4, _expectedIntVec4;

        fgm::Mat3x2<T> _expectedFPMat3x2, _expectedIntMat3x2;
        fgm::Mat3x4<T> _mat3x4, _expectedFPMat3x4, _expectedIntMat3x4;

        fgm::Mat3<T> _expectedFPMat3, _expectedIntMat3;
        fgm::Mat4<T> _mat4;
        fgm::Mat4x2<T> _mat4x2;
        fgm::Mat4x3<T> _mat4x3;

        void SetUp() override
        {

            _vec3            = fgm::Vec3{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988) };
            _expectedFPVec3  = { fgm::Vec3{ T(32.15467085860238683), T(24.40151006828770974),
                                           T(16.28906864577547253) } };
            _expectedIntVec3 = { fgm::Vec3{ T(30), T(23), T(15) } };

            _vec4            = { fgm::Vec4{ T(1.32194213899999991), T(2.12304122299999998), T(3.02134123399999988),
                                 T(4.01283041000000029) } };
            _expectedFPVec4  = fgm::Vec4{ T(11.08456156345330790), T(4.27872517874863956), T(20.91827216587800464),
                                         T(14.10190761507471002) };
            _expectedIntVec4 = fgm::Vec4{ T(9), T(3), T(18), T(13) };


            _expectedFPMat3  = { fgm::Vec3{ T(59.71294882333997123), T(40.93849965675766356), T(16.03666856715538813) },
                                 fgm::Vec3{ T(17.06563996375492565), T(11.97595332411097502), T(8.24852207871460053) },
                                 fgm::Vec3{ T(70.16686590855846362), T(46.29281811210886133),
                                           T(33.79743870785883786) } };
            _expectedIntMat3 = { fgm::Vec3{ T(58), T(40), T(14) }, fgm::Vec3{ T(16), T(11), T(7) },
                                 fgm::Vec3{ T(69), T(45), T(32) } };

            _expectedFPMat3x2 = {
                fgm::Vec3{ T(51.53148302175357287), T(31.05492997565247038), T(18.85558683533477620) },
                fgm::Vec3{ T(14.61642063652532286), T(10.45638242976778720), T(5.07640795416880053) }
            };
            _expectedIntMat3x2 = { fgm::Vec3{ T(50), T(30), T(17) }, fgm::Vec3{ T(14), T(10), T(4) } };

            _mat3x4           = { fgm::Vec3{ T(5.12390421300000032), T(2.01234000000000002), T(0.01283400000000000) },
                                  fgm::Vec3{ T(1.01820339999999998), T(1.02384019999999998), T(0.25123420000000002) },
                                  fgm::Vec3{ T(5.01238399999999995), T(5.01238401234000008), T(1.20830199999999999) },
                                  fgm::Vec3{ T(2.01238399999999995), T(1.10234800000000011), T(3.01234499999999983) } };
            _expectedFPMat3x4 = {
                fgm::Vec3{ T(67.53826583649818360), T(45.22504796609911892), T(27.75047042839509359) },
                fgm::Vec3{ T(28.27462878677400582), T(22.23648098676159535), T(13.56335074930463946) },
                fgm::Vec3{ T(51.74586730346002383), T(31.51383195965590645), T(19.32819075818702714) },
                fgm::Vec3{ T(66.95907009498898788), T(56.22624476530457116), T(26.12189714725359835) }
            };
            _expectedIntMat3x4 = { fgm::Vec3{ T(66), T(44), T(26) }, fgm::Vec3{ T(27), T(21), T(12) },
                                   fgm::Vec3{ T(50), T(30), T(17) }, fgm::Vec3{ T(64), T(54), T(21) } };


            _mat4 = { fgm::Vec4{ T(5.12390421300000032), T(2.01234000000000002), T(5.01238399999999995),
                                 T(7.01203481000000028) },
                      fgm::Vec4{ T(1.01820339999999998), T(1.02384019999999998), T(3.12343210000000004),
                                 T(3.16000000000000014) },
                      fgm::Vec4{ T(5.01238399999999995), T(5.01238401234000008), T(2.12389900000000020),
                                 T(5.12500000000000000) },
                      fgm::Vec4{ T(2.01238399999999995), T(1.10234800000000011), T(9.10234799999999922),
                                 T(4.91999999999999993) } };

            _mat4x2 = { fgm::Vec4{ T(5.12390421300000032), T(5.01238399999999995), T(2.01234000000000002),
                                   T(5.01238401234000008) },
                        fgm::Vec4{ T(1.01820339999999998), T(2.01238399999999995), T(1.02384019999999998),
                                   T(1.10234800000000011) } };

            _mat4x3 = { fgm::Vec4{ T(5.12390421300000032), T(2.01238399999999995), T(5.01238401234000008),
                                   T(3.12343210000000004) },
                        fgm::Vec4{ T(1.01820339999999998), T(2.01234000000000002), T(1.10234800000000011),
                                   T(2.12389900000000020) },
                        fgm::Vec4{ T(5.01238399999999995), T(1.02384019999999998), T(5.01238399999999995),
                                   T(9.10234799999999922) } };
        }
    };
    TYPED_TEST_SUITE(Mat3x4Multiplication, SupportedArithmeticTypes);


    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        // constexpr fgm::Vec2 ROW_VEC2(1, 2);
        constexpr fgm::Vec4 VEC4(1, 2, 3, 4);

        constexpr fgm::Mat3x4 MAT3X4(5, 1, 5, 2, 2, 1, 5, 1, 0, 0, 1, 3);

        // constexpr fgm::Mat4 MAT4(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
        constexpr fgm::Mat4x2 MAT4X2(5, 1, 5, 2, 2, 1, 5, 1);
        constexpr fgm::Mat4x3 MAT4X3(5, 1, 5, 2, 2, 1, 5, 1, 5, 3, 2, 9);


        /// @test Verify that 3x4 matrix times a 4D column vector yields a 3D column vector at compile time.
        constexpr auto EXP_VEC3 = MAT3X4 * VEC4;
        static_assert(EXP_VEC3.x() == 30);
        static_assert(EXP_VEC3.y() == 23);
        static_assert(EXP_VEC3.z() == 15);

        /// @test Verify that 3x4 matrix times a 4x2 matrix yields a 3x2 matrix at compile time.
        constexpr auto EXP_MAT3X2 = MAT3X4 * MAT4X2;
        static_assert(EXP_MAT3X2[0] == fgm::Vec3{ 50, 30, 17 });
        static_assert(EXP_MAT3X2[1] == fgm::Vec3{ 14, 10, 4 });

        /// @test Verify that 3x4 matrix times a 4x3 matrix yields a 3D matrix at compile time.
        constexpr auto EXP_MAT3 = MAT3X4 * MAT4X3;
        static_assert(EXP_MAT3[0] == fgm::Vec3{ 58, 40, 14 });
        static_assert(EXP_MAT3[1] == fgm::Vec3{ 16, 11, 7 });
        static_assert(EXP_MAT3[2] == fgm::Vec3{ 69, 45, 32 });

        // /// @test Verify that 2x4 matrix times a 4x4 matrix yields a 2x4 matrix at compile time.
        // constexpr auto EXP_MAT_2X4 = MAT2X4 * MAT4;
        // static_assert(EXP_MAT_2X4[0] == fgm::Vec2{ 306, 482 });
        // static_assert(EXP_MAT_2X4[1] == fgm::Vec2{ 332, 524 });
        // static_assert(EXP_MAT_2X4[2] == fgm::Vec2{ 358, 566 });
        // static_assert(EXP_MAT_2X4[3] == fgm::Vec2{ 384, 608 });
        //
        //
        // /// @test Verify that 2D row vector times a 2x4 matrix yields a 4D row vector at compile time.
        // constexpr auto EXP_ROW_VEC4 = ROW_VEC2 * MAT2X4;
        // static_assert(EXP_ROW_VEC4.x() == 23);
        // static_assert(EXP_ROW_VEC4.y() == 26);
        // static_assert(EXP_ROW_VEC4.z() == 29);
        // static_assert(EXP_ROW_VEC4.w() == 32);

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

TYPED_TEST(Mat3x4Multiplication, Mat3x4Times4DVector_ReturnsAValid3DVector)
{
    const auto expectedVector = this->_mat3x4 * this->_vec4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_VEC_EQ(this->_expectedFPVec3, expectedVector);
    }
    else
    {
        EXPECT_VEC_EQ(this->_expectedIntVec3, expectedVector);
    }
}


TYPED_TEST(Mat3x4Multiplication, Mat3x4TimesMat4x2_ReturnsAValid3x2Matrix)
{
    const auto matrixProduct = this->_mat3x4 * this->_mat4x2;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat3x2, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat3x2, matrixProduct);
    }
}


TYPED_TEST(Mat3x4Multiplication, Mat3x4TimesMat4x3_ReturnsAValid3DMatrix)
{
    const auto matrixProduct = this->_mat3x4 * this->_mat4x3;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat3, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat3, matrixProduct);
    }
}


// TYPED_TEST(Mat3x4Multiplication, Mat3x4TimesMat4x3_ReturnsAValid2x3Matrix)
// {
//     const auto matrixProduct = this->_mat3x4 * this->_mat4x3;
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
// TYPED_TEST(Mat3x4Multiplication, 2DRowVectorTimesMat3x4_ReturnsAValid4DRowVector)
// {
//     const auto expectedVector = this->_vec2 * this->_mat3x4;
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
