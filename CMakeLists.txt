cmake_minimum_required(VERSION 3.26)
project(Simple_texteditor)

set(CMAKE_CXX_STANDARD 23)

find_package(wxWidgets REQUIRED COMPONENTS core base)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Include wxWidgets headers
include(${wxWidgets_USE_FILE})
include_directories(header src resources)

file(GLOB MY_SOURCES_FILES src/*.cpp)
file(GLOB MY_HEADER_FILES header/*.h)
add_executable(${PROJECT_NAME} ${MY_SOURCES_FILES} ${MY_HEADER_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
