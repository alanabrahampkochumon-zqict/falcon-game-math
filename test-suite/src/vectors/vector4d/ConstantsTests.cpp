/**
 * @file ConstantsTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 24, 2026
 *
 * @brief Verifies @ref fgm::Vector4D constants (@ref fgm::Vector4D::one, @ref fgm::Vector4D::zero, etc).
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector4DTestSetup.h"


using namespace testutils;



template <typename T>
class Vector4DConstants: public ::testing::Test {};
/** @brief Test fixture for @ref fgm::Vector4D constants, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Vector4DConstants, SupportedArithmeticTypes);



/**
 * @addtogroup T_FGM_Vec4_Const
 * @{
 */

/** @test Verifies that @ref fgm::Vector4D::one returns a 4D vector with unit components */
TYPED_TEST(Vector4DConstants, OneReturnsVectorWithUnitComponents)
{
    constexpr TypeParam one = TypeParam(1);
    EXPECT_VEC_CONTAINS(fgm::vec4d::one<TypeParam>, one, one, one, one);
}


/** @test Verifies that @ref fgm::Vector4D::zero returns a 4D vector with zero components */
TYPED_TEST(Vector4DConstants, OneReturnsVectorWithZeroComponents)
{
    EXPECT_VEC_ZERO(fgm::vec4d::zero<TypeParam>);
}

/** @} */