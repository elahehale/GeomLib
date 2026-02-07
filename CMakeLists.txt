# CMakeList.txt : CMake project for GeomLib, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)


project ("GeomLib")


# Add source to this project's executable.
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

set(LIB_SOURCES ${MY_SOURCES})
list(FILTER LIB_SOURCES EXCLUDE REGEX "src/main.cpp")
add_library(GeomLib STATIC ${LIB_SOURCES})

# if I use private, the include path is not propagated to the tests, and i have to add it manually to the executable target, which is not ideal. I want the include path to be automatically propagated to any target that links against GeomLib.
target_include_directories(GeomLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(GeomApp "src/main.cpp")
target_link_libraries(GeomApp PRIVATE GeomLib)


target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") # Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the project

set_property(TARGET GeomLib PROPERTY CXX_STANDARD 20)

# TODO: Add tests and install targets if needed.

# --- Testing Section ---

# 1. Enable testing in CMake
include(CTest)
enable_testing()

# 2. Download GoogleTest automatically
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# For Windows/MSVC compatibility
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 3. Create the test executable
# Note: You should create a 'tests' folder and put your test files there
file(GLOB_RECURSE TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

add_executable(GeomLibTests ${TEST_SOURCES})

# 4. Link your library and GTest
target_link_libraries(GeomLibTests PRIVATE GeomLib GTest::gtest_main)

# 5. Discover and add tests
include(GoogleTest)
gtest_discover_tests(GeomLibTests)