#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include "scene.h"

/**
 * Camera, as a moving point with direction
 */
typedef struct Camera
{
    vec3 position;
    vec3 prev_position;
    vec3 rotation;
    vec3 speed;
} Camera;

/**
 * Is the texture preview visible?
 */
int is_preview_visible;

int is_i_visible;
int is_o_visible;
int is_p_visible;

void set_camera_vertical_speed(Camera *camera, double speed);

/**
 * Initialize the camera to the start position.
 */
void init_camera(Camera *camera);

/**
 * Update the position of the camera.
 */
void update_camera(Camera *camera, double time);

/**
 * Apply the camera settings to the view transformation.
 */
void set_view(const Camera *camera);

/**
 * Set the horizontal and vertical rotation of the view angle.
 */
void rotate_camera(Camera *camera, double horizontal, double vertical);

/**
 * Set the speed of forward and backward motion.
 */
void set_camera_speed(Camera *camera, double speed);

/**
 * Set the speed of left and right side steps.
 */
void set_camera_side_speed(Camera *camera, double speed);

void show_help(struct Scene *scene);
void show_i(struct Scene *scene);
void show_o(struct Scene *scene);
void show_p(struct Scene *scene);
#endif /* CAMERA_H */
