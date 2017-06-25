# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC, FLAGS, CHECKSUM

.section .bss
.align 16
stack_bottom: # this label is not needed for now
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start:

    mov $stack_top, %esp

    call _init

    call kernel_main

    cli
1:  hlt
    jmp 1b

.size _start, . - _start
