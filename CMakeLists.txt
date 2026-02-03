# CMakeList.txt : CMake project for GeomLib, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GeomLib")

# Add source to this project's executable.
add_executable (GeomLib "src/main.cpp" "src/io.cpp" "include/geom/io.h" "include/geom/point.h" "src/point.cpp" "include/geom/Lines.h")

target_include_directories(GeomLib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GeomLib PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
