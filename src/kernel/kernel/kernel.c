#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void)
{
	video_initialize();
	printf("kernel init\n");
}
