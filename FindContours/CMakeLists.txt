
# ================== CONFIGS ======================

## project name
set(PROJECT_NAME        "FindContours")

## C++ language level
set(CMAKE_CXX_STANDARD  14)

set(DEPENDENCIES
    ## dependencies here
    ## e.g. `serial` for `libserial.a` or `libserial.so`
)

set(EXECUTABLE          true)
set(LIBRARY_TYPE        STATIC)
set(DEBUG               true)
set(OPTIMIZATION        2)

# ================== PACKAGES ======================

set(Threads             false)
set(Eigen               false)
set(OpenCV              true)

# ==================================================

cmake_minimum_required(VERSION 3.5)
project(${PROJECT_NAME})

file(GLOB_RECURSE sourcefiles "src/*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)

message("")

message("[CONFIG]   Executable      ${EXECUTABLE}")
if(NOT Executable)
    message("[CONFIG]   LIBRARY_TYPE      ${LIBRARY_TYPE}")
endif()
message("[CONFIG]   Debug           ${DEBUG}")
message("[CONFIG]   Optimization    ${OPTIMIZATION}")
message("[CONFIG]   Dependencies    ${DEPENDENCIES}")
message("[CONFIG]   Language Level  ${CMAKE_CXX_STANDARD}")

message("")

message("[PACKAGE]  Threads         ${Threads}")
message("[PACKAGE]  Eigen           ${Eigen}")
message("[PACKAGE]  OpenCV          ${OpenCV}")

message("")

macro(subdirs result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(IS_DIRECTORY ${curdir}/${child})
            list(APPEND dirlist ${child})
        endif()
    endforeach()
    list(APPEND ${result} ${dirlist})
endmacro()

macro(subfiles result curdir)
    file(GLOB children RELATIVE ${curdir} ${curdir}/*)
    set(filelist "")
    foreach(child ${children})
        if(NOT IS_DIRECTORY ${curdir}/${child})
            list(APPEND filelist ${child})
        endif()
    endforeach()
    set(${result} ${filelist})
endmacro()

set(THIRD_PARTY_LIB_SHARED "")
set(THIRD_PARTY_LIB_STATIC "")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPROJ_PATH=\"\\\"${PROJECT_SOURCE_DIR}\\\"\"")

subdirs(submodules "${PROJECT_SOURCE_DIR}/..")
subdirs(submodules "${PROJECT_SOURCE_DIR}/ThirdParty")
subdirs(submodules "${PROJECT_SOURCE_DIR}/3rdparty")

foreach(submodule ${submodules})
    include_directories(${PROJECT_SOURCE_DIR}/../${submodule}/include)
    link_directories(${PROJECT_SOURCE_DIR}/../${submodule}/build)
    subfiles(libs ${PROJECT_SOURCE_DIR}/../${submodule}/build)

    foreach(lib ${libs})
        if(${lib} MATCHES "lib.+\\.so")
            string(REGEX REPLACE "(lib)|(\\.so)" "" lib ${lib})
            if(NOT ${lib} IN_LIST DEPENDENCIES)
                continue()
            endif()
            list(APPEND THIRD_PARTY_LIB_SHARED ${lib})
            message("[DEPENDENCY] shared lib: `${lib}` in `${submodule}`")
        elseif(${lib} MATCHES "lib.+\\.a")
            string(REGEX REPLACE "(lib)|(\\.a)" "" lib ${lib})
            if(NOT ${lib} IN_LIST DEPENDENCIES)
                continue()
            endif()
            list(APPEND THIRD_PARTY_LIB_STATIC ${lib})
            message("[DEPEND]   static lib: `${lib}` in `${submodule}`")
        endif()
    endforeach()
endforeach()

message("")

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
    MESSAGE("-- Use ccache for compiler")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O${OPTIMIZATION}")

if(DEBUG)
    set(CMAKE_BUILD_TYPE DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    add_compile_definitions(DEBUG)
endif()

if(EXECUTABLE)
    add_executable(${PROJECT_NAME} main.cpp ${sourcefiles})
else()
    add_library(${PROJECT_NAME} ${LIBRARY_TYPE} ${sourcefiles})
endif()

target_link_libraries(${PROJECT_NAME} ${THIRD_PARTY_LIB_STATIC} ${THIRD_PARTY_LIB_SHARED})

if(Threads)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
endif()
if(Eigen)
    find_package(Eigen3 REQUIRED)
    include_directories(${EIGEN3_INCLUDE_DIR})
endif()
if(OpenCV)
    find_package(OpenCV 4 REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
endif()
