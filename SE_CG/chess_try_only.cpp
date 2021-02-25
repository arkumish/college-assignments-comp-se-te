#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;

struct COLOR{
float r;
float g;
float b;
};

void setPixel(int pointx, int pointy, COLOR c)   
      {   
              glColor3f(c.r,c.g,c.b); 
             glBegin(GL_POINTS);   
                  glVertex2f(pointx,pointy);   
             glEnd();   
             glFlush();   
      }

      COLOR getPixel(int x, int y)   
      {   
      	   COLOR c;
           glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,&c);   
           return c;
      }   

void init2d()
{
glClearColor(1.0, 1.0, 1.0,0.0);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(0, 500, 0, 550);
}
void draw(){
	float x=0, y=0;
	COLOR obj = {1, 0, 0};
	for(int i=0;i<5;i++){
       float x1,x2,y1,y2;
	   x1=i*50;
	   x2=i*50;
	   y1=0;
	   y2=200;

	    x=x2*cos((M_PI/180)*45) - y2*sin((M_PI/180)*45);
	    y=x2*sin((M_PI/180)*45) + y2*cos((M_PI/180)*45);

	
	   float xx=x1*cos((M_PI/180)*45) - y1*sin((M_PI/180)*45);
	   float yy=x1*sin((M_PI/180)*45) + y1*cos((M_PI/180)*45);
		if(i == 0)
		{
     	setPixel(x + 250, y + 250, obj);
		}
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		 glVertex2f(x+250,y+250);
		 glVertex2f(xx+250,yy+250);
		glEnd();
	 
	}

	for(int i=0;i<5;i++){
       float x1,x2,y1,y2;
	   x1=0;
	   x2=200;
	   y1=i*50;
	   y2=i*50;

	    x=x2*cos((M_PI/180)*45) - y2*sin((M_PI/180)*45);
	    y=x2*sin((M_PI/180)*45) + y2*cos((M_PI/180)*45);

	
	   float xx=x1*cos((M_PI/180)*45) - y1*sin((M_PI/180)*45);
	   float yy=x1*sin((M_PI/180)*45) + y1*cos((M_PI/180)*45);
		setPixel(x + 250, y + 250, obj);
		glColor3f(0, 0, 0); 
		glBegin(GL_LINES);
		 glVertex2f(x+250,y+250);
		 glVertex2f(xx+250,yy+250);
		glEnd();
	 
	}

	glFlush();
}

 


void floodfill(int x,int y,COLOR newcolor,COLOR oldcolor){
	
	COLOR cc;
	 cc=getPixel(x,y);
    
	if(cc.r==oldcolor.r && cc.g==oldcolor.g && cc.b==oldcolor.b ){
        
         cout<<x<<" "<<y<<endl;
         setPixel(x,y,newcolor);
		 floodfill(x+1,y,newcolor,oldcolor);
		 floodfill(x,y+1,newcolor,oldcolor);
		 floodfill(x-1,y,newcolor,oldcolor);
		 floodfill(x,y-1,newcolor,oldcolor);
		   
	}
	return;
}

void Mouse(int button,int state,int x,int y){
	if(button==GLUT_LEFT_BUTTON && state ==GLUT_DOWN)
	{
y=550-y;
	cout<<x<<" "<<y<<endl;
	COLOR c=getPixel(x,y);
   
    //cout<<c.r<<" "<<c.g<<" "<<c.b<<endl;

	COLOR n;
	n.r=0;
	n.g=0;
	n.b=0;
	floodfill(x,y,n,c);
}
}

void disp(void){
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.0,0.0,0.0);
   draw();
}

int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 550);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("CHESS");
	glutDisplayFunc(disp);
	init2d();
	glutMouseFunc(Mouse);
	glutMainLoop();
    return 0;
}
