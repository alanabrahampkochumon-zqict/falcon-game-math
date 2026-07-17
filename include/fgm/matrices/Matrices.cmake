include_guard()

set(FGM_MAT_DIR "matrices/")
set(FGM_MAT_HEADERS
        Matrix2.h
        Matrix2.tpp
        Mat2x3.h
        Mat2x3.tpp
        Matrix3.h
        Matrix3.tpp
        Matrix4.h
        Matrix4.tpp
)
list(TRANSFORM FGM_MAT_HEADERS PREPEND ${FGM_MAT_DIR})