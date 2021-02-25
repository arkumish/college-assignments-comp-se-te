//assignment 2 circle

#include<bits/stdc++.h>
#include<GL/glut.h>

using namespace std;

int xc,yc,r;
int op;

void init(void){

	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,700,0,700);

	glFlush();

}

void putpixel(int x,int y){

	glBegin(GL_POINTS);
	   glVertex2i(x,y);
	glEnd();
	 //cout<<" --- pp --- ";
	glFlush();   
}

void makecircle(int x, int y)
{  glColor3f(0,1,0);

      putpixel(xc+x,yc+y);
      putpixel(xc+x,yc-y);
      putpixel(xc-x,yc+y);
      putpixel(xc-x,yc-y);

      putpixel(xc+y,yc+x);
      putpixel(xc+y,yc-x);
      putpixel(xc-y,yc+x);
      putpixel(xc-y,yc-x);


          
glFlush();
}




void DDA(){

   glColor3f(1.0,0.0,0.0);
   
   float x1,x2,xi,yi,y1,y2;

   x1=r*cos(0);
   y1=r*sin(0);

   xi=x1;  yi=y1;

   int val; int i=0;

   do{

      val=pow(2,i); i++;

   }while(val<r);

   float e=1/pow(2,i-1);
   glBegin(GL_POINTS);
   do{
          x2=x1+e*y1;
          y2=y1-e*x2;

          glVertex2f(xc+x2,yc+y2);
          glFlush();
          //cout<<" x: "<<xc+x2<<" y : "<<yc+y2;
          x1=x2; y1=y2;
           

   }while((y1-yi)<e || (xi-x1)>e);

   glEnd();
   glFlush();


}



void BSHNM(){

  int p = 3-(2*r);        //decision parameter
     
     int x=0,y=r;
     glBegin(GL_POINTS);
        glVertex2i(xc+x,yc+y);
        glVertex2i(xc-x,yc+y);
        glVertex2i(xc+x,yc-y);
        glVertex2i(xc-x,yc-y);

        glVertex2i(xc+y,yc+x);
        glVertex2i(xc-y,yc+x);
        glVertex2i(xc+y,yc-x);
        glVertex2i(xc-y,yc-x);
        glEnd();



     while(x<y)
     {   makecircle(x,y);
             if(p>=0){
               p+=4*(x-y)+10;y--;
             }
             else
               p+=4*x+6;

             x++;
    
     }


}

void display(void){
  cout<<" i am here ";
  if(op==1) DDA();
  else BSHNM();  
}

int main(int argc , char** argv){

 glutInit(&argc , argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowPosition(100,100);
 glutInitWindowSize(700,700);
 glutCreateWindow("akm");

 init();

 cout<<" enter xc and yc  and radius : ";
 cin>>xc>>yc>>r;
 cout<<" select ( 1: DDA and 2: Bresenhnam ) : ";
 cin>>op;

 



 glutDisplayFunc(display);

glutMainLoop();


	return 0;
}