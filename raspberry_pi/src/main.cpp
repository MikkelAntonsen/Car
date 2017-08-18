#include <iostream>
#include <unistd.h>
#include <cstring>
#include "serial-lib.h"
#include "ArduinoInterface.h"
#include <vector>
#include <string>
#include <raspicam/raspicam.h>

int main()
{
    raspicam::RaspiCam Camera;
    if ( !Camera.open() ) {
	std::cout << "Unable to open camera." << std::endl;
	return 0;
    }

    int fd=-1;
    std::cout << "Trying to connect to arduino" << std::endl;
    while (-1 == fd) {
        fd = serialport_init("/dev/ttyACM0", 4800);
	sleep(1);
	std::cout << ".";
    }
    std::cout << std::endl;

    char buf[100];
    std::vector<int> control_values(2, 0);
    std::cout << "Starting main loop..." << std::endl;
    while (1) {

        serialport_readline(fd, buf, 100, 100);

        for (int i=0; buf[i]!=0; ++i) {
            std::cout << buf[i];
        }
        std::cout << std::endl;


        parse_arduino_input(std::string(buf, 100), control_values);
        std::cout << "steer:"<<control_values[0] << " engine:" << control_values[1] << std::endl;

    }
    return 1;
}
