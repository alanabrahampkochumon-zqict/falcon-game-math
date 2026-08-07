/**
 * @file Mat2x3.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 4, 2026
 *
 * @brief Verifies quaternion assertions in quaternion arithmetic operations that can result in application death.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */

#include "CommonSetup.h"
#include "utils/MatrixUtils.h"
#include "utils/VectorUtils.h"

#include <fgm/matrices/Mat2x3.h>
#include <utility>

/**
 * @addtogroup T_FGM_Mat2x3_Assertion
 * @{
 */

#ifdef ENABLE_DEBUG_TESTS

namespace
{
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat2 (Row, Column) Access.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    class Mat2x3IndexingTests: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2x3InvalidIndex, Mat2x3IndexingTests,
                             testing::Values(std::make_pair(3, 3), std::make_pair(2, 3), std::make_pair(3, 2),
                                             std::make_pair(100, 100)));



    /**
     * @brief Test fixture for @ref fgm::Mat2 Column Access.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    class Mat2x3ColumnIndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2x3InvalidColumnIndex, Mat2x3ColumnIndexingTests, testing::Values(3, 4, 100));



    /**
     * @brief Test fixture for @ref fgm::Mat2x3 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2x3Division: public ::testing::Test
    {
    protected:
        fgm::Mat2x3<T> _matrix;
        T _scalar;
        fgm::Mat2x3<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { fgm::Vec2{ T(7), T(3) }, fgm::Vec2{ T(1), T(6) }, fgm::Vec2{ T(3), T(9) } };
            _scalar         = T(3);
            _expectedMatrix = { fgm::Vec2{ T(2.333333333333333), T(1) }, fgm::Vec2{ T(0.3333333333333333), T(2) },
                                fgm::Vec2{ T(1), T(3) } };
        }
    };
    TYPED_TEST_SUITE(Mat2x3Division, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref fgm::Mat2x3 Division with NaN elements.
     */
    class NaNMat2x3Division: public ::testing::TestWithParam<fgm::Mat2x3<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2x3DivisionTestSuite, NaNMat2x3Division,
                             ::testing::Values(fgm::Mat2x3<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
                                               fgm::Mat2x3<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
                                               fgm::Mat2x3<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
                                               fgm::Mat2x3<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f, 3.0f),
                                               fgm::Mat2x3<float>(3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN, 3.0f),
                                               fgm::Mat2x3<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, fgm::constants::NaN),
                                               fgm::Mat2x3<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                  fgm ::constants::NaN, fgm ::constants::NaN,
                                                                  fgm::constants::NaN, fgm::constants::NaN)));



    /** @brief Test fixture for calculating @ref fgm::Mat2 inverse with singular matrices. */
    class Mat2InverseSingularTests: public testing::TestWithParam<fgm::Mat2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2SingularMatrixInverse, Mat2InverseSingularTests,
                             ::testing::Values(fgm::Mat2{ fgm::Vec2{ 1.0f, 2.0f }, fgm::Vec2{ 1.0f, 2.0f } },
                                               fgm::Mat2{ fgm::Vec2{ 2.0f, 2.0f }, fgm::Vec2{ 2.0f, 2.0f } },
                                               fgm::Mat2{ fgm::Vec2{ 3.0f, 2.0f }, fgm::Vec2{ 6.0f, 4.0f } },
                                               fgm::Mat2{ fgm::Vec2{ 0.0f, 0.0f }, fgm::Vec2{ 4.0f, 5.0f } },
                                               fgm::Mat2{ fgm::Vec2{ 0.0f, 3.0f }, fgm::Vec2{ 0.0f, 5.0f } }));



    /** @brief Test fixture for @ref fgm::Mat2 inverse with NaN elements. */
    class Mat2InverseNaNTests: public ::testing::TestWithParam<fgm::Mat2<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat2NaNMatrixInverse, Mat2InverseNaNTests,
                             ::testing::Values(fgm::Mat2<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
                                               fgm::Mat2<float>(3.0f, fgm::constants::NaN, 3.0f, 3.0f),
                                               fgm::Mat2<float>(3.0f, 3.0f, fgm::constants::NaN, 3.0f),
                                               fgm::Mat2<float>(3.0f, 3.0f, 3.0f, fgm::constants::NaN),
                                               fgm::Mat2<float>(fgm ::constants::NaN, fgm::constants::NaN,
                                                                fgm ::constants::NaN, fgm ::constants::NaN)));
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST_P(Mat2x3ColumnIndexingTests, OutOfBoundAccessTriggers_AssertInDebugMode)
{
    const fgm::Mat2x3 mat(1, 2, 3, 4, 5, 6);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}

TEST_P(Mat2x3IndexingTests, OutOfBoundAccessTriggers_AssertInDebugMode)
{
    const fgm::Mat2x3 mat(1, 2, 3, 4, 5, 6);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}


TEST_P(Mat2x3ColumnIndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat2x3 mat(1, 2, 3, 4, 5, 6);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = fgm::Vec2<int>::zero()), "");
}


TEST_P(Mat2x3IndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat2x3 mat(1, 2, 3, 4, 5, 6);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}


TYPED_TEST(Mat2x3Division, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), ""); }


TYPED_TEST(Mat2x3Division, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(this->_matrix /= 0, ""); }


TEST_P(Mat2InverseSingularTests, Inverse_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(matrix.inverse()), "");
}

TEST_P(Mat2InverseSingularTests, StaticWrapper_Inverse_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Mat2<float>::inverse(matrix)), "");
}

TEST_P(Mat2InverseNaNTests, Inverse_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(matrix.inverse()), "");
}

TEST_P(Mat2InverseNaNTests, StaticWrapper_Inverse_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Mat2<float>::inverse(matrix)), "");
}

#endif

/** @} */
