//Assignment : koch
#include <GL/glut.h>
#include <math.h>



//float oldx=0.7,oldy=0.5;
float oldx=100,oldy=400;

void koch_curve(float dir,float len,GLint count) {
	GLdouble dirRad = 0.0174533 * dir;  
	float newX = oldx + len * cos(dirRad);
	float newY = oldy + len * sin(dirRad);
	if (count==0) {
		glVertex2f(oldx, oldy);
		glVertex2f(newX, newY);
		oldx = newX;
		oldy = newY;

	}
	else {
		count--;
		//draw the four parts of the side _/\_ 
		koch_curve(dir, len, count);
		dir += 60.0;
		koch_curve(dir, len, count);
		dir -= 120.0;
		koch_curve(dir, len, count);
		dir += 60.0;
		koch_curve(dir, len, count);
	}
}

void mydisplay(){
	 glClear( GL_COLOR_BUFFER_BIT );
	 glBegin(GL_LINES);
	 glColor3f(1.0, 0.0, 0.0); // make it red
	 
	
	 
	 koch_curve(0.0,10,5);
	 //koch_curve(-120.0, 0.05, 3);  //for snowflake
	 //koch_curve(120.0,0.05,3);     //for snowflake
	  
	 /* */
	 glEnd();
	 glFlush(); 
}

void init(void){

 glClearColor(1.0,1.0,1.0,0.0);
 glClear(GL_COLOR_BUFFER_BIT);

 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0,700,0,700);

 glFlush();

}

int main(int argc, char** argv)
{
	glutInit(&argc,argv); 
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);      
	glutInitWindowSize(1000,1000);    	
	glutInitWindowPosition(0,0); 
	glutCreateWindow("Koch curve");   
	init();  
	glutDisplayFunc(mydisplay);  
	glutMainLoop();
}