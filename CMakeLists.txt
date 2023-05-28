cmake_minimum_required(VERSION 3.0)

project(ACFramework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)
set(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/out)
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/out)

add_definitions("-DUNICODE" "-D_UNICODE")
add_definitions("-DNOMINMAX" "-D_NOMINMAX")

include_directories(
        ${PROJECT_SOURCE_DIR}
)

link_directories(
        ${PROJECT_SOURCE_DIR}/lib
        ${PROJECT_SOURCE_DIR}/out
)

if(MSVC)
    add_compile_options(
            $<$<CONFIG:>:/MT> #---------|
            $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
            $<$<CONFIG:Release>:/MT> #--|
    )
endif()


file(GLOB_RECURSE  acf_dll_wrapper_source ${PROJECT_SOURCE_DIR}/libacf_dll/*.cc)


add_library(libacf_dll_wrapper STATIC ${acf_dll_wrapper_source})


file(GLOB_RECURSE acf_dll_source ${PROJECT_SOURCE_DIR}/binding_EPL/src/*.cc)


add_library(libacf_Caller SHARED ${acf_dll_source})

target_link_libraries(libacf_Caller libacf_dll_wrapper.lib libacf.lib)

file(GLOB_RECURSE acfclient_source ${PROJECT_SOURCE_DIR}/acfclient/src/*)


add_executable(acfclient ${acfclient_source})

target_link_libraries(acfclient libacf.lib libacf_dll_wrapper.lib)