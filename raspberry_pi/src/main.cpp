#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include "serial-lib.h"
#include "ArduinoInterface.h"
#include <vector>
#include <string>
#include <raspicam/raspicam.h>

int main()
{
    std::ofstream log_file;
    log_file.open("episode_1.log");

    raspicam::RaspiCam Camera;
    if ( !Camera.open() ) {
        log_file << "Unable to open camera." << std::endl;
        return -1;
    }

    /*
     *  Initialize serial communiations
     */
    int fd = -1;
    while (-1 == fd) {
        fd = serialport_init("/dev/ttyACM0", 4800);
        sleep(1);
        log_file << "Unable to open /dev/ttyACM0 for reading: " << fd << std::endl;
    }

    /*
     *  Initialize  output files
     */
    std::ofstream image_file("raspicam_test.ppm", std::ios::binary);
    unsigned char image[Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];
    Camera.grab();
    Camera.retrieve(image, raspicam::RASPICAM_FORMAT_RGB);
    image_file << "P6" << std::endl << Camera.getWidth() << " " << Camera.getHeight() << " 255" << std::endl;
    image_file.write((char *) image, Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB));

    std::ofstream output_file;
    output_file.open("episode_1.data");

    std::vector<int> control_values(2, 0);
    char buf[100];
    std::cout << "Starting..." << std::endl;
    while (1) {

        serialport_readline(fd, buf, 100, 100);

        for (int i=0; buf[i]!=0; ++i) {
            std::cout << buf[i];
        }
        std::cout << std::endl;


        parse_arduino_input(std::string(buf, 100), control_values);
        std::cout << "engine:"<<control_values[0] << " steer:" << control_values[1] << std::endl;
        output_file << control_values[0] << " " << control_values[1] << std::endl;
    }
    output_file.close();
    return 0;
}
