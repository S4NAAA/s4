#ifndef S4_VERTEX_OBJECT_POOL_H
#define S4_VERTEX_OBJECT_POOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "s4_common.h"

#define S4_VERTEX_OBJECT_POOL_MAX 32

struct s4_vertex_object_draw_info {
  unsigned int vao;
  unsigned int ebo;
  unsigned int indices_size;
  unsigned int mode;
};

struct s4_vertex_object_buffer_info {
  unsigned int vbo;
};

struct s4_vertex_object_pool {
  struct s4_vertex_object_draw_info draw_info[S4_VERTEX_OBJECT_POOL_MAX];
  struct s4_vertex_object_buffer_info buffer_info[S4_VERTEX_OBJECT_POOL_MAX];
  /*
   * TODO: add deleting and adding capabilities
   *
   * int states[S4_VERTEX_OBJECT_MAX];
   */
};

/*
 * FIXME: layout is shader dependent, prob should just be an static array,
 *        or be implementent in a shader dependent way
 */

extern unsigned int s4_vertex_object_pool_add(
    unsigned int draw_type, unsigned int mode, float *vertices,
    unsigned int vertices_size, unsigned int *indeces,
    unsigned int indices_size, unsigned int *layout, unsigned int layout_size);

extern void s4_vertex_object_pool_update_vertices(float *vertices,
                                                  unsigned int vertices_size,
                                                  unsigned int *layout,
                                                  unsigned int layout_size,
                                                  unsigned int i);

extern void s4_vertex_object_pool_update_indices(unsigned int *indices,
                                                 unsigned int indices_size,
                                                 unsigned int i);

extern void s4_vertex_object_pool_update_mode(unsigned int mode,
                                              unsigned int i);

extern void s4_vertex_object_pool_draw(unsigned int i);

extern void s4_vertex_object_pool_draw_all(void);

extern void s4_vertex_object_pool_delete(unsigned int i);

extern void s4_vertex_object_pool_delete_all(void);

#ifdef __cplusplus
}
#endif

#endif /* S4_VERTEX_OBJECT_POOL_H */
