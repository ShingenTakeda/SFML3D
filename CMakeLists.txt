cmake_minimum_required(VERSION 2.8)

project(SFML3D)

file(GLOB HEADERS "src/include/*.hpp")
file(GLOB SOURCE "src/*.cpp")
file(GLOB SOIL2 "src/dependencies/SOIL2/*.c" "src/dependencies/SOIL2/*.h")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra")

file(COPY src/shaders src/images DESTINATION midia)

find_package(SFML 2.5 COMPONENTS window graphics audio system network REQUIRED)
find_package(glm REQUIRED)

INCLUDE(FindPackageHandleStandardArgs)
INCLUDE(FindPkgConfig)
INCLUDE(FindOpenGL REQUIRED)
INCLUDE(FindGLEW REQUIRED)

#link_directories(LIBRARIES src/dependencies)

#FIND_PATH( SOIL_INCLUDE_DIRS SOIL.h PATH_SUFFIXES SOIL )
#FIND_LIBRARY( SOIL_LIBRARIES SOIL)

INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS} ${SOIL2})

target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} 
sfml-window sfml-graphics sfml-audio sfml-system sfml-network glm)
