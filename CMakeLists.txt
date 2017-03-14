cmake_minimum_required(VERSION 3.6)

project(location_service)

set(CMAKE_CXX_STANDARD 14)

include_directories(
	./include
)

if (MSVC)

	include_directories(
		"C:/Users/christian/vcpkg/installed/x64-windows/include"
	)

	link_directories(
		"C:/Users/christian/vcpkg/installed/x64-windows/lib"
	)

endif()

set(SOURCES 
	./include/coord.hpp
	./include/coord_tree.hpp
)

if (${CMAKE_BUILD_TYPE_INIT} STREQUAL "Debug")

	LIST(APPEND SOURCES 
		./debug/main.cpp

		./test/rtree_test.cpp
		./test/geographic_test.cpp
	)

elseif (${CMAKE_BUILD_TYPE_INIT} STREQUAL "Release")

	LIST(APPEND SOURCES
		./release/main.cpp)

endif()

add_executable(location_service ${SOURCES})

target_link_libraries(
    location_service

    cpprest_2_9
    mongocxx
    bsoncxx
    )