//line pattern

#include<bits/stdc++.h>
#include<GL/glut.h>

using namespace std;



void putpixel(int x,int y){

    glBegin(GL_POINTS);
       glVertex2i(x,y);
    glEnd();
     //cout<<" --- pp --- ";
    glFlush();   
}

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
    
    
    putpixel(x,y);
    
    for(int i=1;i<=steps;i++)
    {
        x+=x_inc;
        y+=y_inc;
        
        X1=floor(x+0.5);
        Y1=floor(y+0.5);
        
        putpixel(X1,Y1);
    }
    
    
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
     
     int x1,y1,x2,y2,x3,y3,x4,y4;
    cout<<"Enter coordinates of outer sqaure : ";
    
    cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    
    //x3=x1;y3=y2;
    //x4=x2;y4=y1;


    dda(x1,y1,x2,y2);
    dda(x2,y2,x3,y3);
    dda(x3,y3,x4,y4);
    dda(x4,y4,x1,y1);

    int mx1,my1,mx2,my2,mx3,my3,mx4,my4;
    mx1=(x1+x2)/2;  my1=(y1+y2)/2;
    mx2=(x2+x3)/2;  my2=(y2+y3)/2;
    mx3=(x3+x4)/2;  my3=(y3+y4)/2;
    mx4=(x4+x1)/2;  my4=(y4+y1)/2;

    dda(mx1,my1,mx2,my2);
    dda(mx2,my2,mx3,my3);
    dda(mx3,my3,mx4,my4);
    dda(mx4,my4,mx1,my1);

    dda((mx1+mx2)/2,(my1+my2)/2,(mx2+mx3)/2,(my2+my3)/2);
    dda((mx2+mx3)/2,(my2+my3)/2,(mx3+mx4)/2,(my3+my4)/2);
    dda((mx3+mx4)/2,(my3+my4)/2,(mx4+mx1)/2,(my4+my1)/2);
    dda((mx4+mx1)/2,(my4+my1)/2,(mx1+mx2)/2,(my1+my2)/2);




    glFlush();
}

void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,700,0,700);
    glFlush();
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Pattern");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
