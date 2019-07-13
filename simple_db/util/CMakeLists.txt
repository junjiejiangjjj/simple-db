ADD_EXECUTABLE(arena_test arena_test.cc)
TARGET_LINK_LIBRARIES(arena_test util "/usr/local/lib/libgtest.a")
add_test(
NAME
arena_test
COMMAND
${EXECUTABLE_OUTPUT_PATH}/arena_test
)
