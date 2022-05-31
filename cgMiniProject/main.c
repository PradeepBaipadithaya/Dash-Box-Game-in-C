#include <GL/glut.h>
#include<stdio.h>
#include<windows.h>

float y_position = 1.0; //For obstacle dropping from top
float x_direction = 0.0;//For moving our object
int key_l=0,key_r=0;
float x_cord=0;
void keyboard_keys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_LEFT:
        key_l=1;
        //printf("%d",key_l);
        break;
    case GLUT_KEY_RIGHT:
        key_r=1;
        //printf("%d",key_r);
        break;
    }
}
void timer(int)
{

    glutTimerFunc(1000/60,timer,0);
    if(y_position>-1)
        y_position-=0.005;
    if(key_l==1)
    {
        x_direction-=0.015;
        key_l=0;
        //printf("%f",x_direction);
    }
    if(key_r==1)
    {
        x_direction+=0.015;
        key_r=0;
        //printf("%f",x_direction);
    }
    glutPostRedisplay();

}

void rect_obstacle(float x_cord)
{
    glBegin(GL_POLYGON);
    glColor3f(0.1,0.4,0.9);
    printf("%f",x_cord);
    glVertex3f(-x_cord, y_position, 0.0);
    glVertex3f(-x_cord+0.2, y_position, 0.0);
    glVertex3f(-x_cord+0.2, y_position-0.2, 0.0);
    glVertex3f(-x_cord, y_position-0.2, 0.0);
    glEnd();
    glFlush();
}
void ground_line(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(0.1,0.4,0.2);
    glVertex3f(-1.0, -1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0);
    glVertex3f(1.0, -0.85, 0.0);
    glVertex3f(-1.0, -0.85, 0.0);
    glEnd();
    glFlush();

}

void user_obj(int x_value)
{

    glColor3f(0.6,0.8,0.2);
    glBegin(GL_POLYGON);
    glVertex3f(x_value, -0.85, 0.0);
    glVertex3f(x_value+0.2, -0.85, 0.0);
    glVertex3f(x_value+0.2, -0.65, 0.0);
    glVertex3f(x_value, -0.65, 0.0);
    glEnd();
    glFlush();
}


void displayMe(void)
{
    ground_line();
    //user_obj(x_direction);
    rect_obstacle(0.3);
    rect_obstacle(-0.9);
    rect_obstacle(-0.4);
    rect_obstacle(0.8);
    glColor3f(0.6,0.8,0.2);
    glBegin(GL_POLYGON);
    glVertex3f(x_direction, -0.85, 0.0);
    glVertex3f(x_direction+0.2, -0.85, 0.0);
    glVertex3f(x_direction+0.2, -0.65, 0.0);
    glVertex3f(x_direction, -0.65, 0.0);
    glEnd();
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE );
    glutInitWindowSize(1000, 700);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Dash board game");
    glutDisplayFunc(displayMe);
    glutTimerFunc(0,timer,0);
    glutSpecialFunc(keyboard_keys);
    glutMainLoop();
    return 0;
}
