include(FetchContent)


# Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 # release-1.17.0
    SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/vendors/googletest"
    SYSTEM
)

FetchContent_MakeAvailable(googletest)

# Group google_test projects into a "Gtest" folder
set_target_properties(
    gtest gtest_main gmock gmock_main
    PROPERTIES FOLDER "Google Test"
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

if(MSVC)
    target_compile_options(gtest PRIVATE /WX- /W0)
    target_compile_options(gtest_main PRIVATE /WX- /W0)
endif()