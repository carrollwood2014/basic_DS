file(GLOB SRC "*.cpp" "*.h")
add_executable(test_heapsort ${SRC})
target_include_directories (test_heapsort PUBLIC ./)