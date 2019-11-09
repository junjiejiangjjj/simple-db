ADD_EXECUTABLE(net_test net_test.cc)
TARGET_LINK_LIBRARIES(net_test util "/usr/local/lib/libgtest.a")
add_test(
    NAME
    net_test
    COMMAND
    ${EXECUTABLE_OUTPUT_PATH}/net_test
)

ADD_EXECUTABLE(ListenHandlerTest listen_handler_test.cc)
TARGET_LINK_LIBRARIES(ListenHandlerTest net "/usr/local/lib/libgtest.a")
add_test(
    NAME
    ListenHandlerTest
    COMMAND
    ${EXECUTABLE_OUTPUT_PATH}/ListenHandlerTest
)
