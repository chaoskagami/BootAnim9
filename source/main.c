#include "types.h"
#include "draw.h"
#include "memory.h"
#include "hid.h"

#define PAYLOAD_ADDR	0x24F00000

#include "fs.h"
#include "chain.h"

void load_and_run() {
	memcpy((void*)PAYLOAD_ADDR, chain_bin, chain_bin_len);
	((void(*)(void))PAYLOAD_ADDR)();
}

int main(){
	mountSDMC();
	if (*(vu8 *)0x10010000 == 0 && !checkAnyDown()) // check if this is a coldboot and no keys are held
		drawBootScreen();
	load_and_run();
	return 0;
}
