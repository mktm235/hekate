ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/base_rules

TARGET := libsys_lp0
BUILD := ../../build/$(TARGET)
OUTPUT := ../../output
BDKDIR := bdk
BDKINC := -I../../$(BDKDIR)

OBJS = $(addprefix $(BUILD)/,\
	sys_sdramlp0.o \
)

ARCH := -march=armv4t -mtune=arm7tdmi -mthumb-interwork
CFLAGS = $(ARCH) -O2 -nostdlib -fpie -ffunction-sections -fdata-sections -fomit-frame-pointer -std=gnu11 -Wall -Wsign-compare $(CUSTOMDEFINES)
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
