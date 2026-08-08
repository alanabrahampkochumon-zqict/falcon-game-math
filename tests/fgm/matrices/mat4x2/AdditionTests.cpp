/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 21, 2026
 *
 * @brief Verify @ref fgm::Mat4x2 addition logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat4x2TestSetup.h"



/**
 * @addtogroup T_FGM_Mat4x2_Addition
 * @{
 */

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat4x2 Addition.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat4x2AdditionTests: public testing::Test
    {
    protected:
        fgm::Mat4x2<T> _matA;
        fgm::Mat4x2<T> _matB;
        fgm::Mat4x2<T> _expectedSum;

        void SetUp() override
        {
            _matA        = { fgm::Vec4<T>(1, 2, 3, 4), fgm::Vec4<T>(5, 6, 7, 8) };
            _matB        = { fgm::Vec4<T>(5, 6, 1, 5), fgm::Vec4<T>(7, 8, 5, 12) };
            _expectedSum = { fgm::Vec4<T>(6, 8, 4, 9), fgm::Vec4<T>(12, 14, 12, 20) };
        }
    };
    TYPED_TEST_SUITE(Mat4x2AdditionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat4x2 MAT1(1, 2, 3, 4, 5, 6, 7, 8);
        constexpr fgm::Mat4x2 MAT2(5, 6, 7, 8, 10, 11, 12, 13);


        /// @test Verify that Mat4x2 can be added at compile time.
        constexpr fgm::Mat4x2 BINARY_SUM = MAT1 + MAT2;
        static_assert(BINARY_SUM(0, 0) == 6);
        static_assert(BINARY_SUM(0, 1) == 8);
        static_assert(BINARY_SUM(1, 0) == 10);
        static_assert(BINARY_SUM(1, 1) == 12);
        static_assert(BINARY_SUM(2, 0) == 15);
        static_assert(BINARY_SUM(2, 1) == 17);
        static_assert(BINARY_SUM(3, 0) == 19);
        static_assert(BINARY_SUM(3, 1) == 21);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat4x2AdditionTests, PlusOperator_ReturnsMatrixSum)
{
    const fgm::Mat4x2 sum = this->_matA + this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


TEST(Mat4x2Addition, PlusOperator_MixedType_PromotesType)
{
    const fgm::Mat4x2 mat1{ fgm::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, fgm::Vec4{ -3.0f, -4.0f, 12.0f, 0.0f } };
    const fgm::Mat4x2 mat2{
        fgm::Vec4{ 10.0, 2.0, 2.5, 0.5 },
        fgm::Vec4{ 3.0, 8.0, 3.5, 1.5 },
    };

    [[maybe_unused]] const fgm::Mat4x2 sum = mat1 + mat2;
    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


TYPED_TEST(Mat4x2AdditionTests, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


TEST(Mat4x2Addition, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    fgm::Mat4x2 mat1{ fgm::Vec4{ 1.0f, 2.0f, 3.0f, 4.0f }, fgm::Vec4{ -3.0f, -4.0f, 12.0f, 0.0f } };
    const fgm::Mat4x2 mat2{
        fgm::Vec4{ 10.0, 2.0, 2.5, 0.5 },
        fgm::Vec4{ 3.0, 8.0, 3.5, 1.5 },
    };

    mat1 += mat2;
    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
