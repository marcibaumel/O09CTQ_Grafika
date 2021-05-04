#ifndef DRONMOVE_H
#define DRONMOVE_H

#include "utils.h"
#include "scene.h"

void move_dronMove(struct Object *object, double time);

void set_dronMove_side_speed(struct Object *object, double speed);

void set_dronMove_scale(struct Object *object, double inc_size);

void set_dronMove_speed(struct Object *object, double speed);

void rotate_dronMove(struct Object *object, double horizontal);

#endif;