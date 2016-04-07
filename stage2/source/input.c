#include "loader.h"

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

char* getPayloadName() { // Check whether the payload exists, returns the name if so, otherwise returns NULL
	uint32_t pad = HID_PAD;
	if        (pad & BUTTON_A) {
		return payloads[1];
	} else if (pad & BUTTON_B) {
		return payloads[2];
	} else if (pad & BUTTON_SEL) {
		return payloads[3];
	} else if (pad & BUTTON_STA) {
		return payloads[4];
	} else if (pad & BUTTON_RIGHT) {
		return payloads[5];
	} else if (pad & BUTTON_LEFT) {
		return payloads[6];
	} else if (pad & BUTTON_UP) {
		return payloads[7];
	} else if (pad & BUTTON_DOWN) {
		return payloads[8];
	} else if (pad & BUTTON_R) {
		return payloads[9];
	} else if (pad & BUTTON_L) {
		return payloads[10];
	} else if (pad & BUTTON_X) {
		return payloads[11];
	} else if (pad & BUTTON_Y) {
		return payloads[12];
	} else if (pad & BUTTON_ZL) {
		return payloads[13];
	} else if (pad & BUTTON_ZR) {
		return payloads[14];
	}
	return payloads[0];
}

