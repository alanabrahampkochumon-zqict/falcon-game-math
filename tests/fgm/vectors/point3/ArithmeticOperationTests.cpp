/**
 * @file ArithmeticOperationTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: July 30, 2026
 *
 * @brief Verify @ref fgm::Point3 arithmetic operator(+, -) logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Point3TestSetup.h"


/**
 * @addtogroup T_FGM_Point3_Addition
 * @{
 */

namespace
{

    /**************************************
     *                                    *
     *            TEST SETUP              *
     *                                    *
     **************************************/

    /**
     * @brief Test fixture for @ref fgm::Point3 addition operation.
     *
     * @tparam T The scalar type (e.g., float, double) used for the point.
     */
    template <typename T>
    class Point3Addition: public testing::Test
    {
    protected:
        fgm::Vec3<T> _vector;
        fgm::Point3<T> _point;
        fgm::Point3<T> _expectedPoint;

        void SetUp() override
        {
            _vector        = { T(3), T(1), T(6) };
            _point         = { T(1), T(2), T(3) };
            _expectedPoint = { T(4), T(3), T(9) };
        }
    };
    TYPED_TEST_SUITE(Point3Addition, SupportedArithmeticTypes);


    /**
     * @brief Test fixture for @ref fgm::Point3 subtraction operation.
     *
     * @tparam T The scalar type (e.g., float, double) used for the point.
     */
    template <typename T>
    class Point3Subtraction: public testing::Test
    {
    protected:
        fgm::Point3<T> _pointA;
        fgm::Point3<T> _pointB;
        fgm::Point3<T> _expectedVector;

        void SetUp() override
        {
            _pointA         = { T(95), T(11), T(6) };
            _pointB         = { T(8), T(5), T(2) };
            _expectedVector = { T(87), T(6), T(4) };
        }
    };
    TYPED_TEST_SUITE(Point3Subtraction, SupportedArithmeticTypes);



    /**************************************
     *                                    *
     *            STATIC TESTS            *
     *                                    *
     **************************************/

    namespace static_tests
    {
        constexpr fgm::Point3<int> POINT_A(1, 2, 3);
        constexpr fgm::Vec3 DIR_VEC(1, 3, 7);
        constexpr fgm::Point3<int> POINT_B(4, 3, 1);

        /// @test Verify that a Point3 + Vec3 returns the correct Point3 at compile time.
        constexpr auto SUM_POINT = POINT_A + DIR_VEC;
        static_assert(std::is_same_v<decltype(SUM_POINT), const fgm::Point3<int>>);
        static_assert(SUM_POINT.x() == 2);
        static_assert(SUM_POINT.y() == 5);
        static_assert(SUM_POINT.z() == 10);

    } // namespace static_tests

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

TYPED_TEST(Point3Addition, PlusOperator_ReturnsAPointWithComponentwiseSum)
{
    const fgm::Point3 result = this->_point + this->_vector;
    EXPECT_VEC_EQ(this->_expectedPoint, result);
}


TEST(Point3Addition, PlusOperator_MixedTypePromotesType)
{
    const fgm::Point3<float> point(3.0f, 0.0f, -1.0f);
    const fgm::Vec3 vector(9.0, -5.0, 10.0);

    [[maybe_unused]] const fgm::Point3 result = point + vector;

    static_assert(std::is_same_v<decltype(result)::value_type, double>);
}


TYPED_TEST(Point3Addition, PlusEqualsOperator_ReturnsSamePointWithComponentwiseSum)
{
    this->_point += this->_vector;
    EXPECT_VEC_EQ(this->_expectedPoint, this->_point);
}


TEST(Point3Addition, PlusEqualsOperator_MixedTypeDoesNotPromoteType)
{
    fgm::Point3<float> point(3.0f, 0.0f, -1.0f);
    const fgm::Vec3 vector(9.0, -5.0, 10.0);

    static_cast<void>(point += vector);

    static_assert(std::is_same_v<decltype(point)::value_type, float>);
}

/** @} */



/**
 * @addtogroup T_FGM_Point3_Subtraction
 * @{
 */

// /**
//  * @brief Verify that the binary subtraction operator perform a component-wise subtraction and
//  *       returns a new vector instance.
//  */
// TYPED_TEST(Point3Subtraction, MinusOperator_ReturnsDifference)
// {
//     const fgm::Point3 result = this->_pointA - this->_pointB;
//
//     EXPECT_VEC_EQ(this->_expectedVector, result);
// }
//
//
// /**
//  * @brief Verify that the compound subtraction assignment operator perform a component-wise subtraction
//  *       and mutates the vector in-place.
//  */
// TYPED_TEST(Point3Subtraction, MinusEqualsOperator_ReturnsSameVectorWithDifference)
// {
//     this->_pointA -= this->_pointB;
//
//     EXPECT_VEC_EQ(this->_expectedVector, this->_pointA);
// }
//
//
// /**
//  * @brief Verify that the binary subtraction operator perform automatic type promotion
//  *       to the wider numeric type.
//  */
// TEST(Point3Subtraction, MinusOperator_MixedTypePromotesType)
// {
//     const fgm::Point3 vec1(3.0f, 0.0f, -1.0f);
//     const fgm::Point3 vec2(9.0, -5.0, 10.0);
//
//     [[maybe_unused]] const fgm::Point3 result = vec1 - vec2;
//
//     static_assert(std::is_same_v<decltype(result)::value_type, double>);
// }
//
//
// /**
//  * @brief Verify that the compound subtraction assignment operator maintains the destination type and
//  *       perform an implicit cast.
//  */
// TEST(Point3Subtraction, MinusEqualsOperator_MixedTypeDoesNotPromoteType)
// {
//     fgm::Point3 vec1(3.0f, 0.0f, -1.0f);
//     [[maybe_unused]] const fgm::Point3 vec2(9.0, -5.0, 10.0);
//
//     static_cast<void>(vec1 -= vec2);
//
//     static_assert(std::is_same_v<decltype(vec1)::value_type, float>);
// }
//
// /** @} */
//
