#include "dronMove.h"
#include <GL/glut.h>
#include <math.h>
#include "scene.h"
#define size 10

void rotate_dronMove(struct Object *object, double horizontal)
{
    object->rotation.z += horizontal;

    if (object->rotation.z < 0)
    {
        object->rotation.z += 360.0;
    }

    if (object->rotation.z > 360.0)
    {
        object->rotation.z -= 360.0;
    }
}

void set_dronMove_speed(struct Object *object, double speed)
{
    object->speed.z = speed;
}

void set_dronMove_side_speed(struct Object *object, double speed)
{
    object->speed.x = speed;
}

void set_dronMove_scale(struct Object *object, double inc_size)
{
    object->scale.x += inc_size;
    object->scale.z += inc_size;
    object->scale.y += inc_size;
}

void move_dronMove(struct Object *object, double time)
{
    double angle;
    double side_angle;
    angle = degree_to_radian(object->rotation.z);
    side_angle = degree_to_radian(object->rotation.z + 90.0);

    if (!(object->position.x > size - 1 || object->position.x < -size + 1 || object->position.z < -size + 1 || object->position.z > size - 1))
    {
        object->prev_position = object->position;
        object->position.x += cos(angle) * object->speed.z * time;
        object->position.z += sin(angle) * object->speed.z * time;
        object->position.x += cos(side_angle) * object->speed.x * time;
        object->position.z += sin(side_angle) * object->speed.x * time;
    }
    else
    {
        object->position = object->prev_position;
    }
}