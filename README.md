# BootAnim9
Custom boot animations for A9LH

# How to install
Compile with 'make' and copy the resulting arm9loaderhax.bin to your SD card root directory.
Generate your custom animation(s) and copy it/them to your SD card root as /anim/top and /anim/bot

After displaying the animations, it will load and launch a payload from /anim/boot/{button}.bin where {button} is what you held.

# How to generate a custom animation
This process ***requires*** **ffmpeg** with the "transpose" video filter and an animated image with size 400x240 or 320x240.

You can use this command to scale a file, and perform needed operations (as an example):
>ffmpeg -an -i "gif filename" -r 30 -pix_fmt bgr24 -vf "scale=400x240,transpose=1" output.rgb

>*Framerate is recommended to be between 5 and 30, and both animations must have* ***the same framerate***

Copy the resulting output.rgb to /anim/top or /anim/bot, and modify the value in /anim/fps for the set framerate.

Please note that if you want to create a bottom screen animation, you have to use a 320x240 image instead of 400x240. The bottom screen is smaller.

## How to set the framerate

Inside the anim directory there should be a 'fps' file. The sole purpose of this file is to indicate the framerate of the animations, and you have to indicate it in hex.
For example, if your framerate is 15, then the only char in 'config' should be 0x0F (or ASCII char 15). An easy way to do this for linux users is the shell builtin printf: `printf '%c' 15 > fps`

In the case that you currently don't have the 'xxd' utility (you should tho) you can use 'bin2c', however some changes will be required.

## About this branch

This is the land of unstable shit. Tread with caution - I use most of this myself. It should be safe, but no warranty (what warranty?) etc etc.

There's multiple changes in this branch, the most obvious being takeover of BootCTR9/CtrBootManager9's job. It's only capable of loading bin files.

The other major change here is that all functionality has been moved to stage2, and stage1 has been replaced with a stub. This means payloads load near instantly after aborting via button.

Aside from this, filenames for animations were changed to personal taste. This will hopefully become irrelevant once I get some form of config working.

Not the official branch. If you intend to use this, don't report bugs to Wolfvak - chances are it's because you chose to use something unstable rather than the well-tested official release.

## Credits

b1l1s for his ctr library and fs functions.
dark-samus and AuroraWright for the chainloader.
chaoskagami for better code overall and TheBaloneyBoy for ability to skip animations.

### Yes, the files are expected to be big, because they're RAW dumps.
