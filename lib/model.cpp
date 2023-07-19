#include "weather.h"

std::vector<City> ParseCities(std::vector<std::string>& city, size_t max_amount_of_days) {
    std::vector<City> cities(city.size());
    for (int i = 0; i < city.size(); i++) {
        City tmp(city[i], max_amount_of_days);
        tmp.ParseWeather();
        cities[i] = tmp;
    }
    return cities;
}

void City::ParseWeather() {
    auto weather = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast?latitude=" +
                                     std::to_string(latitude_) + "&longitude=" + std::to_string(longitude_) +
                                     "&hourly=temperature_2m,precipitation_probability,precipitation,weathercode,visibility,windspeed_10m&forecast_days=" +
                                     std::to_string(days_.size())});
    json parse_weather = json::parse(weather.text);
    for (int i = 0; i < days_.size(); i++) {
        days_[i].date_ = parse_weather["hourly"]["time"][24 * i + 5];
        for (int j = 0; j < 4; j++) {
            days_[i].weather_[j].temperature_ = parse_weather["hourly"]["temperature_2m"][24 * i + (5 + j * 6)];
            days_[i].weather_[j].precipitation_probability_ = parse_weather["hourly"]["precipitation_probability"][24 * i + (5 + j * 6)];
            days_[i].weather_[j].precipitation_ = parse_weather["hourly"]["precipitation"][24 * i + (5 + j * 6)];
            days_[i].weather_[j].weather_code_ = parse_weather["hourly"]["weathercode"][24 * i + (5 + j * 6)];
            days_[i].weather_[j].visibility_ = parse_weather["hourly"]["visibility"][24 * i + (5 + j * 6)];
            days_[i].weather_[j].wind_speed_ = parse_weather["hourly"]["windspeed_10m"][24 * i + (5 + j * 6)];
        }
    }
}
