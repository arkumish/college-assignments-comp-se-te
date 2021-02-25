//Assignment : snowflake curve

#include <GL/glut.h>
#include <math.h>

GLfloat oldx=-0.7,oldy=0.5;

void snowflake_curve(GLfloat dir,GLfloat len,GLint count) {
	GLdouble dirRad = 0.0174533 * dir;  
	GLfloat newX = oldx + len * cos(dirRad);
	GLfloat newY = oldy + len * sin(dirRad);
	if (count==0) {
		glVertex2f(oldx, oldy);
		glVertex2f(newX, newY);
		oldx = newX;
		oldy = newY;
	}
	else {
		count--;
		//draw the four parts of the side _/\_ 
		snowflake_curve(dir, len, iter);
		dir += 60.0;
		snowflake_curve(dir, len, iter);
		dir -= 120.0;
		snowflake_curve(dir, len, iter);
		dir += 60.0;
		snowflake_curve(dir, len, iter);
	}
}

void display(){
	 glClear( GL_COLOR_BUFFER_BIT );
	 glBegin(GL_LINES);
	 glColor3f(1.0, 0.0, 0.0); // make it red
	 
	
	 
	 snowflake_curve(0.0,0.05,3);
	 snowflake_curve(-120.0, 0.05, 3);  //for snowflake
	 snowflake_curve(120.0,0.05,3);     //for snowflake
	  
	 /* */
	 glEnd();
	 glFlush(); 
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv); 
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);      
	glutInitWindowSize(500,500);    	
	glutInitWindowPosition(0,0); 
	glutCreateWindow("snowflake curve");     
	glutDisplayFunc(display);  
	glutMainLoop();
}