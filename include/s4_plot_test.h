#ifndef S4_PLOT_TEST_H
#define S4_PLOT_TEST_H

#include "s4_common.h"
#include "s4_vertex_object_pool.h"

unsigned int s4_plot_test_get_vertex_object(float x0, float x1, float y0,
                                            float y1, unsigned int count,
                                            float (*func)(float, float));

#endif /* S4_PLOT_TEST_H */
