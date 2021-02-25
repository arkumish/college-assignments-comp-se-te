//Pattern uisng circle and line

#include<bits/stdc++.h>
#include<GL/glut.h>

using namespace std;

void dda(int X1,int Y1,int X2,int Y2)
{
    int dx,dy,steps,x_inc,y_inc;
    dx=X2-X1;
    dy=Y2-Y1;
    
    steps=abs(dx)>abs(dy)?abs(dx):abs(dy);
    x_inc=(float)dx/steps;
    y_inc=(float)dy/steps;
    
    int x,y;
    x=X1;
    y=Y1;
    
    
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    
    for(int i=1;i<=steps;i++)
    {
        x+=x_inc;
        y+=y_inc;
        
        X1=floor(x+0.5);
        Y1=floor(y+0.5);
        
        glBegin(GL_POINTS);
        glVertex2i(X1,Y1);
        glEnd();
    }

}    

void cir(int g,int f,int r)
{
    int x=0,y=r,p=3-(2*r);

    glClear(GL_COLOR_BUFFER_BIT);    
    while(x<y)
    {
        glBegin(GL_POINTS);
        glVertex2i(g+x,f+y);
        glVertex2i(g-x,f+y);
        glVertex2i(g+x,f-y);
        glVertex2i(g-x,f-y);
        glVertex2i(g+y,f+x);
        glVertex2i(g-y,f+x);
        glVertex2i(g+y,f-x);
        glVertex2i(g-y,f-x);
        glEnd();
        
        if(p>=0)
        {
            p+=4*(x-y)+10;
            y--;
        }
        else
            p+=4*x+6;
        x++;
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    dda(100,50,200,50);
    dda(200,50,200,250);
    dda(200,250,100,250);
    dda(100,250,100,50);
    cir(50,50,100);
    cir(50,50,150);
    glFlush();
}

void init(void)
{
    glClearColor(0.0,0.5,0.5,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500,500,-500,500);
}

int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Pattern");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
