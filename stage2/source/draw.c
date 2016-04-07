#include "main.h"

void clear_color(uint8_t b, uint8_t g, uint8_t r) {
	uint8_t* copy_top = FBS->top_left;
	uint8_t* copy_bot = FBS->bottom;

	while(copy_top < (FBS->top_left + TOP_FB_SZ)) {
		*copy_top++ = b;
		*copy_top++ = g;
		*copy_top++ = r;
	}
	while(copy_bot < (FBS->bottom   + BOT_FB_SZ)) {
		*copy_bot++ = b;
		*copy_bot++ = g;
		*copy_bot++ = r;
	}
}

void draw_image_top(uint8_t* image) {
	memcpy(FBS->top_left, image, 400*240*3);
}

void draw_image_bot(uint8_t* image) {
	memcpy(FBS->bottom, image, 320*240*3);
}
