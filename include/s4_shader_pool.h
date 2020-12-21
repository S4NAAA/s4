#ifndef S4_SHADER_H
#define S4_SHADER_H

#ifdef __cplusplus
extern "C" {
#endif

#define S4_SHADER_INFO_POOL_MAX 1
#define S4_SHADER_POOL_MAX 2

#include "s4_common.h"

struct s4_shader_code_info {
  const char *vertex_code;
  const char *geometry_code;
  const char *fragment_code;
};

struct s4_shader_layout_info {
  const unsigned int *const layout;
  const unsigned int layout_size;
};

struct s4_shader_pool_info {
  const struct s4_shader_code_info shader_code[S4_SHADER_INFO_POOL_MAX];
  const struct s4_shader_layout_info shader_layout[S4_SHADER_INFO_POOL_MAX];
};

struct s4_shader_pool {
  unsigned int shaders[S4_SHADER_POOL_MAX];
};

extern unsigned int s4_shader_pool_get_shader_layout_size(
    unsigned int shader_type);

extern const unsigned int *s4_shader_pool_get_shader_layout(
    unsigned int shader_type);

extern unsigned int s4_shader_pool_load_shader(unsigned int shader_type);
extern void s4_shader_pool_use_shader(unsigned int i);
extern void s4_shader_pool_delete_shader(unsigned int i);
extern void s4_shader_pool_uniform_matrix4fv(const char *name, s4_matrix4f m,
                                             unsigned int i);
extern void s4_shader_pool_uniform1i(const char *name, int v, unsigned int i);
extern void s4_shader_pool_uniform2f(const char *name, float v1, float v2,
                                     unsigned int i);

#ifdef __cplusplus
}
#endif
#endif
