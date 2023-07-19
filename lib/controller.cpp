#include "weather.h"

void Update(Parser& parser) {
    auto start = std::chrono::system_clock::now();
    auto stop = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }
        stop = std::chrono::system_clock::now();
        duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
        if (duration.count() % parser.GetFreq() == 0) {
            for (auto & city : parser.cities_) {
                city.ParseWeather();
            }
        }
    }
}

void Output(Parser& parser) {
    int index = 0;
    int amount_of_days = parser.GetInitialAmountOfDays();

    auto screen = ScreenInteractive::TerminalOutput();
    auto renderer = Renderer([&parser, &index, &amount_of_days] {
        return DrawCity(parser.cities_[index], amount_of_days);
    });
    auto component = CatchEvent(renderer, [&](const Event& event) {
        if (event == Event::Escape) {
            screen.ExitLoopClosure()();
            return true;
        } else if (event == Event::Character('N')) {
            index++;
            if (index == parser.cities_.size()) {
                index = 0;
            }
            return true;
        } else if (event == Event::Character('p')) {
            index--;
            if (index == -1) {
                index = parser.cities_.size() - 1;
            }
            return true;
        } else if (event == Event::Character('+')) {
            amount_of_days = std::min(++amount_of_days, static_cast<int>(parser.GetMaxAmountOfDays()));
            return true;
        } else if (event == Event::Character('-')) {
            amount_of_days = std::max(--amount_of_days, 1);
            return true;
        }
        return false;
    });
    screen.Loop(component);
}

void RunWeather(const std::string& input) {
    std::ifstream in(input);
    Parser parser(in);

    std::thread f1(Output, std::ref(parser));
    std::thread f2(Update, std::ref(parser));

    f1.join();
    f2.join();
}
