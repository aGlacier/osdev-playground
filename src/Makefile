# Move to separate file
export OS_NAME := jjb-os
export SYSROOT := $(shell pwd)/sysroot
export INC_DIR := /usr/include
export LIB_DIR := /usr/lib
export CC := i686-elf-gcc --sysroot=$(SYSROOT) -isystem =$(INC_DIR)
export AR := i686-elf-ar
export READELF := i686-elf-readelf
export GEN_ASM_SUFFIX := asm.generated

export DEBUG=-O0 -g

GRUB_CFG := grub.cfg
QEMU_OPTS := -cpu core2duo
QEMU_DEBUG := -s -S

# This kind of targets requires preparation
all: prepare build

build clean install-headers:
	make -C libc $@
	make -C kernel $@

# This target should also generate appropriated files from templates:
#	- .gdbinit with proper binary name
#	- grub confii with proper binary name
prepare: install-headers

iso: kernel/$(OS_NAME).kernel grub/$(GRUB_CFG)
	mkdir -p isodir/boot/grub
	cp kernel/$(OS_NAME).kernel isodir/boot/
	cp grub/$(GRUB_CFG) isodir/boot/grub/$(GRUB_CFG)
	grub-mkrescue -o $(OS_NAME).iso isodir

qemu: kernel/$(OS_NAME).kernel
	qemu-system-i386 $(QEMU_OPTS) -kernel $<

qemu_debug: kernel/$(OS_NAME).kernel
	qemu-system-i386 $(QEMU_OPTS) $(QEMU_DEBUG) -kernel $<

qemu_curses: kernel/$(OS_NAME).kernel
	qemu-system-i386 $(QEMU_OPTS) -nographic -curses -kernel $<

qemu_debug_curses: kernel/$(OS_NAME).kernel
	qemu-system-i386 $(QEMU_OPTS) $(QEMU_DEBUG) -nographic -curses -kernel $<

qemu_cdrom: $(OS_NAME).iso
	qemu-system-i386 $(QEMU_OPTS) -cdrom $<

mrproper: clean
	rm -rf *.iso
	rm -rf isodir
	rm -rf $(SYSROOT)
