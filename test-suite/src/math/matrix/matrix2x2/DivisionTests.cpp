/**
 * @file DivisionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 13, 2026
 *
 * @brief Verifies @ref fgm::Matrix2D division logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "MatrixTestSetup.h"



/**************************************
 *                                    *
 *               SETUP                *
 *                                    *
 **************************************/

template <typename T>
class Matrix2DDivision: public ::testing::Test
{
protected:
    fgm::Matrix2D<T> _matrix;
    T _scalar;
    fgm::Matrix2D<fgm::Magnitude<T>> _expectedMatrix;
    fgm::Matrix2D<T> _expectedTypedMatrix;

    void SetUp() override
    {
        _matrix = { fgm::Vector2D<T>{ 7, 3 }, fgm::Vector2D<T>{ 1, 6 } };
        _scalar = T(3);
        _expectedMatrix = { fgm::Vector2D{ fgm::Magnitude<T>(2.333333333333333), fgm::Magnitude<T>(1) },
                            fgm::Vector2D{ fgm::Magnitude<T>(0.3333333333333333), fgm::Magnitude<T>(2) } };
        _expectedTypedMatrix = { fgm::Vector2D{ T(2.333333333333333), T(1) },
                                 fgm::Vector2D{ T(0.3333333333333333), T(2) } };
    }
};
/** Test fixture for @ref fgm::Matrix2D division, parameterized by @ref SupportedArithmeticTypes */
TYPED_TEST_SUITE(Matrix2DDivision, SupportedArithmeticTypes);


/**
 * @addtogroup T_FGM_Mat2x2_Division
 * @{
 */


/**
 * @brief Verify that the binary division operator perform an element-wise divide
 *        and returns a new matrix instance.
 */
TYPED_TEST(Matrix2DDivision, ReturnsInverseScaledMatrix)
{
    const fgm::Matrix2D inverseScaledMat = this->_matrix / this->_scalar;

    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
}


/** @brief Verify that the binary division operator always return a floating-point matrix. */
TYPED_TEST(Matrix2DDivision, AlwaysReturnFloatingPointMatrix)
{
    [[maybe_unused]] const fgm::Matrix2D inverseScaledMat = this->_matrix / this->_scalar;
    static_assert(std::is_floating_point_v<typename decltype(inverseScaledMat)::value_type>);
}


/** @brief Verify that assertion is triggered when dividing by zero in Debug mode. */
TYPED_TEST(Matrix2DDivision, ByZero_TriggersAssertInDebugMode)
{
    EXPECT_DEBUG_DEATH(this->_matrix / 0, "Matrix division by zero");
}

///**
// * @brief Verify that the binary division operator perform an element-wise divide
// *        and returns a new matrix instance.
// */
//TYPED_TEST(Matrix2DDivision, ReturnsInverseScaledMatrix)
//{
//    const fgm::Matrix2D inverseScaledMat = this->_matrix / this->_scalar;
//
//    EXPECT_MAT_EQ(this->_expectedMatrix, inverseScaledMat);
//}
//
//
///** @brief Verify that the binary division operator always return a floating-point matrix. */
//TYPED_TEST(Matrix2DDivision, AlwaysReturnFloatingPointMatrix)
//{
//    [[maybe_unused]] const fgm::Matrix2D inverseScaledMat = this->_matrix / this->_scalar;
//    static_assert(std::is_floating_point_v<typename decltype(inverseScaledMat)::value_type>);
//}
//
//
///** @brief Verify that assertion is triggered when dividing by zero (compound division) in **Debug Mode**. */
//TYPED_TEST(Matrix2DDivision, ByZero_TriggersAssertInDebugMode)
//{
//    EXPECT_DEBUG_DEATH(this->_matrix / 0, "Matrix division by zero");
//}

/** @} */
