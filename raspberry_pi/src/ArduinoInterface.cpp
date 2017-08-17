#include "ArduinoInterface.h"

void parse_arduino_input(std::string input, std::vector<int> &result)
{
    std::size_t start = input.find(':', 0) + 1;
    std::size_t end = input.find(' ', 0) - 1;

    if (std::string::npos == start || std::string::npos == end) {
        result[0]=-1;
        result[1]=-1;
        return;
    }

    for (size_t i=start; i<end; i++) {
        if (!isdigit(input[i])) {
            result[0]=-1;
            result[1]=-1;
            return;
        }
    }
    std::cout<<std::endl;

    int engine_value = stoi(input.substr(start, end));
    result[0] = engine_value;

    start = input.find(':', end) + 1;
    if (std::string::npos == start) {
        result[0]=-1;
        result[1]=-1;
        return;
    }

    for (size_t i=start; start<end; i++) {
        if (!isdigit(input[i])) {
            result[0]=-1;
            result[1]=-1;
            return;
        }
    }

    int steer_value = stoi(input.substr(start));
    result[1] = steer_value;
}
