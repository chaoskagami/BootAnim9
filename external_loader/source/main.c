#include "fatfs/ff.h"
#include "draw.h"
#include <stddef.h>

#define PAYLOAD_ADDRESS	0x23F00000

#define PB(a) "/anim/boot/" a ".bin"
char *payloads[] = {
	PB("none"),
	PB("a"),
	PB("b"),
	PB("select"),
	PB("start"),
	PB("right"),
	PB("left"),
	PB("up"),
	PB("down"),
	PB("r"),
	PB("l"),
	PB("x"),
	PB("y"),
	PB("zl"),
	PB("zr")
};

int n_payloads = 5;

struct framebuffer_t* framebuffers = (struct framebuffer_t *) 0x23FFFE00;

void whiteScreen() { // Display a white screen
	unsigned char *destc = framebuffers->top_left;
	int size = (400*240*3); // Top framebuffer size
    while(size--)
		*destc++ = 0xFF; // 0xFF = 255 = White
}

int fileExists(char * f_path) { // Check whether file exists
	FIL test;
	if (f_open(&test, f_path, FA_READ) == FR_OK) {
		f_close(&test);
		return 1;
	}

	else return 0;
}

#define BUTTON_A        (1 << 0)
#define BUTTON_B        (1 << 1)
#define BUTTON_SEL      (1 << 2)
#define BUTTON_STA      (1 << 3)
#define BUTTON_RIGHT    (1 << 4)
#define BUTTON_LEFT     (1 << 5)
#define BUTTON_UP       (1 << 6)
#define BUTTON_DOWN     (1 << 7)
#define BUTTON_R        (1 << 8)
#define BUTTON_L        (1 << 9)
#define BUTTON_X        (1 << 10)
#define BUTTON_Y        (1 << 11)

#define BUTTON_ZL       (1 << 14)
#define BUTTON_ZR       (1 << 15)

#define BUTTON_ANY      (BUTTON_A|BUTTON_B|BUTTON_SEL|BUTTON_STA|BUTTON_RIGHT|BUTTON_LEFT|BUTTON_UP|BUTTON_DOWN|BUTTON_R|BUTTON_L|BUTTON_X|BUTTON_Y|BUTTON_ZL|BUTTON_ZR)

#define HID_PAD         (*(volatile unsigned int *)0x10146000 ^ BUTTON_ANY)

char * checkPayloads() { // Check whether the payload exists, returns the name if so, otherwise returns NULL
	unsigned int pad = HID_PAD;
	if ((pad & BUTTON_A) && fileExists(payloads[1])) {
		return payloads[1];
	} else if ((pad & BUTTON_B) && fileExists(payloads[2])) {
		return payloads[2];
	} else if ((pad & BUTTON_SEL) && fileExists(payloads[3])) {
		return payloads[3];
	} else if ((pad & BUTTON_STA) && fileExists(payloads[4])) {
		return payloads[4];
	} else if ((pad & BUTTON_RIGHT) && fileExists(payloads[5])) {
		return payloads[5];
	} else if ((pad & BUTTON_LEFT) && fileExists(payloads[6])) {
		return payloads[6];
	} else if ((pad & BUTTON_UP) && fileExists(payloads[7])) {
		return payloads[7];
	} else if ((pad & BUTTON_DOWN) && fileExists(payloads[8])) {
		return payloads[8];
	} else if ((pad & BUTTON_R) && fileExists(payloads[9])) {
		return payloads[9];
	} else if ((pad & BUTTON_L) && fileExists(payloads[10])) {
		return payloads[10];
	} else if ((pad & BUTTON_X) && fileExists(payloads[11])) {
		return payloads[11];
	} else if ((pad & BUTTON_Y) && fileExists(payloads[12])) {
		return payloads[12];
	} else if ((pad & BUTTON_ZL) && fileExists(payloads[13])) {
		return payloads[13];
	} else if ((pad & BUTTON_ZR) && fileExists(payloads[14])) {
		return payloads[14];
	} else if (fileExists(payloads[0])) {
		return payloads[0];
	}
	return NULL;
}

void main() {
    FATFS fs;
    FIL payload_file;
    unsigned int br;

    f_mount(&fs, "0:", 1);

	char *payload = checkPayloads();
	if (payload == NULL)
		whiteScreen();

	if(f_open(&payload_file, payload, FA_READ) == FR_OK) {
		f_read(&payload_file, (void *)PAYLOAD_ADDRESS, f_size(&payload_file), &br);
		((void (*)())PAYLOAD_ADDRESS)();
    }

	else whiteScreen();
}
