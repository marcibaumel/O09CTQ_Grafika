#include "camera.h"
#include <GL/glut.h>

#include <math.h>
#include "scene.h"
#define size 15

void can_move(Camera *camera)
{
    if (camera->position.x > size || camera->position.x < -size || camera->position.y < -size || camera->position.y > size || camera->position.z > size / 2 - 1 || camera->position.z < -size / 2 + 1)
    {
        camera->prev_position = camera->position;
    }
}

void init_camera(Camera *camera)
{
    camera->position.x = -10.0;
    camera->position.y = 0.0;
    camera->position.z = 0.8;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    is_preview_visible = FALSE;
}

void update_camera(Camera *camera, double time)
{
    double angle;
    double side_angle;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    if (!(camera->position.x > size || camera->position.x < -size || camera->position.y < -size - 1 || camera->position.y > size - 1 || camera->position.z > size / 8 || camera->position.z < 0.3))
    {
        camera->prev_position = camera->position;
        camera->position.x += cos(angle) * camera->speed.y * time;
        camera->position.y += sin(angle) * camera->speed.y * time;
        camera->position.x += cos(side_angle) * camera->speed.x * time;
        camera->position.y += sin(side_angle) * camera->speed.x * time;
        camera->position.z += camera->speed.z * time;
    }
    else
    {
        camera->position = camera->prev_position;
    }
}

void set_camera_vertical_speed(Camera *camera, double speed)
{
    camera->speed.z = speed;
}

void set_view(const Camera *camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera *camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0)
    {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0)
    {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < -80.0)
    {
        camera->rotation.x = -80.0;
    }

    if (camera->rotation.x > 80.0)
    {
        camera->rotation.x = 80.0;
    }
}

void set_camera_speed(Camera *camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera *camera, double speed)
{
    camera->speed.x = speed;
}

/**
 * @brief 
 * Itt nem nagyon értem, hogy kap egyáltalán textúrát
 */

void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void show_help(struct Scene *scene)
{

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[3]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //glColor3f(scene->light, scene->light, scene->light);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-2, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(2, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(2, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-2, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void show_i(struct Scene *scene)
{

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[13]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-2, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(2, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(2, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-2, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}
void show_o(struct Scene *scene)
{

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[14]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-2, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(2, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(2, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-2, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}
void show_p(struct Scene *scene)
{

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, scene->texture_id[15]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-2, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(2, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(2, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-2, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}