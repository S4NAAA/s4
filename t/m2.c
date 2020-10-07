
#include "s4_common.h"
#include "s4_math.h"
#include "s4_renderer.h"
#include "s4_player.h"
#include "s4_camera.h"
#include "s4_debug.h"

int main( void ) {
    int step, b;
    unsigned int program;
    unsigned int texture;
    s4_vector3f model_pos;
    s4_vector3f rot_axis;
    s4_vector3f vel;
    s4_matrix4f rot;
    s4_matrix4f model;
    struct s4_settings settings;
    struct s4_player player;
    struct s4_vertex_object_data vo;

    struct s4_window window = { NULL, 600, 600, "STAN LOONA" };

    unsigned int sizes[] = { 3, 2 };

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    if( !s4_renderer_init( &window ) ) {
        printf( "Couldn't initialize renderer\n" );
        return 0;
    }

    settings.fov = 90.0f * M_PI/ 180.0f;
    settings.width_ratio = 1.0f;
    settings.height_ratio = 1.0f;
    settings.render_distance = 100.0f;

    s4_math_vector3_set( 0.0f, 0.0f, 0.0f, player.pos );
    s4_math_vector3_set( 0.0f, 0.0f, 3.0f, player.camera.pos );
    s4_math_vector3_set( 0.0f, 1.0f, 0.0f, player.camera.up );
    s4_player_set_base_perspective( 0.0, 0.0f, &settings, &player );

    s4_renderer_load_shader( 1, 1, &program );

    vo.vertices_size = 36;
    vo.mode = GL_TRIANGLES;

    glGenVertexArrays( 1, &vo.vao );
    glGenBuffers( 1, &vo.vbo );
    glBindVertexArray( vo.vao );
    glBindBuffer( GL_ARRAY_BUFFER, vo.vbo );

    glBufferData( GL_ARRAY_BUFFER, vo.vertices_size * 5 * 
            sizeof( float ), vertices, GL_STATIC_DRAW );

    s4_renderer_set_attrib_pointers( &sizes[ 0 ], 2, 5 );

    s4_renderer_load_texture( "../../sprites/chaeyoung.png", &texture );

    glUseProgram( program );

    glUniformMatrix4fv( glGetUniformLocation( program, "projection" ),
            1, GL_FALSE, &player.projection[ 0 ][ 0 ] );

    glUniformMatrix4fv( glGetUniformLocation( program, "view" ),
            1, GL_FALSE, &player.camera.view[ 0 ][ 0 ] );

    glUniform1i( glGetUniformLocation( program, "tex" ), 0 );

    s4_math_vector3_set( 0.0f, 0.0f, 0.0f, model_pos );
    s4_math_vector3_set( 0.3f, 0.2f, 0.4f, rot_axis );
    s4_math_vector3_set( 0.0f, 0.0f, 0.1f, vel );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture );
    b = 0;
    step = 0;
    while( !glfwWindowShouldClose( window.gl_data ) ) {
        ++step;
        if ( glfwGetKey( window.gl_data, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
            glfwSetWindowShouldClose( window.gl_data, 1 );

        glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
/*
        s4_camera_look( 0.0f, step * 0.02f, &player.camera );
        glUniformMatrix4fv( glGetUniformLocation( program, "view" ), 
                1, GL_FALSE, &player.camera.view[ 0 ][ 0 ] );
*/
        if( b ) {
            s4_math_vector3f_add( vel, model_pos, model_pos );
            if( model_pos[ 2 ] > 0.0f ) b = 0;
        } else {
            s4_math_vector3f_sub( model_pos, vel, model_pos );
            if( model_pos[ 2 ] < -10.0f ) b = 1;
        }
        
        s4_math_vector3_set( ( 0.03f * step ), 
                             ( 0.02f * step ), 
                             ( 0.04f * step ), rot_axis );

        s4_math_matrix4f_identity( model );
        s4_math_translate( model_pos, model );
        s4_math_make_rotate_matrix( step * 0.02f, rot_axis, rot );
        s4_math_mult_rotation( model, rot, model );

        glUniformMatrix4fv( glGetUniformLocation( program, "model" ),
                1, GL_FALSE, &model[ 0 ][ 0 ] );

        glBindVertexArray( vo.vao );
        glDrawArrays( vo.mode, 0, vo.vertices_size );

        glfwSwapBuffers( window.gl_data );
        glfwPollEvents(); 
    }

    glDeleteVertexArrays( 1, &vo.vao );
    glDeleteBuffers( 1, &vo.vbo );
    glDeleteProgram( program );
    glDeleteTextures( 1, &texture );
    glfwTerminate();

    return 0;
}            
