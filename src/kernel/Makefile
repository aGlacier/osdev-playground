.PHONY: all clean
.SUFFIXES: .o .c .S

ARCH_DIR := arch
KERNEL_DIR := kernel

ARCH_OBJS := $(addprefix $(ARCH_DIR)/,boot.o tty.o uart.o)
KERNEL_OBJS := $(addprefix $(KERNEL_DIR)/,kernel.o)
OBJS := $(ARCH_OBJS) $(KERNEL_OBJS)

LINKER_SCRIPT := $(ARCH_DIR)/linker.ld
CRTI_OBJ := $(ARCH_DIR)/crti.o
CRTBEGIN_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ := $(ARCH_DIR)/crtn.o
OBJ_LINK_LIST := $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)
LOCAL_OBJS := $(CRTI_OBJ) $(OBJS) $(CRTN_OBJ)

INCLUDES := -isystem=
DEFINES := -D__is_kernel
CPPFLAGS += $(DEBUG) $(DEFINES) $(INCUDES)
CFLAGS += -Wall -Wextra -ffreestanding
LIBS += -nostdlib -lk -lgcc

all build: $(OS_NAME).kernel

%.o:%.c
	$(CC) -MD -c -std=gnu99 $(CFLAGS) $(CPPFLAGS) -o $@ $<
	$(CC) -S -std=gnu99 $(CFLAGS) $(CPPFLAGS) -o $@.$(GEN_ASM_SUFFIX) $<

%.o:%.S
	$(CC) -MD -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

$(OS_NAME).kernel: $(OBJ_LINK_LIST) $(LINKER_SCRIPT)
	$(CC) -T $(LINKER_SCRIPT) -o $@ $(OBJ_LINK_LIST) $(LIBS)
	grub-file --is-x86-multiboot $@

install: install-headers

install-headers:
	mkdir -p $(SYSROOT)/$(INC_DIR)
	cp -R --preserve=timestamps include/* $(SYSROOT)/$(INC_DIR)/.

clean:
	rm -f $(OBJS) $(LOCAL_OBJS) $(OS_NAME).kernel $(LOCAL_OBJS:.o=.d)
	rm -f $(addsuffix .$(GEN_ASM_SUFFIX), $(LOCAL_OBJS))

-include $(LOCAL_OBJS:.o=.d)
