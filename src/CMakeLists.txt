cmake_minimum_required(VERSION 3.20)

project(OO_express_calcu LANGUAGES CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
aux_source_directory(. SRCS_DIR)

# add_library(Node node.cpp)
# add_library(Parser parser.cpp )
# add_library(Scanner scanner.cpp)

add_executable(main ${SRCS_DIR})
# target_link_libraries(main Node Parser Scanner)