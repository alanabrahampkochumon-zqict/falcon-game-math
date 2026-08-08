/**
 * @file Mat3.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: August 08, 2026
 *
 * @brief Verifies quaternion assertions in quaternion arithmetic operations that can result in application death.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "CommonSetup.h"
#include "utils/MatrixUtils.h"

#include <fgm/matrices/Mat3.h>
#include <utility>



#ifdef ENABLE_DEBUG_TESTS

/**
 * @addtogroup T_FGM_Mat3x3_Assertion
 * @{
 */

namespace
{
    fgm::Mat3 mat(1, 2, 3);


    /**************************************
     *            TEST SETUP              *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Mat3 invalid (row, column) indices.
     */
    class Mat3IndexingTests: public testing::TestWithParam<std::pair<std::size_t, std::size_t>>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3OutOfBoundsRowColumnIndices, Mat3IndexingTests,
                             testing::Values(std::make_pair(4, 4), std::make_pair(3, 4), std::make_pair(4, 3),
                                             std::make_pair(100, 100)));



    /**
     * @brief Test fixture for @ref fgm::Mat3 invalid column indexing.
     */
    class Mat3ColumnIndexingTests: public testing::TestWithParam<std::size_t>
    {};
    INSTANTIATE_TEST_SUITE_P(Mat3OutOfBoundsColumnIndices, Mat3ColumnIndexingTests, testing::Values(4, 5, 100));


    /**
     * @brief Test fixture for @ref fgm::Mat3 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat2DivisionTests: public testing::Test
    {
    protected:
        fgm::Mat2<T> _matrix;
        T _scalar;
        fgm::Mat2<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { fgm::Vec2<T>{ 7, 3 }, fgm::Vec2<T>{ 1, 6 } };
            _scalar         = T(3);
            _expectedMatrix = { fgm::Vec2{ T(2.333333333333333), T(1) }, fgm::Vec2{ T(0.3333333333333333), T(2) } };
        }
    };
    TYPED_TEST_SUITE(Mat2DivisionTests, SupportedArithmeticTypes);



    /**
     * @brief Test fixture for @ref fgm::Mat3 Division.
     *
     * @tparam T The numeric type (int, float, double...) for matrix values.
     */
    template <typename T>
    class Mat3DivisionTests: public testing::Test
    {
    protected:
        fgm::Mat3<T> _matrix;
        T _scalar;
        fgm::Mat3<T> _expectedMatrix;

        void SetUp() override
        {
            _matrix         = { fgm::Vec3<T>{ 17, 13, 15 }, fgm::Vec3<T>{ 11, 16, 35 }, fgm::Vec3<T>{ 27, 44, 56 } };
            _scalar         = T(7);
            _expectedMatrix = { { T(2.428571428571428), T(1.857142857142857), T(2.142857142857143) },
                                { T(1.571428571428571), T(2.285714285714286), T(5.0) },
                                { T(3.857142857142857), T(6.285714285714286), T(8.0) } };
        }
    };
    TYPED_TEST_SUITE(Mat3DivisionTests, SupportedArithmeticTypes);


    // TODO: Add tests
    // /**
    //  * @brief Test fixture for @ref fgm::Mat2 Division with NaN elements.
    //  */
    // class Mat3DivisionNaNTests: public testing::TestWithParam<fgm::Mat3<float>>
    // {};
    // INSTANTIATE_TEST_SUITE_P(Mat3InvalidDivision, Mat3DivisionNaNTests,
    //                          ::testing::Values(fgm::Mat3<float>(fgm::constants::NaN, 3.0f, 3.0f),
    //                                            fgm::Mat3<float>(3.0f, fgm::constants::NaN, 3.0f),
    //                                            fgm::Mat3<float>(3.0f, 3.0f, fgm::constants::NaN),
    //                                            fgm::Mat3<float>(fgm ::constants::NaN, fgm::constants::NaN,
    //                                                             fgm ::constants::NaN)));
    //


    /** @brief Test fixture for calculating @ref fgm::Mat3 inverse with singular matrices. */
    class Mat3InverseSingularTests: public testing::TestWithParam<fgm::Mat3<float>>
    {};
    INSTANTIATE_TEST_SUITE_P(
        Mat3SingularMatrixInverse, Mat3InverseSingularTests,
        ::testing::Values(
            fgm::Mat3{ fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ 7.0f, 8.0f, 9.0f } },
            fgm::Mat3{ fgm::Vec3{ 1.0f, 1.0f, 5.0f }, fgm::Vec3{ 2.0f, 2.0f, 3.0f }, fgm::Vec3{ 3.0f, 3.0f, 9.0f } },
            fgm::Mat3{ fgm::Vec3{ 0.0f, 0.0f, 0.0f }, fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ 1.0f, 8.0f, 9.0f } },
            fgm::Mat3{ fgm::Vec3{ 0.0f, 5.0f, 1.0f }, fgm::Vec3{ 0.0f, 2.0f, 3.0f }, fgm::Vec3{ 0.0f, 8.0f, 9.0f } },
            fgm::Mat3{ fgm::Vec3{ 1.0f, 2.0f, 3.0f }, fgm::Vec3{ 2.0f, 4.0f, 6.0f }, fgm::Vec3{ 7.0f, 8.0f, 9.0f } },
            fgm::Mat3{ fgm::Vec3{ 1.0f, 2.0f, 1.0f }, fgm::Vec3{ 2.0f, 4.0f, 3.0f }, fgm::Vec3{ 3.0f, 6.0f, 9.0f } }));



    // TODO: Add tests
    // /** @brief Test fixture for @ref fgm::Mat3 inverse with NaN elements. */
    // class Mat3InverseNaNTests: public testing::TestWithParam<fgm::Mat3<float>>
    // {};
    // INSTANTIATE_TEST_SUITE_P(Mat3NaNMatrixInverse, Mat3InverseNaNTests,
    //                          ::testing::Values(fgm::Mat3<float>(fgm::constants::NaN, 3.0f, 3.0f),
    //                                            fgm::Mat3<float>(3.0f, fgm::constants::NaN, 3.0f),
    //                                            fgm::Mat3<float>(3.0f, 3.0f, fgm::constants::NaN),
    //                                            fgm::Mat3<float>(fgm::constants::NaN, fgm::constants::NaN,
    //                                                             fgm::constants::NaN)));

} // namespace



/**************************************
 *           RUNTIME TESTS            *
 **************************************/

TEST_P(Mat3ColumnIndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col]), "");
}

TEST_P(Mat3IndexingTests, OutOfBoundAccess_TriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col)), "");
}


TEST_P(Mat3ColumnIndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto col = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat[col] = fgm::Vec3<int>::zero()), "");
}


TEST_P(Mat3IndexingTests, OutOfBoundMutation_TriggersAssertInDebugMode)
{
    const auto [row, col] = GetParam();
    EXPECT_DEBUG_DEATH(static_cast<void>(mat(row, col) = 5), "");
}


TYPED_TEST(Mat3DivisionTests, DivideOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(static_cast<void>(this->_matrix / 0), ""); }


TYPED_TEST(Mat3DivisionTests, DivideEqualsOperator_ByZeroTriggersAssertInDebugMode)
{ EXPECT_DEBUG_DEATH(this->_matrix /= 0, ""); }


TEST_P(Mat3InverseSingularTests, TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(matrix.inverse()), "");
}


TEST_P(Mat3InverseSingularTests, StaticWrapper_TriggersAssertionInDebugMode)
{
    const auto& matrix = GetParam();
    // Static cast is placed to suppress the no-discard warning
    EXPECT_DEBUG_DEATH(static_cast<void>(fgm::Mat3<float>::inverse(matrix)), "");
}

/** @} */

#endif
