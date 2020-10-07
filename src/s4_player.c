#include "s4_player.h"

void s4_player_set_base_perspective(float pitch, float yaw,
                                    struct s4_settings *player_settings,
                                    struct s4_player *player) {
  s4_math_perspective(player_settings->fov,
                      (float)player_settings->width_ratio /
                          (float)player_settings->height_ratio,
                      S4_COMMON_DEFAULT_NEAR,
                      S4_COMMON_DEFAULT_NEAR + player_settings->render_distance,
                      player->projection);
  s4_camera_look(pitch, yaw, &player->camera);
}
