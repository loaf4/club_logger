set(SRC
    ${CMAKE_CURRENT_LIST_DIR}/test.cpp)

add_executable(ClubLogTest ${SRC})

target_link_libraries(ClubLogTest PRIVATE Catch2::Catch2WithMain ClubLogger Club)
