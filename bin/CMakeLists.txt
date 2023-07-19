add_executable(lab main.cpp)

target_link_libraries(lab PRIVATE cpr::cpr)
target_link_libraries(lab PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(lab PRIVATE MVC)
target_link_libraries(lab PRIVATE ftxui::screen ftxui::dom ftxui::component)

target_include_directories(lab PRIVATE ${PROJECT_SOURCE_DIR})
