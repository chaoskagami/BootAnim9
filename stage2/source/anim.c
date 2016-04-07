#include "main.h"

void delay(u32 n) {
	u32 i = n; while (i--) __asm("andeq r0, r0, r0"); // ASM NOP(e), supposed to delay animation
}

void animationLoop() {
	FIL bgr_anim_bot, bgr_anim_top;

	char *config      = "/anim/fps";
	char *top_anim    = "/anim/top";
	char *bottom_anim = "/anim/bot"; // define file names

	u8 rate = 15; // Default, overridden by config
	u32	topAnimSize = 0, topFrames = 0,	bottomAnimSize = 0,	bottomFrames = 0, configSize = 0;
	unsigned int sink = 0;

	clear_color(0, 0, 0); // Clear to black

	topAnimSize 	= fileSize(top_anim);    // get top screen animation size
	bottomAnimSize 	= fileSize(bottom_anim); // get bottom screen animation size
	configSize 	    = fileSize(config);

	if (topAnimSize == 0 && bottomAnimSize == 0) return; // No animation, just chain already

	// No more 64MB check since we directly read to the framebuffer. It can be unbounded.
	if (topAnimSize)
		topFrames    = ((topAnimSize    - 1) / TOP_FB_SZ);    // get top screen frames
	if (bottomAnimSize)
		bottomFrames = ((bottomAnimSize - 1) / BOT_FB_SZ); // get bottom screen frames

	// Read the config if it exists, otherwise default to 15fps
	if (configSize)
	{
		FIL config_fil;
		f_open(&config_fil, config, FA_READ);
		f_read(&config_fil, &rate, 1, &sink); // Someone could create an invalid config.
	}

	if (topFrames > 0)
		f_open(&bgr_anim_top, top_anim, FA_READ);

	if (bottomFrames > 0)
		f_open(&bgr_anim_bot, bottom_anim, FA_READ);

	u32 maxFrames = max(topFrames, bottomFrames); // Get the maximum amount of frames between the two animations
	u32 delay_ = 0;

	if (rate <= 24) {
		delay_ = (6990480 / rate); // Need to take more accurate measurements, but this will do, it's quite a magic number
	}

	u32 delay__ = (delay_ / 2); // FIXME - THIS IS NOT OKAY. Hey, it's just a bad approximation, M'kay?

	for (u32 curframe = 0; curframe < maxFrames; curframe++) { // loop until the maximum amount of frames, increasing frame count by 1
		if (HID_PAD & BUTTON_ANY) // End the animation if any key is pressed
			break; // Okay, we don't want to draw the frame if the user held the button last frame, that's just silly

		if (topAnimSize != 0 && curframe < topFrames) { // if top animation exists and hasn't ended yet
			f_read(&bgr_anim_top, FBS->top_left, TOP_FB_SZ, &sink); // AKA write to the framebuffer directly.

			if (curframe <= bottomFrames)
				delay(delay__);
			else
				delay(delay_);
		}

		if (bottomAnimSize != 0 && curframe < bottomFrames) { // if bottom animation exists and hasn't ended yet
			f_read(&bgr_anim_bot, FBS->bottom, BOT_FB_SZ, &sink); // AKA write to the framebuffer directly.

			if (curframe <= topFrames) // check whether the top animation is playing
  				delay(delay__); // half the delay
  			else
  				delay(delay_); // whole delay
		}

		// THIS HAS BEEN PARTIALLY CALIBRATED
	}
	// No, I did not forget to f_close() the files. This (somehow) caused a bug that has been fixed by removing these calls
}
