########################################
# STM8 Makefile
# wykys 2021
########################################

########################################
# Target
########################################
TARGET = firmware

########################################
# Building variables
########################################
# Compile for debugging?
# (1 ... yes, 0 ... no)
DEBUG = 1
# How to optimize the program?
# OPT = --opt-code-speed
OPT = --opt-code-size
# OPT = --opt-code-balanced

########################################
# Paths
########################################
# Build path
BUILD_DIR = build

########################################
# Sources
########################################
C_SOURCES = $(wildcard app/src/*.c)
# C_SOURCES += drivers/src/stm8s_adc2.c
# C_SOURCES += drivers/src/stm8s_awu.c
# C_SOURCES += drivers/src/stm8s_beep.c
# C_SOURCES += drivers/src/stm8s_can.c
C_SOURCES += drivers/src/stm8s_conf.c
C_SOURCES += drivers/src/stm8s_clk.c
# C_SOURCES += drivers/src/stm8s_exti.c
# C_SOURCES += drivers/src/stm8s_flash.c
C_SOURCES += drivers/src/stm8s_gpio.c
# C_SOURCES += drivers/src/stm8s_i2c.c
# C_SOURCES += drivers/src/stm8s_itc.c
# C_SOURCES += drivers/src/stm8s_iwdg.c
# C_SOURCES += drivers/src/stm8s_rst.c
# C_SOURCES += drivers/src/stm8s_spi.c
# C_SOURCES += drivers/src/stm8s_tim1.c
# C_SOURCES += drivers/src/stm8s_tim2.c
# C_SOURCES += drivers/src/stm8s_tim3.c
# C_SOURCES += drivers/src/stm8s_tim4.c
# C_SOURCES += drivers/src/stm8s_uart1.c
# C_SOURCES += drivers/src/stm8s_uart3.c
# C_SOURCES += drivers/src/stm8s_wwdg.c

########################################
# Tools
########################################

ifeq ($(findstring 2019, $(shell openocd --version 2>&1)), 2019)
    SWIM = stlink
else
    SWIM = stlink-dap
endif

OPENOCD = openocd -f interface/$(SWIM).cfg -f target/stm8s.cfg -f stm8s-flash.cfg

ifeq ($(OS),Windows_NT)
    SDCC_PATH = "/c/Program Files/SDCC"
else
    SDCC_PATH = /opt/sdcc
endif

CC = $(SDCC_PATH)/bin/sdcc

########################################
# Flags for compiler
########################################

# C defines
C_DEFS =                        \
-DSTM8S208                      \
-DF_CPU=16000000L               \
-DUSE_STDPERIPH_DRIVER

# C includes
C_INCLUDES =                    \
-Iapp/inc                       \
-Idrivers/inc

# Target architecture specification
MCU = -mstm8

CFLAGS = $(MCU) $(OPT) $(C_INCLUDES) $(C_DEFS)

ifeq ($(DEBUG), 1)
CFLAGS += --debug
endif

# Generate dependency information
CFLAGS += -MD

########################################
# Flags for linker
########################################
LIBS = -lstm8
LDFLAGS = $(MCU) $(OPT) $(LIBS)

# Default action: build all
all: $(BUILD_DIR)/$(TARGET).elf


########################################
# Build the application
########################################
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.rel)))
vpath %.c $(sort $(dir $(C_SOURCES)))

$(BUILD_DIR)/%.rel: %.c Makefile | $(BUILD_DIR)
	@$(CC) -o $@ $(CFLAGS) --out-fmt-elf -c $<

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@$(CC) -o $@ $(LDFLAGS) --out-fmt-elf $(OBJECTS) $(C_INCLUDES)

$(BUILD_DIR):
	@mkdir $@

########################################
# Clean up
########################################
clean:
	@rm -rf $(BUILD_DIR)/*

########################################
# Dependencies
########################################
-include $(wildcard $(BUILD_DIR)/*.d)

########################################
# Flash
########################################
flash:
	@$(OPENOCD) -c "init" -c "program_device $(BUILD_DIR)/$(TARGET).elf 0"
build_and_flash: all flash

########################################
# File-independent actions
########################################
.PHONY: clean flash build_and_flash
