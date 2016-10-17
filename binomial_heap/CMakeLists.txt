file(GLOB SRC "*.cpp" "*.h")
add_executable(test_binomialheap ${SRC})
target_include_directories (test_binomialheap PUBLIC ./)