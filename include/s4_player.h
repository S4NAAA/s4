#ifndef S4_PLAYER_H
#define S4_PLAYER_H

#ifdef __cplusplus
extern "C"
#endif

#include "s4_camera.h"
#include "s4_common.h"
#include "s4_math.h"

    extern void
    s4_player_set_base_perspective(float pitch, float yaw,
                                   struct s4_settings *settings,
                                   struct s4_player *player);

#ifdef __cplusplus
}
#endif

#endif
