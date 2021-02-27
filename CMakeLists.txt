cmake_minimum_required(VERSION 3.17)
project(cff)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(U_CHARSET_IS_UTF8=1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(cff main.cpp CFF.cpp CFF.h Token.cpp Token.h Lexer.cpp Lexer.h FileUtils.h StringUtils.h StringUtils.cpp FileUtils.cpp)

target_link_libraries(cff ${CONAN_LIBS})