add_library(db)

target_sources(db
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/record.cc
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/skip_list.h
  ${CMAKE_CURRENT_LIST_DIR}/record.h  
  )

target_include_directories(db
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  )

ADD_EXECUTABLE(SkipListTest skip_list_test.cc)
TARGET_LINK_LIBRARIES(SkipListTest db util common gtest)

add_test(
    NAME
    SkipListTest
    COMMAND
    $<TARGET_FILE:SkipListTest>    
)

ADD_EXECUTABLE(RecordTest record_test.cc)
TARGET_LINK_LIBRARIES(RecordTest db util common gtest)

add_test(
    NAME
    RecordTest
    COMMAND
    $<TARGET_FILE:RecordTest>
)



