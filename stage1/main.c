#include "chain.h"

#define	PAYLOAD_ADDR    0x24F00000

// The only job of this function is to get stage2 running at
// PAYLOAD_ADDR - nothing more, nothing less. It needs no
// external dependencies.

// Eventually this will all disappear to start.s in favor
// of optimized assembly.

void main() {
	for(unsigned int i = 0; i < chain_bin_len; i++)
		((unsigned char*)PAYLOAD_ADDR)[i] = chain_bin[i];

	((void(*)(void))PAYLOAD_ADDR)();
}
