#include "s4_common.h"
#include "s4_input.h"
#include "s4_math.h"
#include "s4_renderer.h"
#include "s4_vertex_object_pool.h"

/*
 * TODO: Make a good example when the vertex object pool system is done
 */

int main(void) {
  int step;
  unsigned int vo;
  unsigned int program, texture;
  s4_vector3f up;
  s4_vector3f rot_axis;
  s4_vector3f pos;
  s4_vector3f center;
  s4_matrix4f projection;
  s4_matrix4f view;
  s4_matrix4f model;
  struct s4_input input;
  struct s4_window window;

  unsigned int layout[] = {3, 2};

  float vertices[] = {
      /* clang-format off */
/*   |   vertex position  |  texture  |
*    |  x      y      z   |  x     y  | */
      -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
       0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 

      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 
      -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 

      -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
      -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 

       0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
       0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 

      -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
       0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
       0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 
      -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 

      -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 
       0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f,  0.5f,  0.5f,  0.0f, 0.0f};
  /* clang-format on */

  unsigned int indices[] = {0,  1,  2,  2,  3,  0,  4,  5,  6,  6,  7,  4,
                            8,  9,  10, 10, 11, 8,  12, 13, 14, 14, 15, 12,
                            16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20};

  s4_math_vector3_set(0.0f, 1.0f, 0.0f, up);
  s4_math_vector3_set(0.0f, 0.0f, -1.0f, center);
  s4_math_vector3_set(1.412f, 0.0f, 1.412f, rot_axis);
  s4_math_vector3_set(0.0f, 0.0, 3.0f, pos);

  if (!s4_renderer_init(600, 600, "STAN LOONA", &window)) {
    printf("Couldn't initialize renderer\n");
    return 0;
  }

  s4_math_perspective(
      s4_math_deg_to_rad(90.0f), (float)window.width / (float)window.height,
      S4_COMMON_DEFAULT_NEAR, S4_COMMON_DEFAULT_NEAR + 100, projection);


  s4_math_look(pos, center, up, view);

  s4_math_matrix4f_identity(model);

  s4_renderer_load_shader(1, 1, &program);

  vo = s4_vertex_object_pool_add(GL_STATIC_DRAW, GL_TRIANGLES, vertices,
                                 sizeof(vertices) / sizeof(vertices[0]),
                                 indices, sizeof(indices) / sizeof(indices[0]),
                                 layout, sizeof(layout) / sizeof(layout[0]));

  s4_renderer_load_texture("../../sprites/chaeyoung.png", &texture);

  glUseProgram(program);
  glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE,
                     &projection[0][0]);

  glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE,
                     &view[0][0]);

  glUniform1i(glGetUniformLocation(program, "tex"), 0);
  glUniform2f(glGetUniformLocation(program, "tex_offset"), 0.0f, 0.0f);

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

    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE,
                       &model[0][0]);

    s4_vertex_object_pool_draw(vo);

    glfwSwapBuffers(window.gl_data);
    glfwPollEvents();
  }

  s4_vertex_object_pool_delete(vo);
  glDeleteProgram(program);
  glDeleteTextures(1, &texture);
  glfwTerminate();

  return 0;
}
