//assignment 1

#include<bits/stdc++.h>
#include<GL/glut.h>

using namespace std;

int x1,x2,y2,y3;
int op;

void init(void){

	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,500,0,300);

	glFlush();

}

void putpixel(int x,int y){

	glBegin(GL_POINTS);
	   glVertex2i(x,y);
	glEnd();
	 //cout<<" --- pp --- ";
	glFlush();   
}

int round_value(float x)
{
	int k=floor(x+0.5);

	return k;
}

void DDA(){

   glColor3f(0.0,0.4,0.2);

   double dx=x2-x1;
   double dy=y3-y2;

   double steps;

   steps= (abs(dx)>abs(dy))?abs(dx):abs(dy);

   float xinc , yinc , x=x1, y=y2;

   xinc= dx/(float)steps;
   yinc=dy/(float)steps;

   putpixel(x1,y2);
   glFlush();

   for(int k=0;k<steps;k++)
   {
      x+=xinc;
      y=y+yinc;

      putpixel(round_value(x),round_value(y));

   }

}


int sign(int x){
 if(x>0) return 1;
 else if(x<0) return -1;
 else return 0;

}

void BSHNM(){

	glColor3f(0.0,0.4,0.2);

  int dx=abs(x2-x1);
  int dy=abs(y3-y2);

  int s1=sign(x2-x1);
  int s2=sign(y3-y2);

   int g;  //error factor
   int x=x1,y=y2;
   if(dx>=dy)      //m<=1 steep slope
   {
       g=2*dy-dx;

       for(int k=0;k<=dx;k++)
       {   
       	  putpixel(x,y);
       	  //cout<<x<<" "<<y<<endl;
            if(g>=0)
            {
            	x+=s1;
            	y+=s2;
            	g+=(2*dy-2*dx);
            }
            else{
            	x+=s1;
            	g+=2*dy;
            }

       }
     putpixel(x2,y3);
    }
    else{
       
        g=2*dx-dy;

        for(int k=0;k<=dy;k++)
        {
        	putpixel(x,y);
        	cout<<x<<" "<<y<<endl;
        	if(g>=0)
        	{
        		x+=s1;
        		y+=s2;
        		g+=2*dx-2*dy;

        	}
        	else{
        		y+=s2;
        		g+=2*dx;
        	}
        }


   putpixel(x2,y3);
    }


glFlush();
}

void display(void){

  if(op==1) DDA();
  else BSHNM();
}

int main(int argc , char** argv){

 glutInit(&argc , argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowPosition(100,100);
 glutInitWindowSize(500,300);
 glutCreateWindow("akm");

 init();

 cout<<" enter x1 and x2 and y1 and y2 : ";
 cin>>x1>>y2>>x2>>y3;
 cout<<" select ( 1: DDA and 2: Bresenhnam ) : ";
 cin>>op;



 glutDisplayFunc(display);

glutMainLoop();


	return 0;
}