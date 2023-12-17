cmake_minimum_required(VERSION 3.10)
project(SampleCompiler CXX)

add_executable(sample-compiler 
    main.cpp
    libs/analisador-sintatico.cpp
    libs/analisador-lexico.cpp
    libs/token.cpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)