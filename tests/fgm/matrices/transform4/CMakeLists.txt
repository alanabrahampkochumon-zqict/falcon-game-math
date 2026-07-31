add_library(Transform4Tests OBJECT)

target_sources(
        Transform4Tests PRIVATE
        AccessAndMutationTests.cpp
        InitializationTests.cpp
)

target_include_directories(
        Transform4Tests PRIVATE
        ${FGM_TEST_ROOT_DIR}/include
)

target_link_libraries(
        Transform4Tests PRIVATE
        FGMTestSetup
)