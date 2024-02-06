add_library(Club STATIC
    ${CMAKE_CURRENT_LIST_DIR}/client.cpp
    ${CMAKE_CURRENT_LIST_DIR}/club.cpp
    ${CMAKE_CURRENT_LIST_DIR}/club_util.cpp
    ${CMAKE_CURRENT_LIST_DIR}/table.cpp)

target_include_directories(Club PUBLIC
    ${CMAKE_CURRENT_LIST_DIR})
