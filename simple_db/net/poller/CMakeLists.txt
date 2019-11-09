
ADD_EXECUTABLE(PollerTest poller_test.cc)
TARGET_LINK_LIBRARIES(PollerTest poller "/usr/local/lib/libgtest.a")
add_test(
    NAME
    PollerTest
    COMMAND
    ${EXECUTABLE_OUTPUT_PATH}/PollerTest
)

ADD_EXECUTABLE(SelectPollerTest select_poller_test.cc)
TARGET_LINK_LIBRARIES(SelectPollerTest poller "/usr/local/lib/libgtest.a")
add_test(
    NAME
    SelectPollerTest
    COMMAND
    ${EXECUTABLE_OUTPUT_PATH}/SelectPollerTest
)
