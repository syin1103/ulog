cmake_minimum_required(VERSION 4.4.5)

project(ulog VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_EXAMPLE "Build ulog examples" ON)
option(BUILD_TESTING "Build unit tests" ON)

# include(FetchContent)
# FetchContent_Declare(
#     fmt
#     GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#     GIT_TAG 11.1.4
#     EXCLUDE_FROM_ALL
# )
# FetchContent_MakeAvailable(fmt)
find_package(fmt CONFIG REQUIRED)

if(BUILD_TESTING)
    include(CTest)
    find_package(GTest CONFIG REQUIRED)

    # set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    # set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

    # FetchContent_Declare(
    #     googletest
    #     GIT_REPOSITORY https://github.com/google/googletest.git
    #     GIT_TAG v1.16.0
    #     EXCLUDE_FROM_ALL
    # )
    # FetchContent_MakeAvailable(googletest EXCLUDE_FROM_ALL)

    enable_testing()

    file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "*_test.cc")
    foreach(TEST_FILE ${TEST_SOURCES})
        get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
        add_executable(${TEST_NAME} ${TEST_FILE})
        target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest_main)
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endforeach()
endif()

if (BUILD_TESTING)
    add_executable(example example/example.cc)
    target_link_libraries(example PRIVATE fmt::fmt)
endif()