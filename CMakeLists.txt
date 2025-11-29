cmake_minimum_required(VERSION 3.10)
Project(test)
file(GLOB_RECURSE SRC "./src/*.cpp" "./src/*.c")
include_directories("./src")
add_executable(exec_renderer main.cpp ${SRC})
# target_link_libraries(exec_renderer ${LINK_LIBS} "-Wl,--rpath=${ORIGIN}")
# add_custom_command(
#     TARGET exec_renderer
#     #  COMMAND cp -rf build/exec_renderer bin/exec_renderer
#     COMMAND cp -rf build/exec_renderer bin/renderer
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )