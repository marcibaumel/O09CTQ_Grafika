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
    init_lists(scene);
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
    load_model(&(scene->dron.model), "models/dron.obj");
    scene->dron.speed.x = 3;
    scene->dron.speed.y = 1;

    load_model(&(scene->movedron.model), "models/dron.obj");
    scene->movedron.scale.x = 0.2;
    scene->movedron.scale.y = 0.2;
    scene->movedron.scale.z = 0.2;

    load_model(&(scene->skeleton), "models/skeleton.obj");
    load_model(&(scene->trex), "models/trex.obj");
    load_model(&(scene->sign), "models/sign2.obj");
    load_model(&(scene->fenceFront), "models/fence.obj");
    load_model(&(scene->grass1_model), "models/grass.obj");
    load_model(&(scene->triceratop), "models/triceratop.obj");
}

void init_lists(Scene *scene)
{
    scene->staticobject_display_list_id[0] = glGenLists(1);
    glNewList(scene->staticobject_display_list_id[0], GL_COMPILE);
    draw_model(&(scene->grass1_model));
    glEndList();
}

void set_position(Scene *scene)
{

    int xy[2];
    int i, j;
    int positiondb = 0;

    srand(time(NULL));
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 2; j++)
        {
            xy[j] = rand() % (50 - (-50)) - 50;
        }
        scene->grass1[i].position.x = xy[0];
        scene->grass1[i].position.y = xy[1];

        scene->positions[positiondb].x = xy[0];
        scene->positions[positiondb].y = xy[1];
        positiondb++;
    }

    scene->skeleton.position.x = 0.0;
    scene->skeleton.position.z = 15.0;

    scene->trex.position.y = -80.0;
    scene->trex.position.z = -30.0;

    scene->fenceFront.position.z = -32.0;

    scene->triceratop.position.z = -10.0;

    scene->dron.position.x = 0;
    scene->dron.position.y = 5;
    scene->dron.position.z = 10;

    scene->movedron.position.x = 0;
    scene->movedron.position.y = 6;
    scene->movedron.position.z = -5;

    scene->sign.position.x = 0;
    scene->sign.position.y = 0;
    scene->sign.position.z = 0;
}

void init_textures(Scene *scene)
{
    scene->texture_id[0] = load_texture("textures/polydesert_atlas.png");
    scene->texture_id[1] = load_texture("textures/floor.png");
    scene->texture_id[2] = load_texture("textures/skybox.jpg");
    scene->texture_id[3] = load_texture("textures/guides2.png");
    scene->texture_id[4] = load_texture("textures/bone.png");
    scene->texture_id[5] = load_texture("textures/trex.jpg");
    scene->texture_id[6] = load_texture("textures/sign.jpg");
    scene->texture_id[7] = load_texture("textures/forest.jpg");
    scene->texture_id[8] = load_texture("textures/fence.jpg");
    scene->texture_id[9] = load_texture("textures/grass.jpg");
    scene->texture_id[10] = load_texture("textures/i.jpg");
    scene->texture_id[11] = load_texture("textures/p.jpg");
    scene->texture_id[12] = load_texture("textures/o.jpg");
    scene->texture_id[13] = load_texture("textures/iT.jpg");
    scene->texture_id[14] = load_texture("textures/oT.jpg");
    scene->texture_id[15] = load_texture("textures/pT.jpg");
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
    ambient_light[3] = 10.0f;

    diffuse_light[0] = scene->light;
    diffuse_light[1] = scene->light;
    diffuse_light[2] = scene->light;
    diffuse_light[3] = 10.0f;

    specular_light[0] = scene->light;
    specular_light[1] = scene->light;
    specular_light[2] = scene->light;
    specular_light[3] = 10.0f;

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

    draw_grass(scene);
    draw_space(scene);

    glBindTexture(GL_TEXTURE_2D, scene->texture_id[3]);
    glPushMatrix();
    glTranslatef(scene->movedron.position.x, scene->movedron.position.y, scene->movedron.position.z);
    glRotatef(scene->movedron.rotation.z, 0, 1, 0);
    glScalef(scene->movedron.scale.x, scene->movedron.scale.y, scene->movedron.scale.z);
    draw_model(&(scene->movedron.model));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[4]);
    glScalef(0.5f, 0.5f, 0.5f);
    glTranslatef(scene->skeleton.position.x, scene->skeleton.position.y, scene->skeleton.position.z + 10);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    angle += 0.1f;
    draw_model(&(scene->skeleton));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[5]);
    glScalef(0.02f, 0.02f, 0.02f);
    glTranslatef(scene->trex.position.x, scene->trex.position.y, scene->trex.position.z);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    draw_model(&(scene->trex));
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[5]);
    glTranslatef(scene->triceratop.position.x, scene->triceratop.position.y, scene->triceratop.position.z);
    glScalef(0.1f, 0.1f, 0.1f);
    glRotatef(angle + 270.0f, 0.0f, 1.0f, 0.0f);
    draw_model(&(scene->triceratop));
    glPopMatrix();

    glPushMatrix();
    glScalef(0.03f, 0.03f, 0.03f);
    glTranslatef(scene->sign.position.x - 200, scene->sign.position.y, scene->sign.position.z - 300);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[10]);
    draw_model(&(scene->sign));
    glPopMatrix();

    glPushMatrix();
    glScalef(0.03f, 0.03f, 0.03f);
    glTranslatef(scene->sign.position.x - 200, scene->sign.position.y, scene->sign.position.z + 300);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[11]);
    draw_model(&(scene->sign));
    glPopMatrix();

    glPushMatrix();
    glScalef(0.03f, 0.03f, 0.03f);
    glTranslatef(scene->sign.position.x - 200, scene->sign.position.y, scene->sign.position.z + 100);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[12]);
    draw_model(&(scene->sign));
    glPopMatrix();

    glPushMatrix();
    glScalef(4.2f, 0.9f, 0.9f);
    glTranslatef(scene->fenceFront.position.x, scene->fenceFront.position.y, scene->fenceFront.position.z);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[8]);
    draw_model(&(scene->fenceFront));
    glPopMatrix();

    glPushMatrix();
    glScalef(4.2f, 0.9f, 0.9f);
    glTranslatef(scene->fenceFront.position.x, scene->fenceFront.position.y, scene->fenceFront.position.z * -1.15);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[8]);
    draw_model(&(scene->fenceFront));
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(4.0f, 0.9f, 0.9f);
    glTranslatef(scene->fenceFront.position.x, scene->fenceFront.position.y, scene->fenceFront.position.z * 0 - 35);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[8]);
    draw_model(&(scene->fenceFront));
    glPopMatrix();

    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glScalef(4.0f, 0.9f, 0.9f);
    glTranslatef(scene->fenceFront.position.x, scene->fenceFront.position.y, scene->fenceFront.position.z * 0 + 35);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[8]);
    draw_model(&(scene->fenceFront));
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, scene->texture_id[7]);
    glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glTranslatef(scene->dron.position.x, scene->dron.position.y, scene->dron.position.z);
    glScalef(0.4f, 0.4f, 0.4f);
    draw_model(&(scene->dron.model));

    glPopMatrix();
}

void draw_grass(Scene *scene)
{
    int i;
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[9]);

    for (i = 0; i < 100; i++)
    {
        glPushMatrix();

        glTranslatef(scene->grass1[i].position.x, 0, scene->grass1[i].position.y);
        glRotatef(scene->grass1[i].rotation, 0, 1, 0);
        glScalef(0.07, 0.07, 0.07);
        glCallList(scene->staticobject_display_list_id[0]);
        glPopMatrix();
    }
}

void draw_space(Scene *scene)
{

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[2]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(100, 60, 100);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(100, 60, -100);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-100, 60, -100);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-100, 60, 100);
    glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, scene->texture_id[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBegin(GL_QUADS);
    int x, z, y;
    for (x = -100; x < 100; x += 3)
    {
        for (z = -100; z < 100; z += 3)
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

    glBindTexture(GL_TEXTURE_2D, scene->texture_id[7]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-100, 0, -100);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-100, 100, -100);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-100, 100, 100);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-100, 0, 100);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, scene->texture_id[7]);

    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(100, 0, 100);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(100, 100, 100);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(100, 100, -100);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(100, 0, -100);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, scene->texture_id[7]);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-100, 0, -100);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(100, 0, -100);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(100, 100, -100);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-100, 100, -100);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, scene->texture_id[7]);

    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-100, 0, 100);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-100, 100, 100);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(100, 100, 100);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(100, 0, 100);
    glEnd();
}
