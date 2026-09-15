include_guard()

set(FGM_VEC_DIR "vectors/")
set(FGM_VEC_HEADERS
        # NON-SIMD CONSTEXPR WRAPPERS
        CVec2.h
        CVec2.tpp
        Point2.h
        Point2.tpp
        Point3.h
        Point3.tpp
        Vec3.h
        Vec3.tpp
        Vec4.h
        Vec4.tpp
        # SIMD-ACCELERATED WRAPPER
        Vec2.h
        Vec2.tpp
)
list(TRANSFORM FGM_VEC_HEADERS PREPEND ${FGM_VEC_DIR})