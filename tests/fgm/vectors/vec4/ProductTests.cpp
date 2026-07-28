/**
 * @file ProductTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 07, 2026
 *
 * @brief Verify @ref fgm::Vec4 dot product logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec4TestSetup.h"



/**
 * @addtogroup T_FGM_Vec4_Product
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
     * @brief Test fixture for @ref fgm::Vec4 dot product.
     *
     * @tparam T The scalar type (e.g., float, double) used for the vectors.
     */
    template <typename T>
    class Vec4DotProduct: public testing::Test
    {
    protected:
        fgm::Vec4<T> _vecA;
        fgm::Vec4<T> _vecB;

        fgm::Vec4<T> _vecAOrthogonal;
        fgm::Vec4<T> _vecBOrthogonal;

        T _expectedDotProduct;

        T _expectedADotA;

        void SetUp() override
        {
            _vecA               = { T(2), T(3), T(4), T(5) };
            _vecB               = { T(6), T(7), T(8), T(9) };
            _vecAOrthogonal     = { T(3), T(0), T(4), T(0) };
            _vecBOrthogonal     = { T(0), T(5), T(0), T(6) };
            _expectedDotProduct = static_cast<T>(110);

            _expectedADotA = static_cast<T>(54);
        }
    };
    TYPED_TEST_SUITE(Vec4DotProduct, SupportedArithmeticTypes);


    /**************************************
     *                                    *
     *           STATIC TESTS             *
     *                                    *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Vec4 VEC_A(1, 2, 3, 4);
        constexpr fgm::Vec4 VEC_B(5, 6, 7, 8);

        /// @test Verify that dot product of two 4D vectors return a valid scale at compile time.
        constexpr auto DOT_PROD = VEC_A.dot(VEC_B);
        static_assert(DOT_PROD == 70);

        /// @test Verify that dot product of two 4D vectors using static variant of cross()
        ///       return a valid scale at compile time.
        constexpr auto DOT_PROD_STATIC = fgm::Vec4<int>::dot(VEC_A, VEC_B);
        static_assert(DOT_PROD_STATIC == 70);


        // /// @test Verify that inner product of two 4D vectors return a valid 4D matrix at compile time.
        // constexpr auto INNER_PROD = VEC_A.innerProduct(VEC_B);
        // static_assert(INNER_PROD[0] == fgm::Vec4{ 3, 6 });
        // static_assert(INNER_PROD[1] == fgm::Vec4{ 4, 8 });
        // static_assert(INNER_PROD[2] == fgm::Vec4{ 4, 8 });
        // static_assert(INNER_PROD[3] == fgm::Vec4{ 4, 8 });
        //
        // /// @test Verify that inner product of two 4D vectors using static variant of cross()
        // ///       return a valid 4D matrix at compile time.
        // constexpr auto INNER_PROD_STATIC = fgm::Vec4<int>::innerProduct(VEC_A, VEC_B);
        // static_assert(INNER_PROD_STATIC[0] == fgm::Vec4{ 3, 6 });
        // static_assert(INNER_PROD_STATIC[1] == fgm::Vec4{ 4, 8 });

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *            DOT PRODUCT             *
 *                                    *
 **************************************/

/** @brief Verify that the dot product of a vector with itself returns its squared magnitude. */
TYPED_TEST(Vec4DotProduct, SelfDotProductReturnsSquareMagnitude)
{

    const TypeParam dotProduct = this->_vecA.dot(this->_vecA);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(this->_expectedADotA, dotProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(this->_expectedADotA, dotProduct);
    }
    else
    {
        EXPECT_EQ(this->_expectedADotA, dotProduct);
    }
}


/** @brief Verify that the dot product of a vector with an orthogonal vector returns zero. */
TYPED_TEST(Vec4DotProduct, OrthogonalDotProductReturnZero)
{
    const TypeParam dotProduct = this->_vecAOrthogonal.dot(this->_vecBOrthogonal);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(0.0, dotProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(0.0f, dotProduct);
    }
    else
    {
        EXPECT_EQ(0, dotProduct);
    }
}


/** @brief Verify that the dot product of a vector with a non-orthogonal vector returns a non-zero scalar. */
TYPED_TEST(Vec4DotProduct, NonOrthogonalDotProductReturnsNonZeroScalar)
{
    const TypeParam dotProduct = this->_vecA.dot(this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(this->_expectedDotProduct, dotProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(this->_expectedDotProduct, dotProduct);
    }
    else
    {
        EXPECT_EQ(this->_expectedDotProduct, dotProduct);
    }
}


/** @brief Verify that the static variant of @ref fgm::Vec4::dot returns a non-zero scalar. */
TYPED_TEST(Vec4DotProduct, StaticWrapper_NonOrthogonalDotProductReturnsNonZeroScalar)
{
    const TypeParam dotProduct = fgm::Vec4<TypeParam>::dot(this->_vecA, this->_vecB);

    if constexpr (std::is_same_v<TypeParam, double>)
    {
        EXPECT_DOUBLE_EQ(this->_expectedDotProduct, dotProduct);
    }
    else if constexpr (std::is_floating_point_v<TypeParam>)
    {
        EXPECT_FLOAT_EQ(this->_expectedDotProduct, dotProduct);
    }
    else
    {
        EXPECT_EQ(this->_expectedDotProduct, dotProduct);
    }
}


/**
 * @brief Verify that the dot product of a vector with another vector in opposite direction
 *        returns a negative scalar.
 */
TEST(Vec4DotProduct, AntiParallelDotProductReturnsNegativeScalar)
{
    // Given two opposite vectors
    const fgm::Vec4 vecA(-1.0, 0.0, 0.0, 0.0);
    const fgm::Vec4 vecB(1.0, 0.0, 0.0, 0.0);

    // When dot with each other
    const double dotProduct = vecA.dot(vecB);

    // Then, the dot product is -1
    EXPECT_DOUBLE_EQ(-1.0, dotProduct);
}


/**
 * @brief Verify that the dot product of a vector with another vector of different type
 *        returns a type promoted vector.
 */
TEST(Vec4DotProduct, MixedTypeDotProductPromotesType)
{
    // Given two vectors of different type
    const fgm::Vec4 vecA(7, 13, 29, 41);
    const fgm::Vec4 vecB(1.123456789, 2.123456789, 3.123456789, 4.123456789);

    // When dot with each other
    const auto dotProduct = vecA.dot(vecB);

    // Then, the dot product is type promoted
    static_assert(std::is_same_v<decltype(dotProduct), const double>);

    // Then, the dot product is non-zero
    EXPECT_DOUBLE_EQ(295.11111101, dotProduct);
}

/** @} */
