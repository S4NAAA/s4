#include <stdio.h>

#include "s4_common.h"
#include "s4_math.h"
#include "s4_renderer.h"
#include "s4_player.h"
#include "s4_camera.h"
#include "s4_debug.h"

int main( void ) {
    unsigned int program;
    unsigned int texture;
    /*
    s4_vector3f model_pos;
    s4_vector3f rot_axis;
    s4_matrix4f rot;
    */
    s4_matrix4f model;
    struct s4_settings settings;
    struct s4_player player;
    struct s4_vertex_object_data vo;
    struct s4_window window = { NULL, 600, 600, "STAN LOONA" };

    unsigned int sizes[] = { 3, 2 };
    float vertices[] = S4_RENDERER_BACKGROUND_VERTICES;

    if( !s4_renderer_init( &window ) ) {
        printf( "Couldn't initialize renderer\n" );
        return 0;
    }

    settings.fov = 70.0f * M_PI/ 180.0f;
    settings.width_ratio = 1.0f;
    settings.height_ratio = 1.0f;
    settings.render_distance = 100.0f;

    s4_math_vector3_set( 0.0f, 0.0f, 0.0f, player.pos );
    s4_math_vector3_set( 0.0f, 0.0f, 1.0f, player.camera.pos );
    s4_math_vector3_set( 0.0f, 1.0f, 0.0f, player.camera.up );
    s4_math_matrix4f_identity( player.projection );
    s4_math_matrix4f_identity( player.camera.view );
    s4_math_matrix4f_identity( model );
    /*s4_player_set_base_perspective( 0.0, 0.0f, &settings, &player );*/

    s4_renderer_load_shader( 1, 1, &program );

    /*
       s4_renderer_load_buffers( &vertices[ 0 ], ( int* )&sizes[ 0 ], 
       GL_TRIANGLES, 36, 2,  &buffers ); */

    /*
       buffers.vertex_size = malloc( 1 * sizeof( unsigned int ) );
       buffers.vao = malloc( 1 * sizeof( unsigned int ) );
       buffers.vbo = malloc( 1 * sizeof( unsigned int ) );
       buffers.mode = malloc( 1 * sizeof( int ) );
     */

    /*s4_renderer_malloc_data( 1, &buffers );*/

    vo.vertices_size = 6;
    vo.mode = GL_TRIANGLES;

    glGenVertexArrays( 1, &vo.vao );
    glGenBuffers( 1, &vo.vbo );
    glBindVertexArray( vo.vao );
    glBindBuffer( GL_ARRAY_BUFFER, vo.vbo );

    glBufferData( GL_ARRAY_BUFFER, vo.vertices_size * 5 * 
            sizeof( float ), ( void* )&vertices[ 0 ], 
            GL_STATIC_DRAW );

    s4_renderer_set_attrib_pointers( ( unsigned int* )&sizes[ 0 ], 2, 5 );

    s4_renderer_load_texture( "../../sprites/chaeyoung.png", &texture );

    glUseProgram( program );

    glUniformMatrix4fv( glGetUniformLocation( program, "projection" ),
            1, GL_FALSE, &player.projection[ 0 ][ 0 ] );

    glUniformMatrix4fv( glGetUniformLocation( program, "view" ),
            1, GL_FALSE, &player.camera.view[ 0 ][ 0 ] );

    glUniformMatrix4fv( glGetUniformLocation( program, "model" ),
            1, GL_FALSE, &model[ 0 ][ 0 ] );

    glUniform1i( glGetUniformLocation( program, "tex" ), 0 );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture );

    while( !glfwWindowShouldClose( window.gl_data ) ) {
        if ( glfwGetKey( window.gl_data, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
            glfwSetWindowShouldClose( window.gl_data, 1 );

        glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glBindVertexArray( vo.vao );
        glDrawArrays( vo.mode, 0, vo.vertices_size );

        glfwSwapBuffers( window.gl_data );
        glfwPollEvents(); 
    }

    /*s4_renderer_free_data( &buffers );*/
    glDeleteVertexArrays( 1, &vo.vao );
    glDeleteBuffers( 1, &vo.vbo );
    glDeleteProgram( program );
    glDeleteTextures( 1, &texture );
    glfwTerminate();

    return 0;
}            
