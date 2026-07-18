include_guard()

set(FGM_VEC_DIR "vectors/")
set(FGM_VEC_HEADERS
        Vec2.h
        Vec2.tpp
        Vec3.h
        Vec3.tpp
        Vec4.h
        Vec4.tpp
        Tensors.h
)
list(TRANSFORM FGM_VEC_HEADERS PREPEND ${FGM_VEC_DIR})