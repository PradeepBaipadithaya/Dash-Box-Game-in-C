#include <GL/glut.h>
#include<stdio.h>
#include<windows.h>

float y_position = 1.0; //For obstacle dropping from top
float x_direction = 0.0;//For moving our object
int key_l=0,key_r=0;
float x_cord=0;
int count=0;
//static int y_cord =1;


void collision_detected(float rect_x_value, float rect_y_value)
{

    //Collision at top-left and top-right of user obj
    //printf("%f\n",x_direction);
    //printf("%f\n",rect_x_value);
    //printf("%f\n",rect_y_value);
    if(rect_y_value<=-0.45 && rect_y_value>=-0.65 && rect_x_value >= x_direction && rect_x_value-0.2<=x_direction+0.2)
    {
        printf("Collision at top-left of user obj");
       // printf("%f",rect_x_value);
        //printf("%f\n",x_direction);

    }

    //Collision at bottom-right and bottom-left of user obj
     if(rect_y_value<=-0.65 && rect_y_value>=-0.85 && rect_x_value >= x_direction && rect_x_value-0.2<=x_direction+0.2)
    {
        printf("Collision at bottom-left of user obj");
       // printf("%f",rect_x_value);
        //printf("%f\n",x_direction);

    }



}
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

    if(y_position==-10.0)
        y_position=1.0;

    if(y_position>-10.0)
    {
        y_position-=0.005;
        count+=1;
    }


    if(key_l==1 && x_direction>=-1)
    {
        x_direction-=0.015;
        key_l=0;
        //printf("%f",x_direction);
    }
    if(key_r==1 && x_direction<=0.8)
    {
        x_direction+=0.015;
        key_r=0;
        //printf("%f",x_direction);
    }



    glutPostRedisplay();

}

void rect_obstacle(float x_cord,float time_to_start)
{
    glBegin(GL_POLYGON);
    glColor3f(0.1,0.4,0.9);
    //int y_cord = y_position+time_to_start;
    //printf("%f",x_cord);
    collision_detected(x_cord,y_position+time_to_start);
    glVertex3f(x_cord, y_position+time_to_start, 0.0);
    glVertex3f(x_cord-0.2, y_position+time_to_start, 0.0);
    glVertex3f(x_cord-0.2, y_position-0.2+time_to_start, 0.0);
    glVertex3f(x_cord, y_position-0.2+time_to_start, 0.0);
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
    rect_obstacle(0.3,0.0);
    rect_obstacle(-0.9,0.5);
    rect_obstacle(-0.4,0.2);
    rect_obstacle(0.8,0.3);
    rect_obstacle(0.4,0.8);
    rect_obstacle(-0.1,1.3);
    rect_obstacle(0.8,0.36);
    rect_obstacle(0.3,0.3);
    rect_obstacle(-0.8,1.3);
    rect_obstacle(-0.32,1.3);
    rect_obstacle(0.12,0.3);
    rect_obstacle(0.65,1.9);
    rect_obstacle(-0.88,0.3);
    rect_obstacle(0.28,1.39);
    rect_obstacle(-0.48,0.3);
    rect_obstacle(-0.83,1.39);
    rect_obstacle(0.34,0.32);
    rect_obstacle(-0.82,1.3);

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
    glutInitWindowPosition(250, 50);
    glutCreateWindow("Dash board game");
    glutDisplayFunc(displayMe);
    glutTimerFunc(0,timer,0);
    glutSpecialFunc(keyboard_keys);
    glutMainLoop();
    return 0;
}
