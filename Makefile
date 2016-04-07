rwildcard = $(foreach d, $(wildcard $1*), $(filter $(subst *, %, $2), $d) $(call rwildcard, $d/, $2))

PATH := $(PATH):$(DEVKITARM)/bin

CC := arm-none-eabi-gcc
AS := arm-none-eabi-as
LD := arm-none-eabi-ld
OC := arm-none-eabi-objcopy

name := BootAnim9

dir_source := stage1
dir_data := data
dir_build := build

ASFLAGS := -mlittle-endian -mcpu=arm946e-s -march=armv5te
CFLAGS := -Wall -Wextra -MMD -MP -marm $(ASFLAGS) -fno-builtin -fshort-wchar -std=c11 -Wno-main -O2 -ffast-math

objects = $(patsubst $(dir_source)/%.s, $(dir_build)/%.o, \
			  $(patsubst $(dir_source)/%.c, $(dir_build)/%.o, \
			  $(call rwildcard, $(dir_source), *.s *.c)))

.PHONY: all
all: external arm9loaderhax.bin arm9payload.bin

.PHONY: clean
clean: external_clean
	@rm -rf $(dir_build) arm9loaderhax.bin arm9payload.bin $(dir_source)/chain.h

arm9loaderhax.bin: $(dir_build)/main.bin
	@cp -av $(dir_build)/main.bin $@

arm9payload.bin: $(dir_build)/main.bin
	@cp -av $(dir_build)/main.bin $@

$(dir_build)/main.bin: $(dir_build)/main.elf
	$(OC) -S -O binary $< $@

$(dir_build)/main.elf: $(objects)
	# FatFs requires libgcc for __aeabi_uidiv
	$(CC) -nostartfiles $(LDFLAGS) -T linker.ld $(OUTPUT_OPTION) $^

$(dir_build)/%.o: $(dir_source)/%.c
	@mkdir -p "$(@D)"
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(dir_build)/%.o: $(dir_source)/%.s
	@mkdir -p "$(@D)"
	$(COMPILE.s) $(OUTPUT_OPTION) $<

external:
	@make -C stage2
	@cp stage2/stage2.bin chain.bin
	@xxd -i chain.bin > $(dir_source)/chain.h
	@rm chain.bin

external_clean:
	@make -C stage2 clean

include $(call rwildcard, $(dir_build), *.d)
