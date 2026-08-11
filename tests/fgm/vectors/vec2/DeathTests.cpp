#ifdef ENABLE_DEBUG_TESTS
class Vec2Indexing: public testing::TestWithParam<std::size_t>
{};
INSTANTIATE_TEST_SUITE_P(Vec2Tests, Vec2Indexing, testing::Values(3, 4, 100));
#endif

#ifdef ENABLE_DEBUG_TESTS
/** @brief Verify that @ref fgm::Vec2 out-of-bounds access triggers assert in debug mode. */
TEST_P(Vec2Indexing, OutOfBoundAccessTriggersAssertInDebugMode)
{
    const fgm::Vec2 vec(1, 2);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index], "");
}
#endif


#ifdef ENABLE_DEBUG_TESTS
/** @brief Verify that @ref fgm::Vec2 out-of-bounds mutation triggers assert in debug mode. */
TEST_P(Vec2Indexing, OutOfBoundMutationTriggersAssertInDebugMode)
{
    fgm::Vec2 vec(1, 2);
    const auto index = GetParam();
    EXPECT_DEBUG_DEATH(vec[index] = 2, "");
}
#endif



/**************************************
 *        SCALAR DIVISION TESTS       *
 **************************************/

#ifndef ENABLE_DEBUG_TESTS
/**
 * @brief Verify that dividing a float vector by zero returns an
 *       infinity vector of float type.
 */
TEST(Vec2ScalarDivision, FloatVectorDivisionByZeroReturnsInfinityVector)
{
    const fgm::Vec2 vec(1.0f, 3.0f);
    EXPECT_VEC_INF(vec / 0);
}


/**
 * @brief Verify that dividing a double vector by zero returns an
 *       infinity vector of double type.
 */
TEST(Vec2ScalarDivision, DoubleVectorDivisionByZeroReturnsInfinityVector)
{
    const fgm::Vec2 vec(1.0, 3.0);
    EXPECT_VEC_INF(vec / 0);
}
#endif


#ifdef ENABLE_DEBUG_TESTS

/**
 * @brief Verify that the binary division assignment operator when dividing a vector by zero,
 *        triggers assert in debug mode.
 */
TYPED_TEST(Vec2ScalarDivision, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec / 0), ""); }


/**
 * @brief Verify that the compound division assignment operator when dividing a vector by zero,
 *        triggers assert in debug mode.
 */
TYPED_TEST(Vec2ScalarDivision, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{
    [[maybe_unused]] fgm::Vec2 newVec = this->_vec;
    EXPECT_DEBUG_DEATH(static_cast<void>(newVec /= 0), "");
}
#endif
#ifdef ENABLE_DEBUG_TESTS
/**
 * @brief Verify that normalizing a vector with zero magnitude triggers assert in debug mode.
 */
TYPED_TEST(Vec2NormalizationTests, ZeroMagnitudeTriggersAssertInDebugMode)
{
    const fgm::Vec2<TypeParam> zVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(zVec.normalize()), "");
}


/**
 * @brief Verify that normalizing a vector with zero magnitude using static variant of fgm::Vec2::normalize triggers
 *        assert in debug mode.
 */
TYPED_TEST(Vec2NormalizationTests, StaticWrapper_ZeroMagnitudeTriggersAssertInDebugMode)
{
    const fgm::Vec2<TypeParam> zVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Vec2<TypeParam>::normalize(zVec)), "");
}

#endif

#ifdef ENABLE_DEBUG_TESTS
/**
 * @brief Verify that projecting a vector onto zero vector triggers assert in debug mode.
 */
TYPED_TEST(Vec2ProjectionTests, ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const fgm::Vec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.project(zeroVec)), "");
}


/**
 * @brief Verify that projecting a vector onto zero vector using static variant of @ref fgm::Vec2::project
 *        triggers assert in debug mode.
 */
TYPED_TEST(Vec2ProjectionTests, StaticWrapper_ProjectionOntoZeroVectorTriggersAssertionInCallback)
{
    const fgm::Vec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Vec2<TypeParam>::project(this->_vec, zeroVec)), "");
}

#endif


#ifdef ENABLE_DEBUG_TESTS
/**
 * @brief Verify that rejecting a vector from a zero vector triggers assert in debug mode.
 */
TYPED_TEST(Vec2RejectionTests, FromZeroVectorTriggersAssertionInCallback)
{
    const fgm::Vec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(this->_vec.reject(zeroVec)), "");
}


/**
 * @brief Verify that rejecting a vector from a zero vector using static variant of @ref fgm::Vec2::reject
 *        triggers assert in debug mode.
 */
TYPED_TEST(Vec2RejectionTests, StaticWrapper_FromZeroVectorTriggersAssertionInCallback)
{
    const fgm::Vec2<TypeParam> zeroVec(0, 0);
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Vec2<TypeParam>::reject(this->_vec, zeroVec)), "");
}

#endif

