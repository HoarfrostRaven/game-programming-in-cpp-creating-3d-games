cmake_minimum_required(VERSION 3.25)
project(Chapter01)

set(CMAKE_CXX_STANDARD 17)

set(SDL_H /usr/local/Cellar/sdl2/2.28.1/include) # 这个SDL开发包的路径，可以通过brew info sdl2查出来
include_directories(${SDL_H}) # 添加SDL头文件搜索路径

set(SDL_LIB /usr/local/Cellar/sdl2/2.28.1/lib/libSDL2-2.0.0.dylib)
link_libraries(${SDL_LIB}) # 增加SDL链接库目录

add_executable(Chapter01 main.cpp Game.cpp Game.h)
