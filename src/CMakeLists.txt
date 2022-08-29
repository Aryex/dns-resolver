cmake_minimum_required(VERSION 3.22.1)

project(dns_resolver VERSION 1.0)

set(libDirs "")
set(optionalLibDirs "")
set(incDirs "")
set(optionalIncDirs "")
set(libs "")
set(optionalLibs "")

# To allow include library_directories.cmake in this project
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

configure_file(project_config.h.in project_config.h)
list(APPEND incDirs ${PROJECT_BINARY_DIR}) 

add_executable(${PROJECT_NAME} main.cpp)
target_link_directories(${PROJECT_NAME} PRIVATE ${libDirs} ${optionalLibDirs})
target_include_directories(${PROJECT_NAME} PUBLIC ${incDirs} ${optionalIncDirs})
target_link_libraries(${PROJECT_NAME} ${libs} ${optionalLibs})

string(COMPARE EQUAL "${CMAKE_BUILD_TYPE}" "DEBUG" isBuildDebug)
message(STATUS ${CMAKE_BUILD_TYPE})
if(isBuildDebug)
    include(CTest)
endif()
if (BUILD_TESTING)
    message(STATUS "Building tests...")
    add_subdirectory(tests)
    message(STATUS "Tests built")
endif()