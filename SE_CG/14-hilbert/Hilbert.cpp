#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

class hilbert{
float xp,yp;
queue<pair<int , int> > points;
public:
	hilbert(){
		xp = INT_MIN;
		yp = INT_MIN;
	}	
	
	void lineTo(float x1,float y1){
		if(xp == INT_MIN){
			xp = x1;
			yp = y1;
			return;
		}
		glBegin(GL_LINES);
			glVertex2f(xp,yp);		
			glVertex2f(x1,y1);
		glEnd();
		glFlush();
		xp = x1;
		yp = y1;
	}

	void hilbertCurve(float x , float y ,float xi ,float yi ,float xj ,float yj , int ord ){
		if(ord <= 0){
			float x1 = x + (xi+yi)/2;
			float y1 = y + (xj+yj)/2;
			lineTo(x1,y1);		
		}else{
			hilbertCurve(x          ,y,yi/2     ,yj/2   ,xi/2   ,xj/2   ,ord-1);
			hilbertCurve(x+xi/2	    ,y+xj/2		,xi/2	,xj/2	,yi/2	,yj/2	,ord-1);
			hilbertCurve(x+xi/2+yi/2,y+xj/2+yj/2,xi/2	,xj/2	,yi/2	,yj/2	,ord-1);
			hilbertCurve(x+xi/2+yi	,y+xj/2+yj	,-yi/2	,-yj/2	,-xi/2	,-xj/2	,ord-1);		
		}
	}
};

void init2d()//how to display
{
	glClearColor (0.0,0.0,0.0,0.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0,800.0, 0.0, 800.0);//same like window size(xl,xh,yl,yh)
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);//set color
	glFlush();
	cout<<"Enter order of curve : ";
	int ord;
	cin>>ord;
	hilbert a;
	a.hilbertCurve(0,0,800,0,0,800,ord);
}
int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize (800, 800);
	glutInitWindowPosition (00, 00);
	glutCreateWindow ("Amitav");
	init2d();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

