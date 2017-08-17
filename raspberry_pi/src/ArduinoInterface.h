#ifndef __ARDUINO_INTERFACE_H__
#define __ARDUINO_INTERFACE_H__

#include "serial-lib.h"
#include <vector>
#include <string>
#include <iostream>
#include <ctype.h>

void parse_arduino_input(std::string, std::vector<int> &);

#endif
