#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"


#include <obj/model.h>

typedef struct Object
{
    Model model;
    vec3 position;
    vec3 scale;
    vec3 speed;
    vec3 rotation;
    vec3 prev_position;
} Object;

typedef struct Scene
{
    Object skeleton;
    Object trex;
    Object sign;
    Material material;
    GLuint texture_id[10];
    float light;
} Scene;

void init_scene(Scene *scene);

void set_position(Scene *scene);

void set_lighting(Scene *scene);

void set_material(const Material *material);

void draw_scene(const Scene *scene);

void init_models(Scene *scene);

void init_textures(Scene *scene);

void draw_ground(Scene *scene);

#endif /* SCENE_H */
