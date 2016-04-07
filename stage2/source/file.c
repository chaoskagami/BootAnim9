#include "main.h"

// Note that whilst this is A-OK on the 3ds, this is an unacceptable
// check on any other platform due to ToCToU vulns.

int f_exists(char * f_path) { // Check whether file exists.
	FIL test;
	if (f_open(&test, f_path, FA_READ) == FR_OK) {
		f_close(&test);
		return 1;
	}
	return 0;
}

