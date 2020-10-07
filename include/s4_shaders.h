#ifndef S4_SHADERS_H
#define S4_SHADERS_H

#ifdef __cplusplus
extern "C" {
#endif

#define S4_SHADERS_VERTEX_1 1
#define S4_SHADERS_VERTEX_CODE_1                        \
  "#version 330 core\n"                                 \
  "layout ( location = 0 ) in vec3 vertex_position;\n"  \
  "layout ( location = 1 ) in vec2 in_texture_coord;\n" \
  "out vec2 out_texture_coord;\n"                       \
  "uniform mat4 model;\n"                               \
  "uniform mat4 view;\n"                                \
  "uniform mat4 projection;\n"                          \
  "void main()\n"                                       \
  "{\n"                                                 \
  "gl_Position = projection * view * model *\n"         \
  "vec4( vertex_position, 1.0f );\n"                    \
  "out_texture_coord = in_texture_coord;\n"             \
  "}"

#define S4_SHADERS_FRAGMENT_1 1
#define S4_SHADERS_FRAGMENT_CODE_1                                     \
  "#version 330 core\n"                                                \
  "in vec2 out_texture_coord;\n"                                       \
  "out vec4 fragment_color;\n"                                         \
  "uniform vec2 tex_offset;\n"                                         \
  "uniform sampler2D tex;\n"                                           \
  "void main()\n"                                                      \
  "{\n"                                                                \
  "fragment_color = texture( tex, out_texture_coord + tex_offset );\n" \
  "}"

#define S4_SHADERS_VERTEX_2 2
#define S4_SHADERS_VERTEX_CODE_2                                \
  "#version 330 core\n"                                         \
  "layout ( location = 0 ) in vec3 vertex_position;\n"          \
  "layout ( location = 1 ) in vec2 in_texture_coord;\n"         \
  "out vec2 out_texture_coord;\n"                               \
  "uniform vec3 pos_offset;\n"                                  \
  "void main()\n"                                               \
  "{\n"                                                         \
  "gl_Position = vec4( pos_offset + vertex_position, 1.0f );\n" \
  "out_texture_coord = in_texture_coord;\n"                     \
  "}"

#ifdef __cplusplus
}
#endif
#endif
