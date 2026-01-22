cmake_minimum_required(VERSION 3.14)
project(SyntheticCompData CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch csv-parser library
FetchContent_Declare(
  csv
  GIT_REPOSITORY https://github.com/vincentlaucsb/csv-parser.git
  GIT_TAG 2.2.3
)

# Fetch gnuplot-iostream library (header-only, just need the source)
FetchContent_Declare(
  gnuplot
  GIT_REPOSITORY https://github.com/dstahlke/gnuplot-iostream.git
  GIT_TAG master
)

# Disable tests and examples from dependencies
set(CSV_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(CSV_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_GetProperties(gnuplot)
if(NOT gnuplot_POPULATED)
    FetchContent_Populate(gnuplot)
    # Don't add the subdirectory to avoid building tests
endif()

FetchContent_MakeAvailable(csv)

# Main application executable
add_executable(example example.cpp CGenerator.cpp)

# Plotting application executable (requires Boost)
find_package(Boost COMPONENTS iostreams filesystem system QUIET)
if(Boost_FOUND)
    add_executable(plotting plotting.cpp)
    target_link_libraries(plotting PRIVATE csv ${Boost_LIBRARIES})
    target_include_directories(plotting PRIVATE ${gnuplot_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
    message(STATUS "Building plotting executable (Boost found)")
else()
    message(STATUS "Skipping plotting executable (Boost not found). Install Boost to build it: brew install boost")
endif()

