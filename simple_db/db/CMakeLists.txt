add_library(db)

target_sources(db
  
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/skip_list.h
  )

target_include_directories(util
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  )

ADD_EXECUTABLE(SkipListTest skip_list_test.cc)
TARGET_LINK_LIBRARIES(SkipListTest common db util gtest)
