#include <GL/glut.h>
#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
float y_position = 1.0; //For obstacle dropping from top
float x_direction = 0.0;//For moving our object
int key_l=0,key_r=0;
float x_cord=0;
int count=0;
int score_value =0;
int health_value =3;
int flag =1;
//static int y_cord =1;
float a[250];

//double r[20];


float rand_zo(){
    float r=(float)rand() / (float)RAND_MAX;
    return r;
}
float random_num()
{

    float ra=(float)rand() / (float)RAND_MAX;
    float r =fmod((float)rand(),50.0)+ra;
    return  r;
}

void score(int score_value){
    char r2[50];
    itoa(score_value,r2,10);
    char r1[]="SCORE : ";
    glColor3f(1.0,1.0,1.0);
    glRasterPos3f(-0.98,0.9,0.0);
    for(int i=0;r1[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r1[i]);


    for(int i=0;r2[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r2[i]);
}


void health(int health_value){
    char r2[50];
    itoa(health_value,r2,10);
    char r1[]="HEALTH : ";
    glColor3f(1.0,1.0,1.0);
    glRasterPos3f(0.70,0.9,0.0);
    for(int i=0;r1[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r1[i]);

    for(int i=0;r2[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r2[i]);

}

void collision_detected(float rect_x_value, float rect_y_value)
{

    if(rect_y_value<=-0.45 && rect_y_value>=-0.65 && rect_x_value >= x_direction && rect_x_value-0.2<=x_direction+0.2)
    {
        //printf("Collision at top-left of user obj");
        x_direction = 0.0;
        y_position +=0.8;
        health_value-=1;

    }

    //Collision at bottom-right and bottom-left of user obj
     if(rect_y_value<=-0.65 && rect_y_value>=-0.85 && rect_x_value >= x_direction && rect_x_value-0.2<=x_direction+0.2)
    {
        //printf("Collision at bottom-left of user obj");
        x_direction = 0.0;
        y_position +=0.8;
        health_value-=1;

    }
}

void update_score(float rect_y_value)
{
    if(rect_y_value>=-1.004998 && rect_y_value<=-0.999998)
    {
        score_value+=10;
        //printf("%f",rect_y_value);
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

    if(y_position>=-1.004998 && y_position<=-0.999998)
    {


        score_value+=10;
        printf("%f",y_position);
    }


    if(y_position>-500.0)
    {
        y_position-=0.005;
        //printf("%f\n",y_position);
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

void rect_obstacle(float x_cord,double time_to_start)
{
    glBegin(GL_POLYGON);
    glColor3f(0.1,0.4,0.9);
    //int y_cord = y_position+time_to_start;
    //printf("%f",x_cord);
    collision_detected(x_cord,y_position+time_to_start);
    update_score(y_position+time_to_start);
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

void finish(int score_value){
    glClear(GL_COLOR_BUFFER_BIT);

    char r3[50];
    itoa(score_value,r3,10);
    char r1[]="GAME OVER ";
    char r2[]="TOTAL SCORE : ";
    glColor3f(1.0,1.0,1.0);
    glRasterPos3f(-0.2,0.0,0.0);
    for(int i=0;r1[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r1[i]);
    glRasterPos3f(-0.25,-0.1,0.0);
    for(int i=0;r2[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r2[i]);

    for(int i=0;r3[i]!='\0';i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,r3[i]);

}

void displayMe(void)
{
    ground_line();
    score(score_value);
    health(health_value);

    srand(time(0));
    if(health_value<=0){
        finish(score_value);
        y_position=-500;
        x_direction=-2.0;
    }

    if(flag){
    for(int i=0; i<250;i++){
            a[i] =random_num();
            //printf("%f\n",a[i]);
        }
        flag =0;
    }
    for(int i=0;i<250;i=i+10)
    {
        rect_obstacle(-0.8,a[i]);
        rect_obstacle(-0.7,a[i+1]);
        rect_obstacle(-0.5,a[i+2]);
        rect_obstacle(-0.3,a[i+3]);
        rect_obstacle(-0.1,a[i+4]);
        rect_obstacle(0.1,a[i+5]);
        rect_obstacle(0.3,a[i+6]);
        rect_obstacle(0.5,a[i+7]);
        rect_obstacle(0.7,a[i+8]);
        rect_obstacle(0.85,a[i+9]);
    }

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
