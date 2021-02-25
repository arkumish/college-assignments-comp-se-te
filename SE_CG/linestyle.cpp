//assignment : line pattern

#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;

class line_design
{
    int x1,y1,x2,y2;
public:
    void input(){
        cout << "enter coordinates (x1 , y1 , x2 ,y2 ) : ";
        cin >> x1 >> y1 >>x2>>y2;
    }

 void putpixel(int x,int y){

    glBegin(GL_POINTS);
       glVertex2i(x,y);
    glEnd();
     //cout<<" --- pp --- ";
    glFlush();   
}   

void dash()
{
    float dx=x2-x1;
    float dy=y2-y1;
    int steps;
    if(abs(dx)>abs(dy))
        steps=(int)abs(dx);
    else
        steps=abs(dy);
    float xinc=(float)dx/steps;
    float yinc=(float)dy/steps;
    float x,y;
    x=x1;
    y=y1;
    glBegin (GL_POINTS);
    glVertex2i (x,y);
    glEnd ();
    for(int i=1;i<=steps;i++)
    {
        x+=xinc;
        y+=yinc;
        
        x1=x+0.5;
        y1=y+0.5;
        if(i%5<6)
        putpixel(x1,y1);       
    }
}

void dotted()
{
    float dx=x2-x1;
    float dy=y2-y1;
    int steps;
    if(abs(dx)>abs(dy))
        steps=(int)abs(dx);
    else
        steps=abs(dy);
    float xinc=(float)dx/steps;
    float yinc=(float)dy/steps;
    float x,y;
    x=x1;
    y=y1;
    putpixel(x,y);
    for(int i=1;i<=steps;i++)
    {
        x+=xinc;
        y+=yinc;
        
        x1=x+0.5;
        y1=y+0.5;
        if(i%4==0)
        putpixel(x1,y1);
    }
}


void thick()
{
    float thickness,wy,wx;
    cout<<"\nEnter the thickness of line : ";
    cin>>thickness;
    
    if(x2!=x1){
    if ((y2 - y1) / (x2 - x1) < 1)    
    {
         wy = (thickness-1)*sqrt(pow((x2-x1),2)+pow((y2-y1),2))/(2*fabs(x2-x1));
         for(int i = 0; i < wy; i++)
         {
             dda(x1, y1 - i, x2, y2 - i);
             dda(x1, y1 + i, x2, y2 + i);
         }
    }
    else
    {
         wx = (thickness-1)*sqrt(pow((x2-x1),2)+pow((y2-y1),2))/(2*fabs(y2-y1));
         for(int i = 0; i < wx; i++)
         {
             dda(x1 - i, y1, x2 - i, y2);
             dda(x1 + i, y1, x2 + i, y2);
         }
    }

}
    
    
}

void dda(float x1,float y1,float x2,float y2)
{
    float dx=x2-x1;
    float dy=y2-y1;
    int steps;
    if(abs(dx)>abs(dy))
        steps=(int)abs(dx);
    else
        steps=abs(dy);
    float xinc=(float)dx/steps;
    float yinc=(float)dy/steps;
    float x,y;
    x=x1;
    y=y1;
    putpixel(x,y);
    for(int i=1;i<=steps;i++)
    {
        x+=xinc;
        y+=yinc;
        
        x1=x+0.5;
        y1=y+0.5;
        putpixel(x1,y1);
    }
}
};


void display ( ){
    line_design b; 
    glClearColor(0.0,0.0,0.0,0.0);
    glClear (GL_COLOR_BUFFER_BIT); 
    glColor3f(1.0,1.0,0.0);
    int op;
    do{
        cout<<" ---------------- LINE DESIGN ----------------------" << endl;
        cout << "1)\t Dashed line" << endl;
        cout << "2)\t Dotted line" << endl;
        cout << "3)\t Thick line" << endl;
        cout << "-1)\tEXIT" << endl;
        cout<<" select option : ";
        cin >> op;
        switch(op){
            case 1:
                b.input();
                b.dash();
                glFlush();
                break;
            case 2:
                b.input();
                b.dotted();   
                glFlush();
                break;
            case 3:
                b.input();
                b.thick();   
                glFlush();
                break;
            case 0:
                cout << "exit" << endl;
                break;
            default:
                cout << "kindly check your input" << endl;
        }
    }
    while(op);
}

void init(){
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(0.0,500.0,0.0,500.0);
        glFlush();
}

int main(int argc , char *argv[]){
    glutInit (&argc, argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow ("line design "); 
    init();
    glutDisplayFunc (display);
    glutMainLoop ();
}



