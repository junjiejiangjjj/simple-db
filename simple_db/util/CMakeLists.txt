add_library(util)

target_sources(util
  PRIVATE
  comparator.cc
  arena.cc
  no_destructor.h
  block_queue.h
  thread_pool.cc
  writable_file.cc
  log_writer.cc
  log_format.h
  PUBLIC
  # ${CMAKE_CURRENT_LIST_DIR}/arena.h
  # ${CMAKE_CURRENT_LIST_DIR}/comparator.h
  # ${CMAKE_CURRENT_LIST_DIR}/slice.h
  # ${CMAKE_CURRENT_LIST_DIR}/thread_pool.h  
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


ADD_EXECUTABLE(block_queue_test block_queue_test.cc)
TARGET_LINK_LIBRARIES(block_queue_test util common gtest)

add_test(
  NAME
  block_queue_test
  COMMAND
  $<TARGET_FILE:block_queue_test>
  )

ADD_EXECUTABLE(comparator_test comparator_test.cc)
TARGET_LINK_LIBRARIES(comparator_test util common gtest)

add_test(
  NAME
  comparator_test
  COMMAND
  $<TARGET_FILE:comparator_test>
  )

ADD_EXECUTABLE(no_destructor_test no_destructor_test.cc)
TARGET_LINK_LIBRARIES(no_destructor_test util common gtest)

add_test(
  NAME
  no_destructor_test
  COMMAND
  $<TARGET_FILE:no_destructor_test>
  )

ADD_EXECUTABLE(slice_test slice_test.cc)
TARGET_LINK_LIBRARIES(slice_test util common gtest)

add_test(
  NAME
  slice_test
  COMMAND
  $<TARGET_FILE:slice_test>
  )


ADD_EXECUTABLE(thread_pool_test thread_pool_test.cc)
TARGET_LINK_LIBRARIES(thread_pool_test util common gtest)

add_test(
  NAME
  thread_pool_test
  COMMAND
  $<TARGET_FILE:thread_pool_test>
  )
