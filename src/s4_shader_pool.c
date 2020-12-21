#include "s4_shader_pool.h"

static struct s4_shader_pool s_s4_global_shader_pool;
static unsigned int s_s4_global_current_shader_pool_size = 0;

static const unsigned int s_s4_shader_pool_layout_0[] = {3, 2};

static struct s4_shader_pool_info s_s4_global_shader_pool_info = {
    .shader_code[0] =
        {.vertex_code = "#version 330 core\n"
                        "layout (location = 0) in vec3 vertex_position;\n"
                        "layout (location = 1) in vec2 in_texture_coord;\n"
                        "out vec2 out_texture_coord;\n"
                        "uniform mat4 model;\n"
                        "uniform mat4 view;\n"
                        "uniform mat4 projection;\n"
                        "void main()\n"
                        "{\n"
                        "gl_Position = projection * view * model * "
                        "vec4(vertex_position, 1.0f);\n"
                        "out_texture_coord = in_texture_coord;\n"
                        "}",

         .geometry_code = NULL,

         .fragment_code =
             "#version 330 core\n"
             "in vec2 out_texture_coord;\n"
             "out vec4 fragment_color;\n"
             "uniform vec2 tex_offset;\n"
             "uniform sampler2D tex;\n"
             "void main()\n"
             "{\n"
             "fragment_color = texture(tex, out_texture_coord + tex_offset);\n"
             "}"},
    .shader_layout[0] = {.layout = s_s4_shader_pool_layout_0,
                         .layout_size = sizeof(s_s4_shader_pool_layout_0) /
                                        sizeof(s_s4_shader_pool_layout_0[0])}};

unsigned int s4_shader_pool_get_shader_layout_size(unsigned int shader_type) {
  return s_s4_global_shader_pool_info.shader_layout[shader_type].layout_size;
}

const unsigned int *s4_shader_pool_get_shader_layout(unsigned int shader_type) {
  return s_s4_global_shader_pool_info.shader_layout[shader_type].layout;
}

unsigned int s4_shader_pool_load_shader(unsigned int shader_type) {
  int success;
  char log[512];
  unsigned int vertex, fragment, pos, *program;

  struct s4_shader_code_info shader_code =
      s_s4_global_shader_pool_info.shader_code[shader_type];

  assert(s_s4_global_current_shader_pool_size < S4_SHADER_POOL_MAX);

  pos = s_s4_global_current_shader_pool_size++;

  program = &s_s4_global_shader_pool.shaders[pos];

  success = 0;

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &shader_code.vertex_code, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, &log[0]);
    printf("ERROR::VERTEX::SHADER::COMPILATION_FAILED: %s\n", log);
    goto fail_vertex;
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &shader_code.fragment_code, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, &log[0]);
    printf("ERROR::FRAGMENT::SHADER::COMPILATION_FAILED: %s\n", log);
    goto fail_fragment;
  }

  *program = glCreateProgram();
  glAttachShader(*program, vertex);
  glAttachShader(*program, fragment);
  glLinkProgram(*program);
  glGetProgramiv(*program, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(*program, 512, NULL, &log[0]);
    printf("ERROR::SHADER::LINKING_FAILED: %s\n", log);
    goto cleanup;
  }

cleanup:
  glDeleteShader(fragment);
fail_fragment:
  glDeleteShader(vertex);
fail_vertex:
  return pos;
}

void s4_shader_pool_use_shader(unsigned int i) {
  glUseProgram(s_s4_global_shader_pool.shaders[i]);
}

/*
  Getto setup, uniform location will be stored in next implementations
*/

void s4_shader_pool_uniform_matrix4fv(const char *name, s4_matrix4f m,
                                      unsigned int i) {
  glUniformMatrix4fv(
      glGetUniformLocation(s_s4_global_shader_pool.shaders[i], name), 1,
      GL_FALSE, &m[0][0]);
}

void s4_shader_pool_uniform1i(const char *name, int v, unsigned int i) {
  glUniform1i(glGetUniformLocation(s_s4_global_shader_pool.shaders[i], name),
              v);
}

void s4_shader_pool_uniform2f(const char *name, float v1, float v2,
                               unsigned int i) {
  glUniform2f(glGetUniformLocation(s_s4_global_shader_pool.shaders[i], name),
              v1, v2);
}
