PROJECT(Simple-DB)
add_subdirectory(util)
add_subdirectory(net)

AUX_SOURCE_DIRECTORY(util DIR_UTIL)
ADD_LIBRARY(util STATIC ${DIR_UTIL})
TARGET_LINK_LIBRARIES(util pthread)

AUX_SOURCE_DIRECTORY(common DIR_COMMON)
ADD_LIBRARY(common STATIC ${DIR_COMMON})
TARGET_LINK_LIBRARIES(common pthread)

# AUX_SOURCE_DIRECTORY(net DIR_UTIL)
ADD_LIBRARY(net STATIC net/tcp_server.cc net/poller/poller.cc net/poller/select_poller.cc)
TARGET_LINK_LIBRARIES(net pthread)
