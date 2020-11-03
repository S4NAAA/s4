#include "s4_vertex_object_pool.h"

static struct s4_vertex_object_pool s_s4_global_vertex_object_pool;

static unsigned int s_s4_global_current_vertex_object_pool_size = 0;

unsigned int s4_vertex_object_pool_add(
    unsigned int draw_type, unsigned int mode, float *vertices,
    unsigned int vertices_size, unsigned int *indices,
    unsigned int indices_size, unsigned int *sizes, unsigned int sizes_size) {
  unsigned int i, slice_size, offset, slice_char_size;

  struct s4_vertex_object_draw_data *draw_data;
  struct s4_vertex_object_buffer_data *buffer_data;

  assert(s_s4_global_current_vertex_object_pool_size <
         S4_VERTEX_OBJECT_POOL_MAX);

  ++s_s4_global_current_vertex_object_pool_size;

  draw_data = &s_s4_global_vertex_object_pool
                   .draw_data[s_s4_global_current_vertex_object_pool_size - 1];

  buffer_data =
      &s_s4_global_vertex_object_pool
           .buffer_data[s_s4_global_current_vertex_object_pool_size - 1];

  draw_data->indices_size = indices_size;
  draw_data->mode = mode;

  slice_size = 0;
  for (i = 0; i < sizes_size; ++i) slice_size += sizes[i];

  buffer_data->slice_size = slice_size;

  glGenVertexArrays(1, &draw_data->vao);
  glGenBuffers(1, &draw_data->ebo);
  glGenBuffers(1, &buffer_data->vbo);

  glBindVertexArray(draw_data->vao);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_data->vbo);

  glBufferData(GL_ARRAY_BUFFER, vertices_size * sizeof(float), vertices,
               draw_type);

  offset = 0;
  slice_char_size = slice_size * sizeof(float);

  for (i = 0; i < sizes_size; ++i) {
    glVertexAttribPointer(i, sizes[i], GL_FLOAT, GL_FALSE, slice_char_size,
                          (void *)(offset * sizeof(float)));

    glEnableVertexAttribArray(i);
    offset += sizes[i];
  }

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, draw_data->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size * sizeof(float), indices,
               draw_type);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  return s_s4_global_current_vertex_object_pool_size - 1;
}

/*
 * TODO: make update functions
 */

void s4_vertex_object_pool_draw_all(void) {
  unsigned int i, size;

  size = s_s4_global_current_vertex_object_pool_size;

  for (i = 0; i < size; ++i) {
    const struct s4_vertex_object_draw_data *draw_data =
        &s_s4_global_vertex_object_pool.draw_data[i];

    glBindVertexArray(draw_data->vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, draw_data->ebo);

    /*printf("%u\n", draw_data->indices_size);*/

    glDrawElements(draw_data->mode, draw_data->indices_size, GL_UNSIGNED_INT,
                   0);
  }

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


/*
 * FIXME: Make a proper delete implementation
 */ 

static void s4_vertex_object_pool_delete(unsigned int i) {
  struct s4_vertex_object_draw_data *draw_data =
      &s_s4_global_vertex_object_pool.draw_data[i];

  struct s4_vertex_object_buffer_data *buffer_data = 
      &s_s4_global_vertex_object_pool.buffer_data[i];

  glDeleteVertexArrays(1, &draw_data->vao);
  glDeleteBuffers(1, &draw_data->ebo);
  glDeleteBuffers(1, &buffer_data->vbo);
}

void s4_vertex_object_pool_delete_all(void) {
  unsigned int i, size;

  size = s_s4_global_current_vertex_object_pool_size;

  for (i = 0; i < size; ++i)
    s4_vertex_object_pool_delete(i);
}


