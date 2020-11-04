#ifndef S4_SHADERS_H
#define S4_SHADERS_H

#ifdef __cplusplus
extern "C" {
#endif

static char s_s4_shaders_vertex_code_1[] =
    "#version 330 core\n"
    "layout ( location = 0 ) in vec3 vertex_position;"
    "layout ( location = 1 ) in vec2 in_texture_coord;"
    "out vec2 out_texture_coord;"
    "uniform mat4 model;"
    "uniform mat4 view;"
    "uniform mat4 projection;"
    "void main()"
    "{"
    "gl_Position = projection * view * model * vec4( vertex_position, 1.0f );"
    "out_texture_coord = in_texture_coord;"
    "}";

static char s_s4_shader_fragment_code_1[] =
    "#version 330 core\n"
    "in vec2 out_texture_coord;\n"
    "out vec4 fragment_color;\n"
    "uniform vec2 tex_offset;\n"
    "uniform sampler2D tex;\n"
    "void main()\n"
    "{\n"
    "fragment_color = texture( tex, out_texture_coord + tex_offset );\n"
    "}";

#define S4_SHADERS_VERTEX_1 1
#define S4_SHADERS_FRAGMENT_1 1

#ifdef __cplusplus
}
#endif
#endif
