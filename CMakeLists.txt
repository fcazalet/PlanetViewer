cmake_minimum_required(VERSION 3.10.0)
project(Helloworld VERSION 0.1.0 LANGUAGES C CXX)

include_directories("C:/msys64/ucrt64/include")
link_directories("C:/msys64/ucrt64/lib")

add_executable(PlanetViewer main.cpp Camera.cpp)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(PlanetViewer SDL2)
target_link_libraries(PlanetViewer glu32)
target_link_libraries(PlanetViewer opengl32)