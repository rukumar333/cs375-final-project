cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(NearestNeighbor)
set(CMAKE_BUILD_TYPE Release)

add_subdirectory(third_party)
find_package(PCL 1.8 REQUIRED COMPONENTS common kdtree)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

## C++11 support
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Increase warning levels
if(CMAKE_COMPILER_IS_GNUCXX)
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

add_executable(main.exe main.cpp NearestNeighbor.cpp external.cpp)
target_compile_features(main.exe PRIVATE
    cxx_aggregate_default_initializers
    cxx_lambdas
    cxx_nullptr
    cxx_auto_type
    cxx_generalized_initializers
    cxx_range_for
    cxx_uniform_initialization
    cxx_delegating_constructors)
target_link_libraries(main.exe ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})
target_include_directories(main.exe PUBLIC third_party/nanoflann/include)
