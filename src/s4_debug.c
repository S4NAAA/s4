
#include "s4_debug.h"
void pm4f(s4_matrix4f m) {
  int i, j;
  for (i = 0; i < 4; ++i) {
    for (j = 0; j < 4; ++j) printf("%.3f, ", m[i][j]);
    printf("\n");
  }
  printf("\n");
}

void pv3f(s4_vector3f v) { printf("%.3f, %.3f, %.3f\n\n", v[0], v[1], v[2]); }
