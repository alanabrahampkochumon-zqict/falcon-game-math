/**
 * @file VectorAlgebraTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 05, 2026
 *
 * @brief Verify @ref fgm::Quaternion dot product logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"
#include "utils/MatrixUtils.h"
#include "utils/VectorUtils.h"

#include <fgm/matrices/Mat4.h>



/**
 * @addtogroup T_FGM_Quaternion_Algebra
 * @{
 */

namespace
{

    /**************************************
     *               SETUP                *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Quaternion dot product.
     *
     * @tparam T The scalar type (e.g., float, double) used for the quaternions.
     */
    template <typename T>
    class QuaternionDotProduct: public testing::Test
    {
    protected:
        fgm::Quaternion<T> _quatA, _quatB;
        T _expectedDotProduct;

        void SetUp() override
        {
            _quatA              = { T(2), T(3), T(4), T(5) };
            _quatB              = { T(6), T(7), T(8), T(9) };
            _expectedDotProduct = static_cast<T>(110);
        }
    };
    TYPED_TEST_SUITE(QuaternionDotProduct, SupportedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Quaternion QUAT_A(1, 2, 3, 4);
        constexpr fgm::Quaternion QUAT_B(5, 6, 7, 8);

        /// @test Verify that dot product of two quaternions return a valid scalar at compile time.
        constexpr auto DOT_PROD = QUAT_A.dot(QUAT_B);
        static_assert(DOT_PROD == 70);

        /// @test Verify that dot product of two quaternions using static variant
        ///       return a valid scalar at compile time.
        constexpr auto DOT_PROD_STATIC = fgm::Quaternion<int>::dot(QUAT_A, QUAT_B);
        static_assert(DOT_PROD_STATIC == 70);

    } // namespace static_tests

} // namespace



/**************************************
 *            DOT PRODUCT             *
 **************************************/

TYPED_TEST(QuaternionDotProduct, DotProductReturnsNonZeroScalar)
{
    const TypeParam dotProduct = this->_quatA.dot(this->_quatB);

    testutils::EXPECT_MAG_EQ(this->_expectedDotProduct, dotProduct);
}


TYPED_TEST(QuaternionDotProduct, DotProductIsCommutative)
{
    const auto aDotB = this->_quatA.dot(this->_quatB);
    const auto bDotA = this->_quatB.dot(this->_quatA);

    testutils::EXPECT_MAG_EQ(aDotB, bDotA);
}

TEST(QuaternionDotProduct, MixedTypeDotProductPromotesType)
{
    const fgm::Quaternion quatA(7, 13, 29, 41);
    const fgm::Quaternion quatB(1.123456789, 2.123456789, 3.123456789, 4.123456789);

    [[maybe_unused]] const auto dotProduct = quatA.dot(quatB);

    static_assert(std::is_same_v<decltype(dotProduct), const double>);
}



TYPED_TEST(QuaternionDotProduct, StaticWrapper_DotProductReturnsNonZeroScalar)
{
    const TypeParam dotProduct = fgm::Quaternion<TypeParam>::dot(this->_quatA, this->_quatB);

    testutils::EXPECT_MAG_EQ(this->_expectedDotProduct, dotProduct);
}


TYPED_TEST(QuaternionDotProduct, StaticWrapper_DotProductIsCommutative)
{
    const auto aDotB = fgm::Quaternion<TypeParam>::dot(this->_quatA, this->_quatB);
    const auto bDotA = fgm::Quaternion<TypeParam>::dot(this->_quatB, this->_quatA);

    testutils::EXPECT_MAG_EQ(aDotB, bDotA);
}

TEST(QuaternionDotProduct, StaticWrapper_MixedTypeDotProductPromotesType)
{
    const fgm::Quaternion quatA(7, 13, 29, 41);
    const fgm::Quaternion quatB(1.123456789, 2.123456789, 3.123456789, 4.123456789);

    [[maybe_unused]] const auto dotProduct = fgm::Quaternion<int>::dot(quatA, quatB);

    static_assert(std::is_same_v<decltype(dotProduct), const double>);
}

/** @} */
