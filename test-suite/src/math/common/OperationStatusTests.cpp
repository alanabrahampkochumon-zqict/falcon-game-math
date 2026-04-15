/**
 * @file OperationCodeTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: March 30, 2026
 *
 * @brief Verify @ref fgm::OperationStatus code to message mapping.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <common/OperationStatus.h>
#include <gtest/gtest.h>



/** @brief Parameters for testing @ref fgm::OperationStatus mapping to string message. */
struct OperationStatusMappingParams
{
    fgm::OperationStatus status;
    const char* expectedMessage;
};
/** @brief Test fixture for @ref fgm::OperationStatus mapping, parameterized by @ref OperationStatusMappingParams. */
class OperationStatusMappingTests: public ::testing::TestWithParam<OperationStatusMappingParams>
{};




/**
 * @addtogroup T_Op_Status
 * @{
 */

TEST_P(OperationStatusMappingTests, ReturnsCorrectMessage)
{
    const auto& [status, expectedMessage] = GetParam();
    const auto message = fgm::getStatusMessage(status);
    EXPECT_STREQ(expectedMessage, message);
}


INSTANTIATE_TEST_SUITE_P(
    OperationStatusMappingTestSuite, OperationStatusMappingTests,
    ::testing::Values(OperationStatusMappingParams{ fgm::OperationStatus::SUCCESS, "Operation success!" },
                      OperationStatusMappingParams{ fgm::OperationStatus::DIVISIONBYZERO, "Failure: Division by Zero" },
                      OperationStatusMappingParams{ fgm::OperationStatus::NANOPERAND,
                                                    "Failure: NaN operand encountered" },
                      OperationStatusMappingParams{ static_cast<fgm::OperationStatus>(7), "Failure: Unknown error" }));

/** @} */
