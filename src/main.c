#include "math.h"
#include "s4_common.h"
#include "s4_cube_test.h"
#include "s4_input.h"
#include "s4_math.h"
#include "s4_renderer.h"
#include "s4_shader_pool.h"
#include "s4_plot_test.h"
#include "s4_vertex_object_pool.h"

/*
 * TODO: Make a good example when the vertex object pool system is done
 *       Implement a proper projection-view-model system
 *       Implement a data orientet object system for visual objects
 *       Implement a shader system and fix shader pool with the new shader impl
 */

static float f(float x, float y) { return sinf(3.1 * (x * x + y * y)); }

int main(void) {
  int step;
  unsigned int vo, vo_cube;
  unsigned int shader, texture;
  s4_vector3f up;
  s4_vector3f rot_axis;
  s4_vector3f pos;
  s4_vector3f plot_pos;
  s4_vector3f center;
  s4_matrix4f projection;
  s4_matrix4f view;
  s4_matrix4f model;
  struct s4_input input;
  struct s4_window window;

  s4_math_vector3_set(0.0f, 1.0f, 0.0f, up);
  s4_math_vector3_set(0.0f, 0.0f, -2.0f, center);
  s4_math_vector3_set(1.412f, 0.0f, 1.412f, rot_axis);
  s4_math_vector3_set(0.0f, 0.0f, 3.0f, pos);
  s4_math_vector3_set(-0.5f, 0.7f, -0.5f, plot_pos);

  if (!s4_renderer_init(600, 600, "STAN LOONA", &window)) {
    printf("Couldn't initialize renderer\n");
    return 0;
  }

  s4_math_perspective(
      s4_math_deg_to_rad(90.0f), (float)window.width / (float)window.height,
      S4_COMMON_DEFAULT_NEAR, S4_COMMON_DEFAULT_NEAR + 100, projection);

  s4_math_look(pos, center, up, view);
  s4_math_matrix4f_identity(model);

  shader = s4_shader_pool_load_shader(0);

  vo = s4_plot_test_add_vertex_object(0, 1, 0, 1, 64, f);

  vo_cube = s4_vertex_object_pool_add(
      GL_STATIC_DRAW, GL_TRIANGLES, 0, s_s4_cube_test_vertices,
      sizeof(s_s4_cube_test_vertices) / sizeof(s_s4_cube_test_vertices[0]),
      s_s4_cube_test_indices,
      sizeof(s_s4_cube_test_indices) / sizeof(s_s4_cube_test_indices[0]));

  s4_renderer_load_texture("../../sprites/chaeyoung.png", &texture);

  s4_shader_pool_use_shader(shader);

  s4_shader_pool_uniform_matrix4fv("projection", projection, shader);
  s4_shader_pool_uniform_matrix4fv("view", view, shader);
  s4_shader_pool_uniform1i("tex", 0, shader);
  s4_shader_pool_uniform2f("tex_offset", 0.0f, 0.0f, shader);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  step = 0;

  while (!glfwWindowShouldClose(window.gl_data)) {
    ++step;
    s4_input_update(&window, &input);

    if (input.esc_state == GLFW_PRESS)
      glfwSetWindowShouldClose(window.gl_data, 1);

    /*glClearColor(0.0f, 0.0f, 0.0f, 1.0f);*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    s4_math_make_rotate_matrix(step * 0.02f, rot_axis, model);
    s4_math_translate(plot_pos, model);
    s4_shader_pool_uniform_matrix4fv("model", model, shader);
    s4_vertex_object_pool_draw(vo);
    s4_shader_pool_uniform_matrix4fv("model", model, shader);
    s4_vertex_object_pool_draw(vo_cube);

    glfwSwapBuffers(window.gl_data);
    glfwPollEvents();
  }

  s4_vertex_object_pool_delete(vo);
  s4_vertex_object_pool_delete(vo_cube);
  glDeleteTextures(1, &texture);
  glfwTerminate();

  return 0;
}
