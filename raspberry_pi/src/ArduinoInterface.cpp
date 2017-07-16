#include "ArduinoInterface.h"

void parse_arduino_input(std::string input, std::vector<int> &result)
{
    std::size_t start = input.find(':', 0) + 1;
    std::size_t end = input.find(' ', 0) - 1;
    int engine_value = stoi(input.substr(start, end));
    result[0] = engine_value;

    start = input.find(':', end) + 1;
    int steer_value = stoi(input.substr(start));
    result[1] = steer_value;
}
