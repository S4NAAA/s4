#ifndef S4_CAMERA_H
#define S4_CAMERA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "s4_common.h"
#include "s4_math.h"

/*
extern void
s4_camera_set_direction( float pitch, float yaw, struct s4_camera *camera );
*/
extern void s4_camera_look(float pitch, float yaw, struct s4_camera *camera);

#ifdef __cplusplus
}
#endif

#endif
