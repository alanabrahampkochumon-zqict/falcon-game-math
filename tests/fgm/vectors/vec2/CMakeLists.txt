add_library(Vec2Tests OBJECT)

target_sources(
        Vec2Tests PRIVATE
        AccessAndMutationTests.cpp
        AliasTests.cpp
        ArithmeticOperationTests.cpp
        BooleanBitOperationTests.cpp
        ComparisonTests.cpp
        ConstantsTests.cpp
        DistanceTests.cpp
        EqualityTests.cpp
        InitializationTests.cpp
        MagnitudeTests.cpp
        NormalizationTests.cpp
        PNormTests.cpp
        ProductTests.cpp
        ProjectionTests.cpp
        RejectionTests.cpp
        StringRepresentationTests.cpp
        SwizzlingTests.cpp
        TypeConversionTests.cpp
        UtilityTests.cpp
)

target_include_directories(
        Vec2Tests PRIVATE
        ${FGM_TEST_ROOT_DIR}/include
)


target_link_libraries(
        Vec2Tests PRIVATE
        FGM
        GTest::gtest
        GTest::gtest_main
        StrictWarnings
        ProjectSanitizers
        NonComprehensiveTestMode
)