find_package(Catch2 REQUIRED)

add_executable(tests main.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2)
target_link_libraries(tests PRIVATE safecppjson)
