#ifndef __MAIN_H
#define __MAIN_H

#include "fatfs/ff.h"
#include <stdint.h>

struct framebuffer_t { // Thanks to mid-kid for the framebuffer structure
    unsigned char *top_left;
    unsigned char *top_right;
    unsigned char *bottom;
};
#define FBS ((struct framebuffer_t *)0x23FFFE00)
// Keep in mind the 3DS' screens are flipped, e.g. they're 240x400, not 400x240.

#define TOP_FB_SZ (400*240*3)
#define BOT_FB_SZ (320*240*3)

#define PAYLOAD_ADDRESS	0x23F00000

#define PB(a) "/anim/boot/" a ".bin"

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

#define BUTTON_ANY      0xffff

#define HID_PAD         ((*(volatile uint32_t *)0x10146000) ^ BUTTON_ANY)

void  clear_color    (uint8_t b,  uint8_t g,  uint8_t r);
int   f_exists       (char * f_path);
char* getPayloadName ();
void draw_image_top(uint8_t* image);
void draw_image_bot(uint8_t* image);
void memcpy(void *dest,        void *src,     uint32_t size);
void memset(void *destination, uint32_t data, uint32_t len);

#endif
