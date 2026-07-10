include_guard()

set(FGM_VEC_DIR "vectors/")
set(FGM_VEC_HEADERS
        Vector2.h
        Vector2.tpp
        Vector3.h
        Vector3.tpp
        Vector4.h
        Vector4.tpp
)
list(TRANSFORM FGM_VEC_HEADERS PREPEND ${FGM_VEC_DIR})