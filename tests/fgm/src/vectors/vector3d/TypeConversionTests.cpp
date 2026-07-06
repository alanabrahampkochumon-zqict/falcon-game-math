/**
 * @file TypeConversionTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: April 02, 2026
 *
 * @brief Verify @ref fgm::Vector3 conversion constructor logic.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "Vector3TestSetup.h"



/**
 * @addtogroup T_FGM_Vec3_Type_Conv
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
    constexpr fgm::Vector3 vecF(3.0f, 1.0f, 4.0f);
    constexpr fgm::Vector3<double> vecD(vecF);
    static_assert(std::is_same_v<decltype(vecD)::value_type, double>);

    [[maybe_unused]] constexpr fgm::Vector3<float> vecF2(vecD);
    static_assert(std::is_same_v<decltype(vecF2)::value_type, float>);

} // namespace



/**************************************
 *                                    *
 *           RUNTIME TESTS            *
 *                                    *
 **************************************/


/**
 * @brief Verify that the conversion constructor correctly promotes components from float to double.
 */
TEST(Vector3ConversionConstructor, PromotesType)
{
    const fgm::Vector3 vec1(3.0f, 1.0f, 6.0f);

    [[maybe_unused]] const fgm::Vector3<double> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, double>);
}


/** @brief Verify that the conversion constructor ensures deep-copy value semantics. */
TEST(Vector3ConversionConstructor, ReturnsNewInstance)
{
    // Given a float vector
    const fgm::Vector3 vec1(3.0f, 1.0f, 6.0f);

    // When converted to a double vector
    fgm::Vector3<double> vec2(vec1);
    // And one of its value mutated
    vec2.x() = 5;

    // Then, the float vector remains unchanged
    EXPECT_VEC_CONTAINS(vec1, 3.0f, 1.0f, 6.0f);

    // And, the new vector is of type double with the mutated value
    EXPECT_VEC_CONTAINS(vec2, 5.0, 1.0, 6.0);
}


/**
 * @brief Verify that the conversion constructor correctly demotes components from double to float.
 */
TEST(Vector3ConversionConstructor, DemotesType)
{
    const fgm::Vector3 vec1(3.0, 1.0, 6.0);

    [[maybe_unused]] const fgm::Vector3<float> vec2(vec1);

    static_assert(std::is_same_v<decltype(vec2)::value_type, float>);
}

/** @} */
