# ==============================================================================
# AUTOMOTIVE EMBEDDED COMPILATION MAKEFILE (FIXED FOR 64-BIT COMPILER OVERFLOW)
# Supports output formats: .elf (debug), .hex (flash), .bin (binary), .exe (run)
# All comments and echo strings are written in English to prevent font encoding issues.
# ==============================================================================

CC = gcc
OBJCOPY = objcopy

# LINKER FLAGS CONFIGURATION
# -Wl,--image-base=0x400000 forces the application base address into lower 32-bit space.
# This ensures compatibility with the 32-bit Intel Hex format used by objcopy.
LDFLAGS = -Wl,--image-base=0x400000

CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Wconversion -g
INCLUDES = -Ican_demo

SRCS = can_demo/Can.c \
       can_demo/CanIf.c \
       can_demo/PduR.c \
       can_demo/Com.c \
       can_demo/Rte.c \
       can_demo/Swc.c \
       can_demo/main.c

OUTPUT_DIR = can_demo
TARGET_ELF = $(OUTPUT_DIR)/can_demo.elf
TARGET_HEX = $(OUTPUT_DIR)/can_demo.hex
TARGET_BIN = $(OUTPUT_DIR)/can_demo.bin
TARGET_EXE = $(OUTPUT_DIR)/can_demo.exe

all: $(TARGET_ELF) $(TARGET_HEX) $(TARGET_BIN) $(TARGET_EXE)

# STEP 1: LINKING PROCESS -> Generate the main .elf file (Used for Lauterbach Debugging)
$(TARGET_ELF): $(SRCS)
	@echo "==== [STEP 1] Compiling and Linking to generate ELF: $(TARGET_ELF) ===="
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(SRCS) -o $(TARGET_ELF)

# STEP 2: EXTRACT INTEL HEX FILE (For physical flash programmers)
$(TARGET_HEX): $(TARGET_ELF)
	@echo "==== [STEP 2] Automatically extracting Intel HEX structure ===="
	$(OBJCOPY) -O ihex $(TARGET_ELF) $(TARGET_HEX)

# STEP 3: EXTRACT RAW BINARY FILE (For binary flashing tools)
$(TARGET_BIN): $(TARGET_ELF)
	@echo "==== [STEP 3] Automatically extracting RAW Binary structure ===="
	$(OBJCOPY) -O binary $(TARGET_ELF) $(TARGET_BIN)

# STEP 4: GENERATE WINDOWS EXECUTABLE (Direct binary copy from .elf image)
$(TARGET_EXE): $(TARGET_ELF)
	@echo "==== [STEP 4] Generating local Windows executable .exe ===="
	@copy /Y $(TARGET_ELF) $(TARGET_EXE) >nul 2>&1 || cp $(TARGET_ELF) $(TARGET_EXE) >nul 2>&1 || exit 0

# TARGET TO RUN THE SIMULATION DIRECTLY
run: all
	@echo "==== [RUN] Executing the generated firmware simulation ===="
	@$(TARGET_EXE)

# TARGET TO CLEAN UP GENERATED OUTPUTS
clean:
	@echo "Cleaning up generated firmware outputs..."
	del /Q $(TARGET_ELF) 2>nul || exit 0
	del /Q $(TARGET_HEX) 2>nul || exit 0
	del /Q $(TARGET_BIN) 2>nul || exit 0
	del /Q $(TARGET_EXE) 2>nul || exit 0