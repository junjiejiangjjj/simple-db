add_library(net)

target_sources(net
  PRIVATE
  event_handler.cc
  event_loop.cc
  tcp_server.cc
  socket_opt.cc
  connector.cc
  net_util.cc
  poller/poller.cc
  poller/select_poller.cc
  poller/epoll.cc
  # poller/select_poller.h
  PUBLIC
  # ${CMAKE_CURRENT_LIST_DIR}/event_loop.h
  # ${CMAKE_CURRENT_LIST_DIR}/event_handler.h
  # ${CMAKE_CURRENT_LIST_DIR}/tcp_server.h
  # ${CMAKE_CURRENT_LIST_DIR}/socket_opt.h
  # ${CMAKE_CURRENT_LIST_DIR}/connector.h
  # ${CMAKE_CURRENT_LIST_DIR}/callback_base.h
  # ${CMAKE_CURRENT_LIST_DIR}/poller/event.h
  # ${CMAKE_CURRENT_LIST_DIR}/poller/poller.h
  )


target_include_directories(net
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  )



ADD_EXECUTABLE(ConnectorTest connector_test.cc)
TARGET_LINK_LIBRARIES(ConnectorTest net gtest)

add_test(
  NAME
  ConnectorTest
  COMMAND
  $<TARGET_FILE:ConnectorTest>
    )


ADD_EXECUTABLE(SocketOptTest socket_opt_test.cc)
TARGET_LINK_LIBRARIES(SocketOptTest net gtest)

add_test(
  NAME
  SocketOptTest
  COMMAND
  $<TARGET_FILE:SocketOptTest>
  )



ADD_EXECUTABLE(PollerTest poller/poller_test.cc)
TARGET_LINK_LIBRARIES(PollerTest net gtest)
add_test(
    NAME
    PollerTest
    COMMAND
    PollerTest
)

ADD_EXECUTABLE(SelectPollerTest poller/select_poller_test.cc)
TARGET_LINK_LIBRARIES(SelectPollerTest net gtest)
add_test(
    NAME
    SelectPollerTest
    COMMAND
    SelectPollerTest
    )

ADD_EXECUTABLE(NetTest net_test)
TARGET_LINK_LIBRARIES(NetTest net util common)
