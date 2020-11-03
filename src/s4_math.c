#include "s4_math.h"

void s4_math_matrix4f_identity(s4_matrix4f out) {
  out[0][0] = 1.0f;
  out[0][1] = 0.0f;
  out[0][2] = 0.0f;
  out[0][3] = 0.0f;

  out[1][0] = 0.0f;
  out[1][1] = 1.0f;
  out[1][2] = 0.0f;
  out[1][3] = 0.0f;

  out[2][0] = 0.0f;
  out[2][1] = 0.0f;
  out[2][2] = 1.0f;
  out[2][3] = 0.0f;

  out[3][0] = 0.0f;
  out[3][1] = 0.0f;
  out[3][2] = 0.0f;
  out[3][3] = 1.0f;
}
/*
void s4_math_vector3f_set( float f0, float f1, float f2,
        s4_vector3f out ) {
    out[ 0 ] = f0; out[ 1 ] = f1; out[ 2 ] = f2;
}

void s4_math_vector4f_set( float f0, float f1, float f2, float f3,
        s4_vector3f out ) {
    out[ 0 ] = f0; out[ 1 ] = f1; out[ 2 ] = f2;
    out[ 3 ] = f3;
}


void s4_math_vector3f_copy( s4_vector3f in, s4_vector3f out ) {
    out[ 0 ] = in[ 0 ]; out[ 1 ] = in[ 1 ]; out[ 2 ] = in[ 2 ];
    // memcpy( &in[ 0 ], &out[ 0 ], 3 * sizeof( float ) );
}

void s4_math_vector4f_copy( s4_vector4f in, s4_vector4f out ) {
    out[ 0 ] = in[ 0 ]; out[ 1 ] = in[ 1 ]; out[ 2 ] = in[ 2 ];
    out[ 3 ] = in[ 3 ];
}

void s4_math_matrix3f_copy( s4_matrix3f in, s4_matrix3f out ) {
    out[ 0 ][ 0 ] = in[ 0 ][ 0 ]; out[ 0 ][ 1 ] = in[ 0 ][ 1 ];
    out[ 0 ][ 2 ] = in[ 0 ][ 2 ];

    out[ 1 ][ 0 ] = in[ 1 ][ 0 ]; out[ 1 ][ 1 ] = in[ 1 ][ 1 ];
    out[ 1 ][ 2 ] = in[ 1 ][ 2 ];

    out[ 2 ][ 0 ] = in[ 2 ][ 0 ]; out[ 2 ][ 1 ] = in[ 2 ][ 1 ];
    out[ 2 ][ 2 ] = in[ 2 ][ 2 ];
}

void s4_math_matrix4f_copy( s4_matrix4f in, s4_matrix4f out ) {
    out[ 0 ][ 0 ] = in[ 0 ][ 0 ]; out[ 0 ][ 1 ] = in[ 0 ][ 1 ];
    out[ 0 ][ 2 ] = in[ 0 ][ 2 ]; out[ 0 ][ 3 ] = in[ 0 ][ 3 ];

    out[ 1 ][ 0 ] = in[ 1 ][ 0 ]; out[ 1 ][ 1 ] = in[ 1 ][ 1 ];
    out[ 1 ][ 2 ] = in[ 1 ][ 2 ]; out[ 1 ][ 3 ] = in[ 1 ][ 3 ];

    out[ 2 ][ 0 ] = in[ 2 ][ 0 ]; out[ 2 ][ 1 ] = in[ 2 ][ 1 ];
    out[ 2 ][ 2 ] = in[ 2 ][ 2 ]; out[ 2 ][ 3 ] = in[ 2 ][ 3 ];

    out[ 3 ][ 0 ] = in[ 3 ][ 0 ]; out[ 3 ][ 1 ] = in[ 3 ][ 1 ];
    out[ 3 ][ 2 ] = in[ 3 ][ 2 ]; out[ 3 ][ 3 ] = in[ 3 ][ 3 ];
}
*/
void s4_math_vector3f_scale(s4_vector3f v, float s, s4_vector3f out) {
  out[0] = s * v[0];
  out[1] = s * v[1];
  out[2] = s * v[2];
}

void s4_math_vector4f_scale(s4_vector4f v, float s, s4_vector4f out) {
  out[0] = s * v[0];
  out[1] = s * v[1];
  out[2] = s * v[2];
  out[3] = s * v[3];
}

void s4_math_vector3f_add(s4_vector3f v1, s4_vector3f v2, s4_vector3f out) {
  out[0] = v1[0] + v2[0];
  out[1] = v1[1] + v2[1];
  out[2] = v1[2] + v2[2];
}

void s4_math_vector4f_add(s4_vector4f v1, s4_vector4f v2, s4_vector4f out) {
  out[0] = v1[0] + v2[0];
  out[1] = v1[1] + v2[1];
  out[2] = v1[2] + v2[2];
  out[3] = v1[3] + v2[3];
}

void s4_math_vector3f_sub(s4_vector3f v1, s4_vector3f v2, s4_vector3f out) {
  out[0] = v1[0] - v2[0];
  out[1] = v1[1] - v2[1];
  out[2] = v1[2] - v2[2];
}
/*
 *float s4_math_vector3f_dot(s4_vector3f v1, s4_vector3f v2) {
 *  return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
 *}
 */

void s4_math_vector3f_cross(s4_vector3f v1, s4_vector3f v2, s4_vector3f out) {
  s4_vector3f tmp1, tmp2;

  s4_math_vector3_copy(v1, tmp1);
  s4_math_vector3_copy(v2, tmp2);

  out[0] = tmp1[1] * tmp2[2] - tmp1[2] * tmp2[1];
  out[1] = tmp1[2] * tmp2[0] - tmp1[0] * tmp2[2];
  out[2] = tmp1[0] * tmp2[1] - tmp1[1] * tmp2[0];
}

void s4_math_matrix4f_mul_vector4f(s4_matrix4f m, s4_vector4f v,
                                   s4_vector3f out) {
  s4_vector4f tmp;

  s4_math_vector4_copy(v, tmp);

  out[0] =
      m[0][0] * tmp[0] + m[1][0] * tmp[1] + m[2][0] * tmp[2] + m[3][0] * tmp[3];
  out[1] =
      m[0][1] * tmp[0] + m[1][1] * tmp[1] + m[2][1] * tmp[2] + m[3][1] * tmp[3];
  out[2] =
      m[0][2] * tmp[0] + m[1][2] * tmp[1] + m[2][2] * tmp[2] + m[3][2] * tmp[3];
  out[3] =
      m[0][3] * tmp[0] + m[1][3] * tmp[1] + m[2][3] * tmp[2] + m[3][3] * tmp[3];
}

float s4_math_vector3f_norm(s4_vector3f v) {
  return sqrtf(s4_math_vector3_dot(v, v));
}

void s4_math_vector3f_normalize(s4_vector3f v, s4_vector3f out) {
  float mag;

  mag = s4_math_vector3f_norm(v);
  out[0] = v[0] / mag;
  out[1] = v[1] / mag;
  out[2] = v[2] / mag;
}

void s4_math_find_dir(float pitch, float yaw, s4_vector3f up, s4_vector3f dir) {
  s4_vector4f side, new_dir;
  s4_matrix4f rotation1, rotation2;

  new_dir[0] = 0.0f;
  new_dir[1] = 0.0f;
  new_dir[2] = -1.0f;
  new_dir[3] = 1.0f;

  s4_math_vector3f_cross(new_dir, up, side);
  s4_math_make_rotate_matrix(yaw, up, rotation1);
  s4_math_make_rotate_matrix(pitch, side, rotation2);
  s4_math_matrix4f_mul_vector4f(rotation2, new_dir, new_dir);
  s4_math_matrix4f_mul_vector4f(rotation1, new_dir, new_dir);

  s4_math_vector3_copy(new_dir, dir);
}

void s4_math_look(s4_vector3f eye, s4_vector3f dir, s4_vector3f up,
                  s4_matrix4f out) {
  s4_vector3f f, u, s;

  s4_math_vector3f_normalize(dir, f);
  s4_math_vector3f_cross(f, up, s);
  s4_math_vector3f_normalize(s, s);
  s4_math_vector3f_cross(s, f, u);

  out[0][0] = s[0];
  out[0][1] = u[0];
  out[0][2] = -f[0];
  out[0][3] = 0.0f;

  out[1][0] = s[1];
  out[1][1] = u[1];
  out[1][2] = -f[1];
  out[1][3] = 0.0f;

  out[2][0] = s[2];
  out[2][1] = u[2];
  out[2][2] = -f[2];
  out[2][3] = 0.0f;

  out[3][0] = -s4_math_vector3_dot(s, eye);
  out[3][1] = -s4_math_vector3_dot(u, eye);
  out[3][2] = s4_math_vector3_dot(f, eye);
  out[3][3] = 1.0f;
}

void s4_math_look_at(s4_vector3f eye, s4_vector3f center, s4_vector3f up,
                     s4_matrix4f out) {
  s4_vector3f dir;

  s4_math_vector3f_sub(eye, center, dir);
  s4_math_look(eye, dir, up, out);
}

void s4_math_perspective(float fov, float ratio, float near, float far,
                         s4_matrix4f out) {
  float f, fn;

  f = 1.0f / tanf(fov * 0.5f);
  fn = 1.0f / (near - far);

  out[0][0] = f / ratio;
  out[0][1] = 0.0f;
  out[0][2] = 0.0f;
  out[0][3] = 0.0f;

  out[1][0] = 0.0f;
  out[1][1] = f;
  out[1][2] = 0.0f;
  out[1][3] = 0.0f;

  out[2][0] = 0.0f;
  out[2][1] = 0.0f;
  out[2][2] = (near + far) * fn;
  out[2][3] = -1.0f;

  out[3][0] = 0.0f;
  out[3][1] = 0.0f;
  out[3][2] = 2 * near * far * fn;
  out[3][3] = 0.0f;
}
void s4_math_ortho(float left, float right, float bottom, float top, float near,
                   float far, s4_matrix4f out) {
  float rl, tb, fn;

  rl = 1.0f / (right - left);
  tb = 1.0f / (top - bottom);
  fn = -1.0f / (far - near);

  out[0][1] = 0.0f;
  out[0][2] = 0.0f;
  out[0][3] = 0.0f;
  out[1][0] = 0.0f;
  out[1][2] = 0.0f;
  out[1][3] = 0.0f;
  out[2][0] = 0.0f;
  out[2][1] = 0.0f;
  out[2][3] = 0.0f;

  out[0][0] = 2.0f * rl;
  out[1][1] = 2.0f * tb;
  out[2][2] = 2.0f * fn;
  out[3][0] = -(right + left) * rl;
  out[3][1] = -(top + bottom) * tb;
  out[3][2] = (far + near) * fn;
  out[3][3] = 1.0f;
}
void s4_math_translate(s4_vector3f v, s4_matrix4f in_out) {
  s4_vector4f v1, v2, v3;

  s4_math_vector4f_scale(in_out[0], v[0], v1);
  s4_math_vector4f_scale(in_out[1], v[1], v2);
  s4_math_vector4f_scale(in_out[2], v[2], v3);

  s4_math_vector4f_add(v1, in_out[3], in_out[3]);
  s4_math_vector4f_add(v2, in_out[3], in_out[3]);
  s4_math_vector4f_add(v3, in_out[3], in_out[3]);
}

void s4_math_make_rotate_matrix(float angle, s4_vector3f axis,
                                s4_matrix4f out) {
  float c;
  s4_vector3f naxis, v, vs;

  c = cosf(angle);

  s4_math_vector3f_normalize(axis, naxis);
  s4_math_vector3f_scale(naxis, 1.0f - c, v);
  s4_math_vector3f_scale(naxis, sinf(angle), vs);
  s4_math_vector3f_scale(naxis, v[0], out[0]);
  s4_math_vector3f_scale(naxis, v[1], out[1]);
  s4_math_vector3f_scale(naxis, v[2], out[2]);

  out[0][0] += c;
  out[0][1] += vs[2];
  out[0][2] -= vs[1];
  out[0][3] = 0.0f;

  out[1][0] -= vs[2];
  out[1][1] += c;
  out[1][2] += vs[0];
  out[1][3] = 0.0f;

  out[2][0] += vs[1];
  out[2][1] -= vs[0];
  out[2][2] += c;
  out[2][3] = 0.0f;

  out[3][0] = 0.0f;
  out[3][1] = 0.0f;
  out[3][2] = 0.0f;
  out[3][3] = 1.0f;
}

void s4_math_mult_rotation(s4_matrix4f m1, s4_matrix4f m2, s4_matrix4f out) {
  float a00 = m1[0][0], a01 = m1[0][1], a02 = m1[0][2], a03 = m1[0][3],
        a10 = m1[1][0], a11 = m1[1][1], a12 = m1[1][2], a13 = m1[1][3],
        a20 = m1[2][0], a21 = m1[2][1], a22 = m1[2][2], a23 = m1[2][3],
        a30 = m1[3][0], a31 = m1[3][1], a32 = m1[3][2], a33 = m1[3][3],
        b00 = m2[0][0], b01 = m2[0][1], b02 = m2[0][2], b10 = m2[1][0],
        b11 = m2[1][1], b12 = m2[1][2], b20 = m2[2][0], b21 = m2[2][1],
        b22 = m2[2][2], b30 = m2[3][0], b31 = m2[3][1], b32 = m2[3][2],
        b33 = m2[3][3];

  out[0][0] = a00 * b00 + a10 * b01 + a20 * b02;
  out[0][1] = a01 * b00 + a11 * b01 + a21 * b02;
  out[0][2] = a02 * b00 + a12 * b01 + a22 * b02;
  out[0][3] = a03 * b00 + a13 * b01 + a23 * b02;

  out[1][0] = a00 * b10 + a10 * b11 + a20 * b12;
  out[1][1] = a01 * b10 + a11 * b11 + a21 * b12;
  out[1][2] = a02 * b10 + a12 * b11 + a22 * b12;
  out[1][3] = a03 * b10 + a13 * b11 + a23 * b12;

  out[2][0] = a00 * b20 + a10 * b21 + a20 * b22;
  out[2][1] = a01 * b20 + a11 * b21 + a21 * b22;
  out[2][2] = a02 * b20 + a12 * b21 + a22 * b22;
  out[2][3] = a03 * b20 + a13 * b21 + a23 * b22;

  out[3][0] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
  out[3][1] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
  out[3][2] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
  out[3][3] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;
}
