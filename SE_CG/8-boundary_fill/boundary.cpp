#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

using namespace std;

int n,x,y;
void delay(float ms){
    clock_t goal = ms + clock();
    while(goal>clock());
}

void init(){
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,640,0,480);
}

void bound_it(int x, int y, float* fillColor, float* bc){
    float color[3];
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
    if((color[0]!=bc[0] || color[1]!=bc[1] || color[2]!=bc[2])&&(
     color[0]!=fillColor[0] || color[1]!=fillColor[1] || color[2]!=fillColor[2])){
        glColor3f(fillColor[0],fillColor[1],fillColor[2]);
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        glFlush();

        /* for 4 connected */
        bound_it(x+1,y,fillColor,bc);
        bound_it(x-2,y,fillColor,bc);
        bound_it(x,y+2,fillColor,bc);
        bound_it(x,y-2,fillColor,bc);
     

        /* for 8 connected 
           
        bound_it(x + 1, y, fillColor,bc);
        bound_it(x, y + 1, fillColor,bc);
        bound_it(x - 1, y, fillColor,bc);
        bound_it(x, y - 1, fillColor,bc);
        bound_it(x - 1, y - 1, fillColor,bc);
        bound_it(x - 1, y + 1, fillColor,bc);
        bound_it(x + 1, y - 1, fillColor,bc);
        bound_it(x + 1, y + 1, fillColor,bc);



        */

    }
}

void mouse(int btn, int state, int x, int y){
    y = 480-y;
    if(btn==GLUT_LEFT_BUTTON)
    {
        if(state==GLUT_DOWN)
        {
            float bCol[] = {1,0,0};
            float color[] = {0,0,1};
            //glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,intCol);
            bound_it(x,y,color,bCol);
        }
    }
}

void world(){
    glLineWidth(3);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    cout<<" enter value of n : ";
    cin>>n;
    cout<<" enter ( "<<n<<" ) coordinates of shape : \n";
    glBegin(GL_LINE_LOOP);
     for(int i=0;i<n;i++){
        cin>>x>>y;
        glVertex2i(x,y);
        
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(200,200);
    glutCreateWindow("Many Amaze Very GL WOW");
    glutDisplayFunc(world);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}