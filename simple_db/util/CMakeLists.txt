ADD_EXECUTABLE(arena_test arena_test.cc)
TARGET_LINK_LIBRARIES(arena_test util "/usr/local/lib/libgtest.a")
add_test(
    NAME
    arena_test
    COMMAND
    ${EXECUTABLE_OUTPUT_PATH}/arena_test
)

ADD_EXECUTABLE(LoggingTest logging_test.cc)
TARGET_LINK_LIBRARIES(LoggingTest util "/usr/local/lib/libgtest.a")
add_test(
    NAME
    LoggingTest
    COMMAND
    ${EXECUTABLE_OUTPUT_PATH}/LoggingTest
)

# ADD_EXECUTABLE(LoggStreamTest logg_stream_test.cc)
# TARGET_LINK_LIBRARIES(LoggStreamTest util "/usr/local/lib/libgtest.a")
# add_test(
#     NAME
#     LoggStreamTest
#     COMMAND
#     ${EXECUTABLE_OUTPUT_PATH}/LoggStreamTest
# )

ADD_EXECUTABLE(StringUtilTest string_util_test.cc)
TARGET_LINK_LIBRARIES(StringUtilTest util "/usr/local/lib/libgtest.a")
add_test(
    NAME
    StringUtilTest
    COMMAND
    ${EXECUTABLE_OUTPUT_PATH}/StringUtilTest
)
