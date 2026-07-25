/**
 * @file Mat2x3.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 17, 2026
 *
 * @brief Verify @ref fgm::Mat2x3 composition (matrix-matrix Composition) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <fgm/matrices/extra/Comp.h>
#include <gtest/gtest.h>


using namespace testutils;



/**
 * @addtogroup T_FGM_Mat2x3_Comp
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
     * @brief Test fixture for @ref fgm::Mat2x3 matrix composition.
     *
     * @tparam T The scalar type (e.g., float, double) used for the matrices.
     */
    template <typename T>
    class Mat2x3Composition: public ::testing::Test
    {

    protected:
        fgm::Mat2<T> _expectedFPMat2, _expectedIntMat2;
        fgm::Mat2x3<T> _mat2x3, _expectedFPMat2x3, _expectedIntMat2x3;
        fgm::Mat2x4<T> _expectedFPMat2x4, _expectedIntMat2x4;

        fgm::Mat3x2<T> _mat3x2;
        fgm::Mat3<T> _mat3;
        fgm::Mat3x4<T> _mat3x4;


        void SetUp() override
        {

            _expectedFPMat2  = { fgm::Vec2{ T(26.51643186788337658), T(64.24805428618311964) },
                                 fgm::Vec2{ T(39.21223418982177122), T(83.83742932933810721) } };
            _expectedIntMat2 = { fgm::Vec2{ T(24), T(63) }, fgm::Vec2{ T(38), T(83) } };


            _mat2x3            = { fgm::Vec2{ T(1.32194213899999991), T(4.01283041000000029) },
                                   fgm::Vec2{ T(2.12304122299999998), T(5.10238399999999981) },
                                   fgm::Vec2{ T(3.02134123399999988), T(6.01238399999999995) } };
            _expectedFPMat2x3  = { fgm::Vec2{ T(26.19000158099516895), T(60.96569200495833485) },
                                   fgm::Vec2{ T(8.94885622184232510), T(20.98134846327739567) },
                                   fgm::Vec2{ T(8.83851247021109643), T(25.41503573309023878) } };
            _expectedIntMat2x3 = { fgm::Vec2{ T(24), T(60) }, fgm::Vec2{ T(8), T(20) }, fgm::Vec2{ T(7), T(25) } };


            _expectedFPMat2x4  = { fgm::Vec2{ T(11.08456156345330790), T(30.90625299866951892) },
                                   fgm::Vec2{ T(4.27872517874863956), T(10.82041990645499396) },
                                   fgm::Vec2{ T(20.91827216587800464), T(52.95373054018485703) },
                                   fgm::Vec2{ T(14.10190761507471002), T(31.81133338990943926) } };
            _expectedIntMat2x4 = { fgm::Vec2{ T(9), T(30) }, fgm::Vec2{ T(3), T(9) }, fgm::Vec2{ T(18), T(51) },
                                   fgm::Vec2{ T(13), T(31) } };


            _mat3x2 = { fgm::Vec3{ T(5.12390421300000032), T(5.01238399999999995), T(3.01238040000000007) },
                        fgm::Vec3{ T(1.01820339999999998), T(5.01238042099999959), T(9.01081203400000064) } };

            _mat3 = { fgm::Vec3{ T(5.12390421300000032), T(2.01238399999999995), T(5.01238401234000008) },
                      fgm::Vec3{ T(1.01820339999999998), T(2.01234000000000002), T(1.10234800000000011) },
                      fgm::Vec3{ T(5.01238399999999995), T(1.02384019999999998), T(0.01283400000000000) } };

            _mat3x4 = { fgm::Vec3{ T(5.12390421300000032), T(2.01234000000000002), T(0.01283400000000000) },
                        fgm::Vec3{ T(1.01820339999999998), T(1.02384019999999998), T(0.25123420000000002) },
                        fgm::Vec3{ T(5.01238399999999995), T(5.01238401234000008), T(1.20830199999999999) },
                        fgm::Vec3{ T(2.01238399999999995), T(1.10234800000000011), T(3.01234499999999983) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x3Composition, SupportedArithmeticTypes);



    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        // STATIC TEST SETUP
        constexpr fgm::Mat2x3 MAT2X3(1, 2, 3, 4, 5, 6);
        constexpr fgm::Mat3 MAT3X3(5, 6, 7, 8, 9, 10, 11, 12, 13);
        constexpr fgm::Mat3x2 MAT3X2(5, 6, 7, 8, 9, 10);
        constexpr fgm::Mat3x4 MAT3X4(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);


        /// @test Verify that 2x3 matrix times a 3x2 matrix yields a 2x2 matrix at compile time.
        constexpr auto EXP_MAT2 = MAT2X3 * MAT3X2;
        static_assert(EXP_MAT2[0] == fgm::Vec2{ 46, 109 });
        static_assert(EXP_MAT2[1] == fgm::Vec2{ 52, 124 });

        /// @test Verify that 2x3 matrix times a 3x3 matrix yields a 2x3 matrix at compile time.
        constexpr auto EXP_MAT2X3 = MAT2X3 * MAT3X3;
        static_assert(EXP_MAT2X3[0] == fgm::Vec2{ 54, 126 });
        static_assert(EXP_MAT2X3[1] == fgm::Vec2{ 60, 141 });
        static_assert(EXP_MAT2X3[2] == fgm::Vec2{ 66, 156 });

        /// @test Verify that 2x3 matrix times a 3x4 matrix yields a 2x4 matrix at compile time.
        constexpr auto EXP_MAT2X4 = MAT2X3 * MAT3X4;
        static_assert(EXP_MAT2X4[0] == fgm::Vec2{ 62, 143 });
        static_assert(EXP_MAT2X4[1] == fgm::Vec2{ 68, 158 });
        static_assert(EXP_MAT2X4[2] == fgm::Vec2{ 74, 173 });
        static_assert(EXP_MAT2X4[3] == fgm::Vec2{ 80, 188 });

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *            RUNTIME TESTS           *
 *                                    *
 **************************************/

TYPED_TEST(Mat2x3Composition, Mat2x3TimesMat3x2_ReturnsAValid2DMatrix)
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


TYPED_TEST(Mat2x3Composition, Mat2x3TimesMat3_ReturnsAValid2x3Matrix)
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


TYPED_TEST(Mat2x3Composition, Mat2x3TimesMat3x4_ReturnsAValid2x4Matrix)
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


/** @} */
