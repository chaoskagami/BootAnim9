#include "main.h"

int main(){
	mountSDMC();
	if ((*(vu8 *)0x10010000 == 0) & !(HID_PAD & BUTTON_ANY)) // check if this is a coldboot and if key is pressed
		animationLoop();
	loader();
	return 0;
}
