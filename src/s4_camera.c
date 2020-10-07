#include "s4_camera.h"

/*
   void s4_camera_set_direction( float pitch, float yaw,
   struct s4_camera *camera ) {
   float *dir, *up;
   s4_vector4f side;
   s4_matrix4f rotation1, rotation2;

   dir = ( float* )&camera->dir[ 0 ];
   up = ( float* )&camera->up[ 0 ];

   dir[ 0 ] = 0.0f; dir[ 1 ] = 0.0f;
   dir[ 2 ] = -1.0f; dir[ 3 ] = 1.0f;

   s4_math_vector3f_cross( dir, up, side );
   s4_math_make_rotate_matrix( yaw, up, rotation1 );
   s4_math_make_rotate_matrix( pitch, side, rotation2 );
   s4_math_matrix4f_mul_vector4f( rotation2, dir, dir );
   s4_math_matrix4f_mul_vector4f( rotation1, dir, dir );
   }*/

void s4_camera_look(float pitch, float yaw, struct s4_camera *camera) {
  s4_math_create_dir(pitch, yaw, camera->up, camera->dir);
  s4_math_look(camera->pos, camera->dir, camera->up, camera->view);
}
