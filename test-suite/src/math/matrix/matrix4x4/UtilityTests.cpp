/**
 * @file UtilityTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 23, 2026
 *
 * @brief Verify @ref fgm::Matrix3D utility functions.
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
struct Matrix3DUtilityParams
{
    fgm::Matrix3D<T> mat;
    bool expected;
};
/** @brief Test fixture for @ref fgm::Matrix3D infinity checker, parameterized by @ref VectorUtilityParams */
class Matrix3DInfChecker: public ::testing::TestWithParam<Matrix3DUtilityParams<float>>
{};

/** @brief Test fixture for @ref fgm::Matrix3D NaN checker, parameterized by @ref VectorUtilityParams */
class Matrix3DNaNChecker: public ::testing::TestWithParam<Matrix3DUtilityParams<float>>
{};


template <typename T>
class Matrix3DIntegralUtility: public ::testing::Test
{};
/** @brief Test fixture for @ref fgm::Matrix3D utilities, parameterized by @ref SupportedIntegralTypes */
TYPED_TEST_SUITE(Matrix3DIntegralUtility, SupportedIntegralTypes);



/**
 * @addtogroup T_FGM_Mat3x3_Utils
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

namespace
{
    constexpr fgm::Matrix3D INF_MAT(fgm::constants::INFINITY_F, 1.0f, 1.0f);
    constexpr fgm::Matrix3D NAN_MAT(fgm::constants::NaN, 1.0f, 1.0f);
    constexpr fgm::Matrix3D MAT(1.0f, 1.0f, 1.0f);


    /** @brief Verify that the matrix hasNaN utility is available at compile time. */
    namespace
    {
        // Member functions
        static_assert(NAN_MAT.hasNaN() == true);
        static_assert(MAT.hasNaN() == false);

        // Static functions
         static_assert(fgm::Matrix3D<float>::hasNaN(NAN_MAT) == true);
         static_assert(fgm::Matrix3D<float>::hasNaN(MAT) == false);
    } // namespace


    /** @brief Verify that the matrix hasInf utility is available at compile time. */
    namespace
    {
        // Member functions
         static_assert(INF_MAT.hasInf() == true);
        static_assert(MAT.hasInf() == false);

        // Static functions
        static_assert(fgm::Matrix3D<float>::hasInf(INF_MAT) == true);
        static_assert(fgm::Matrix3D<float>::hasInf(MAT) == false);
    } // namespace

} // namespace


/**************************************
 *                                    *
 *      INFINITY CHECKER TESTS        *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Matrix3D::hasInf returns `true` if any of elements are IEE754 infinity
 *        and False otherwise.
 */
TEST_P(Matrix3DInfChecker, ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasInf());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix3DInfCheckerTestSuite, Matrix3DInfChecker,
    ::testing::Values(Matrix3DUtilityParams{ fgm::Matrix3D(fgm::constants::INFINITY_F, 1.0f, 1.0f), true },
                      Matrix3DUtilityParams{ fgm::Matrix3D(1.0f, fgm::constants::INFINITY_F, 1.0f), true },
                      Matrix3DUtilityParams{ fgm::Matrix3D(1.0f, 1.0f, fgm::constants::INFINITY_F), true },
                      Matrix3DUtilityParams{ fgm::Matrix3D(fgm::constants::INFINITY_F, fgm::constants::INFINITY_F,
                                                           fgm::constants::INFINITY_F),
                                             true },
                      Matrix3DUtilityParams{ fgm::Matrix3D(1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Matrix3D::hasInf returns `false` for integral types. */
TYPED_TEST(Matrix3DIntegralUtility, HasInf_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix3D(value, value, value).hasInf());
}


/**
 * @brief Verify that the static variant of @ref std::Matrix3D::hasInf returns `true` if any of elements are IEE754
 *        infinity and False otherwise.
 */
TEST_P(Matrix3DInfChecker, StaticWrapper_ReturnTrueIfAnyElementIsInfinity)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix3D<float>::hasInf(mat));
}


/** @brief Verify that the static variant of @ref std::Matrix3D::hasInf returns `false` for integral types. */
TYPED_TEST(Matrix3DIntegralUtility, StaticWrapper_HasInf_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix3D<TypeParam>::hasInf(fgm::Matrix3D(value, value, value)));
}



/**************************************
 *                                    *
 *         NAN CHECKER TESTS          *
 *                                    *
 **************************************/

/**
 * @brief Verify that @ref std::Matrix3D::hasNaN returns `true` if any of elements are IEE754 NaN(Not-a-Number)
 *       and `false` otherwise.
 */
TEST_P(Matrix3DNaNChecker, ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, mat.hasNaN());
}
INSTANTIATE_TEST_SUITE_P(
    Matrix3DNaNCheckerTestSuite, Matrix3DNaNChecker,
    ::testing::Values(Matrix3DUtilityParams{ fgm::Matrix3D(fgm::constants::NaN, 1.0f, 1.0f), true },
                      Matrix3DUtilityParams{ fgm::Matrix3D(1.0f, fgm::constants::NaN, 1.0f), true },
                      Matrix3DUtilityParams{ fgm::Matrix3D(1.0f, 1.0f, fgm::constants::NaN), true },
                      Matrix3DUtilityParams{
                          fgm::Matrix3D(fgm::constants::NaN, fgm::constants::NaN, fgm::constants::NaN), true },
                      Matrix3DUtilityParams{ fgm::Matrix3D(1.0f, 1.0f, 1.0f), false }));


/** @brief Verify that @ref std::Matrix3D::hasNaN returns `false` for integral types. */
TYPED_TEST(Matrix3DIntegralUtility, HasNaN_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix3D(value, value, value).hasNaN());
}


/**
 * @brief Verify that the static variant of @ref std::Matrix3D::hasNaN returns `true` if any of elements are IEE754
 *        NaN(Not-a-Number) and `false` otherwise.
 */
TEST_P(Matrix3DNaNChecker, StaticWrapper_ReturnTrueIfAnyElementIsNaN)
{
    const auto& [mat, expected] = GetParam();
    EXPECT_EQ(expected, fgm::Matrix3D<float>::hasNaN(mat));
}


/** @brief Verify that the static variant of @ref std::Matrix3D::hasNaN returns `false` for integral types. */
TYPED_TEST(Matrix3DIntegralUtility, StaticWrapper_HasNaN_ReturnsFalseForIntegrals)
{
    constexpr auto value = TypeParam(1);
    EXPECT_FALSE(fgm::Matrix3D<TypeParam>::hasNaN(fgm::Matrix3D(value, value, value)));
}

/** @} */
