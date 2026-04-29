#pragma once
/**
 * @file PreprocessorDefinitions.h
 * @author Alan Abraham P Kochumon
 * @date Created on: April 23, 2026
 *
 * @brief Preprocessor directives for compiler intrinsic debug breaks, and assertions.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <type_traits>



/**
 * @addtogroup FGM_Macro
 * @{
 */

/**
 * @brief Triggers a compiler-specific breakpoint.
 */
#ifdef _MSC_VER
    #define FGM_DEBUG_BREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
    #define FGM_DEBUG_BREAK() __builtin_trap()
#else
    #include <signal.h>
    #define FGM_DEBUG_BREAK() raise(SIGTRAP)
#endif


/**
 * @def FGM_ASSERT_MSG(condition, message)
 * @brief Asserts a condition is `true`, breaking into the debugger with a custom message if `false`.
 *
 * @note This macro is strictly active only in **Debug** builds. In **Release** builds
 *       (when `NDEBUG` is defined), it expands into a zero-cost void cast.
 * @note To ensure that the macro support compile-time evaluation an exception is thrown,
 *       instead of logging during compile time.
 *
 * @param condition The boolean expression to evaluate.
 * @param message   A string literal or streamable object providing context on the failure.
 */
#ifndef NDEBUG
    #define FGM_ASSERT_MSG(condition, message)                                                                         \
        do                                                                                                             \
        {                                                                                                              \
            if (std::is_constant_evaluated())                                                                          \
            {                                                                                                          \
                if (!(condition))                                                                                      \
                    throw message;                                                                                     \
            }                                                                                                          \
            else                                                                                                       \
            {                                                                                                          \
                if (!(condition))                                                                                      \
                {                                                                                                      \
                    std::cerr << "[FGM ASSERTION FAILED]\n"                                                            \
                              << "Condition: " << #condition << "\n"                                                   \
                              << "Message:   " << (message) << "\n"                                                    \
                              << "Location:  " << __FILE__ << ":" << __LINE__ << std::endl;                            \
                    FGM_DEBUG_BREAK();                                                                                 \
                }                                                                                                      \
            }                                                                                                          \
        } while (false)
#else
    #define FGM_ASSERT_MSG(condition, message) ((void) 0)
#endif

/**
 * @def FGM_ASSERT(condition)
 * @brief Asserts a condition is `true`, breaking into the debugger if `false`.
 *
 * @note This macro is strictly active only in **Debug** builds. In **Release** builds
 *       (when `NDEBUG` is defined), it expands into a zero-cost void cast.
 * @note To ensure that the macro support compile-time evaluation an exception is thrown,
 *       instead of logging during compile time.
 *
 * @param condition The boolean expression to evaluate.
 */
#ifndef NDEBUG
    #define FGM_ASSERT(condition)                                                                                      \
        do                                                                                                             \
        {                                                                                                              \
            if (std::is_constant_evaluated())                                                                          \
            {                                                                                                          \
                if (!(condition))                                                                                      \
                    throw std::string("[FGM ASSERTION FAILED]\n") + std::string(#condition);                           \
            }                                                                                                          \
            else                                                                                                       \
            {                                                                                                          \
                if (!(condition))                                                                                      \
                {                                                                                                      \
                    std::cerr << "[FGM ASSERTION FAILED]\n"                                                            \
                              << "Condition: " << #condition << "\n"                                                   \
                              << "Location:  " << __FILE__ << ":" << __LINE__ << std::endl;                            \
                    FGM_DEBUG_BREAK();                                                                                 \
                }                                                                                                      \
            }                                                                                                          \
        } while (false) #else
    #define FGM_ASSERT(condition) ((void) 0)
#endif

/** @} */
