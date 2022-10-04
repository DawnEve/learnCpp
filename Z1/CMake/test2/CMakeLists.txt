cmake_minimum_required(VERSION 3.10) #最低的cmake版本
project(Test2)

add_executable(main)
file(GLOB sources CONFIGURE_DEPENDS *.cpp *.h)
target_sources(main PUBLIC ${sources})
