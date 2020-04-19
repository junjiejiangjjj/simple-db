add_library(db)

target_sources(db
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/record.cc
  ${CMAKE_CURRENT_LIST_DIR}/mem_table.cc
  ${CMAKE_CURRENT_LIST_DIR}/table.cc  
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/skip_list.h
  ${CMAKE_CURRENT_LIST_DIR}/record.h
  ${CMAKE_CURRENT_LIST_DIR}/mem_table.h
  ${CMAKE_CURRENT_LIST_DIR}/table.h  
  )

target_include_directories(db
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  )

ADD_EXECUTABLE(SkipListTest skip_list_test.cc)
TARGET_LINK_LIBRARIES(SkipListTest db util common gtest)

add_test(
    NAME
    DB-SkipListTest
    COMMAND
    $<TARGET_FILE:SkipListTest>    
)

ADD_EXECUTABLE(RecordTest record_test.cc)
TARGET_LINK_LIBRARIES(RecordTest db util common gtest)

add_test(
    NAME
    DB-RecordTest
    COMMAND
    $<TARGET_FILE:RecordTest>
    )

ADD_EXECUTABLE(MemTableTest mem_table_test.cc)
TARGET_LINK_LIBRARIES(MemTableTest db util common gtest)

add_test(
    NAME
    DB-MemTableTest
    COMMAND
    $<TARGET_FILE:MemTableTest>
    )


ADD_EXECUTABLE(TableTest table_test.cc)
TARGET_LINK_LIBRARIES(TableTest db util common gtest)

add_test(
    NAME
    DB-TableTest
    COMMAND
    $<TARGET_FILE:TableTest>
)  
