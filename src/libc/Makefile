.PHONY: all clean
.SUFFIXES: .o .c .S

INCLUDES := $(addprefix -I,include)
DEFINES := -D__is_kernel -D__is_libk
CPPFLAGS += $(DEBUG) $(DEFINES) $(INCLUDES)
CFLAGS += -Wall -Wextra -ffreestanding

OBJS := $(patsubst %.c, %.o, $(wildcard *.c) $(wildcard */*.c))

all: libk.a

%.o:%.c
	$(CC) -MD -c -std=c99 $(CFLAGS) $(CPPFLAGS) -o $@ $<
	$(CC) -S -std=c99 $(CFLAGS) $(CPPFLAGS) -o $@.$(GEN_ASM_SUFFIX) $<

build: install-libs

libk.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

install: install-headers install-libs

install-libs: libk.a
	mkdir -p $(SYSROOT)/$(LIB_DIR)
	cp -R --preserve=timestamps $^ $(SYSROOT)/$(LIB_DIR)/.

install-headers:
	mkdir -p $(SYSROOT)/$(INC_DIR)
	cp -R --preserve=timestamps include/* $(SYSROOT)/$(INC_DIR)/.

clean:
	rm -rf *.a $(OBJS) $(OBJS:.o=.d) $(addsuffix .$(GEN_ASM_SUFFIX),$(OBJS))

-include $(LOCAL_OBJS:.o=.d)
