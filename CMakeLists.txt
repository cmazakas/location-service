cmake_minimum_required(VERSION 3.6)

project(location_service)

set(CMAKE_CXX_STANDARD 14)

include_directories(
	./include
)

# at some point in time, this obviously needs to be
# refactored
# however, using vcpkg is pretty forgiving to this end
if (MSVC)

	include_directories(
		"/vcpkg/installed/x64-windows/include"
	)

	link_directories(
		"/vcpkg/installed/x64-windows/lib"
	)

endif()

# create common library of source files to
# link against
set(
	SOURCES 

	./include/coord.hpp
	./include/coord_tree.hpp
	./include/csv_parser.hpp
	)

#add_library(locservice ${SOURCES})

# generate release binary
add_executable(location_service ./release/main.cpp)

# generate testing binary
add_executable(
	tests 
	
	./debug/main.cpp

	./test/rtree_test.cpp
	./test/geographic_test.cpp
	./test/parsing_tests.cpp
	)

set(
	LIBS
	
	#locservice

	cpprest_2_9
	mongocxx
	bsoncxx
	)

target_link_libraries(location_service ${LIBS})
target_link_libraries(tests ${LIBS})