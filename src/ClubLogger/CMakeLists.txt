add_library(ClubLogger STATIC
    ${CMAKE_CURRENT_LIST_DIR}/day_logger.cpp)

target_include_directories(ClubLogger PUBLIC
    ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(ClubLogger PUBLIC Club)
