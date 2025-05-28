#include "camera.h"
#include "character.h"
#include "environment.h"
#include "game.h"
#include "utils.h"

float camera_center_pos_x_m;
float camera_center_pos_y_m;
float capture_window_width_m;
float capture_window_height_m;
float ratio;

float zero_x, zero_y;
float x_m_to_p, y_m_to_p;

const int DEFAULT_CAPTURE_WINDOW_WIDTH_M = 40;
const int MIN_CAPTURE_WINDOW_WIDTH_M = 1;
const int MAX_CAPTURE_WINDOW_WIDTH_M = 40;

void initialize_camera(Level *lvl) {
	capture_window_width_m = DEFAULT_CAPTURE_WINDOW_WIDTH_M;
	ratio = (float) screen_height / screen_width;
	capture_window_height_m = capture_window_width_m * ratio;
	camera_center_pos_x_m = MAX(MIN(capture_window_width_m / 2, lvl->starting_point.x_m), lvl->width_m - capture_window_width_m / 2);
	camera_center_pos_y_m = MAX(MIN(capture_window_height_m / 2, lvl->starting_point.y_m), lvl->height_m - capture_window_height_m / 2);
}

void calculate_m_to_p_coefficients(Level *lvl) {
	zero_x = (float) screen_width * (.5 - camera_center_pos_x_m / capture_window_width_m);
	zero_y = (float) screen_height * (.5 + camera_center_pos_y_m / capture_window_height_m);

	x_m_to_p = screen_width / capture_window_width_m;
	y_m_to_p = screen_height / capture_window_height_m;
}

void calculate_m_to_p_coordinates(float x_m, float y_m, int *x, int *y) {
	*x = (int) (zero_x + x_m * x_m_to_p);
	*y = (int) (zero_y - y_m * y_m_to_p);
}

void calculate_m_to_p_dimesions(float w_m, float h_m, int *w, int* h) {
	*w = (int) (ABS(w_m * x_m_to_p));
	*h = (int) (ABS(h_m * y_m_to_p));
}

void center_camera(Level *lvl) {
	camera_center_pos_x_m = character.x_m;
	camera_center_pos_x_m = MIN(lvl->width_m - capture_window_width_m / 2, camera_center_pos_x_m);
	camera_center_pos_x_m = MAX(capture_window_width_m / 2, camera_center_pos_x_m);

	camera_center_pos_y_m = character.y_m;
	camera_center_pos_y_m = MIN(lvl->height_m - capture_window_height_m / 2, camera_center_pos_y_m);
	camera_center_pos_y_m = MAX(capture_window_height_m / 2, camera_center_pos_y_m);
}

void zoom_in(void) {
	if (capture_window_width_m > MIN_CAPTURE_WINDOW_WIDTH_M) {
		capture_window_width_m--;
		capture_window_height_m = capture_window_width_m * ratio;
	}
}

void zoom_out(void) {
	if (capture_window_width_m < MAX_CAPTURE_WINDOW_WIDTH_M) {
		capture_window_width_m++;
		capture_window_height_m = capture_window_width_m * ratio;
	}
}

