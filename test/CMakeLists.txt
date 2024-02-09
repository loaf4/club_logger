set(SRC
    ${CMAKE_CURRENT_LIST_DIR}/test.cpp)

add_executable(ClubLoggerTest ${SRC})

target_link_libraries(ClubLoggerTest PRIVATE Catch2::Catch2WithMain ClubLogger Club)
