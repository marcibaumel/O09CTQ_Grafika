#include "dron.h"
#include <GL/glut.h>
#include <math.h>
#include "scene.h"
#define size 10

void move_dron(struct Object *object, double time)
{
    if (object->position.x < -size + 1)
    {
        object->speed.x *= -1;
    }
    if (object->position.x > size - 1)
    {
        object->speed.x *= -1;
    }
    if (object->position.y < 5)
    {
        object->speed.y *= -1;
    }
    if (object->position.y > 20)
    {
        object->speed.y *= -1;
    }
    if (object->position.z < -size + 1)
    {
        object->speed.z *= -1;
    }
    if (object->position.z > size - 1)
    {
        object->speed.z *= -1;
    }

    object->position.x += object->speed.x * time;
    object->position.y += object->speed.y * time;
    object->position.z += object->speed.z * time;
}
