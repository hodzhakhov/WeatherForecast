add_library(MVC controller.cpp model.cpp view.cpp weather.cpp weather.h)

target_link_libraries(MVC PRIVATE cpr::cpr)
target_link_libraries(MVC PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(MVC PRIVATE ftxui::screen ftxui::dom ftxui::component)
