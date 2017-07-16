#include <iostream>
#include <unistd.h>
#include <cstring>
#include "serial-lib.h"
#include "ArduinoInterface.h"
#include <vector>
#include <string>

int main()
{
    int fd;
    fd = serialport_init("/dev/ttyACM0", 115200);
    char buf[100];

    std::vector<int> control_values(2, 0);
    std::cout << "Starting..." << std::endl;
    while (1) {

        serialport_readline(fd, buf, 100, 100);

        for (int i=0; buf[i]!=0; ++i) {
            std::cout << buf[i];
        }
        std::cout << std::endl;


        parse_arduino_input(std::string(buf, 100), control_values);
        std::cout << "steer:"<<control_values[0] << " engine:" << control_values[1] << std::endl;

    }
}
