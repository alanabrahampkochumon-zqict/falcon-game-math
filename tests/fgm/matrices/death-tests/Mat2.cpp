

#ifdef ENABLE_DEBUG_TESTS
    #include <utility>

    /**
     * @brief Test fixture for @ref fgm::Mat2 invalid (row, column) indices.
     */
    class Mat2IndexingTests: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
INSTANTIATE_TEST_SUITE_P(Mat2OutOfBoundsRowColumnIndices, Mat2IndexingTests,
                         testing::Values(std::make_pair(3, 3), std::make_pair(2, 3), std::make_pair(3, 2),
                                         std::make_pair(100, 100)));


/**
 * @brief Test fixture for @ref fgm::Mat2 invalid column indexing.
 */
class Mat2ColumnIndexingTests: public testing::TestWithParam<std::size_t>
{};
INSTANTIATE_TEST_SUITE_P(Mat2OutOfBoundsColumnIndices, Mat2ColumnIndexingTests, testing::Values(3, 4, 100));
#endif




#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that @ref fgm::Mat2 out-of-bounds column access triggers assert in debug mode. */
TEST_P(Mat2ColumnIndexingTests, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Mat2 mat(1, 2);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}

/** @brief Verify that @ref fgm::Mat2 out-of-bounds row, column access triggers assert in debug mode. */
TEST_P(Mat2IndexingTests, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Mat2 mat(1, 2);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}

#endif


#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that @ref fgm::Mat2 out-of-bounds column mutation triggers assert in debug mode. */
TEST_P(Mat2ColumnIndexingTests, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat2 mat(1, 2);
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = fgm::Vec2<int>::zero()), "");
}


/** @brief Verify that @ref fgm::Mat2 out-of-bounds row, column mutation triggers assert in debug mode. */
TEST_P(Mat2IndexingTests, OutOfBoundMutationTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Mat2 mat(1, 2);
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}

#endif

#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Mat2Division, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), ""); }

#endif

#ifdef ENABLE_DEBUG_TESTS

/** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
TYPED_TEST(Mat2Division, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(this->_matrix /= 0, ""); }

#endif
