# herramientas
AS = as
CC = gcc
LD = ld

# flags
ASFLAGS = --32
#CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-pic -nostdlib -lgcc
CFLAGS = -m32 -ffreestanding -O0 -Wall -Wextra -fno-exceptions -fno-pic -nostdlib
LDFLAGS = -m elf_i386 -T src/boot/linker.ld -nostdlib

# directorios
BUILD_DIR = build
ISO_DIR = iso
SRC_DIR = src

# archivos fuente
BOOT_S = $(SRC_DIR)/boot/boot.s
CONWAY_C = $(SRC_DIR)/kernel/conway.c
KERNEL_C = $(SRC_DIR)/kernel/kernel.c
GRAPHICS_C = $(SRC_DIR)/kernel/graphics.c
LINKER_LD = $(SRC_DIR)/boot/linker.ld

# archivos objeto
BOOT_O = $(BUILD_DIR)/boot.o
KERNEL_O = $(BUILD_DIR)/kernel.o
GRAPHICS_O = $(BUILD_DIR)/graphics.o
CONWAY_O = $(BUILD_DIR)/conway.o

# kernel binario
KERNEL_BIN = $(ISO_DIR)/boot/kernel.bin

# ISO final
ISO_FILE = ConwayOS.iso

# target principal
all: $(ISO_FILE)

# crear directorios si no existen
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(ISO_DIR)/boot/grub:
	mkdir -p $(ISO_DIR)/boot/grub

# compilar boot.s
$(BOOT_O): $(BOOT_S) | $(BUILD_DIR)
	@echo "Compilando boot.s..."
	$(AS) $(ASFLAGS) $(BOOT_S) -o $(BOOT_O)
	@echo "boot.o creado"

# compilar kernel.c
$(KERNEL_O): $(KERNEL_C) | $(BUILD_DIR)
	@echo "Compilando kernel.c..."
	$(CC) $(CFLAGS) -c $(KERNEL_C) -o $(KERNEL_O)
	@echo "kernel.o creado"

# compilar graphics.c
$(GRAPHICS_O): $(GRAPHICS_C) | $(BUILD_DIR)
	@echo "Compilando graphics.c..."
	$(CC) $(CFLAGS) -c $(GRAPHICS_C) -o $(GRAPHICS_O)
	@echo "graphics.o creado"

# compilar conway.c
$(CONWAY_O): $(CONWAY_C) | $(BUILD_DIR)
	@echo "Compilando conway.c..."
	$(CC) $(CFLAGS) -c $(CONWAY_C) -o $(CONWAY_O)
	@echo "conway.o creado"

# enlazar kernel
$(KERNEL_BIN): $(BOOT_O) $(KERNEL_O) $(GRAPHICS_O) $(CONWAY_O) $(LINKER_LD) | $(ISO_DIR)/boot/grub
	@echo "Enlazando kernel..."
	$(LD) $(LDFLAGS) $(BOOT_O) $(KERNEL_O) $(CONWAY_O) $(GRAPHICS_O) -o $(KERNEL_BIN)
	@echo "kernel.bin creado"

# verificar que es un kernel multiboot vÃ¡lido
verify: $(KERNEL_BIN)
	@if grub-file --is-x86-multiboot $(KERNEL_BIN); then \
		echo "Kernel multiboot vÃ¡lido"; \
	else \
		echo "ERROR: Kernel NO es multiboot vÃ¡lido"; \
		exit 1; \
	fi

# crear ISO booteable
$(ISO_FILE): $(KERNEL_BIN) verify
	grub-mkrescue -o $(ISO_FILE) $(ISO_DIR)
	@echo ""
	@echo "=========================================="
	@echo " ISO creado correctamente: $(ISO_FILE)"
	@echo "=========================================="

# limpiar archivos generados
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(KERNEL_BIN)
	rm -f $(ISO_FILE)

# limpiar todo incluyendo directorios
distclean: clean
	rm -rf $(ISO_DIR)/boot

.PHONY: all clean distclean run debug verify