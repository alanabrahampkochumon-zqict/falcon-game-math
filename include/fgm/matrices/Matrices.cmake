include_guard()

set(FGM_MAT_DIR "matrices/")
set(FGM_MAT_HEADERS
        Mat2.h
        Mat2.tpp
        Mat2x3.h
        Mat2x3.tpp
        Mat2x4.h
        Mat2x4.tpp
        Mat3x2.h
        Mat3x2.tpp
        Mat3.tpp
        Mat3.h
        Mat3x4.h
        Mat3x4.tpp
        Mat4.h
        Mat4.tpp
        Mat4x2.h
        Mat4x2.tpp
#        MatMul.h
#        MatMul.tpp
)
list(TRANSFORM FGM_MAT_HEADERS PREPEND ${FGM_MAT_DIR})