#include <stddef.h>
#include <stdint.h>

#include "fatfs/ff.h"

struct framebuffer_t { // Thanks to mid-kid for the framebuffer structure
    unsigned char *top_left;
    unsigned char *top_right;
    unsigned char *bottom;
};
#define FBS ((struct framebuffer_t *)0x23FFFE00)

typedef uint8_t		uint8;
typedef uint16_t	uint16;
typedef uint32_t	uint32;
typedef uint64_t	uint64;

typedef float		float32;
typedef double		float64;

typedef uint8_t		u8;
typedef uint16_t	u16;
typedef uint32_t	u32;
typedef uint64_t	u64;

typedef volatile u8          vu8;
typedef volatile u16         vu16;
typedef volatile u32         vu32;
typedef volatile u64         vu64;

#define TOP_FB_SZ (240*400*3)
#define BOT_FB_SZ (240*320*3)

#define B_A        (1 << 0)
#define B_B        (1 << 1)
#define B_SL       (1 << 2)
#define B_ST       (1 << 3)
#define B_RI       (1 << 4)
#define B_LE       (1 << 5)
#define B_UP       (1 << 6)
#define B_DO       (1 << 7)
#define B_R        (1 << 8)
#define B_L        (1 << 9)
#define B_X        (1 << 10)
#define B_Y        (1 << 11)

#define BUTTON_ANY      0xFFF

#define HID_PAD         ((*(volatile uint32_t *)0x10146000) ^ BUTTON_ANY)

#define max(a, b) \
	(((a) > (b)) ? (a) : (b))

void animationLoop();
u32 mountSDMC(void);
u32 fileSize(const char *path);
void memcpy(void *dest, void *src, u32 size);
void memset(void *destination, u32 data, u32 len);
void clear_color(u8 b, u8 g, u8 r);
