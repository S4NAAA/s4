#include "s4_camera.h"
#include "s4_common.h"
#include "s4_debug.h"
#include "s4_input.h"
#include "s4_math.h"
#include "s4_player.h"
#include "s4_renderer.h"

int main(void) {
  int step;
  unsigned int program, texture;
  s4_vector3f model_pos;
  s4_vector3f rot_axis;
  s4_matrix4f proj;
  s4_matrix4f rot;
  s4_matrix4f model;
  struct s4_input input;
  struct s4_settings settings;
  struct s4_camera camera;
  struct s4_vertex_object_data vo;
  struct s4_window window;

  unsigned int sizes[] = {3, 2};

  float vertices[] = {
      /* clang-format off */
/*   |   vertex position  |  texture  |
*    |  x      y      z   |  x     y  | */
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

       0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f};
  /* clang-format on */

  if (!s4_renderer_init(600, 600, "STAN LOONA", &window)) {
    printf("Couldn't initialize renderer\n");
    return 0;
  }

  settings.fov = s4_math_deg_to_rad(90.0f);
  settings.width_ratio = 1.0f;
  settings.height_ratio = 1.0f;
  settings.render_distance = 100.0f;

  s4_math_vector3_set(0.0f, 1.0f, 0.0f, camera.up);
  s4_math_vector3_set(0.0f, 0.0f, 3.0f, camera.pos);
  s4_math_perspective(
      settings.fov, (float)settings.width_ratio / (float)settings.height_ratio,
      S4_COMMON_DEFAULT_NEAR, S4_COMMON_DEFAULT_NEAR + settings.render_distance,
      proj);

  s4_camera_look(0.0f, 0.0f, &camera);

  s4_renderer_load_shader(1, 1, &program);
  s4_renderer_load_vertex_data(GL_STATIC_DRAW, GL_TRIANGLES, vertices,
                               sizeof(vertices) / sizeof(vertices[0]), sizes,
                               sizeof(sizes) / sizeof(sizes[0]), &vo);
  s4_renderer_load_texture("../../sprites/chaeyoung.png", &texture);

  glUseProgram(program);
  glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE,
                     &proj[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE,
                     &camera.view[0][0]);
  glUniform1i(glGetUniformLocation(program, "tex"), 0);
  glUniform2f(glGetUniformLocation(program, "tex_offset"), 0.0f, 0.0f);

  s4_math_vector3_set(0.0f, 0.0f, 0.0f, model_pos);
  s4_math_vector3_set(0.3f, 0.2f, 0.4f, rot_axis);

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

    s4_math_vector3_set((0.03f * step), (0.02f * step), (0.04f * step),
                        rot_axis);
    s4_math_matrix4f_identity(model);
    s4_math_translate(model_pos, model);
    s4_math_make_rotate_matrix(step * 0.02f, rot_axis, rot);
    s4_math_mult_rotation(model, rot, model);

    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE,
                       &model[0][0]);

    s4_renderer_draw(&vo);

    glfwSwapBuffers(window.gl_data);
    glfwPollEvents();
  }

  s4_renderer_free_vertex_data(&vo);
  glDeleteProgram(program);
  glDeleteTextures(1, &texture);
  glfwTerminate();

  return 0;
}
