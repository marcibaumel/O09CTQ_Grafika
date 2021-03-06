#include "callbacks.h"
#include "scene.h"
#include "dronMove.h"
#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 50.0

struct
{
    int x;
    int y;
} mouse_position;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&camera);
    draw_scene(&scene);
    glPopMatrix();

    if (is_preview_visible)
    {
        show_help(&scene);
    }
    if (is_i_visible)
    {
        show_i(&scene);
    }
    if (is_o_visible)
    {
        show_o(&scene);
    }
    if (is_p_visible)
    {
        show_p(&scene);
    }

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO)
    {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else
    {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 1000.0);
}

void mouse(int button, int state, int x, int y)
{
    mouse_position.x = x;
    mouse_position.y = y;
}

void motion(int x, int y)
{
    rotate_camera(&camera, mouse_position.x - x, mouse_position.y - y);
    mouse_position.x = x;
    mouse_position.y = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        set_camera_speed(&camera, 3);
        break;
    case 's':
        set_camera_speed(&camera, -3);
        break;
    case 'a':
        set_camera_side_speed(&camera, 3);
        break;
    case 'd':
        set_camera_side_speed(&camera, -3);
        break;
    case 't':
        if (is_preview_visible)
        {
            is_preview_visible = FALSE;
        }
        else
        {
            is_preview_visible = TRUE;
        }
        break;

    case 'i':
        if (is_i_visible)
        {
            is_i_visible = FALSE;
        }
        else
        {
            is_i_visible = TRUE;
        }
        break;
    case 'o':
        if (is_o_visible)
        {
            is_o_visible = FALSE;
        }
        else
        {
            is_o_visible = TRUE;
        }
        break;
    case 'p':
        if (is_p_visible)
        {
            is_p_visible = FALSE;
        }
        else
        {
            is_p_visible = TRUE;
        }
        break;
    case '+':
        if (scene.light < 1.0)
        {
            scene.light += 0.1;
        }
        break;
    case '-':
        if (scene.light > 0.2)
        {
            scene.light -= 0.1;
        }
        break;
    case 'q':
        set_camera_vertical_speed(&camera, -2);
        break;
    case 'e':
        set_camera_vertical_speed(&camera, 2);
        break;
    case 'v':
        set_dronMove_speed(&(scene.movedron), 4);
        break;
    case 'b':
        set_dronMove_speed(&(scene.movedron), -4);
        break;
    case 'n':
        rotate_dronMove(&(scene.movedron), -25);
        break;
    case 'm':
        rotate_dronMove(&(scene.movedron), 25);
        break;
    case 'k':
        set_dronMove_scale(&(scene.movedron), 0.01);
        break;
    case 'l':
        set_dronMove_scale(&(scene.movedron), -0.01);
        break;
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 's':
        set_camera_speed(&camera, 0.0);
        break;
    case 'a':
    case 'd':
        set_camera_side_speed(&camera, 0.0);
        break;
    case 'q':
    case 'e':
        set_camera_vertical_speed(&camera, 0.0);
        break;
        x = x;
        y = y;
    case 'v':
    case 'b':
        set_dronMove_speed(&(scene.movedron), 0.0);
        break;
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;

    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time);
    move_dron(&(scene.dron), elapsed_time);
    move_dronMove(&(scene.movedron), elapsed_time);
    rotate_dronMove(&(scene.movedron), 0);

    glutPostRedisplay();
}
