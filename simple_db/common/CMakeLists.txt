ADD_EXECUTABLE(string_util_test string_util_test.cc)
TARGET_LINK_LIBRARIES(string_util_test common gtest)
add_test(
    NAME
    string_util_test
    COMMAND
    ${EXECUTABLE_OUTPUT_PATH}/string_util_test
)
