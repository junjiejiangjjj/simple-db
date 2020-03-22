add_library(util)

target_sources(util
  PRIVATE
  comparator.cc
  arena.cc
  no_destructor.h
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/arena.h
  ${CMAKE_CURRENT_LIST_DIR}/comparator.h
  ${CMAKE_CURRENT_LIST_DIR}/slice.h  
  )

target_include_directories(util
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  )


ADD_EXECUTABLE(arena_test arena_test.cc)
TARGET_LINK_LIBRARIES(arena_test util common gtest)

add_test(
  NAME
  arena_test
  COMMAND
  $<TARGET_FILE:arena_test>
  )


