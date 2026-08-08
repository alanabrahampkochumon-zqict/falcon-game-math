/**
 * @file Mat3x2.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 08, 2026
 *
 * @brief Verifies quaternion assertions in quaternion arithmetic operations that can result in application death.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <fgm/matrices/Mat3x2.h>
#include <utility>



#ifdef ENABLE_DEBUG_TESTS

/**
 * @addtogroup T_FGM_Mat3x2_Assertion
 * @{
 */

namespace
{
    fgm::Mat3x2 mat(1, 2, 3);


    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat3 invalid (row, column) indices.
     */
    class Mat3x2IndexingTests: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3x2OutOfBoundsRowColumnIndices, Mat3x2IndexingTests,
                             testing::Values(std::make_pair(3, 3), std::make_pair(2, 3), std::make_pair(3, 2),
                                             std::make_pair(100, 100)));


    class Mat3x2ColumnIndexing: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3x2OutOfBoundsColumnIndices, Mat3x2ColumnIndexing, testing::Values(3, 4, 100));


} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST_P(Mat3x2ColumnIndexingTests, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}


TEST_P(Mat3x2IndexingTests, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}


TEST_P(Mat3x2ColumnIndexingTests, OutOfBoundMutationTriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = fgm::Vec3<int>::zero()), "");
}


TEST_P(Mat3x2IndexingTests, OutOfBoundMutationTriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}

/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Mat3x2DivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), ""); }

/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Mat3x2DivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(this->_matrix /= 0, ""); }
/** @} */

#endif
