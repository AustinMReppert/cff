cmake_minimum_required(VERSION 3.17)
project(cff)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(U_CHARSET_IS_UTF8=1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(cff src/main.cpp src/CFF.cpp src/CFF.h src/Token.cpp src/Token.h src/Lexer.cpp src/Lexer.h src/FileUtils.h src/StringUtils.h src/StringUtils.cpp src/FileUtils.cpp)

target_link_libraries(cff ${CONAN_LIBS})