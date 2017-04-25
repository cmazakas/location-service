cmake_minimum_required(VERSION 3.6)

project(location_service)

set(CMAKE_CXX_STANDARD 14)

# Boost dependency
find_package(Boost REQUIRED)

# Find our cpprestsdk libs
# Finding any arbitrary header seems to do
find_path(CPPRESTSDK_INCLUDE_DIR cpprest/http_listener.h)
find_library(CPPRESTSDK_LIBRARY cpprest_2_9)

include_directories(${CPPRESTSDK_INCLUDE_DIR})
link_libraries(${CPPRESTSDK_LIBRARY})

# Find mongocxx driver and BSON libraries
find_path(MONGOCXX_INCLUDE_DIR mongocxx/database.hpp)
find_path(BSONCXX_INCLUDE_DIR  bsoncxx/json.hpp)

find_library(MONGOCXX_LIBRARY mongocxx)
find_library(BSONCXX_LIBRARY  bsoncxx)

include_directories(${MONGOCXX_INCLUDE_DIR} ${BSONCXX_INCLUDE_DIR})

link_libraries(${MONGOCXX_LIBRARY} ${BSONCXX_LIBRARY})

# Catch dependency for testing
find_path(CATCH_INCLUDE_DIR catch.hpp)
include_directories(${CATCH_INCLUDE_DIR})


include_directories(
	./include

    ${Boost_INCLUDE_DIR}
)

set(
    HEADERS

    ./include/coord.hpp
    ./include/coord_tree.hpp

    ./include/csv_grammar.hpp
    ./include/csv_row_t.hpp
    ./include/csv_parser.hpp
)

# create common library of source files to
# link against
set(
    SOURCES 

    ./src/csv_parser.cpp
    )

add_library(locservice STATIC ${SOURCES})

link_libraries(locservice)

# generate release binary
add_executable(location_service ./release/main.cpp ${HEADERS})

# generate testing binary
add_executable(
	location_service_tests 
	
    ${HEADERS}

	./debug/main.cpp

	./test/rtree_test.cpp
	./test/geographic_test.cpp
    ./test/csv_grammar_tests.cpp
    ./test/csv_parser_tests.cpp
	)

install(
	TARGETS location_service location_service_tests
	DESTINATION bin
	)

enable_testing()
add_test(NAME lsvc_tests COMMAND location_service_tests)