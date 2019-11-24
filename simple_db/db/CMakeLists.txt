
ADD_EXECUTABLE(SkipListTest skip_list_test.cc)
TARGET_LINK_LIBRARIES(SkipListTest db "/usr/local/lib/libgtest.a")
add_test(
    NAME
    SkipListTest
    COMMAND
    ${EXECUTABLE_OUTPUT_PATH}/SkipListTest
)
