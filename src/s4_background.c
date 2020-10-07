#include "s4_background.h"
/*
void s4_background_load_vertex_data( struct s4_background *background ) {

    struct s4_vertex_object_data *data;

    static const unsigned int stride[] = S4_RENDERER_BACKGROUND_STRIDE;
    static const unsigned int stride_length =
        sizeof( stride ) / sizeof( stride[ 0 ] );
    static const float vertices[] = S4_RENDERER_BACKGROUND_VERTICES;
    static unsigned int slice_size = 0;

    if( slice_size == 0 ) {
        unsigned int i;

        for( i = 0; i < stride_length; ++i )
            slice_size += stride[ i ];
    }

    data = &background->vd;
    data->vertices_size = vertices_size;
    data->slice_size = slice_size;
    data->mode = GL_TRIANGLES;

    glGenVertexArrays( 1, &data->vao );
    glGenBuffers( 1, &data->vbo );

    glBindVertexArray( data->vao );
    glBindBuffer( GL_ARRAY_BUFFER, data->vbo );

    s4_renderer_set_attrib_pointers( stride, stride_length, slice_size );
}
*/
