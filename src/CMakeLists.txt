set(SRC 
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

add_executable(${PROJECT_NAME} ${SRC})

add_subdirectory(Club)
add_subdirectory(ClubLogger)
target_link_libraries(${PROJECT_NAME} PRIVATE ClubLogger)
