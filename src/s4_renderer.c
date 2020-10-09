#include "s4_renderer.h"

static void s_s4_framebuffer_callback(GLFWwindow *window, int width,
                                      int height);

int s4_renderer_init(unsigned int width, unsigned int height, const char *title,
                     struct s4_window *window) {
  if (!glfwInit()) {
    printf("Failed to initialize GLFW\n");
    return 0;
  }

  window->gl_data = NULL;
  window->width = width;
  window->height = height;
  /* vvv idk if this is valid vvv */
  window->title = title;
  /* ^^^      prob not        ^^^ */

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window->gl_data = glfwCreateWindow(window->width, window->height,
                                     window->title, NULL, NULL);

  glfwMakeContextCurrent(window->gl_data);

  if (window->gl_data == NULL) {
    printf("Failed to initialize GLFW window\n");
    goto failed_loading;
  }

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    goto failed_loading;
  }

  glfwSetFramebufferSizeCallback(window->gl_data, s_s4_framebuffer_callback);
  glEnable(GL_DEPTH_TEST);

  return 1;

failed_loading:
  glfwTerminate();
  return 0;
}

void s4_renderer_load_shader(unsigned int vertex_shader,
                             unsigned int fragment_shader,
                             unsigned int *program) {
  int success;
  char log[512];
  const char *code;
  unsigned int vertex, fragment;

  success = 0;

  switch (vertex_shader) {
    case S4_SHADERS_VERTEX_1:
      code = S4_SHADERS_VERTEX_CODE_1;
      break;
    case S4_SHADERS_VERTEX_2:
      code = S4_SHADERS_VERTEX_CODE_2;
      break;
    default:
      goto fail_vertex;
  }

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &code, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, &log[0]);
    printf("ERROR::VERTEX::SHADER::COMPILATION_FAILED: %s\n", log);
    goto fail_vertex;
  }

  switch (fragment_shader) {
    case S4_SHADERS_FRAGMENT_1:
      code = S4_SHADERS_FRAGMENT_CODE_1;
      break;
    default:
      goto fail_fragment;
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &code, NULL);
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
  return;
}

void s4_renderer_load_texture(const char *path, unsigned int *id) {
  unsigned int error, width, height;
  unsigned char *image;

  error = lodepng_decode32_file(&image, &width, &height, path);

  if (error) {
    printf("Failed loading image at path: %s\nLodePNG error %u: %s\n", path,
           error, lodepng_error_text(error));
    return;
  }

  glGenTextures(1, id);
  glBindTexture(GL_TEXTURE_2D, *id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);
  free(image);
}

void s4_renderer_draw(struct s4_vertex_object_data *data) {
  glBindVertexArray(data->vao);
  glDrawArrays(data->mode, 0, data->vertices_size);
}

void s4_renderer_load_vertex_data(unsigned int draw_type, unsigned int mode,
                                  float *vertices, unsigned int vertices_size,
                                  unsigned int *sizes, unsigned int sizes_size,
                                  struct s4_vertex_object_data *data) {
  unsigned int i, slice_size, offset, slice_char_size;

  slice_size = 0;

  for (i = 0; i < sizes_size; ++i) slice_size += sizes[i];

  data->vertices_size = vertices_size / slice_size;
  data->slice_size = slice_size;
  data->mode = mode;

  glGenVertexArrays(1, &data->vao);
  glGenBuffers(1, &data->vbo);

  glBindVertexArray(data->vao);
  glBindBuffer(GL_ARRAY_BUFFER, data->vbo);

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
}

void s4_renderer_free_vertex_data(struct s4_vertex_object_data *data) {
  glDeleteVertexArrays(1, &data->vao);
  glDeleteBuffers(1, &data->vbo);
}

static void s_s4_framebuffer_callback(GLFWwindow *window, int width,
                                      int height) {
  (void)window;
  glViewport(0, 0, width, height);
}
