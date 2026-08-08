/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 04, 2026
 *
 * @brief Verify @ref fgm::Mat4 addition logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4TestSetup.h"



/**
 * @addtogroup T_FGM_Mat4x4_Addition
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat4 Addition.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4AdditionTests: public testing::Test
    {
    protected:
        fgm::Mat4<T> _matA;
        fgm::Mat4<T> _matB;
        fgm::Mat4<T> _expectedSum;

        void SetUp() override
        {
            _matA        = { { T(1), T(2), T(3), T(4) },
                             { T(5), T(6), T(7), T(8) },
                             { T(9), T(10), T(11), T(12) },
                             { T(13), T(14), T(15), T(16) } };
            _matB        = { { T(10), T(20), T(30), T(40) },
                             { T(50), T(60), T(70), T(80) },
                             { T(90), T(100), T(110), T(100) },
                             { T(12), T(13), T(14), T(14) } };
            _expectedSum = {
                { T(11), T(22), T(33), T(44) },
                { T(55), T(66), T(77), T(88) },
                { T(99), T(110), T(121), T(112) },
                { T(25), T(27), T(29), T(30) },
            };
        }
    };
    TYPED_TEST_SUITE(Mat4AdditionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat4 matA(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
        constexpr fgm::Mat4 matB(5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
        constexpr fgm::Mat4 binarySum = matA + matB;

        /// @test Verify that Mat4 can be added at compile time.
        static_assert(binarySum(0, 0) == 6);
        static_assert(binarySum(0, 1) == 8);
        static_assert(binarySum(0, 2) == 10);
        static_assert(binarySum(0, 3) == 12);
        static_assert(binarySum(1, 0) == 14);
        static_assert(binarySum(1, 1) == 16);
        static_assert(binarySum(1, 2) == 18);
        static_assert(binarySum(1, 3) == 20);
        static_assert(binarySum(2, 0) == 22);
        static_assert(binarySum(2, 1) == 24);
        static_assert(binarySum(2, 2) == 26);
        static_assert(binarySum(2, 3) == 28);
        static_assert(binarySum(3, 0) == 30);
        static_assert(binarySum(3, 1) == 32);
        static_assert(binarySum(3, 2) == 34);
        static_assert(binarySum(3, 3) == 36);

    } // namespace static_tests
} // namespace


/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4AdditionTests, PlusOperator_ReturnsMatrixSum)
{
    const fgm::Mat4 sum = this->_matA + this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


TEST(Mat4AdditionTests, PlusOperator_MixedType_PromotesType)
{
    constexpr fgm::Mat4 mat1{ fgm::Vec4{ 1.0f, 2.0f, 3.0f, 7.5f }, fgm::Vec4{ -3.0f, -4.0f, 10.0f, -11.0f },
                              fgm::Vec4{ 4.5f, 3.25f, 3.16f, -22.0f }, fgm::Vec4{ 15.0f, 32.0f, 101.0f, 12.5f } };
    constexpr fgm::Mat4 mat2{ fgm::Vec4{ 11.0, 10.0, 2.0, -1.0 }, fgm::Vec4{ 3.0, -8.0, 12.0, 11.0 },
                              fgm::Vec4{ 3.25, 5.1, 0.0, 0.25 }, fgm::Vec4{ 12.0, 13.0, 14.0, 15.0 } };

    [[maybe_unused]] constexpr fgm::Mat4 sum = mat1 + mat2;
    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


TYPED_TEST(Mat4AdditionTests, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


TEST(Mat4Addition, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    [[maybe_unused]] fgm::Mat4 mat1{ fgm::Vec4{ 1.0f, 2.0f, 3.0f, 7.5f }, fgm::Vec4{ -3.0f, -4.0f, 10.0f, -11.0f },
                                     fgm::Vec4{ 4.5f, 3.25f, 3.16f, -22.0f },
                                     fgm::Vec4{ 15.0f, 32.0f, 101.0f, 12.5f } };
    [[maybe_unused]] constexpr fgm::Mat4 mat2{ fgm::Vec4{ 11.0, 10.0, 2.0, -1.0 }, fgm::Vec4{ 3.0, -8.0, 12.0, 11.0 },
                                               fgm::Vec4{ 3.25, 5.1, 0.0, 0.25 }, fgm::Vec4{ 12.0, 13.0, 14.0, 15.0 } };

    (void) (mat1 += mat2);
    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
