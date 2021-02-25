#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;

int g,f,r;

void display(void)
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
    glFlush();
}

void init(void)
{
    glClearColor(1.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500,500,-500,500);
}

int main(int argc,char** argv)
{
    cout<<"Enter the center of the circle: ";
    cin>>g>>f;
    cout<<"\nEnter the radius of the circle: ";
    cin>>r;
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(50,100);
    glutCreateWindow("Bresenham circle drawing algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
