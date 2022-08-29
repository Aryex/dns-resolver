set(libs "")
set(libDirs "")
set(incDirs "")

set(demo1tester1 "demo_1_tester_1")
add_executable(${demo1tester1} tester_1.cpp)

list(APPEND incDirs ${PROJECT_BINARY_DIR})

target_include_directories(${demo1tester1} PUBLIC ${incDirs})
target_link_directories(${demo1tester1} PRIVATE ${libDirs})
target_link_libraries(${demo1tester1} ${libs})

add_test(NAME "Demo tester 1 in test suite 1 " COMMAND ${demo1tester1})