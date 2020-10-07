#include "s4_input.h"

void s4_input_update(struct s4_window *window, struct s4_input *input) {
  glfwGetCursorPos(window->gl_data, &input->x_cursor_pos, &input->y_cursor_pos);
  input->esc_state = glfwGetKey(window->gl_data, GLFW_KEY_ESCAPE);
}
