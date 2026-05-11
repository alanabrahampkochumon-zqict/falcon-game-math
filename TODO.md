# TODO LIST

## Matrices

- Add custom assert
- Add benchmarking to determine whether |(Bitwise OR) or ||(Logical OR) provides better performance in branching(used in safeDiv, and other similar functions)
- Separate projection into two methods one, where the B is normalized and other where it is not.
- Remove all unnecessary branching unless critically required, if more code leads, like in case projection overloads, then its safer to choose that route.

## Vectors

- Add assert to div, normalize
- Update / to return Vector\*\*<Magnitude<T>>
- Add MSVC compiler check in equality to separate NaN evaluation during compile time
