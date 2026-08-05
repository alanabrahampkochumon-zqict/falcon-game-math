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


/**
 * @addtogroup T_FGM_Quaternion_Algebra
 * @{
 */

namespace
{

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

    } // namespace static_tests


} // namespace



/**************************************
 *           CONJUGATE TESTS          *
 **************************************/

TYPED_TEST(QuaternionConjugateTests, ReturnsAQuaternionWithInvertedVectorPart)
{ EXPECT_QUAT_EQ(this->_expectedConjugate, this->_quat.conjugate()); }


TYPED_TEST(QuaternionConjugateTests, StaticWrapper_ReturnsAQuaternionWithInvertedVectorPart)
{ EXPECT_QUAT_EQ(this->_expectedConjugate, fgm::Quaternion<TypeParam>::conjugate(this->_quat)); }

/** @} */
