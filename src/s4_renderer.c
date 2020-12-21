#include "s4_renderer.h"

#include <stdlib.h>

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
  window->title = title;

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
  glfwSwapInterval(1);

  return 1;

failed_loading:
  glfwTerminate();
  return 0;
}

/*
 * TODO: Refactor method for the vertex object pool system
 */
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

static void s_s4_framebuffer_callback(GLFWwindow *window, int width,
                                      int height) {
  (void)window;
  glViewport(0, 0, width, height);
}
