#include "types.h"
#include "hid.h"

int checkAnyDown() {
	return !!(~HID_STATE & BUTTON_ANY);
}
