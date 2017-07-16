#include "CppUTest/TestHarness.h"
#include "../src/ArduinoInterface.h"

TEST_GROUP(ArduinoInputTestGroup)
{
};

TEST(ArduinoInputTestGroup, FirstTest)
{
    std::string test_string = "steer:1 engine:2";
    std::vector<int> result(2, 0);
    parse_arduino_input(test_string, result);
    CHECK(result[0] == 1);
    CHECK(result[1] == 2);
}

TEST(ArduinoInputTestGroup, SecondTest)
{
    std::string test_string = "steer:184 engine:695";
    std::vector<int> result(2, 0);
    parse_arduino_input(test_string, result);
    CHECK(result[0] == 184);
    CHECK(result[1] == 695);
}

TEST(ArduinoInputTestGroup, ThirdTest)
{
    std::string test_string = "steer:1670 engine:2482";
    std::vector<int> result(2, 0);
    parse_arduino_input(test_string, result);
    CHECK(result[0] == 1670);
    CHECK(result[1] == 2482);
}
