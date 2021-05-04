cmake_minimum_required(VERSION 3.20)
project(demo VERSION 0.1.0)

set(VCPKG_ROOT_DIR "C:/Tools/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT_DIR}/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang")
set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++")


INCLUDE_DIRECTORIES(
    ${VCPKG_ROOT_DIR}/installed/x86-windows/include
    )
    
LINK_DIRECTORIES(
    ${VCPKG_ROOT_DIR}/installed/x86-windows/lib
)
        
add_executable(demo main.cpp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
        
# All linking libraries go here
 TARGET_LINK_LIBRARIES(demo
    glew32 SDL2 OpenGL32
 )
