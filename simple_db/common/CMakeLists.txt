add_library(common)

target_sources(common
  PRIVATE
  logging.cc
  string_util.cc
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/common.h
  ${CMAKE_CURRENT_LIST_DIR}/logging.h
  ${CMAKE_CURRENT_LIST_DIR}/string_util.h
  )

target_include_directories(util
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
    )


ADD_EXECUTABLE(string_util_test string_util_test.cc)
TARGET_LINK_LIBRARIES(string_util_test common gtest)
add_test(
    NAME
    string_util_test
    COMMAND
    $<TARGET_FILE:string_util_test>
)
