#include "fb.h"
#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

framebuffer_t *create_framebuffer()
{
    framebuffer_t *fbuf = malloc(sizeof(framebuffer_t));

    int fd = open("/dev/fb0", O_RDWR, S_IRUSR | S_IWUSR);

    if (fd >= 0) {
        struct fb_var_screeninfo vinfo;
        ioctl(fd, FBIOGET_VSCREENINFO, &vinfo);

        fbuf->fd = fd;
        fbuf->width = vinfo.xres;
        fbuf->height = vinfo.yres;
        fbuf->bpp = vinfo.bits_per_pixel;
        fbuf->fb = mmap(0, vinfo.xres * vinfo.yres * (vinfo.bits_per_pixel / 8), PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)0);
    }

    return fbuf;
}

void set_pixel(framebuffer_t *fb, int x, int y, int color) {
    int offset = (y * fb->width + x) * 4;
    char r = color >> 16;
    char g = (color >> 8) & 0xFF;
    char b = color & 0xFF;
    fb->fb[offset] = b;
    fb->fb[offset+1] = g;
    fb->fb[offset+2] = r;
    fb->fb[offset+3] = 0;
}

void draw_quad(framebuffer_t *fb, int x, int y, int width, int height, int color)
{
    for (int i=x; i < width; i ++) {
        for (int j=y; j < height; j++) {
            set_pixel(fb, i, j, color);
        }
    }
}

void draw_line(framebuffer_t *fb, int sx, int sy, int ex, int ey, int color) {
    int dx = ex - sx;
    int dy = ey - sy;
    int i1 = 2 * dy;
    int i2 = 2 * (dy - dx);
    int d = i1 - dx;

    int x, y, end_x;
    if (dx < 0) {
        x = ex;
        y = ey;
        end_x = sx;
    } else if (dx > 0) {
        x = sx;
        y = sy;
        end_x = ex;
    }

    set_pixel(fb, x, y, color);

    while (x < end_x) {
        if (d < 0) {
            d += i1;
        } else if (d >= 0) {
            d += i2;
            y += 1;
        }

        x += 1;

        set_pixel(fb, x, y, color);
    }
}

void free_framebuffer(framebuffer_t *fb)
{
    munmap(fb->fb, fb->width * fb->height * (fb->bpp / 8));
    close(fb->fd);
    free(fb);

}
