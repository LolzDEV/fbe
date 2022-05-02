#include "../libfbe/src/fb.h"

int main(void)
{
   framebuffer_t *fb = create_framebuffer();

   draw_quad(fb, 6, 6, 400, 400, 0x00FF00);

   free_framebuffer(fb);

}
