/**
 * @file LoadStoreTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 18, 2026
 *
 * @brief Verify @ref falcon::Simd128 arithmetics.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "SIMDTestSetup.h"

#include <array>
#include <falcon_simd/memory/Simd128.h>



/**
 * @addtogroup T_SIMD128_Arithmetic
 * @{
 */

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)
namespace
{
    /**
     * @brief Test Fixture for Simd128 load and store operations.
     */
    template <typename T>
    class Simd128ArithmeticTests: public testing::Test
    {
    public:
        std::array<typename T::Type, 16> lhsData = { 10, 2, 0, 3, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
        std::array<typename T::Type, 16> rhsData = { 12, 15, 8, 1, 5, 11, 3, 28, 2, 7, 5, 6, 4, 11, 4, 6 };
    };
    TYPED_TEST_SUITE(Simd128ArithmeticTests, Simd128RegisterTypeHints);

} // namespace


TYPED_TEST(Simd128ArithmeticTests, BinaryAddOperation_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = static_cast<Type>(i * 3);
        rhs[i]      = static_cast<Type>(i * 5);
        expected[i] = static_cast<Type>((i * 3) + (i * 5));
    }

    falcon::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA + regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd128ArithmeticTests, BinaryAddOperation_WorksWithMixedNumbers)
{

    alignas(16) std::array<float, 4> lhs{ 1, 5, -2, 0 }, rhs{ -1, 5, -5, -1 }, expected{ 0, 10, -7, -1 }, result{};

    falcon::Simd128_t<float, 4> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    const auto regRes = regA + regB;
    regRes.storeAligned(result.data());


    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128ArithmeticTests, CompoundAddOperation_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = static_cast<Type>(i * 3);
        rhs[i]      = static_cast<Type>(i * 5);
        expected[i] = static_cast<Type>((i * 3) + (i * 5));
    }

    falcon::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA += regB;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd128ArithmeticTests, CompoundAddOperation_WorksWithMixedNumbers)
{

    alignas(16) std::array<float, 4> lhs{ 1, 5, -2, 0 }, rhs{ -1, 5, -5, -1 }, expected{ 0, 10, -7, -1 }, result{};

    falcon::Simd128_t<float, 4> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA += regB;
    regA.storeAligned(result.data());


    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128ArithmeticTests, BinarySubtractOperation_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = static_cast<Type>(i * 5);
        rhs[i]      = static_cast<Type>(i * 3);
        expected[i] = static_cast<Type>((i * 5) - (i * 3));
    }

    falcon::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA - regB;

    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd128ArithmeticTests, BinarySubtractOperation_WorksWithMixedNumbers)
{

    alignas(16) std::array<float, 4> lhs{ 1, 5, -2, 0 }, rhs{ -1, 5, -5, -1 }, expected{ 2, 0, 3, 1 }, result{};

    falcon::Simd128_t<float, 4> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    const auto regRes = regA - regB;
    regRes.storeAligned(result.data());


    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128ArithmeticTests, CompoundSubtractOperation_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = static_cast<Type>(i * 5);
        rhs[i]      = static_cast<Type>(i * 3);
        expected[i] = static_cast<Type>((i * 5) - (i * 3));
    }

    falcon::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA -= regB;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd128ArithmeticTests, CompoundSubtractOperation_WorksWithMixedNumbers)
{

    alignas(16) std::array<float, 4> lhs{ 1, 5, -2, 0 }, rhs{ -1, 5, -5, -1 }, expected{ 2, 0, 3, 1 }, result{};

    falcon::Simd128_t<float, 4> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA -= regB;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}



TYPED_TEST(Simd128ArithmeticTests, BinaryMultiplication_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->lhsData[i];
        rhs[i]      = this->rhsData[i];
        expected[i] = static_cast<Type>(rhs[i] * lhs[i]);
    }

    falcon::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA * regB;
    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd128ArithmeticTests, BinaryMultiplicationOperation_WorksWithMixedNumbers)
{
    alignas(16) std::array<float, 4> lhs{ 1, 5, -2, 0 }, rhs{ -1, 5, -5, -1 }, result{};
    const std::array<float, 4> expected{ -1, 25, 10, 0 };

    falcon::Simd128_t<float, 4> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    const auto regRes = regA * regB;
    regRes.storeAligned(result.data());


    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}



TYPED_TEST(Simd128ArithmeticTests, CompoundMultiplication_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->lhsData[i];
        rhs[i]      = this->rhsData[i];
        expected[i] = static_cast<Type>(rhs[i] * lhs[i]);
    }

    falcon::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA *= regB;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd128ArithmeticTests, CompoundMultiplicationOperation_WorksWithMixedNumbers)
{
    alignas(16) std::array<float, 4> lhs{ 1, 5, -2, 0 }, rhs{ -1, 5, -5, -1 }, result{};
    const std::array<float, 4> expected{ -1, 25, 10, 0 };

    falcon::Simd128_t<float, 4> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    regA *= regB;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}


TYPED_TEST(Simd128ArithmeticTests, DivReg_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->lhsData[i];
        rhs[i]      = this->rhsData[i];
        expected[i] = static_cast<Type>(lhs[i] / rhs[i]);
    }

    falcon::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA.divReg(regB);
    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}



/// @test Verify that division using divReg function returns the correct value for the largest and smallest numbers.
TYPED_TEST(Simd128ArithmeticTests, DivReg_MaintainsPrecisionForAtUpperAndLowerLimits)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;

    constexpr auto largestNumber  = std::numeric_limits<Type>::max();
    constexpr auto smallestNumber = std::numeric_limits<Type>::min();

    // We are swapping for the largest and smallest for the first two indices
    // since we have at least 2 lanes(128 / 64(max data type size)) we can safely inject those values
    alignas(16) std::array<Type, Lane> lhs{}, rhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->lhsData[i];
        rhs[i]      = this->rhsData[i];
        expected[i] = static_cast<Type>(lhs[i] / rhs[i]);
    }
    lhs[0]      = largestNumber;
    lhs[1]      = smallestNumber;
    expected[0] = static_cast<Type>(lhs[0] / rhs[0]);
    expected[1] = static_cast<Type>(lhs[1] / rhs[1]);


    falcon::Simd128_t<Type, Lane> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    auto regRes = regA.divReg(regB);
    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd128ArithmeticTests, DivReg_WorksWithMixedNumbers)
{
    alignas(16) std::array<float, 4> lhs{ 25, -51, 13, 0 }, rhs{ -5, 25, 3, 16 }, result{};
    const std::array<float, 4> expected{ -5, -2.04f, 4.333333f, 0 };

    falcon::Simd128_t<float, 4> regA, regB;
    regA.loadAligned(lhs.data());
    regB.loadAligned(rhs.data());

    const auto regRes = regA.divReg(regB);
    regRes.storeAligned(result.data());


    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}



TYPED_TEST(Simd128ArithmeticTests, BinaryDivideOperator_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    const Type divisor    = Type(5);

    alignas(16) std::array<Type, Lane> lhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->lhsData[i];
        expected[i] = static_cast<Type>(lhs[i] / divisor);
    }

    falcon::Simd128_t<Type, Lane> regA;
    regA.loadAligned(lhs.data());

    auto regRes = regA / divisor;
    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}



/// @test Verify that division using operator/ returns the correct value for the largest and smallest numbers.
TYPED_TEST(Simd128ArithmeticTests, BinaryDivideOperator_MaintainsPrecisionForAtUpperAndLowerLimits)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    const Type divisor    = Type(5);

    constexpr auto largestNumber  = std::numeric_limits<Type>::max();
    constexpr auto smallestNumber = std::numeric_limits<Type>::min();

    // We are swapping for the largest and smallest for the first two indices
    // since we have at least 2 lanes(128 / 64(max data type size)) we can safely inject those values
    alignas(16) std::array<Type, Lane> lhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->lhsData[i];
        expected[i] = static_cast<Type>(lhs[i] / divisor);
    }
    lhs[0]      = largestNumber;
    lhs[1]      = smallestNumber;
    expected[0] = static_cast<Type>(lhs[0] / divisor);
    expected[1] = static_cast<Type>(lhs[1] / divisor);


    falcon::Simd128_t<Type, Lane> regA;
    regA.loadAligned(lhs.data());

    auto regRes = regA / divisor;
    regRes.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd128ArithmeticTests, BinaryDivideOperator_WorksWithMixedNumbers)
{
    alignas(16) std::array<float, 4> lhs{ 25, -51, 13, 0 }, result{};
    const std::array<float, 4> expected{ -6.25f, 12.75f, -3.25f, 0 };

    falcon::Simd128_t<float, 4> regA;
    regA.loadAligned(lhs.data());

    const auto regRes = regA / -4;
    regRes.storeAligned(result.data());


    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}



TYPED_TEST(Simd128ArithmeticTests, CompoundDivideOperator_ReturnsAValidResult)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    const Type divisor    = Type(5);

    alignas(16) std::array<Type, Lane> lhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->lhsData[i];
        expected[i] = static_cast<Type>(lhs[i] / divisor);
    }

    falcon::Simd128_t<Type, Lane> regA;
    regA.loadAligned(lhs.data());

    regA /= divisor;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}



/// @test Verify that division using operator/ returns the correct value for the largest and smallest numbers.
TYPED_TEST(Simd128ArithmeticTests, CompoundDivideOperator_MaintainsPrecisionForAtUpperAndLowerLimits)
{
    using Type            = TypeParam::Type;
    constexpr size_t Lane = TypeParam::VALUE;
    const Type divisor    = Type(5);

    constexpr auto largestNumber  = std::numeric_limits<Type>::max();
    constexpr auto smallestNumber = std::numeric_limits<Type>::min();

    // We are swapping for the largest and smallest for the first two indices
    // since we have at least 2 lanes(128 / 64(max data type size)) we can safely inject those values
    alignas(16) std::array<Type, Lane> lhs{}, expected{}, result{};
    for (size_t i = 0; i < Lane; ++i)
    {
        lhs[i]      = this->lhsData[i];
        expected[i] = static_cast<Type>(lhs[i] / divisor);
    }
    lhs[0]      = largestNumber;
    lhs[1]      = smallestNumber;
    expected[0] = static_cast<Type>(lhs[0] / divisor);
    expected[1] = static_cast<Type>(lhs[1] / divisor);


    falcon::Simd128_t<Type, Lane> regA;
    regA.loadAligned(lhs.data());

    regA /= divisor;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < Lane; ++i)
    {
        EXPECT_ANY_EQ(expected[i], result[i]);
    }
}


TEST(Simd128ArithmeticTests, CompoundDivideOperator_WorksWithMixedNumbers)
{
    alignas(16) std::array<float, 4> lhs{ 25, -51, 13, 0 }, result{};
    const std::array<float, 4> expected{ -6.25f, 12.75f, -3.25f, 0 };

    falcon::Simd128_t<float, 4> regA;
    regA.loadAligned(lhs.data());

    regA /= -4;
    regA.storeAligned(result.data());

    for (size_t i = 0; i < 4; ++i)
    {
        EXPECT_FLOAT_EQ(expected[i], result[i]);
    }
}

#endif

/** @} */
