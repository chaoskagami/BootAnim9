#include "loader.h"

void die() {
	clear_color(0xff, 0xff, 0xff);
	while(1); // Deathtrap.
}

void loader() {
    FIL payload_file;
    unsigned int br;

	char *payload = getPayloadName();
	if (!f_exists(payload))
		die();  // No file found. We need to stop here.

	// Read payload into memory and jump to.
	if(f_open(&payload_file, payload, FA_READ) == FR_OK) {
		f_read(&payload_file, (void *)PAYLOAD_ADDRESS, f_size(&payload_file), &br);
		((void (*)())PAYLOAD_ADDRESS)();
    }

	die();
}
