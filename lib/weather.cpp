#include "weather.h"

const std::string& City::GetName() const {
    return name_of_city_;
}

City::City(const std::string& name_of_city, size_t amount_of_days) : name_of_city_(name_of_city),
                                                                     days_(amount_of_days) {
    auto coordinates = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city?name=" + name_of_city_},
                                cpr::Header{{"X-Api-Key", "dr5wNoaF5feEChhA6AtUPg==uxQy6k2wQ8BislRy"}});
    json parse_response = json::parse(coordinates.text.substr(1, coordinates.text.length() - 2));
    latitude_ = parse_response["latitude"];
    longitude_ = parse_response["longitude"];
    for (int i = 0; i < amount_of_days; i++) {
        days_[i].weather_.resize(4);
    }
}

const std::vector<Day>& City::GetDays() const {
    return days_;
}

Parser::Parser(std::ifstream& in) {
    json info = json::parse(in);
    max_amount_of_days_ = info["days"];
    freq_ = info["freq"];
    initial_amount_of_days_ = info["init"];
    std::vector<std::string> city(info["name"].size());
    for (int i = 0; i < city.size(); i++) {
        city[i] = info["name"][i];
    }
    cities_ = ParseCities(city, max_amount_of_days_);
}

int Parser::GetFreq() const {
    return freq_;
}

int Parser::GetMaxAmountOfDays() const {
    return max_amount_of_days_;
}

int Parser::GetInitialAmountOfDays() const {
    return initial_amount_of_days_;
}
