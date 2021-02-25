#include<stdio.h>
#include<GL/glut.h>
GLfloat x1,y1,x2,y2,x3,y3,x4,y4;
void edgedetect(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,int *le,int *re)
{
            float mx,x,temp;
            int i;
            if((y2-y1)<0)    // if second point is below first point interchange them
            {
              temp=x1;x1=x2;x2=temp;
              temp=y1;y1=y2;y2=temp;
            }
              if((y2-y1)!=0)      // if denominator is zero we can't find slope
                        mx=(x2-x1)/(y2-y1);
            else
                        mx=x2-x1;    // y2-y1=0 implies line is horizontal
            x=x1;
            for(i=y1;i<y2;i++)        // starting from x1,y1 add slope mx to x
            {                                  // and round it to find the next point on the
                                                // line. For that particular scan line i
                        if(x<le[i])         // insert the x value into either le or re.
                                    le[i]=x; // Initially both le and re will contain same 
                                                // value...
                        if(x>re[i])         // in the next time for the other edge
                                    re[i]=x; // either le or re will change
                        x+=mx;            // NOTE: le and re are integer arrays and x
            }                                  // is float so automatic type conversion.
}
void drawpixel(int x,int y)
{
            glColor3f(0.0,1.0,1.0);
            glBegin(GL_POINTS);
            glVertex2i(x,y);
            glEnd();
}
void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
            int le[500],re[500];
            int i,y;
            for(i=0;i<500;i++)   // initialize le and re array values
            {
                        le[i]=500;
                        re[i]=0;
            }
            edgedetect(x1,y1,x2,y2,le,re);    // call edge detect four times
            edgedetect(x2,y2,x3,y3,le,re);    // once for each edge.
            edgedetect(x3,y3,x4,y4,le,re);
            edgedetect(x4,y4,x1,y1,le,re);
for(y=0;y<500;y++)        // for every scan line with value y
{
           if(le[y]<=re[y])            // refer to le and re arrays to see if a part
                        for(i=le[y]+1;i<re[y];i++) // of the scanline is inside polygon
                                    drawpixel(i,y);       // if so draw a horizontal line from
}                                                              // left edge to right edge
}
void display()
{
            glClear(GL_COLOR_BUFFER_BIT);

            x1=200,y1=200,x2=100,y2=300,x3=200,y3=400,x4=300,y4=300;
            
            glBegin(GL_LINE_LOOP);       // draw the boundary of the polygon
            glVertex2f(x1,y1);                   // to be filled.
             glVertex2f(x2,y2);
            glVertex2f(x3,y3);
            glVertex2f(x4,y4);
    glEnd();
   scanfill(x1,y1,x2,y2,x3,y3,x4,y4);       // call scanfill to fill the polygon
   glFlush();   // Usually students fail the lab because they forget glFlush.
}
void myinit()
{
            glClearColor(1.0,1.0,1.0,1.0);
            glColor3f(0.0,0.0,1.0);
            glPointSize(1.0);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(0.0,499.0,0.0,499.0);
}
int main(int argc,char **argv)
{          glutInit(&argc,argv);
            glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
            glutInitWindowSize(500,500);// 500 height is hardcoded
            glutInitWindowPosition(0,0);
            glutCreateWindow("scanfill");
            glutDisplayFunc(display);
            myinit();
            glutMainLoop();
            return 0;
   }