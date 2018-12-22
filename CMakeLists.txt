#rememmber to clean this shit up, my dude
cmake_minimum_required(VERSION 2.8)

project(SFML3D)

file(GLOB HEADERS "src/include/*.hpp" "src/include/ECS/Core/*.hpp" "src/include/ECS/*.hpp")
file(GLOB SOURCE "src/*.cpp" "src/include/*.cpp")
file(GLOB SOIL2 "src/dependencies/SOIL2/*.c" "src/dependencies/SOIL2/*.h")
file(GLOB MATHS "src/include/Maths/*.hpp" "src/include/Maths/*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

file(COPY src/shaders src/images DESTINATION midia)

find_package(SFML 2.5 COMPONENTS window graphics audio system network REQUIRED)
find_package(glm REQUIRED)

INCLUDE(FindPackageHandleStandardArgs)
INCLUDE(FindPkgConfig)
INCLUDE(FindOpenGL REQUIRED)
INCLUDE(FindGLEW REQUIRED)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS} ${SOIL2})

target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${MATHS}
sfml-window sfml-graphics sfml-audio sfml-system sfml-network glm)
