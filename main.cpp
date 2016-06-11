#ifdef __APPLE__
#include <GLUT/glut.h>
#else 
#include <GL/glut.h> 
#endif

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <glm/glm.hpp>

//globals
static int g_Width = 600;
static int g_Height = 600;
static GLfloat g_nearPlane = 1;
static GLfloat g_farPlane = 1000;


float angle = 0.0f;

void renderScene()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    gluLookAt
    (
        0.0f, 0.0f, 10.0f,
        0.0f, 0.0f, 0.0f,
        0.f, 1.0f, 0.0f
    );
    
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.0, -2.0, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    glVertex3f(0.0, 2.0, 0.0);
    glEnd();
    
    angle += 0.1f;
    
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
    
    //idle
    glutIdleFunc(renderScene);
    
    //enter GLUT event processing cycle
    glutMainLoop();
    
    
    return 1;
}

