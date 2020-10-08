#ifndef S4_MATH_H
#define S4_MATH_H

#ifdef __cplusplus
extern "C"
#endif

#include <math.h>

#include "s4_common.h"

#define S4_MATH_DEG_TO_RAD_CONSTANT 0.01745329252
#define S4_MATH_RAD_TO_DEG_CONSTANT 57.2957795131

#define s4_math_deg_to_rad(v) (v * S4_MATH_DEG_TO_RAD_CONSTANT)

#define s4_math_rad_to_deg(v) (v * S4_MATH_RAD_TO_DEG_CONSTANT)

#define s4_math_vector3_set(f0, f1, f2, out) \
  do {                                       \
    out[0] = f0;                             \
    out[1] = f1;                             \
    out[2] = f2;                             \
  } while (0)

#define s4_math_vector4_set(f0, f1, f2, f3, out) \
  do {                                           \
    out[0] = f0;                                 \
    out[1] = f1;                                 \
    out[2] = f2;                                 \
    out[3] = f3;                                 \
  } while (0)

#define s4_math_vector3_copy(in, out) \
  do {                                \
    out[0] = in[0];                   \
    out[1] = in[1];                   \
    out[2] = in[2];                   \
  } while (0)

#define s4_math_vector4_copy(in, out) \
  do {                                \
    out[0] = in[0];                   \
    out[1] = in[1];                   \
    out[2] = in[2];                   \
    out[3] = in[3];                   \
  } while (0)

#define s4_math_matrix3_copy(in, out) \
  do {                                \
    out[0][0] = in[0][0];             \
    out[0][1] = in[0][1];             \
    out[0][2] = in[0][2];             \
    out[1][0] = in[1][0];             \
    out[1][1] = in[1][1];             \
    out[1][2] = in[1][2];             \
    out[2][0] = in[2][0];             \
    out[2][1] = in[2][1];             \
    out[2][2] = in[2][2];             \
  } while (0)

#define s4_math_matrix4_copy(in, out) \
  do {                                \
    out[0][0] = in[0][0];             \
    out[0][1] = in[0][1];             \
    out[0][2] = in[0][2];             \
    out[0][3] = in[0][3];             \
    out[1][0] = in[1][0];             \
    out[1][1] = in[1][1];             \
    out[1][2] = in[1][2];             \
    out[1][3] = in[1][3];             \
    out[2][0] = in[2][0];             \
    out[2][1] = in[2][1];             \
    out[2][2] = in[2][2];             \
    out[2][3] = in[2][3];             \
    out[3][0] = in[3][0];             \
    out[3][1] = in[3][1];             \
    out[3][2] = in[3][2];             \
    out[3][3] = in[3][3];             \
  } while (0)

#define s4_math_vector3_dot(v1, v2) \
  v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]

    extern void
    s4_math_matrix4f_identity(s4_matrix4f out);

extern void s4_math_vector3f_scale(s4_vector3f v, float s, s4_vector3f out);

extern void s4_math_vector4f_scale(s4_vector4f v, float s, s4_vector3f out);

extern void s4_math_vector3f_add(s4_vector3f v1, s4_vector3f v2,
                                 s4_vector3f out);

extern void s4_math_vector4f_add(s4_vector4f v1, s4_vector4f v2,
                                 s4_vector4f out);

extern void s4_math_vector3f_sub(s4_vector3f v1, s4_vector3f v2,
                                 s4_vector3f out);
/*
 *extern float s4_math_vector3f_dot(s4_vector3f v1, s4_vector3f v2);
 */

extern void s4_math_vector3f_cross(s4_vector3f v1, s4_vector3f v2,
                                   s4_vector3f out);

extern float s4_math_vector3f_norm(s4_vector3f v);

extern void s4_math_vector3f_normalize(s4_vector3f v, s4_vector3f out);

extern void s4_math_vector3f_cross(s4_vector3f v1, s4_vector3f v2,
                                   s4_vector3f out);

extern void s4_math_matrix4f_mul_vector4f(s4_matrix4f m, s4_vector4f v,
                                          s4_vector4f out);

extern void s4_math_create_dir(float pitch, float yaw, s4_vector3f up,
                               s4_vector3f dir);

extern void s4_math_look(s4_vector3f eye, s4_vector3f dir, s4_vector3f up,
                         s4_matrix4f out);

extern void s4_math_look_at(s4_vector3f eye, s4_vector3f center, s4_vector3f up,
                            s4_matrix4f out);

extern void s4_math_perspective(float fov, float ratio, float near, float far,
                                s4_matrix4f out);

extern void s4_math_ortho(float left, float right, float bottom, float top,
                          float near, float far, s4_matrix4f out);

extern void s4_math_translate(s4_vector3f v, s4_matrix4f in_out);

extern void s4_math_make_rotate_matrix(float angle, s4_vector3f axis,
                                       s4_matrix4f out);

extern void s4_math_mult_rotation(s4_matrix4f m1, s4_matrix4f m2,
                                  s4_matrix4f out);

#ifdef __cplusplus
}
#endif

#endif
