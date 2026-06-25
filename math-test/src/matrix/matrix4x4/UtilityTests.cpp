/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01, 2026
 *
 * @brief Verify @ref fgm::Matrix4 utility functions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <MatrixTestSetup.h>



/**************************************
 *                                    *
 *                SETUP               *
 *                                    *
 **************************************/

template <typename T>
    requires std::floating_point<T>
struct Matrix4UtilityParams
{
    fgm::Matrix4<T> mat;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Matrix4 infinity checker, parameterized by @ref VectorUtilityParams */
class Matrix4InfChecker: public ::testing::TestWithParam<Matrix4UtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Matrix4 NaN checker, parameterized by @ref VectorUtilityParams */
class Matrix4NaNChecker: public ::testing::TestWithParam<Matrix4UtilityParams<float>>
{};


template <typename T>
class Matrix4IntegralUtility: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Matrix4 utilities, parameterized by @ref SupportedIntegralTypes */
TYPED_TEST_SUITE(Matrix4IntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Mat4x4_Utils
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace
{
    constexpr fgm::Matrix4 INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f);
    constexpr fgm::Matrix4 MAT(1.0f, 1.0f, 1.0f, 1.0f);


    /** @brief Verify that the matrix hasNaN utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(MAT.hasNaN() == false);

        // Static functions
        static_assert(fgm::Matrix4<float>::hasNaN(MAT) == false);
    } // namespace


    /** @brief Verify that the matrix hasInf utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        // Static functions
        static_assert(fgm::Matrix4<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Matrix4<float>::hasInf(MAT) == false);
    } // namespace

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Matrix4::hasInf returns `true` if any of elements are IEE754 infinity
 *        and False otherwise.
 */
TEST_P(Matrix4InfChecker, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix4InfCheckerTestSuite, Matrix4InfChecker,
    ::testing::Values(Matrix4UtilityParams{ fgm::Matrix4(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
                      Matrix4UtilityParams{ fgm::Matrix4(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                      Matrix4UtilityParams{ fgm::Matrix4(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Matrix4UtilityParams{ fgm::Matrix4(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                      Matrix4UtilityParams{ fgm::Matrix4(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                           fgm::constants::INFINITY_F, fgm::constants::INFINITY_F),
                                             true },
                      Matrix4UtilityParams{ fgm::Matrix4(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Matrix4::hasInf returns `false` for integral types. */
TYPED_TEST(Matrix4IntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix4(value, value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Matrix4::hasInf returns `true` if any of elements are IEE754
 *        infinity and False otherwise.
 */
TEST_P(Matrix4InfChecker, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix4<float>::hasInf(mat));
}


/** @brief Verify that the static variant of @ref std::Matrix4::hasInf returns `false` for integral types. */
TYPED_TEST(Matrix4IntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix4<TypeParam>::hasInf(fgm::Matrix4(value, value, value, value)));
}



/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Matrix4::hasNaN returns `true` if any of elements are IEE754 NaN(Not-a-Number)
 *       and `false` otherwise.
 */
TEST_P(Matrix4NaNChecker, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix4NaNCheckerTestSuite, Matrix4NaNChecker,
    ::testing::Values(Matrix4UtilityParams{ fgm::Matrix4(fgm::constants::NaN, 1.0f, 1.0f, 1.0f), true },
                      Matrix4UtilityParams{ fgm::Matrix4(1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
                      Matrix4UtilityParams{ fgm::Matrix4(1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                      Matrix4UtilityParams{ fgm::Matrix4(1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
                      Matrix4UtilityParams{ fgm::Matrix4(fgm::constants::NaN, fgm::constants::NaN,
                                                           fgm::constants::NaN, fgm::constants::NaN),
                                             true },
                      Matrix4UtilityParams{ fgm::Matrix4(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Matrix4::hasNaN returns `false` for integral types. */
TYPED_TEST(Matrix4IntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix4(value, value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Matrix4::hasNaN returns `true` if any of elements are IEE754
 *        NaN(Not-a-Number) and `false` otherwise.
 */
TEST_P(Matrix4NaNChecker, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix4<float>::hasNaN(mat));
}


/** @brief Verify that the static variant of @ref std::Matrix4::hasNaN returns `false` for integral types. */
TYPED_TEST(Matrix4IntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    const auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix4<TypeParam>::hasNaN(fgm::Matrix4(value, value, value, value)));
}

/** @} */
