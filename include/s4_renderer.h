#ifndef S4_RENDERER_H
#define S4_RENDERER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lodepng.h"
#include "s4_common.h"
#include "s4_shaders.h"

extern int s4_renderer_init(unsigned int width, unsigned int height,
                            const char *title, struct s4_window *window);

extern void s4_renderer_load_shader(unsigned int vertex_shader,
                                    unsigned int fragment_shader,
                                    unsigned int *program);

extern void s4_renderer_load_texture(const char *path, unsigned int *id);

#define S4_RENDERER_BACKGROUND_VERTICES                                        \
  {                                                                            \
    -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, \
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f,     \
        0.0f, 0.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f                             \
  }

#ifdef __cpluplus
}
#endif

#endif
