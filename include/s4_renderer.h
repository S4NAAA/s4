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

xtern void s4_renderer_load_texture(const char *path, unsigned int *id);

extern void s4_renderer_draw(struct s4_vertex_object_data *data);

extern void s4_renderer_load_vertex_data(unsigned int draw_type,
                                         unsigned int mode, float *vertices,
                                         unsigned int vertices_size,
                                         unsigned int *sizes,
                                         unsigned int sizes_size,
                                         struct s4_vertex_object_data *data);

extern void s4_renderer_free_vertex_data(struct s4_vertex_object_data *data);

#define S4_RENDERER_BACKGROUND_STRIDE \
  { 3, 2 }

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
