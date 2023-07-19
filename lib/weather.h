#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>

#include <thread>

#include <winsock2.h>
#include <windows.h>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "ftxui/screen/box.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

using json = nlohmann::json;

using namespace ftxui;

struct Weather {
    int temperature_;
    int precipitation_;
    uint16_t precipitation_probability_;
    uint8_t weather_code_;
    uint16_t visibility_;
    int wind_speed_;
};

struct Day {
    std::vector<Weather> weather_;
    std::string date_;
};

class City {
private:
    std::string name_of_city_;
    double latitude_ = 0;
    double longitude_ = 0;
    std::vector<Day> days_;
public:
    City() = default;

    explicit City(const std::string& name_of_city, size_t amount_of_days);

    ~City() = default;

    const std::string& GetName() const;

    const std::vector<Day>& GetDays() const;

    void ParseWeather();
};

std::vector<City> ParseCities(std::vector<std::string>& city, size_t max_amount_of_days);

class Parser {
private:
    int freq_ = 0;
    int max_amount_of_days_ = 0;
    int initial_amount_of_days_ = 1;
public:

    std::vector<City> cities_;

    explicit Parser(std::ifstream& in);

    int GetFreq() const;

    int GetMaxAmountOfDays() const;

    int GetInitialAmountOfDays() const;
};

Element SetPicture(size_t code);

Element DrawPartOfDay(const Weather& weather, const std::string& day_part);

Element DrawDay(const Day& weather, const std::string& date);

Element DrawCity(const City& city, int amount_of_days);

void RunWeather(const std::string& input);
