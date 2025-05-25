#ifndef CAMERA_H
#define CAMERA_H

#include "environment.h"

extern float camera_center_pos_x_m;
extern float camera_center_pos_y_m;
extern float capture_window_width_m;
extern float capture_window_height_m;

void initialize_camera(Level *lvl);
void zoom_in(void);
void zoom_out(void);
void calculate_m_to_p_coefficients(Level *lvl);
void calculate_m_to_p_coordinates(float x_m, float y_m, int *x, int *y);
void calculate_m_to_p_dimesions(float w_m, float h_m, int *w, int* h);

#endif
