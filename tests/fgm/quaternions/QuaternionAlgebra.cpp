/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 03, 2026
 *
 * @brief Verify @ref fgm::Quaternion quaternion algebra(Conjugate, Inverse,...).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"
#include "utils/VectorUtils.h"


/**
 * @addtogroup T_FGM_Quaternion_Algebra
 * @{
 */

namespace
{
    using namespace testutils;

    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for verifying quaternion conjugate across different scalar types.
     *
     * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionConjugateTests: public testing::Test
    {
    protected:
        fgm::Quaternion<T> _quat;
        fgm::Quaternion<T> _expectedConjugate;

        void SetUp() override
        {
            _quat              = fgm::Quaternion<T>{ T(8), T(-4), T(7), T(5) };
            _expectedConjugate = fgm::Quaternion<T>{ T(-8), T(4), T(-7), T(5) };
        }
    };
    TYPED_TEST_SUITE(QuaternionConjugateTests, SupportedSignedArithmeticTypes);


    /**
     * @brief Test fixture for verifying quaternion magnitude across different scalar types.
     *
     * @tparam T The scalar type (int, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionMagnitudeTests: public testing::Test
    {
    protected:
        fgm::Quaternion<T> _quat;
        fgm::Magnitude<T> _expectedMagnitude;

        void SetUp() override
        {
            _quat              = { T(1), T(2), T(3), T(4) };
            _expectedMagnitude = fgm::Magnitude<T>(5.477225575051661);
        }
    };
    TYPED_TEST_SUITE(QuaternionMagnitudeTests, SupportedArithmeticTypes);



    /**************************************
     *            STATIC TESTS            *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Quaternion QUAT_A(-1, 12, 3, 4);
        // constexpr fgm::Quaternion QUAT_B(5, 12, -5, 3);

        /// @test Verify that quaterion conjugate returns a valid quaternion at compile-time.
        constexpr auto QUAT_CONJUGATE = QUAT_A.conjugate();
        static_assert(QUAT_CONJUGATE.i() == 1);
        static_assert(QUAT_CONJUGATE.j() == -12);
        static_assert(QUAT_CONJUGATE.k() == -3);
        static_assert(QUAT_CONJUGATE.s() == 4);

        /// @test Verify that quaterion conjugate(static wrapper) returns a valid quaternion at compile-time.
        constexpr auto QUAT_CONJUGATE_STATIC = fgm::Quaternion<int>::conjugate(QUAT_A);
        static_assert(QUAT_CONJUGATE_STATIC.i() == 1);
        static_assert(QUAT_CONJUGATE_STATIC.j() == -12);
        static_assert(QUAT_CONJUGATE_STATIC.k() == -3);
        static_assert(QUAT_CONJUGATE_STATIC.s() == 4);

        // TODO: Add quaternion magnitude test after adding fgm::sqrt(constexpr)

    } // namespace static_tests

} // namespace



/**************************************
 *           CONJUGATE TESTS          *
 **************************************/

TYPED_TEST(QuaternionConjugateTests, ReturnsAQuaternionWithInvertedVectorPart)
{ EXPECT_QUAT_EQ(this->_expectedConjugate, this->_quat.conjugate()); }


TYPED_TEST(QuaternionConjugateTests, StaticWrapper_ReturnsAQuaternionWithInvertedVectorPart)
{ EXPECT_QUAT_EQ(this->_expectedConjugate, fgm::Quaternion<TypeParam>::conjugate(this->_quat)); }



/**************************************
 *          MAGNITUDE TESTS           *
 **************************************/

TYPED_TEST(QuaternionMagnitudeTests, NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = this->_quat.mag();

    static_assert(std::is_floating_point_v<decltype(magnitude)>);
    testutils::EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


TYPED_TEST(QuaternionMagnitudeTests, MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = this->_quat.mag();
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}


TYPED_TEST(QuaternionMagnitudeTests, StaticWrapper_NonUnitVectorReturnsCorrectMagnitude)
{
    const auto magnitude = fgm::Quaternion<TypeParam>::mag(this->_quat);

    static_assert(std::is_floating_point_v<decltype(magnitude)>);
    testutils::EXPECT_MAG_EQ(this->_expectedMagnitude, magnitude);
}


TYPED_TEST(QuaternionMagnitudeTests, StaticWrapper_MagnitudeIsAlwaysTypedPromotedToFloatingPointType)
{
    [[maybe_unused]] const auto magnitude = fgm::Quaternion<TypeParam>::mag(this->_quat);
    static_assert(std::is_floating_point_v<decltype(magnitude)>);
}


/** @} */
