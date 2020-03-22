PROJECT(Simple-DB)

add_library(simple_db)

add_subdirectory(util)
add_subdirectory(net)
#add_subdirectory(db)
add_subdirectory(common)

target_link_libraries(simple_db
  PRIVATE
  util
  net
  common
  )


