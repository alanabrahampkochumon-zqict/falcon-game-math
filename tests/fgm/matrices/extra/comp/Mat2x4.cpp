/**
 * @file Mat2x4.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 24, 2026
 *
 * @brief Verify @ref fgm::Mat2x4 composition (matrix-matrix Composition) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <fgm/matrices/extra/Comp.h>
#include <gtest/gtest.h>


using namespace testutils;



/**
 * @addtogroup T_FGM_Mat2x4_Comp
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
     * @brief Test fixture for @ref fgm::Mat2x4 matrix composition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2x4Composition: public testing::Test
    {

    protected:
        fgm::Mat2<T> _mat2, _expectedFPMat2, _expectedIntMat2;
        fgm::Mat2x3<T> _expectedFPMat2x3, _expectedIntMat2x3;
        fgm::Mat2x4<T> _mat2x4, _expectedFPMat2x4, _expectedIntMat2x4;

        /// 2x2 by 2x4 multiplication result
        fgm::Mat2x4<T> _expectedFPMat2x4SquareMat, _expectedIntMat2x4SquareMat;

        fgm::Mat4<T> _mat4;
        fgm::Mat4x2<T> _mat4x2;
        fgm::Mat4x3<T> _mat4x3;

        void SetUp() override
        {
            _expectedFPMat2  = { fgm::Vec2{ T(51.53148302175357287), T(31.05492997565247038) },
                                 fgm::Vec2{ T(14.61642063652532286), T(10.45638242976778720) } };
            _expectedIntMat2 = { fgm::Vec2{ T(50), T(30) }, fgm::Vec2{ T(14), T(10) } };

            _expectedFPMat2x3  = { fgm::Vec2{ T(59.71294882333997123), T(40.93849965675766356) },
                                   fgm::Vec2{ T(17.06563996375492565), T(11.97595332411097502) },
                                   fgm::Vec2{ T(70.16686590855846362), T(46.29281811210886133) } };
            _expectedIntMat2x3 = { fgm::Vec2{ T(58), T(40) }, fgm::Vec2{ T(16), T(11) }, fgm::Vec2{ T(69), T(45) } };


            _mat2 = { fgm::Vec2{ T(1.32194213899999991), T(3.02134123399999988) },
                      fgm::Vec2{ T(2.12304122299999998), T(4.01283041000000029) } };

            _mat2x4            = { fgm::Vec2{ T(5.12390421300000032), T(2.01234000000000002) },
                                   fgm::Vec2{ T(1.01820339999999998), T(1.02384019999999998) },
                                   fgm::Vec2{ T(5.01238399999999995), T(5.01238401234000008) },
                                   fgm::Vec2{ T(2.01238399999999995), T(1.10234800000000011) } };
            _expectedFPMat2x4  = { fgm::Vec2{ T(67.53826583649818360), T(45.22504796609911892) },
                                   fgm::Vec2{ T(28.27462878677400582), T(22.23648098676159535) },
                                   fgm::Vec2{ T(51.74586730346002383), T(31.51383195965590645) },
                                   fgm::Vec2{ T(66.95907009498898788), T(56.22624476530457116) } };
            _expectedIntMat2x4 = { fgm::Vec2{ T(66), T(44) }, fgm::Vec2{ T(27), T(21) }, fgm::Vec2{ T(50), T(30) },
                                   fgm::Vec2{ T(64), T(54) } };

            _expectedFPMat2x4SquareMat  = { fgm::Vec2{ T(5.12390421300000032), T(2.01234000000000002) },
                                            fgm::Vec2{ T(1.01820339999999998), T(1.02384019999999998) },
                                            fgm::Vec2{ T(5.01238399999999995), T(5.01238401234000008) },
                                            fgm::Vec2{ T(2.01238399999999995), T(1.10234800000000011) } };
            _expectedIntMat2x4SquareMat = { fgm::Vec2{ T(9), T(23) }, fgm::Vec2{ T(3), T(7) },
                                            fgm::Vec2{ T(15), T(35) }, fgm::Vec2{ T(4), T(10) } };

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
    TYPED_TEST_SUITE(Mat2x4Composition, SupportedArithmeticTypes);


    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr fgm::Mat2 MAT2(1, 2, 3, 4);
        constexpr fgm::Mat2x4 MAT2X4(5, 6, 7, 8, 9, 10, 11, 12);

        constexpr fgm::Mat4 MAT4(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
        constexpr fgm::Mat4x2 MAT4X2(5, 6, 7, 8, 9, 10, 11, 12);
        constexpr fgm::Mat4x3 MAT4X3(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);


        /// @test Verify that 2x4 matrix times a 4x2 matrix yields a 2x2 matrix at compile time.
        constexpr auto EXP_MAT2 = MAT2X4 * MAT4X2;
        static_assert(EXP_MAT2[0] == fgm::Vec2{ 218, 346 });
        static_assert(EXP_MAT2[1] == fgm::Vec2{ 244, 388 });

        /// @test Verify that 2x4 matrix times a 4x3 matrix yields a 2x3 matrix at compile time.
        constexpr auto EXP_MAT2X3 = MAT2X4 * MAT4X3;
        static_assert(EXP_MAT2X3[0] == fgm::Vec2{ 262, 414 });
        static_assert(EXP_MAT2X3[1] == fgm::Vec2{ 288, 456 });
        static_assert(EXP_MAT2X3[2] == fgm::Vec2{ 314, 498 });


        /// @test Verify that 2x4 matrix times a 4x4 matrix yields a 2x4 matrix at compile time.
        constexpr auto EXP_MAT2X4 = MAT2X4 * MAT4;
        static_assert(EXP_MAT2X4[0] == fgm::Vec2{ 306, 482 });
        static_assert(EXP_MAT2X4[1] == fgm::Vec2{ 332, 524 });
        static_assert(EXP_MAT2X4[2] == fgm::Vec2{ 358, 566 });
        static_assert(EXP_MAT2X4[3] == fgm::Vec2{ 384, 608 });

        /// @test Verify that 2x2 matrix times a 2x4 matrix yields a 2x4 matrix at compile time.
        constexpr auto EXP_MAT2X4SQ = MAT2 * MAT2X4;
        static_assert(EXP_MAT2X4SQ[0] == fgm::Vec2{ 23, 51 });
        static_assert(EXP_MAT2X4SQ[1] == fgm::Vec2{ 26, 58 });
        static_assert(EXP_MAT2X4SQ[2] == fgm::Vec2{ 29, 65 });
        static_assert(EXP_MAT2X4SQ[3] == fgm::Vec2{ 32, 72 });

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

TYPED_TEST(Mat2x4Composition, Mat2x4TimesMat4x2_ReturnsAValid2DMatrix)
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


TYPED_TEST(Mat2x4Composition, Mat2x4TimesMat4_ReturnsAValid2x4Matrix)
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


TYPED_TEST(Mat2x4Composition, Mat2x4TimesMat4x3_ReturnsAValid2x3Matrix)
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


TYPED_TEST(Mat2x4Composition, Mat2TimesMat2x4_ReturnsAValid2x4Matrix)
{
    const auto matrixProduct = this->_mat2 * this->_mat2x4;
    if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_MAT_EQ(this->_expectedFPMat2x4SquareMat, matrixProduct);
    }
    else
    {
        EXPECT_MAT_EQ(this->_expectedIntMat2x4SquareMat, matrixProduct);
    }
}



/** @} */
