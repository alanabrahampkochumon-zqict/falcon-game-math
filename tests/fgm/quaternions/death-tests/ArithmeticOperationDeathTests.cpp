/**
 * @file ArithmeticOperationDeathTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 4, 2026
 *
 * @brief Verifies quaternion assertions in quaternion arithmetic operations that can result in application death.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "../include/QuaternionTestSetup.h"


namespace
{
    /**
     * @brief Test fixture for verifying quaternion scalar division assertions.
     *
     * @tparam T The scalar type (uint32_t, float, double...) for the quaternion values.
     */
    template <typename T>
    class QuaternionScalarDivisionDeathTests: public testing::Test
    {
    protected:
        fgm::Quaternion<T> _quat;

        void SetUp() override { _quat = { T(17), T(31), T(59), T(73) }; }
    };
    TYPED_TEST_SUITE(QuaternionScalarDivisionDeathTests, SupportedArithmeticTypes);

} // namespace



#ifdef ENABLE_DEBUG_TESTS

// Debug Mode behaviour

TYPED_TEST(QuaternionScalarDivisionDeathTests, DivideOperator_ByZeroTriggersAssertionInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_quat / TypeParam(0)), ""); }


TYPED_TEST(QuaternionScalarDivisionDeathTests, DivideEqualsOperator_ByZeroTriggersAssertionInDebugMode)
{
    [[maybe_unused]] fgm::Quaternion newVec = this->_quat;
    EXPECT_DEBUG_DEATH(static_cast<void>(newVec /= TypeParam(0)), "");
}

#else

// Release mode behaviour

TEST(QuaternionScalarDivision, FloatQuaternionDivisionByZero_ReturnsInfinityQuaternion_InReleaseMode)
{
    const fgm::Quaternion quat(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_QUAT_INF(quat / 0);
}


TEST(QuaternionScalarDivision, DoubleQuaternionDivisionByZero_ReturnsInfinityQuaternion_InReleaseMode)
{
    const fgm::Quaternion quat(1.0, 2.0, 3.0, 4.0);
    EXPECT_QUAT_INF(quat / 0);
}

#endif
