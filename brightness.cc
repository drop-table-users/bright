#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <exception>
#include <cmath>
#include <chrono>
#include <thread>

#include "brightness.h"

using namespace std;

const char* MAX_BRIGHT_FILE = "/sys/class/backlight/intel_backlight/max_brightness";
const char* BRIGHT_FILE = "/sys/class/backlight/intel_backlight/brightness";

ulong read_numeric_file(const char* path) {
    ifstream num_file(path);
    string num_str;
    getline(num_file, num_str);
    num_file.close();

    return atoi(num_str.c_str());
}

void write_numeric_file(const char* path, ulong num) {
    ofstream num_file(path);
    num_file << num;
    num_file.close();
}

ulong max_bright() {
    return read_numeric_file(MAX_BRIGHT_FILE);
}

ulong current_bright() {
    return read_numeric_file(BRIGHT_FILE);
}

void set_bright(ulong new_bright) {
    if (new_bright < 0 || new_bright > max_bright())
        throw range_error("Invalid brightness change!");

    write_numeric_file(BRIGHT_FILE, new_bright);
}

void gradual_set_bright(ulong prev, ulong new_) {
        ulong current = prev;
        while (current != new_) {
            set_bright(current);
            std::this_thread::sleep_for(std::chrono::nanoseconds(100));

            if (prev > new_)
                --current;
            else
                ++current;
        }
        set_bright(new_);
}
