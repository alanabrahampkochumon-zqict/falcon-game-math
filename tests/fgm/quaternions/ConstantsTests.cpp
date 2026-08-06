/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 06, 2026
 *
 * @brief Verify @ref fgm::Quaternion constants (@ref fgm::Quaternion::one(), @ref fgm::Quaternion::zero(),
 *        @ref fgm::Quaternion::identity()).
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "include/QuaternionTestSetup.h"



/**
 * @addtogroup T_FGM_Quaternion_Const
 * @{
 */

namespace
{
    /**************************************
     *             TEST SETUP             *
     **************************************/

    /**
     * @brief Test fixture for testing @ref fgm::Quaternions across different types.
     *
     * @tparam T The scalar type of values to check against.
     */
    template <typename T>
    class QuaternionConstants: public testing::Test
    {
    protected:
        T _one  = T(1);
        T _zero = T(0);
    };
    TYPED_TEST_SUITE(QuaternionConstants, SupportedSignedArithmeticTypes);



    /**************************************
     *           STATIC TESTS             *
     **************************************/

    namespace static_tests
    {
        /// @test Verify that @ref Quaternion::one() returns a quaternion with unit components at compile time.
        static_assert(fgm::Quaternion<int>::one().x() == 1);
        static_assert(fgm::Quaternion<int>::one().y() == 1);
        static_assert(fgm::Quaternion<int>::one().z() == 1);
        static_assert(fgm::Quaternion<int>::one().w() == 1);

        /// @test Verify that @ref Quaternion::zero() returns a quaternion with unit components at compile time.
        static_assert(fgm::Quaternion<int>::zero().x() == 0);
        static_assert(fgm::Quaternion<int>::zero().y() == 0);
        static_assert(fgm::Quaternion<int>::zero().z() == 0);
        static_assert(fgm::Quaternion<int>::zero().w() == 0);


        /// @test Verify that @ref Quaternion::identity() returns a quaternion with unit scalar and
        ///       zero vector part at compile time.
        static_assert(fgm::Quaternion<int>::zero().x() == 0);
        static_assert(fgm::Quaternion<int>::zero().y() == 0);
        static_assert(fgm::Quaternion<int>::zero().z() == 0);
        static_assert(fgm::Quaternion<int>::zero().w() == 0);

    } // namespace static_tests

} // namespace



TYPED_TEST(QuaternionConstants, One_ReturnsAQuaternionWithUnitComponents)
{
    const auto one = TypeParam(1);
    EXPECT_QUAT_CONTAINS(fgm::Quaternion<TypeParam>::one(), one, one, one, one);
}


TYPED_TEST(QuaternionConstants, Zero_ReturnsAQuaternionWithZeroComponents)
{
    const auto zero = TypeParam(0);
    EXPECT_QUAT_CONTAINS(fgm::Quaternion<TypeParam>::zero(), zero, zero, zero, zero);
}


TYPED_TEST(QuaternionConstants, Identity_ReturnsAQuaternionWithUnitScalarAndZeroVectorPart)
{
    const auto zero = TypeParam(0);
    const auto one  = TypeParam(1);
    // NOTE: Quaternion is of the form [v w] = [i j k w]
    EXPECT_QUAT_CONTAINS(fgm::Quaternion<TypeParam>::identity(), zero, zero, zero, one);
}



/** @} */
