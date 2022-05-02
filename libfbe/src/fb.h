#ifndef FB_H_
#define FB_H_

#include <stdlib.h>
typedef struct framebuffer {
    // Framebuffer file descriptor
    int fd;
    // Pointer to framebuffer (memory mapped)
    char* fb;
    // Framebuffer size and bits/pixel
    int width, height, bpp;
} framebuffer_t;

extern framebuffer_t *create_framebuffer();
extern void free_framebuffer(framebuffer_t *fb);
extern void set_pixel(framebuffer_t *fb, int x, int y, int color);
extern void draw_line(framebuffer_t *fb, int sx, int sy, int ex, int ey, int color);
extern void draw_quad(framebuffer_t *fb, int x, int y, int width, int height, int color);

#endif // FB_H_
