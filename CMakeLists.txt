cmake_minimum_required(VERSION 3.26)
project(Simple_texteditor)

find_package(wxWidgets REQUIRED COMPONENTS core base stc)
# Include wxWidgets headers
include(${wxWidgets_USE_FILE})
set(CMAKE_CXX_STANDARD 23)
include_directories(header src resources)

file(GLOB MY_SOURCES_FILES src/*.cpp)
file(GLOB MY_HEADER_FILES header/*.h)
add_executable(${PROJECT_NAME} ${MY_SOURCES_FILES} ${MY_HEADER_FILES}
)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
