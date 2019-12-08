
ADD_EXECUTABLE(SkipListTest skip_list_test.cc)
TARGET_LINK_LIBRARIES(SkipListTest common db util gtest)
add_test(
    NAME
    SkipListTest
    COMMAND
    ${EXECUTABLE_OUTPUT_PATH}/SkipListTest
)
