#include <stdexcept>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <thread>
#include "brightness.h"

using std::cout;
using std::endl;

int main(int argc, char** argv) {
	if (argc != 2)
		throw std::runtime_error("Exactly one argument required!");

	const char* arg = argv[1];
	if (*arg == 'c') {
		cout << 100 * (float)(current_bright()) / max_bright() << endl;
		return 0;
	}

	unsigned arg_len = strlen(arg);
	char* clean_arg = new char[arg_len];
	unsigned clean_i = 0;

	for (int i = 0; i < arg_len; ++i) {
		if (arg[i] != '%') {
			clean_arg[clean_i] = arg[i];
			++clean_i;
		}
	}

	double arg_perc = strtod(clean_arg, NULL) / 100;

	if (arg_perc == 0 && *clean_arg != '0')
		throw std::runtime_error("Invalid argument.");

	ulong new_bright = round(arg_perc * max_bright());

#ifdef _GRADUAL_CHANGE
	gradual_set_bright(current_bright(), new_bright);
#else
	set_bright(new_bright);
#endif

	return 0;
}
