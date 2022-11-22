
#define GLEW_STATIC

#include <stdlib.h>
#include <GL/glut.h>

GLfloat vertices[] = { -1, -1, -1,   //setting up cube vertices
                       1, -1, -1,
                       1, 1, -1,
                      -1, 1, -1,
                      -1, -1, 1,
                      1, -1, 1,
                      1, 1, 1,
                      -1, 1, 1 };

GLfloat colours[] = { 0, 0, 0,   //setting up cloours for the cube vertices
                       1, 0, 0,
                       1, 1, 0,
                       0, 1, 0,
                       0, 0, 1,
                       1, 0, 1,
                       1, 1, 1,
                       0, 1, 1 };
GLubyte cubeIndices[] = { 0, 3, 2, 1,
                          2, 3, 7, 6,
                          0, 4, 7, 3,
                          1, 2, 6, 5,
                          4, 5, 6, 7,
                          0, 1, 5, 4 };

static GLfloat theta[] = { 0, 0, 0 };  //array variable for angles
static GLint axis = 2;   //assume right moue is clicked initally 

void display(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(theta[0], 1, 0, 0);     //angle rotation for x axis
    glRotatef(theta[1], 0, 1, 0);     //angle rotation for y axis
    glRotatef(theta[2], 0, 0, 1);     //angle rotation for z axis

    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);  //draw the cube
    glutSwapBuffers();  //show the output
}

void spinCube() 
{
    theta[axis] += 0.05f;  //rotate for 2 degrees

    if (theta[axis] > 360) //if angle goes over 360, make it 0
    {
        theta[axis] -= 360; 
    }

    glutPostRedisplay(); // call display again
}

void mouse(int button, int state, int x, int y) 
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) //if left mouse button is pressed rotate x axis
    {
        axis = 0;
    }

    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) //if middle mouse button is pressed rotate y axis
    {
        axis = 1;
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) //if right mouse button is pressed rotate z axis
    {
        axis = 2;
    }


}

void Reshape(int w, int h) 
{
    glViewport(0, 0, w, h);  //setting up the window
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();

    if (w <= h) 
    {
        glOrtho(-2, 2, -2 * (GLfloat)h / (GLfloat)w, 2 * (GLfloat)h / (GLfloat)w, -10, 10); //ensuring window set up is correct
    } 
    else
        glOrtho(-2 * (GLfloat)w / (GLfloat)h, 2 * (GLfloat)w / (GLfloat)h, -2, 2, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //Initialising window
    glutInitWindowSize(1000, 1000); //Establishing window size
    glutCreateWindow("Spinny CUBE!!!!!"); //Creating window

    glutReshapeFunc(Reshape); //calls window reshape function when window is adjusted
    
    glutDisplayFunc(display); // call display function
    
    glutIdleFunc(spinCube); //when window is idle call spinCube

    glutMouseFunc(mouse); //calls mouse function when using a mouse

    glEnable(GL_DEPTH_TEST); // enables depth for 3D

    glEnableClientState(GL_COLOR_ARRAY); //enables color and vertx operations
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colours);

    glColor3f(1, 1, 1);

    glutMainLoop();
}