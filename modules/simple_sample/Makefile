ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/base_rules

TARGET := module_sample
BUILD := ../../build/$(TARGET)
OUTPUT := ../../output
SOURCEDIR = simple_sample
BDKDIR := bdk
BDKINC := -I../../$(BDKDIR)
VPATH = $(dir ./) $(dir $(wildcard ./*/))

OBJS = $(addprefix $(BUILD)/,\
	module_sample.o \
	gfx.o \
)

GFX_INC   := '"../modules/$(SOURCEDIR)/gfx/gfx.h"'

CUSTOMDEFINES := -DGFX_INC=$(GFX_INC)

ARCH := -march=armv4t -mtune=arm7tdmi -mthumb-interwork
CFLAGS = $(ARCH) -O2 -nostdlib -fpie -ffunction-sections -fdata-sections -fomit-frame-pointer -std=gnu11 -Wall $(CUSTOMDEFINES)
LDFLAGS = $(ARCH) -fpie -pie -nostartfiles -lgcc

.PHONY: clean all

all: $(TARGET).bso
$(BUILD)/%.o: ./%.c
	@mkdir -p "$(BUILD)"
	@$(CC) $(CFLAGS) $(BDKINC) -c $< -o $@

$(TARGET).bso: $(OBJS)
	@$(CC) $(LDFLAGS) -e _modInit $^ -o $(OUTPUT)/$(TARGET).bso
	@$(STRIP) -g $(OUTPUT)/$(TARGET).bso
	@echo  -e "-------------\nBuilt module: "$(TARGET)".bso\n-------------"

clean:
	@rm -rf $(OUTPUT)/$(TARGET).bso
