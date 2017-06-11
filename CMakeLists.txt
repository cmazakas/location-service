# this is the current default version Visual Studio is using :P
cmake_minimum_required(VERSION 3.6)

project(location_service)
set(CMAKE_CXX_STANDARD 14)

# Boost dependency
find_package(Boost REQUIRED)

# Find our cpprestsdk libs
# Finding any arbitrary header will do until more robust find modules are written
find_path(CPPREST_INCLUDE_DIR cpprest/http_listener.h)
find_library(CPPREST_LIBRARY cpprest_2_9)

# Catch dependency for testing
# Find the Catch header then create an INTERFACE
# library from it which we can then later include
find_path(CATCH_INCLUDE_DIR catch.hpp)
add_library(CATCH_LIBRARY INTERFACE)
target_include_directories(CATCH_LIBRARY INTERFACE ${CATCH_INCLUDE_DIR})

# set all the headers for the project
set(
    HEADERS

    ./include/csv_grammar.hpp
    ./include/csv_row_t.hpp
    ./include/csv_parser.hpp
    ./include/csv_row_to_point.hpp
    ./include/point_t.hpp
    ./include/equal.hpp
    ./include/csv_to_rtree.hpp
    ./include/location_server.hpp
    ./include/csv_rows_to_zip_point_map.hpp
    ./include/csv_rows_from_range.hpp
    ./include/find_zip_data.hpp
    ./include/handle_http_req.hpp
)

# create common library of source files to
# link against
set(
    SOURCES 

    ./src/csv_parser.cpp
    ./src/csv_row_to_point.cpp
    ./src/point_t.cpp
    ./src/equal.cpp
    ./src/csv_to_rtree.cpp
    ./src/location_server.cpp
    ./src/csv_rows_to_zip_point_map.cpp
    ./src/find_zip_data.cpp
    ./src/handle_http_req.cpp
 )

 add_library(
    locservice 
    STATIC ${SOURCES})

 target_include_directories(
    locservice 

    PUBLIC
    ./include
    ${Boost_INCLUDE_DIR}
    ${CPPREST_INCLUDE_DIR}
)

target_link_libraries(
    locservice

    ${CPPREST_LIBRARY}
)

 # these are all of our current testing files
set(
    TESTS

    ./test/csv_grammar_tests.cpp
    ./test/csv_parser_tests.cpp
    ./test/csv_row_to_point_tests.cpp
    ./test/csv_to_rtree_tests.cpp
    ./test/location_server_tests.cpp
    ./test/csv_rows_to_zip_point_map_tests.cpp
)

# generate release binary
add_executable(
    location_service

    ./release/main.cpp 
    ${HEADERS}
)

target_link_libraries(
    location_service

    locservice
)

# generate testing binary
add_executable(
    location_service_tests 
	
    ./debug/main.cpp
    ${HEADERS}
    ${TESTS}
)

target_link_libraries(
    location_service_tests

    locservice
    ${CATCH_LIBRARY}
)

# create a simple install rule (probably needs to be ironed out)
install(
    TARGETS location_service location_service_tests
    DESTINATION bin
)

# add some CTest functionality as well
# unfortunately, only the Catch binary is run so as far as
# CTest knows, only one test is actually run
enable_testing()
add_test(
    NAME lsvc_tests 
    COMMAND location_service_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})