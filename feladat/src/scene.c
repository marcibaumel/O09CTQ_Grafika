#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_scene(Scene *scene)
{
    init_models(scene);
    set_position(scene);
    init_textures(scene);

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

    scene->light = 0.7f;
}

void init_models(Scene *scene)
{
    load_model(&(scene->skeleton), "models/skeleton.obj");
    load_model(&(scene->trex), "models/trex.obj");
    load_model(&(scene->sign), "models/sign.obj");
}

void set_position(Scene *scene)
{
    scene->skeleton.position.x = 0.0;
    scene->skeleton.position.z = 20.0;

    scene->trex.position.y = -0.8;
}

void init_textures(Scene *scene)
{
    scene->texture_id[0] = load_texture("textures/polydesert_atlas.png");
    scene->texture_id[1] = load_texture("textures/floor.png");
    scene->texture_id[2] = load_texture("textures/up.png");
    scene->texture_id[3] = load_texture("textures/guide.png");
    scene->texture_id[4] = load_texture("textures/bone.png");
    scene->texture_id[5] = load_texture("textures/trex.jpg");
    scene->texture_id[6] = load_texture("textures/sign.jpg");
}

void set_lighting(Scene *scene)
{
    float ambient_light[4];
    float diffuse_light[4];
    float specular_light[4];
    float position[4];

    ambient_light[0] = scene->light;
    ambient_light[1] = scene->light;
    ambient_light[2] = scene->light;
    ambient_light[3] = 1.0f;

    diffuse_light[0] = scene->light;
    diffuse_light[1] = scene->light;
    diffuse_light[2] = scene->light;
    diffuse_light[3] = 1.0f;

    specular_light[0] = scene->light;
    specular_light[1] = scene->light;
    specular_light[2] = scene->light;
    specular_light[3] = 1.0f;

    position[0] = 0.0f;
    position[1] = 0.0f;
    position[2] = 10.0f;
    position[3] = 0.0f;

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

float angle = 0.0f;

void draw_scene(const Scene *scene)
{
    set_material(&(scene->material));
    set_lighting(scene);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(90, 1, 0, 0);

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[4]);
    glTranslatef(scene->skeleton.position.x, scene->skeleton.position.y, scene->skeleton.position.z);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    angle += 0.1f;
    draw_model(&(scene->skeleton));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[5]);
    glTranslatef(scene->trex.position.x, scene->trex.position.y, scene->trex.position.z);
    glScalef(0.01f, 0.01f, 0.01f);
    draw_model(&(scene->trex));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[2]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(2000, 60, 2000);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(2000, 60, -2000);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-2000, 60, -2000);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-2000, 60, 2000);
    glEnd();
    glPopMatrix();
    draw_ground(scene);
}

void draw_ground(Scene *scene)
{
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBegin(GL_QUADS);
    int x, z, y;
    for (x = -210; x < 210; x += 3)
    {
        for (z = -210; z < 210; z += 3)
        {
            y = 0;
            glTexCoord2f(0.0, 0.0);
            glNormal3f(0, -1, 0);
            glVertex3f(x, y, z);
            glTexCoord2f(1.0, 0.0);
            glNormal3f(0, -1, 0);
            glVertex3f(x + 3, y, z);
            glTexCoord2f(1.0, 1.0);
            glNormal3f(0, -1, 0);
            glVertex3f(x + 3, y, z + 3);
            glTexCoord2f(0.0, 1.0);
            glNormal3f(0, -1, 0);
            glVertex3f(x, y, z + 3);
        }
    }
    glEnd();
}
