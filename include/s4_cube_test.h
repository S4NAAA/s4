#ifndef S4_CUBE_TEST_H
#define S4_CUBE_TEST_H

static unsigned int s_s4_cube_test_layout[] = {3, 2};

static float s_s4_cube_test_vertices[] = {
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

static unsigned int s_s4_cube_test_indices[] = {
    0,  1,  2,  2,  3,  0,  4,  5,  6,  6,  7,  4,  8,  9,  10, 10, 11, 8,
    12, 13, 14, 14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20};

#endif