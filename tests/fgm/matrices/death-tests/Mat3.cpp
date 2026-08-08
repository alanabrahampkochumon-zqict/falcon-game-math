/**
 * @file Mat2.cpp
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

#include <fgm/matrices/Mat2.h>
#include <utility>


#ifdef ENABLE_DEBUG_TESTS

/**
 * @addtogroup T_FGM_Mat3x3_Assertion
 * @{
 */

namespace
{
    fgm::Mat2 mat(1, 2);

    /**************************************
     *            TEST SETUP              *
     **************************************/



    class Mat3Indexing: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3Tests, Mat3Indexing,
                             testing::Values(std::make_pair(4, 4), std::make_pair(3, 4), std::make_pair(4, 3),
                                             std::make_pair(100, 100)));

    class Mat3ColumnIndexing: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3Tests, Mat3ColumnIndexing, testing::Values(4, 5, 100));
} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/
/** @brief Verify that @ref fgm::Mat3 out-of-bounds column access triggers assert in debug mode. */
TEST_P(Mat3ColumnIndexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Mat3 mat(1, 2, 3);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}

/** @brief Verify that @ref fgm::Mat3 out-of-bounds row, column access triggers assert in debug mode. */
TEST_P(Mat3Indexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Mat3 mat(1, 2, 3);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}


/** @brief Verify that @ref fgm::Mat3 out-of-bounds column mutation triggers assert in debug mode. */
TEST_P(Mat3ColumnIndexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat3 mat(1, 2, 3);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = fgm::Vec3<int>::zero()), "");
}


/** @brief Verify that @ref fgm::Mat3 out-of-bounds row, column mutation triggers assert in debug mode. */
TEST_P(Mat3Indexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat3 mat(1, 2, 3);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}

/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Mat3DivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), ""); }

/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Mat3DivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(this->_matrix /= 0, ""); }

/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Mat3::inverse
 *        triggers assertion in debug mode.
 */
TEST_P(Mat3InverseSingularTests, TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(matrix.inverse()), "");
}

/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Mat3::inverse
 *        triggers assertion in debug mode.
 */
TEST_P(Mat3InverseSingularTests, StaticWrapper_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Mat3<float>::inverse(matrix)), "");
}

/** @} */

#endif

