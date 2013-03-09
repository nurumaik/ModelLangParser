project(ModelLang CXX)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(LexerTestSrc LexerTest.cpp Lex.cpp Scanner.cpp Ident.cpp)
add_executable(lexer_test ${LexerTestSrc})
