#include <iostream>
#include <unistd.h>
#include <cstring>
#include "serial-lib.h"

long int parse_string(const char *strptr);

int main()
{
    int fd;
    fd = serialport_init("/dev/ttyACM1", 115200);
    char buf[100];
    const char* strptr=buf;

    int current=0;
    int cnt;
    while (1) {
        cnt = serialport_read_until(fd, buf, '\n', 100, 100);
        for (int i=0; buf[i]!=0; ++i) {
            std::cout << buf[i];
        }
        std::cout << "Distance yo " << parse_string(strptr) << std::endl;
        std::cout << std::endl;

    }
    // std::cout << r << std::endl;

}

long int parse_string(const char *strptr)
{
    char buf[5] = {0};
    const char *start = strchr(strptr, ':');
    const char *end = strchr(strptr, ' ');
    return  end-start;
}

// int main()
// {
//     libusb_device **devices;
//     libusb_device *found;
//     ssize_t cnt;
//     int r;
// 
//     r = libusb_init(NULL);
//     libusb_set_debug(NULL, LIBUSB_LOG_LEVEL_DEBUG);
//     if (r < 0) {
//         std::cout << "Shit's fucked " << r << std::endl;
//     }
// 
//     cnt = libusb_get_device_list(NULL, &devices);
//     if (cnt < 0) { 
//         std::cout << "Shit's bonkers..." << std::endl;
//     }
// 
//     // for (int i=0; i<cnt; ++i) {
//     //    libusb_device *device = devices[i]; 
//     // }
// 
//     int i=0;
//     libusb_device *dev;
// 	uint8_t path[8];
//     libusb_device *arduino;
//     while ((dev=devices[i++]) != NULL) {
// 		r = libusb_get_port_numbers(dev, path, sizeof(path));
//         if (0 < r && path[0] == 1) {
//             std::cout << "Found the arduino." << std::endl;
//             arduino = dev;
//         }
//     }
// 
//     if (NULL == arduino) {
//         std::cout << "Arduino is hiding..." << std::endl; 
//         return -1;
//     } 
// 
// 
//     libusb_device_handle *handle;
//     r = libusb_open(arduino, &handle);
//     if (0 != r) {
//         std::cout << "Arduino already disappeared, leaving only the mysterious message '" << r << "'" << std::endl; 
//         if (LIBUSB_ERROR_ACCESS == r) {
//             std::cout << "Which is to say, user has insufficient permissions..." << std::endl;
//         }
//         return -1;
//     }
// 
//     
//     uint8_t buf[100];
//     cnt = libusb_control_transfer(handle, 0x80, 0x0a, 0, 0, buf, 4, 0);
//     std::cout << "Bytes received " << cnt << std::endl;
//     std::cout << LIBUSB_ERROR_TIMEOUT << std::endl;
//     std::cout << LIBUSB_ERROR_PIPE << std::endl;
//     std::cout << LIBUSB_ERROR_NO_DEVICE << std::endl;
// 
//     libusb_free_device_list(devices, 1);
// 
//     // libusb_device_handle *handle;
//     // libusb_open("/dev/ttyACM0", &handle);
//     // std::cout << "yeah boi" << std::endl;
// }
