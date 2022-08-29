set(libraryTargetName "mylibrary")

add_library(${libraryTargetName} "my_library.cpp")

target_include_directories(${libraryTargetName} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")