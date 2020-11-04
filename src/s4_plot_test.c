#include "s4_plot_test.h"

/* could've had just used a static float pool to upload the vertices */
#include <stdlib.h>

unsigned int s4_plot_test_add_vertex_object(float x0, float x1, float z0,
                                            float z1, unsigned int count,
                                            float (*func)(float, float)) {
  float y0, y1, dx, dz, dif_x, dif_z, dif_y, *vertices;
  unsigned int vertices_size, indices_size, i, j, vo, *indices;

  unsigned int layout[] = {3, 2};

  vertices_size = count * count * 5;
  indices_size = (count - 1) * (count - 1) * 6;

  vertices = malloc(vertices_size * sizeof(float));
  indices = malloc(indices_size * sizeof(unsigned int));

  dif_x = x1 - x0;
  dif_z = z1 - z0;
  dx = dif_x / (float)(count - 1);
  dz = dif_z / (float)(count - 1);

  y0 = func(x0, z0);
  y1 = y0;

  for (i = 0; i < vertices_size; i += 5) {
    const unsigned int ix = (i / 5) / count;
    const unsigned int iz = (i / 5) % count;

    const float x = x0 + ix * dx;
    const float z = z0 + iz * dz;

    vertices[i] = x;
    vertices[i + 1] = func(x, z);
    vertices[i + 2] = z;

    vertices[i + 3] = (float)ix / (float)count;
    vertices[i + 4] = (float)iz / (float)count;

    if (vertices[i + 1] < y0) y0 = vertices[i + 1];
    if (vertices[i + 1] > y1) y1 = vertices[i + 1];
  }

  dif_y = ((y1 - y0) != 0) ? y1 - y0 : 1;

  for (i = 0; i < vertices_size; i += 5) {
    vertices[i] = (vertices[i] - x0) / dif_x;
    vertices[i + 1] = (vertices[i + 1] - y0) / dif_y;
    vertices[i + 2] = (vertices[i + 2] - z0) / dif_z;
  }

  for (i = 0; i < count - 1; ++i) {
    for (j = 0; j < count - 1; ++j) {
      unsigned int k = (i * (count - 1) + j) * 6;
      unsigned int m = i * count + j;

      indices[k] = m;
      indices[k + 1] = m + 1;
      indices[k + 2] = m + count + 1;
      indices[k + 3] = m + count + 1;
      indices[k + 4] = m + count;
      indices[k + 5] = m;
    }
  }

  vo = s4_vertex_object_pool_add(GL_STATIC_DRAW, GL_TRIANGLES, vertices,
                                 vertices_size, indices, indices_size, layout,
                                 2);

  free(vertices);
  free(indices);

  return vo;
}
