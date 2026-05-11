/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: May 01, 2026
 *
 * @brief Verify @ref fgm::Matrix4D utility functions.
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
struct Matrix4DUtilityParams
{
    fgm::Matrix4D<T> mat;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Matrix4D infinity checker, parameterized by @ref VectorUtilityParams */
class Matrix4DInfChecker: public ::testing::TestWithParam<Matrix4DUtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Matrix4D NaN checker, parameterized by @ref VectorUtilityParams */
class Matrix4DNaNChecker: public ::testing::TestWithParam<Matrix4DUtilityParams<float>>
{};


template <typename T>
class Matrix4DIntegralUtility: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Matrix4D utilities, parameterized by @ref SupportedIntegralTypes */
TYPED_TEST_SUITE(Matrix4DIntegralUtility, SupportedIntegralTypes);



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
    constexpr fgm::Matrix4D INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f);
    constexpr fgm::Matrix4D NAN_MAT(fgm::constants::NaN, 1.0f, 1.0f, 1.0f);
    constexpr fgm::Matrix4D MAT(1.0f, 1.0f, 1.0f, 1.0f);


    /** @brief Verify that the matrix hasNaN utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(NAN_MAT.hasNaN() == true);
        static_assert(MAT.hasNaN() == false);

        // Static functions
         static_assert(fgm::Matrix4D<float>::hasNaN(NAN_MAT) == true);
         static_assert(fgm::Matrix4D<float>::hasNaN(MAT) == false);
    } // namespace


    /** @brief Verify that the matrix hasInf utility is available at compile time. */
    namespace
    {
        // Member functions
         static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        // Static functions
        static_assert(fgm::Matrix4D<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Matrix4D<float>::hasInf(MAT) == false);
    } // namespace

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Matrix4D::hasInf returns `true` if any of elements are IEE754 infinity
 *        and False otherwise.
 */
TEST_P(Matrix4DInfChecker, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix4DInfCheckerTestSuite, Matrix4DInfChecker,
    ::testing::Values(Matrix4DUtilityParams{ fgm::Matrix4D(fgm::constants::INFINITY_F, 1.0f, 1.0f, 1.0f), true },
                      Matrix4DUtilityParams{ fgm::Matrix4D(1.0f, fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                      Matrix4DUtilityParams{ fgm::Matrix4D(1.0f, 1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Matrix4DUtilityParams{ fgm::Matrix4D(1.0f, 1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                      Matrix4DUtilityParams{ fgm::Matrix4D(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                           fgm::constants::INFINITY_F,
                                                           fgm::constants::INFINITY_F),
                                             true },
                      Matrix4DUtilityParams{ fgm::Matrix4D(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Matrix4D::hasInf returns `false` for integral types. */
TYPED_TEST(Matrix4DIntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix4D(value, value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Matrix4D::hasInf returns `true` if any of elements are IEE754
 *        infinity and False otherwise.
 */
TEST_P(Matrix4DInfChecker, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix4D<float>::hasInf(mat));
}


/** @brief Verify that the static variant of @ref std::Matrix4D::hasInf returns `false` for integral types. */
TYPED_TEST(Matrix4DIntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix4D<TypeParam>::hasInf(fgm::Matrix4D(value, value, value, value)));
}



/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Matrix4D::hasNaN returns `true` if any of elements are IEE754 NaN(Not-a-Number)
 *       and `false` otherwise.
 */
TEST_P(Matrix4DNaNChecker, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix4DNaNCheckerTestSuite, Matrix4DNaNChecker,
    ::testing::Values(Matrix4DUtilityParams{ fgm::Matrix4D(fgm::constants::NaN, 1.0f, 1.0f, 1.0f), true },
                      Matrix4DUtilityParams{ fgm::Matrix4D(1.0f, fgm::constants::NaN, 1.0f, 1.0f), true },
                      Matrix4DUtilityParams{ fgm::Matrix4D(1.0f, 1.0f, fgm::constants::NaN, 1.0f), true },
                      Matrix4DUtilityParams{ fgm::Matrix4D(1.0f, 1.0f, 1.0f, fgm::constants::NaN), true },
                      Matrix4DUtilityParams{ fgm::Matrix4D(fgm::constants::NaN, fgm::constants::NaN,
                                                           fgm::constants::NaN, fgm::constants::NaN),
                                             true },
                      Matrix4DUtilityParams{ fgm::Matrix4D(1.0f, 1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Matrix4D::hasNaN returns `false` for integral types. */
TYPED_TEST(Matrix4DIntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix4D(value, value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Matrix4D::hasNaN returns `true` if any of elements are IEE754
 *        NaN(Not-a-Number) and `false` otherwise.
 */
TEST_P(Matrix4DNaNChecker, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix4D<float>::hasNaN(mat));
}


/** @brief Verify that the static variant of @ref std::Matrix4D::hasNaN returns `false` for integral types. */
TYPED_TEST(Matrix4DIntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix4D<TypeParam>::hasNaN(fgm::Matrix4D(value, value, value, value)));
}

/** @} */
