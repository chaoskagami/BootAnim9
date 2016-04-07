#include "main.h"

void delay(u32 n) {
	u32 i = n; while (i--) __asm("andeq r0, r0, r0"); // ASM NOP(e), supposed to delay animation
}

int read_config(char* buffer) {
	/* TODO - actually parse like a config file rather than dumb string reading
              strtok will be handy for this */

	FIL config;
	unsigned int sink;

	if(f_open(&config, "/anim/config.txt", FA_READ)) {
		// Open failed. Return 0.
		return 0;
	}

	u32 size = min(f_size(&config), 4096);

	memset(buffer, 0, 4096);

	f_read(&config, buffer, size, &sink);

	f_close(&config);

	// One last fixup - get rid of any \r and \n
	for(int i=0; buffer[i] != 0; i++) {
		if (buffer[i] == '\n' || buffer[i] == '\r') {
			buffer[i] = '\0';
			break;
		}
	}
	return 1;
}

void animationLoop() {
	FIL bgr_anim_bot, bgr_anim_top;

	char fps_anim[4096]    = "/anim/"; // 4096 is okay here, since MAX_PATH is 4096 on Fat32.
	char top_anim[4096]    = "/anim/";
	char bottom_anim[4096] = "/anim/";
	char buffer[4096];

	if (!read_config(buffer)) {
		// Couldn't load configuration, time to bounce.
		return;
	}

	strcat(fps_anim, buffer);
	strcat(top_anim, buffer);
	strcat(bottom_anim, buffer);

	strcat(fps_anim,    "/fps");
	strcat(top_anim,    "/top");
	strcat(bottom_anim, "/bot");

	u8 rate = 15; // Default, overridden by config
	u32	topAnimSize = 0, topFrames = 0,	bottomAnimSize = 0,	bottomFrames = 0, configSize = 0;
	unsigned int sink = 0;

	clear_color(0, 0, 0); // Clear to black

	topAnimSize 	= fileSize(top_anim);    // get top screen animation size
	bottomAnimSize 	= fileSize(bottom_anim); // get bottom screen animation size
	configSize 	    = fileSize(fps_anim);

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
		f_open(&config_fil, fps_anim, FA_READ);
		f_read(&config_fil, &rate, 1, &sink); // Someone could create an invalid config.
		f_close(&config_fil);
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
	// FIXME - f_close plxkthxbaiwhatever
}
