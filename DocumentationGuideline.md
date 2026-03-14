# Documentation Guideline for Falcon Game Math Library (FGM)

## 1. General Language & Formatting

- **Tense:** Use imperative present tense (e.g., "Calculate", not "Calculates").
- **Dialect:** Use American English.
- **Entity References:** - Use `@ref` for internal classes, structs, and concepts to generate hyperlinks.
    - Use backticks ( \` \` ) for variables, constants, and `std` library types.
- **Formulas:** Use LaTeX (enclosed in `$`) for mathematical definitions to ensure clarity.

## 2. Doxygen Nomenclature

### Brief (`@brief`)

- **Style:** Single imperative sentence. Do not repeat the function signature.
- **Good:** `@brief Computes the dot product.`
- **Bad:** `@brief This function returns the dot product as a T.`

### Note (`@note`)

- **Style:** Use for important constraints or non-obvious behavior.
- **Example:** `@note Arithmetic operations are restricted via the @ref StrictArithmetic concept.`

### Extended Explanations (`@par <Heading>`)

- **Usage:** Use for configuration flags, detailed algorithmic explanations, or complex notes.

### Parameters (`@param`)

- **Format:** `[direction] name Description.`
- **Direction:** Always specify `[in]`, `[out]`, or `[in,out]`.
- **Example:** `@param[in] epsilon Maximum allowable difference for equality.`

### Template Parameters (`@tparam`)

- **Usage:** Describe requirements for template arguments.
- **Example:** `@tparam T Type of the vector components. Must satisfy @ref Arithmetic.`

### Returns (`@return`)

- **Guideline:** Omit the type name (it's in the signature).
- **Style:** Capitalize the first letter. Use "True if..." for booleans.
- **Good:** `@return Magnitude of the @ref Vector3D.`
- **Good:** `@return True if all components match exactly.`

---

## 3. Test Nomenclature (Google Test)

### Test Brief

- **Style:** Single sentence describing the verification goal.
- **Example:** `/** @brief Verifies @ref Vector4D normalization logic. */`

### Test Suite & Name

- **Suite Name:** Single PascalCase word (e.g., `Vector4DMath`).
- **Test Name:** Descriptive PascalCase. Use a single underscore to separate the "Target" from the "Condition".
- **Prefixes:** - `StaticWrapper_`: For static versions of member functions.
    - `Operator_`: For operator overloads (e.g., `OperatorPlus_ReturnsCorrectSum`).
- **Constraint:** Maximum of two underscores per test name.

### Test Body Commenting

- **Documentation**- Use @test to write a brief description of what the test are supposed to verify
- **Structure:** Optionally use **Given / When / Then** blocks to separate setup, action, and assertion.

## Sample Documentation

```c++
/**
 * @file Vector4D.h
 * @author Alan Abraham P Kochumon
 * @date Created on: January 26, 2026
 *
 * @brief Templated 4D Vector supporting integral, floating-point and boolean types.
 * @tparam T Type of Vector4D components. Must satisfy @ref Arithmetic concept.
 *
 * @note Arithmetic operations are limited to numeric types via @ref StrictArithmetic concept.
 *
 * @par Configuration
 * Define `ENABLE_FGM_SHADER_OPERATORS` to enable comparison operators (>, <, etc.).
 * Even if disabled, functional comparisons like `greaterThan()` remain available.
 * Define `FORCE_SCALAR` to turn off SIMD which is on by default on supported hardware.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */
```
