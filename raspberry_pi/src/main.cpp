#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include "serial-lib.h"
#include "ArduinoInterface.h"
#include <vector>
#include <string>

int main()
{

    std::ofstream log_file;
    log_file.open("episode_1.log");
    /*
     *  Initialize serial communiations
     */
    int fd = -1;
    while (-1 == fd) {
        fd = serialport_init("/dev/ttyACM0", 115200);
        sleep(1);
        log_file << "Unable to open /dev/ttyACM0 for reading: " << fd << std::endl;
    }
    char buf[100];
    std::vector<int> control_values(2, 0);

    /*
     *  Initialize  output files
     */
    std::ofstream output_file;
    output_file.open("episode_1.data");

    std::cout << "Starting..." << std::endl;
    while (1) {

        //serialport_readline(fd, buf, 100, 100);
        sleep(5);
        serialport_read_until(fd, buf, '\n', 100, 100);

        // for (int i=0; buf[i]!=0; ++i) {
        //     std::cout << buf[i];
        // }
        // std::cout << std::endl;

        parse_arduino_input(std::string(buf, 100), control_values);
        std::cout << "engine:"<<control_values[0] << " steer:" << control_values[1] << std::endl;
        output_file << control_values[0] << " " << control_values[1] << std::endl;
    }
    output_file.close();
}
