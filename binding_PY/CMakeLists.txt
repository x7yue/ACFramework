cmake_minimum_required(VERSION 3.0)
project(acf_py)


set(EXAMPLE_VERSION_INFO 0.0.1)

set(ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)
set(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/out)
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/out)

add_subdirectory(pybind11)

pybind11_add_module(acf_py ${PROJECT_SOURCE_DIR}/src/main.cpp)

link_directories(
        ${PROJECT_SOURCE_DIR}/../lib
        ${PROJECT_SOURCE_DIR}/../out
)



target_compile_definitions(${PROJECT_NAME}
        PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO} )

