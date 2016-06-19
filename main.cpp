#ifdef __APPLE__
#include <GLUT/glut.h>
#else 
#include <GL/glut.h> 
#endif

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/time.h>
#include <glm/glm.hpp>

#include "glui.h"
//#include "terrain.h"
#include "rover.h"
#include "camera.h"

//globals
static int g_Width = 600;
static int g_Height = 600;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;

int window_id;

float rover_z = 0.0;

float angle = 0.0;
float lx = 0.0, lz = -1.0;
float x = 400.0, z = -400.0;

Camera camera;

struct ControlStates
{
    bool forward, backward, left, right, yawLeft, yawRight, pitchUp,
    pitchDown, rollLeft, rollRight;
} controls;

void init()
{
    controls.forward = false;
    controls.backward = false;
    controls.left = false;
    controls.right = false;
    controls.rollRight = false;
    controls.rollLeft = false;
    controls.pitchDown = false;
    controls.pitchUp = false;
    controls.yawLeft = false;
    controls.yawRight = false;
}

/*keyboard
void processNormalKeys(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

void processSpecialKeys(int key, int xx, int yy)
{
    float fraction = 1;
    
    switch (key)
    {
        case GLUT_KEY_LEFT:
            angle -= 0.01;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_RIGHT:
            angle += 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_UP:
            x += lx * fraction;
            z += lz * fraction;
            break;
        case GLUT_KEY_DOWN:
            x -= lx * fraction;
            z -= lz * fraction;
            break;
    }
}
*/

void myGlutIdle()
{
    if(glutGetWindow() != window_id)
        glutSetWindow(window_id);
    glutPostRedisplay();
}

void moveRover()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glPushMatrix();
    glTranslatef(0, 0, rover_z);
    glVertexPointer(3, GL_FLOAT, 0, roverPositions);
    glDrawArrays(GL_TRIANGLES, 0, roverVertices);
    
    
    glPopMatrix();
    glDisableClientState(GL_VERTEX_ARRAY);
    
    rover_z -=1;
    
}

void drawGrid(int HALF_GRID_SIZE)
{
    glBegin(GL_LINES);
    glColor3f(0.75f, 0.75f, 0.75f);
    for(int i=-HALF_GRID_SIZE;i<=HALF_GRID_SIZE;i++)
    {
        glVertex3f((float)i,0,(float)-HALF_GRID_SIZE);
        glVertex3f((float)i,0,(float)HALF_GRID_SIZE);
        
        glVertex3f((float)-HALF_GRID_SIZE,0,(float)i);
        glVertex3f((float)HALF_GRID_SIZE,0,(float)i);
    }
    glEnd();
}

void renderScene()
{
    if (controls.forward) camera.forward();		if (controls.backward) camera.backward();
    if (controls.left) camera.left();			if (controls.right) camera.right();
    if (controls.yawLeft) camera.yawLeft();		if (controls.yawRight) camera.yawRight();
    if (controls.rollLeft) camera.rollLeft();	if (controls.rollRight) camera.rollRight();
    if (controls.pitchUp) camera.pitchUp();		if (controls.pitchDown) camera.pitchDown();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100, (float)g_Width / (float)g_Height, g_nearPlane, g_farPlane);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    camera.transformOrientation();
    
    /*
    gluLookAt
    (
        x, 600.0, z,
        x + lx, 1.0, z + lz,
        0.0, 1.0, 0.0
    );*/
    
    //glPushMatrix();
    //glTranslatef(0, -109.624, 0);
    drawGrid(1000);
    //glPopMatrix();
    
    
    
    /*
   //Draw Ground *later going to be terrain*
    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
    glTranslatef(0, -109.624, 0);
    glRectf(-1000.0, 1000.0, 1000.0, -1000.0);
    glPopMatrix();

  
    
    terrainLoadFromImage("heightmap.tga", 1);
    terrainScale(-10, 30);
    int myDisplayList = terrainCreateDL(0, 0, 0);
    glCallList(myDisplayList);
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, roverPositions);
    glDrawArrays(GL_TRIANGLES, 0, roverVertices);
    glDisableClientState(GL_VERTEX_ARRAY);*/
    glColor3f(1.0, 1.0, 1.0);
    moveRover();
    
    glFlush();
    glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
            controls.forward = true;
            break;
        case 's':
            controls.backward = true;
            break;
        case 'a':
            controls.left = true;
            break;
        case 'd':
            controls.right = true;
            break;
        case 'l':
            controls.rollRight = true;
            break;
        case 'j':
            controls.rollLeft = true;
            break;
        case 'i':
            controls.pitchDown = true;
            break;
        case 'k':
            controls.pitchUp = true;
            break;
        case 'q':
            controls.yawLeft = true;
            break;
        case 'e':
            controls.yawRight = true;
            break;
    }
    
}

void keyUp(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w':
            controls.forward = false;
            break;
        case 's':
            controls.backward = false;
            break;
        case 'a':
            controls.left = false;
            break;
        case 'd':
            controls.right = false;
            break;
        case 'l':
            controls.rollRight = false;
            break;
        case 'j':
            controls.rollLeft = false;
            break;
        case 'i':
            controls.pitchDown = false;
            break;
        case 'k':
            controls.pitchUp = false;
            break;
        case 'q':
            controls.yawLeft = false;
            break;
        case 'e':
            controls.yawRight = false;
            break;
    }
}

void changesize(int w, int h)
{
    g_Width = w;
    g_Height = h;
    
    float ratio = 1.0 * w / h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(100, ratio, g_nearPlane, g_farPlane);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    //init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(1, 1);
    glutInitWindowSize(g_Width, g_Height);
    window_id = glutCreateWindow("Simulation");
    init();
    
    //register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changesize);
    glutIdleFunc(moveRover);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    
    //GLUI
    GLUI *glui = GLUI_Master.create_glui( "GLUI");
    glui->add_statictext("Simulation Options");
    glui->add_column(1);
    
    
    
    glui->set_main_gfx_window(window_id);
    GLUI_Master.set_glutIdleFunc(myGlutIdle);

    //enter GLUT event processing cycle
    glutMainLoop();
    
    
    return 1;
}

