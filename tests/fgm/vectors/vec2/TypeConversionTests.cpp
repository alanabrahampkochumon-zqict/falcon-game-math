/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 04, 2026
 *
 * @brief Verify @ref fgm::Vec2 conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vec2TestSetup.h"



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
    constexpr fgm::Vec2 vecF(3.0f, 1.0f);
    constexpr fgm::Vec2<double> vecD(vecF);
    static_assert(std::is_same_v<decltype(vecD)::value_type, double>);

    [[maybe_unused]] constexpr fgm::Vec2<float> vecF2(vecD);
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
TEST(Vec2ConversionConstructor, PromotesType)
{
    const fgm::Vec2 vec1(3.0f, 1.0f);

    [[maybe_unused]] const fgm::Vec2<double> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, double>);
}


/** @brief Verify that the conversion constructor ensures deep-copy value semantics. */
TEST(Vec2ConversionConstructor, ReturnsNewInstance)
{
    // Given a float vector
    const fgm::Vec2 vec1(3.0f, 1.0f);

    // When converted to a double vector
    fgm::Vec2<double> vec2(vec1);
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
TEST(Vec2ConversionConstructor, DemotesType)
{
    const fgm::Vec2 vec1(3.0, 1.0);

    [[maybe_unused]] const fgm::Vec2<float> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, float>);
}

/** @} */
