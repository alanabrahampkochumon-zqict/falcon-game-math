/**
 * @file LoadStoreTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 22, 2026
 *
 * @brief Verify @ref falcon::Simd128 comparison operators (>, <, >=, <=, ==, !=).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */



#include "SIMDTestSetup.h"

#include <array>
#include <falcon_simd/memory/Simd128.h>


/**
 * @addtogroup T_SIMD128_Cmp
 * @{
 */

// TODO: Remove Preprocessor after implementing individual simd paths
#if defined(FALCON_ENABLE_AVX512) || defined(FALCON_ENABLE_AVX2) || defined(FALCON_ENABLE_AVX) ||                      \
    defined(FALCON_ENABLE_SSE4) || defined(FALCON_ENABLE_SSE2)
namespace
{
    /**
     * @brief Test Fixture for Simd128 comparison operations(>, <, >=, <=, ==, !=).
     * @tparam T The test matrix(Type, LaneCount) used for the different registers.
     */
    template <typename T>
    class Simd128ComparisonTests: public testing::Test
    {
    public:
        using Type                   = typename T::Type;
        static constexpr size_t Lane = T::VALUE;
        std::array<typename T::Type, 16> lhsData, rhsData, gtMask;

    protected:
        void SetUp() override
        {
            const Type False = Type(0);
            const Type True  = getAllOnes<Type>();
            if constexpr (std::is_signed_v<Type>)
            {
                lhsData = { 15, -2, 0, -3, 5, -11, 15, 3, -1, 2, -5, 12, -14, 3, 15, 12 };
                rhsData = { -12, 15, 8, 1, -5, 11, -3, 28, 2, 7, -5, 6, -4, 11, 4, 6 };
                gtMask  = { True,  False, False, False, True,  False, True, False,
                            False, False, False, True,  False, False, True, True };
            }
            else
            {
                lhsData = { 15, 2, 0, 3, 5, 11, 15, 3, 1, 2, 5, 12, 14, 3, 15, 12 };
                rhsData = { 12, 15, 8, 1, 5, 11, 3, 28, 2, 7, 5, 6, 4, 11, 4, 6 };
                gtMask  = { True,  False, False, True, False, False, True, False,
                            False, False, False, True, True,  False, True, True };
            }
        }
    };
    TYPED_TEST_SUITE(Simd128ComparisonTests, Simd128RegisterTypeHints);

} // namespace


TYPED_TEST(Simd128ComparisonTests, GreaterThanOperator_ReturnsAValidMask)
{
    using Type = typename TypeParam::Type;

    falcon::Simd128_t<Type, this->Lane> a{}, b{};
    a.load(this->lhsData.data());
    b.load(this->rhsData.data());

    std::array<Type, this->Lane> result{};
    auto resReg = a > b;
    resReg.store(result.data());
    for (size_t i = 0; i < this->Lane; ++i)
    {
        EXPECT_TRUE(isEqualBitwise(this->gtMask[i], result[i]))
            << "Equality mismatch at index " << i << "\nExpected: " << this->gtMask[i] << "\nGot: " << result[i]
            << '\n';
    }
}

TEST(Simd128ComparisonTests, GreaterThanOperator_MixedValues_ReturnsAValidMask) {}

#endif

/** @} */
