/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vector2D conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector2DTestSetup.h"



/**
 * @addtogroup T_FGM_Vec2_Type_Conv
 * @{
 */

/**************************************
 *                                    *
 *            STATIC TESTS            *
 *                                    *
 **************************************/

/** @brief Verify that vector conversion constructor is available during compile time. */
namespace
{
    const fgm::Vector2D vecF(3.0f, 1.0f);
    const fgm::Vector2D<double> vecD(vecF);
    static_assert(std::is_same_v<decltype(vecD)::value_type, double>);

    const fgm::Vector2D<float> vecF2(vecD);
    static_assert(std::is_same_v<decltype(vecF2)::value_type, float>);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/

/**
 * @brief Verify that the conversion constructor promotes value type of vector components from float to double.
 */
TEST(Vector2DConversionConstructor, PromotesType)
{
    const fgm::Vector2D vec1(3.0f, 1.0f);

    [[maybe_unused]] const fgm::Vector2D<double> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, double>);
}


/** @brief Verify that the conversion constructor ensures deep-copy value semantics. */
TEST(Vector2DConversionConstructor, ReturnsNewInstance)
{
    // Given a float vector
    const fgm::Vector2D vec1(3.0f, 1.0f);

    // When converted to a double vector
    fgm::Vector2D<double> vec2(vec1);
    // And one of its value mutated
    vec2.x() = 5;

    // Then, the float vector remains unchanged
    EXPECT_VEC_CONTAINS(vec1, 3.0f, 1.0f);

    // And, the new vector is of type double with the mutated value
    EXPECT_VEC_CONTAINS(vec2, 5.0, 1.0);
}


/**
 * @brief Verify that the conversion constructor correctly demotes value type of vector components from double to float.
 */
TEST(Vector2DConversionConstructor, DemotesType)
{
    const fgm::Vector2D vec1(3.0, 1.0);

    [[maybe_unused]] const fgm::Vector2D<float> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, float>);
}

/** @} */
