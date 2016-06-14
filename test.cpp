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

//#include "terrain.h"
#include "rover.h"


//globals
static int g_Width = 600;
static int g_Height = 600;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;

int attribute_position, attribute_vertex;


float angle = 0.0;
float lx = 0.0, lz = -1.0;
float x = 100.0, z = 105.0;


//keyboard
void processNormalKeys(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

void processSpecialKeys(int key, int xx, int yy)
{
    float fraction = 0.5;
    
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

void renderScene()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    gluLookAt
    (
        x, 400.0, z,
        x + lx, 1.0, z + lz,
        0.0, 1.0, 0.0
    );
    
   /* //Draw Ground *later going to be terrain*
    
    glBegin(GL_QUADS);
        glVertex3f(-100.0, 0.0, -100);
        glVertex3f(-100.0, 0.0, 100);
        glVertex3f(100.0, 0.0, -100);
        glVertex3f(100.0, 0.0, -100);
    glEnd();

  
    
    terrainLoadFromImage("heightmap.tga", 1);
    terrainScale(-10, 30);
    int myDisplayList = terrainCreateDL(0, 0, 0);
    glCallList(myDisplayList);*/
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, roverPositions);
    glDrawArrays(GL_TRIANGLES, 0, roverVertices);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    glutSwapBuffers();
}

void changesize(GLint w, GLint h)
{
    g_Width = w;
    g_Height = h;
    
    float ratio = 1.0 * w / h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(65, ratio, g_nearPlane, g_farPlane);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char **argv)
{
    //init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowPosition(1, 1);
    glutInitWindowSize(g_Width, g_Height);
    glutCreateWindow("Simulation");
    
    //register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changesize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    //enter GLUT event processing cycle
    glutMainLoop();
    
    
    return 1;
}

