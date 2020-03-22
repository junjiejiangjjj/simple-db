PROJECT(Simple-DB)

add_library(simple_db)

add_subdirectory(util)
add_subdirectory(net)
# add_subdirectory(db)
add_subdirectory(common)

target_link_libraries(simple_db
  PRIVATE
  util
  net
  common
  )

# AUX_SOURCE_DIRECTORY(util DIR_UTIL)
# ADD_LIBRARY(util STATIC ${DIR_UTIL})
# TARGET_LINK_LIBRARIES(util)

# AUX_SOURCE_DIRECTORY(common DIR_COMMON)
# ADD_LIBRARY(common STATIC ${DIR_COMMON})
# TARGET_LINK_LIBRARIES(common)

# AUX_SOURCE_DIRECTORY(net DIR_NET)
# AUX_SOURCE_DIRECTORY(net/poller DIR_POLLER)
# ADD_LIBRARY(net STATIC ${DIR_NET} ${DIR_POLLER})
# TARGET_LINK_LIBRARIES(net)

# AUX_SOURCE_DIRECTORY(db DIR_DB)
# ADD_LIBRARY(db STATIC ${DIR_DB})
# TARGET_LINK_LIBRARIES(db)

