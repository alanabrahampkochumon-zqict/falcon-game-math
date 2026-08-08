/**
 * @file AdditionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 18, 2026
 *
 * @brief Verify @ref fgm::Mat3x2 addition logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Mat3x2TestSetup.h"


/**
 * @addtogroup T_FGM_Mat3x2_Addition
 * @{
 */

namespace
{

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat3x2 Addition.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3x2AdditionTests: public testing::Test
    {
    protected:
        fgm::Mat3x2<T> _matA;
        fgm::Mat3x2<T> _matB;
        fgm::Mat3x2<T> _expectedSum;

        void SetUp() override
        {
            _matA        = { fgm::Vec3<T>(1, 2, 3), fgm::Vec3<T>(4, 5, 6) };
            _matB        = { fgm::Vec3<T>(5, 6, 1), fgm::Vec3<T>(7, 8, 5) };
            _expectedSum = { fgm::Vec3<T>(6, 8, 4), fgm::Vec3<T>(11, 13, 11) };
        }
    };
    TYPED_TEST_SUITE(Mat3x2AdditionTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Mat3x2 MAT1(1, 2, 3, 4, 5, 6);
        constexpr fgm::Mat3x2 MAT2(5, 6, 7, 8, 10, 11);

        /// @test Verify that Mat3x2 can be added at compile time.
        constexpr fgm::Mat3x2 BINARY_SUM = MAT1 + MAT2;
        static_assert(BINARY_SUM(0, 0) == 6);
        static_assert(BINARY_SUM(0, 1) == 8);
        static_assert(BINARY_SUM(1, 0) == 10);
        static_assert(BINARY_SUM(1, 1) == 12);
        static_assert(BINARY_SUM(2, 0) == 15);
        static_assert(BINARY_SUM(2, 1) == 17);

    } // namespace static_tests
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TYPED_TEST(Mat3x2AdditionTests, PlusOperator_ReturnsMatrixSum)
{
    const fgm::Mat3x2 sum = this->_matA + this->_matB;

    EXPECT_MAT_EQ(this->_expectedSum, sum);
}


TEST(Mat3x2AdditionTests, PlusOperator_MixedType_PromotesType)
{
    const fgm::Mat3x2 mat1{ fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ -3.0f, -4.0f, 12.0f } };
    const fgm::Mat3x2 mat2{
        fgm::Vec3{ 10.0, 2.0, 2.5 },
        fgm::Vec3{ 3.0, 8.0, 3.5 },
    };

    [[maybe_unused]] const fgm::Mat3x2 sum = mat1 + mat2;
    static_assert(std::is_same_v<decltype(sum)::value_type, double>);
}


TYPED_TEST(Mat3x2AdditionTests, PlusEqualsOperator_ReturnsSameMatrixWithSum)
{
    this->_matA += this->_matB;
    EXPECT_MAT_EQ(this->_expectedSum, this->_matA);
}


TEST(Mat3x2AdditionTests, PlusEqualsOperator_MixedType_DoesNotPromoteType)
{
    fgm::Mat3x2 mat1{ fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ -3.0f, -4.0f, 12.0f } };
    const fgm::Mat3x2 mat2{
        fgm::Vec3{ 10.0, 2.0, 2.5 },
        fgm::Vec3{ 3.0, 8.0, 3.5 },
    };

    mat1 += mat2;
    static_assert(std::is_same_v<decltype(mat1)::value_type, float>);
}

/** @} */
