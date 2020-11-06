#include "s4_vertex_object_pool.h"

static struct s4_vertex_object_pool s_s4_global_vertex_object_pool;

static unsigned int s_s4_global_current_vertex_object_pool_size = 0;

unsigned int s4_vertex_object_pool_add(
    unsigned int draw_type, unsigned int mode, float *vertices,
    unsigned int vertices_size, unsigned int *indices,
    unsigned int indices_size, unsigned int *layout, unsigned int layout_size) {
  unsigned int i, slice_size, offset, slice_char_size, pos;

  struct s4_vertex_object_draw_info *draw_info;
  struct s4_vertex_object_buffer_info *buffer_info;

  assert(s_s4_global_current_vertex_object_pool_size <
         S4_VERTEX_OBJECT_POOL_MAX);

  pos = ++s_s4_global_current_vertex_object_pool_size;

  draw_info = &s_s4_global_vertex_object_pool.draw_info[pos];
  buffer_info = &s_s4_global_vertex_object_pool.buffer_info[pos];

  draw_info->indices_size = indices_size;
  draw_info->mode = mode;

  slice_size = 0;
  for (i = 0; i < layout_size; ++i) slice_size += layout[i];

  glGenVertexArrays(1, &draw_info->vao);
  glGenBuffers(1, &draw_info->ebo);
  glGenBuffers(1, &buffer_info->vbo);

  glBindVertexArray(draw_info->vao);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_info->vbo);

  glBufferData(GL_ARRAY_BUFFER, vertices_size * sizeof(float), vertices,
               draw_type);

  offset = 0;
  slice_char_size = slice_size * sizeof(float);
  for (i = 0; i < layout_size; ++i) {
    glVertexAttribPointer(i, layout[i], GL_FLOAT, GL_FALSE, slice_char_size,
                          (void *)(offset * sizeof(float)));

    glEnableVertexAttribArray(i);
    offset += layout[i];
  }

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, draw_info->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size * sizeof(float), indices,
               draw_type);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  return pos;
}

/*
 * TODO: make update functions
 */

void s4_vertex_object_pool_draw(unsigned int i) {
  const struct s4_vertex_object_draw_info *draw_info =
      &s_s4_global_vertex_object_pool.draw_info[i];

  glBindVertexArray(draw_info->vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, draw_info->ebo);

  glDrawElements(draw_info->mode, draw_info->indices_size, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void s4_vertex_object_pool_draw_all(void) {
  unsigned int i, size;

  size = s_s4_global_current_vertex_object_pool_size;

  for (i = 0; i < size; ++i) {
    const struct s4_vertex_object_draw_info *draw_info =
        &s_s4_global_vertex_object_pool.draw_info[i];

    glBindVertexArray(draw_info->vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, draw_info->ebo);

    glDrawElements(draw_info->mode, draw_info->indices_size, GL_UNSIGNED_INT,
                   0);
  }

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/*
 * FIXME: Make a proper delete implementation
 */

void s4_vertex_object_pool_delete(unsigned int i) {
  struct s4_vertex_object_draw_info *draw_info =
      &s_s4_global_vertex_object_pool.draw_info[i];

  struct s4_vertex_object_buffer_info *buffer_info =
      &s_s4_global_vertex_object_pool.buffer_info[i];

  glDeleteVertexArrays(1, &draw_info->vao);
  glDeleteBuffers(1, &draw_info->ebo);
  glDeleteBuffers(1, &buffer_info->vbo);
}

void s4_vertex_object_pool_delete_all(void) {
  unsigned int i, size;

  size = s_s4_global_current_vertex_object_pool_size;

  for (i = 0; i < size; ++i) s4_vertex_object_pool_delete(i);
}
