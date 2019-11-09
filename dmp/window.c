#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>

uint32_t pix_col(uint8_t r, uint8_t g, uint8_t b, struct fb_var_screeninfo *vinfo)
{
	return (r<<vinfo->red.offset) | (g<<vinfo->green.offset) | (b<<vinfo->blue.offset);
}

int main()
{
	struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;

	int fb_fd = open("/dev/fb0", O_RDWR);
	if (fb_fd < 0)
	{
		printf("\033[31mError opening the device\n\033[0m");
		exit(1);
	}
	printf("\033[32mSucces opening the device\n\033[0m");
	if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo) > 0)
	{
		printf("\033[31mError getting 'V' Screen info\n\033[0m");
		exit(1);
	}
	printf("\033[32mSucces opening the device\n\033[0m");

	if (ioctl(fb_fd, FBIOGET_FSCREENINFO, &finfo) > 0)
	{
		printf("\033[31mError getting 'F' Screen info\n\033[0m");
		exit(1);
	}

	long screensize = vinfo.xres * vinfo.yres * (vinfo.bits_per_pixel / 8);
	printf("\033[33mScreensize %li \nylen: %u xlen: %u\nline_len: %u\n", screensize, vinfo.yres, vinfo.xres, finfo.line_length);

	char *fbp = (char *) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, (off_t) 0);
	if (fbp == NULL)
	{
		printf("\033[31m Frame buffer pointer NULL\n\033[0m");
		exit(1);
	}

	unsigned int x, y;

	for (x = 0; x < 300; x++)
	{
		for (y = 0; y < 300; y++)
		{
			long location = ((x + vinfo.xoffset) * (vinfo.bits_per_pixel / 8))
				+ ((y + vinfo.yoffset) * (finfo.line_length));


			*(fbp + location) = 100;
			*(fbp + location + 1) = 15 + (x - 100) / 2;
			*(fbp + location + 2) = 200 - (y - 100) / 5;
			*(fbp + location + 3) = 0;
		}
	}
	munmap(fbp, screensize);
	sleep(3);

	close(fb_fd);
	return (0);
}

/*			printf("location %li pix_col %lu x: %u y: %u\n", location, (unsigned long int) pix_col(0xFF, 0x00, 0xFF, &vinfo), x, y);*/
