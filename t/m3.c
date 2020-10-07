#include "s4_common.h"
#include "s4_renderer.h"
#include "s4_math.h"
#include "s4_input.h"

int main( void ) {
    unsigned int shader, texture;
    struct s4_vertex_object_data vo;
    struct s4_input input;

    struct s4_window window = { NULL, 600, 600, "STAN LOONA" };
    unsigned int sizes[] = { 3, 2 };
    float vertices[] = S4_RENDERER_BACKGROUND_VERTICES;


    if( !s4_renderer_init( &window ) ) {
        printf( "Couldn't initialize renderer\n" );
        goto cleanup;
    }

    s4_renderer_load_shader( 2, 1, &shader );
    s4_renderer_load_texture( "../../sprites/chaeyoung.png", &texture );
    vo.vertices_size = 6;
    vo.slice_size = 5;
    vo.mode = GL_TRIANGLES;

    glGenVertexArrays( 1, &vo.vao );
    glGenBuffers( 1, &vo.vbo );
    glBindVertexArray( vo.vao );
    glBindBuffer( GL_ARRAY_BUFFER, vo.vbo );

    glBufferData( GL_ARRAY_BUFFER, 
            vo.vertices_size * vo.slice_size * sizeof( float ), vertices, 
            GL_STATIC_DRAW );

    s4_renderer_set_attrib_pointers( &sizes[ 0 ], 2, vo.slice_size );

    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, texture );

    glUseProgram( shader );
    glUniform1i( glGetUniformLocation( shader, "tex" ), 0 );
    glUniform3f( glGetUniformLocation( shader, "pos_offset" ), 
            0.0f, 0.0f, 0.0f );
    glUniform2f( glGetUniformLocation( shader, "tex_offset" ), 0.0f, 0.0f );

    while( !glfwWindowShouldClose( window.gl_data  ) ) {

        s4_input_update( &window, &input );
        if( input.esc_state == GLFW_PRESS ) 
            glfwSetWindowShouldClose( window.gl_data, 1 );

        glClearColor( 0.0f, 0.0f ,0.0f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        
        glUniform2f( glGetUniformLocation( shader, "tex_offset" ), 
                input.x_cursor_pos / window.width ,
                input.y_cursor_pos / window.height );
        glBindVertexArray( vo.vao );
        glDrawArrays( vo.mode, 0, vo.vertices_size );
        glfwSwapBuffers( window.gl_data );
        glfwPollEvents();
    }

    glDeleteVertexArrays( 1, &vo.vao );
    glDeleteBuffers( 1, &vo.vao );
    glDeleteProgram( shader );
    glDeleteTextures( 1, &texture );
    glfwTerminate();
cleanup:
    return 0;
}
