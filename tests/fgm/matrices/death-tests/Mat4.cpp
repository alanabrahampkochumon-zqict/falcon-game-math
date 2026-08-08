/**
 * @file Mat3x4.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 08, 2026
 *
 * @brief Verifies quaternion assertions in quaternion arithmetic operations that can result in application death.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <fgm/matrices/Mat3x4.h>
#include <utility>



#ifdef ENABLE_DEBUG_TESTS

/**
 * @addtogroup T_FGM_Mat3x4_Assertion
 * @{
 */

namespace
{
    fgm::Mat3x4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    class Mat4Indexing: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat4Tests, Mat4Indexing,
                             testing::Values(std::make_pair(5, 5), std::make_pair(4, 5), std::make_pair(5, 4),
                                             std::make_pair(100, 100)));

    class Mat4ColumnIndexing: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat4Tests, Mat4ColumnIndexing, testing::Values(5, 6, 100));
    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat3x4 invalid (row, column) indices.
     */
    class Mat3x4IndexingTests: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3x4OutOfBoundsRowColumnIndices, Mat3x4IndexingTests,
                             testing::Values(std::make_pair(3, 3), std::make_pair(3, 4), std::make_pair(4, 3),
                                             std::make_pair(100, 100)));



    /**
     * @brief Test fixture for @ref fgm::Mat3x4 invalid column indices.
     */
    class Mat3x4ColumnIndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3x4OutOfBoundsColumnIndices, Mat3x4ColumnIndexingTests, testing::Values(4, 5, 100));



    /**
     * @brief Test fixture for @ref fgm::Mat3x4 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3x4DivisionTests: public testing::Test
    {
    protected:
        fgm::Mat3x4<T> _matrix;
        T _scalar;
        fgm::Mat3x4<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix = { fgm::Vec3{ T(7), T(3), T(0) }, fgm::Vec3{ T(1), T(6), T(6) }, fgm::Vec3{ T(0), T(6), T(9) },
                        fgm::Vec3{ T(27), T(24), T(30) } };
            _scalar = T(3);
            _expectedMatrix = { fgm::Vec3{ T(2.333333333333333), T(1), T(0) },
                                fgm::Vec3{ T(0.3333333333333333), T(2), T(2) }, fgm::Vec3{ T(0), T(2), T(3) },
                                fgm::Vec3{ T(9), T(8), T(10) } };
        }
    };
    TYPED_TEST_SUITE(Mat3x4DivisionTests, SupportedArithmeticTypes);


    // TODO: Add after adding assertions
    // /**
    //  * @brief Test fixture for @ref fgm::Mat3x4 Division with NaN elements.
    //  */
    // class NaNMat3x4Division: public testing::TestWithParam<fgm::Mat3x4<float>>
    // {};
    // INSTANTIATE_TEST_SUITE_P(
    //     Mat3x4DivisionTestSuite, NaNMat3x4Division,
    //     ::testing::Values(
    //         fgm::Mat3x4<float>(fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         fgm::Mat3x4<float>(3.0f,
    //         fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         fgm::Mat3x4<float>(3.0f, 3.0f,
    //         fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         fgm::Mat3x4<float>(3.0f, 3.0f, 3.0f,
    //         fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         fgm::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f,
    //         fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         fgm::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         fgm::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f),
    //         fgm::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         fgm::constants::NaN, 3.0f, 3.0f, 3.0f, 3.0f),
    //         fgm::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         fgm::constants::NaN, 3.0f, 3.0f, 3.0f),
    //         fgm::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         fgm::constants::NaN, 3.0f, 3.0f),
    //         fgm::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         fgm::constants::NaN, 3.0f),
    //         fgm::Mat3x4<float>(3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
    //         fgm::constants::NaN), fgm::Mat3x4<float>(fgm ::constants::NaN, fgm::constants::NaN, fgm ::constants::NaN,
    //         fgm ::constants::NaN,
    //                            fgm::constants::NaN, fgm::constants::NaN, fgm ::constants::NaN, fgm::constants::NaN,
    //                            fgm ::constants::NaN, fgm ::constants::NaN, fgm::constants::NaN,
    //                            fgm::constants::NaN)));


} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST_P(Mat3x4ColumnIndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}


TEST_P(Mat3x4IndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}


TEST_P(Mat3x4ColumnIndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = fgm::Vec3<int>::zero()), "");
}


TEST_P(Mat3x4IndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}


TYPED_TEST(Mat3x4DivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), ""); }


TYPED_TEST(Mat3x4DivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(this->_matrix /= 0, ""); }

///////////////////////////////////////////////
/** @brief Verify that @ref fgm::Mat4 out-of-bounds column access triggers assert in debug mode. */
TEST_P(Mat4ColumnIndexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Mat4 mat(1, 2, 3, 4);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}

/** @brief Verify that @ref fgm::Mat4 out-of-bounds row, column access triggers assert in debug mode. */
TEST_P(Mat4Indexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Mat4 mat(1, 2, 3, 4);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}
/** @brief Verify that @ref fgm::Mat4 out-of-bounds column mutation triggers assert in debug mode. */
TEST_P(Mat4ColumnIndexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat4 mat(1, 2, 3, 4);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = fgm::Vec4<int>::zero()), "");
}


/** @brief Verify that @ref fgm::Mat4 out-of-bounds row, column mutation triggers assert in debug mode. */
TEST_P(Mat4Indexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat4 mat(1, 2, 3, 4);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}

/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Mat4Division, DivideOperator_ByZeroTriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), "");
}

/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Mat4Division, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix /= 0), "");
}

/**
 * @brief Verify that inverting a singular matrix using @ref fgm::Mat4::inverse
 *        triggers assertion in debug mode.
 */
TEST_P(Mat4InverseSingularTests, TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(matrix.inverse()), "");
}

/**
 * @brief Verify that inverting a singular matrix using static variant of @ref fgm::Mat4::inverse
 *        triggers assertion in debug mode.
 */
TEST_P(Mat4InverseSingularTests, StaticWrapper_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Mat4<float>::inverse(matrix)), "");
}

/** @} */

#endif
