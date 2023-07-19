#include "weather.h"

static std::map<int, std::string> weathercode = {{0,  "Clear sky"},
                                                 {1,  "Mainly clear"},
                                                 {2,  "Partly cloudy"},
                                                 {3,  "Overcast"},
                                                 {45, "Fog"},
                                                 {48, "Depositing rime fog"},
                                                 {51, "Light drizzle"},
                                                 {53, "Moderate drizzle"},
                                                 {55, "Dense drizzle"},
                                                 {56, "Light freezing drizzle"},
                                                 {57, "Dense freezing drizzle"},
                                                 {61, "Slight rain"},
                                                 {63, "Moderate rain"},
                                                 {65, "Heavy rain"},
                                                 {66, "Light freezing rain"},
                                                 {67, "Heavy freezing rain"},
                                                 {71, "Slight snow fall"},
                                                 {73, "Moderate snow fall"},
                                                 {75, "Heavy snow fall"},
                                                 {77, "Snow grains"},
                                                 {80, "Slight rain shower"},
                                                 {81, "Moderate rain shower"},
                                                 {82, "Violent rain shower"},
                                                 {85, "Slight snow shower"},
                                                 {86, "Heavy snow shower"},
                                                 {95, "Thunderstorm"},
                                                 {96, "Thunderstorm with slight hail"},
                                                 {99, "Thunderstorm with heavy hail"}};

Element SetPicture(size_t code) {
    Element picture;
    if ((code == 0) || (code == 1)) {
        picture = vbox({
                               text("       \\   /      "),
                               text("        .-.        "),
                               text("     ― (   ) ―    "),
                               text("        `-’        "),
                               text("       /   \\      ")
                       }) | flex;
    } else if (code == 2) {
        picture = vbox({
                               text("   .( ).           "),
                               text("  (_._)_) .(  )    "),
                               text("         (_.)_._)  ")
                       }) | flex;
    } else if (code == 3) {
        picture = vbox({
                               text("          .--.     "),
                               text("      .-( --- ).   "),
                               text("    (___.__)__)    ")
                       }) | flex;
    } else if ((code == 45) || (code == 48)) {
        picture = vbox({
                               text("   _   -_   _-     "),
                               text("  -_   -  _ -- _   "),
                               text("    _  -  _- -_    "),
                               text("   - _-  _ _- -    ")
                       }) | flex;
    } else if ((code == 51) || (code == 53) || (code == 55) || (code == 56) ||
               (code == 57) || (code == 61) || (code == 63) || (code == 66)) {
        picture = vbox({
                               text("   .( ).           "),
                               text("  (_._)_)  .(  )   "),
                               text("  ' '   ' (_.)_._) "),
                               text("   '   '    '  '   "),
                               text("          '  '   ' ")
                       }) | flex;
    } else if ((code == 65) || (code == 67) || (code == 80) ||
               (code == 81) || (code == 82)) {
        picture = vbox({
                               text("         .--.      "),
                               text("     .-( --- ).    "),
                               text("    (___.__)__)    "),
                               text("     / /  /  /     "),
                               text("    / /  /  /      ")
                       }) | flex;
    } else if ((code == 71) || (code == 73)) {
        picture = vbox({
                               text("   .( ).           "),
                               text("  (_._)_)  .(  )   "),
                               text("  *   *  (_.)_._)  "),
                               text("     *    *    *   "),
                               text("        *    *     ")
                       }) | flex;
    } else if ((code == 75) || (code == 85) || (code == 86)) {
        picture = vbox({
                               text("         .--.      "),
                               text("     .-( --- ).    "),
                               text("    (___.__)__)    "),
                               text("    * *  * * *     "),
                               text("   * * * * * *     ")
                       }) | flex;
    } else if (code == 77) {
        picture = vbox({
                               text("         .--.      "),
                               text("     .-( --- ).    "),
                               text("    (___.__)__)    "),
                               text("     o  o   o      "),
                               text("     o o  o  o     "),
                       }) | flex;
    } else if (code == 95) {
        picture = vbox({
                               text("         .--.      "),
                               text("     .-( --- ).    "),
                               text("    (___.__)__)    "),
                               text("      _/  _/       "),
                               text("     /   /         ")
                       }) | flex;
    } else if ((code == 96) || (code == 99)) {
        picture = vbox({
                               text("         .--.      "),
                               text("     .-( --- ).    "),
                               text("    (___.__)__)    "),
                               text("    o  _/  _/      "),
                               text("      / o /  o     "),
                       }) | flex;
    }
    return picture;
}

Element DrawPartOfDay(const Weather& weather, const std::string& part_of_day) {
    Element picture = SetPicture(weather.weather_code_);

    std::string type_of_weather = weathercode[weather.weather_code_];

    Element inner_box = vbox({
                                     text(type_of_weather) | hcenter,
                                     text("Temperature: " + std::to_string(weather.temperature_) + " °С") | hcenter,
                                     text("Wind speed: " + std::to_string(weather.wind_speed_) + " km/h") | hcenter,
                                     text("Visibility: " + std::to_string(weather.visibility_) + " m") | hcenter,
                                     text("Precipitation: " + std::to_string(weather.precipitation_) +
                                          " mm | " + std::to_string(
                                             weather.precipitation_probability_) + " %") | hcenter
                             });

    Element box = window(text(""), vbox({text(part_of_day) | hcenter | color(Color::Yellow1) | flex,
                                         hbox({ picture | hcenter | vcenter, inner_box | vcenter }) }));
    return box;
}

Element DrawDay(const Day& weather, const std::string& date) {
    Element morning = DrawPartOfDay(weather.weather_[0], "morning");
    Element afternoon = DrawPartOfDay(weather.weather_[1], "afternoon");
    Element evening = DrawPartOfDay(weather.weather_[2], "evening");
    Element night = DrawPartOfDay(weather.weather_[3], "night");

    Element day = vbox(text("date: " + date.substr(0, date.size() - 6)), hbox(morning, afternoon, evening, night));
    return day;
}

Element DrawCity(const City& city, int amount_of_days) {
    Elements town;
    town.push_back(text(city.GetName()) | bold);
    for (int i = 0; i < amount_of_days; ++i) {
        Element day = DrawDay(city.GetDays()[i], city.GetDays()[i].date_);
        town.push_back(day);
    }
    Element CityRender = vbox(std::move(town));
    return CityRender;
}
