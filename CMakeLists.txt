cmake_minimum_required(VERSION 3.17)
project(cff)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(U_CHARSET_IS_UTF8=1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(cff src/main.cpp src/CFF.cpp src/CFF.h src/Token.cpp src/Token.h src/Lexer.cpp src/Lexer.h src/utils/FileUtils.h src/utils/StringUtils.h src/utils/StringUtils.cpp src/utils/FileUtils.cpp src/Parser.cpp src/Parser.h src/AST.cpp src/AST.h src/ASTNode.cpp src/ASTNode.h src/BinaryExpression.cpp src/BinaryExpression.h src/NumLiteral.cpp src/NumLiteral.h src/ASTNodeVisitor.cpp src/ASTNodeVisitor.h src/ASTPrinter.cpp src/ASTPrinter.h src/Statement.cpp src/Statement.h src/Assignment.cpp src/Assignment.h src/StatementList.cpp src/StatementList.h)

target_link_libraries(cff ${CONAN_LIBS})