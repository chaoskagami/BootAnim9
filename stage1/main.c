#include "chain.h"

#define	PAYLOAD_ADDR    0x24F00000

void main() {
	for(unsigned int i = 0; i < chain_bin_len; i++)
		((unsigned char*)PAYLOAD_ADDR)[i] = chain_bin[i];

	((void(*)(void))PAYLOAD_ADDR)();
}
