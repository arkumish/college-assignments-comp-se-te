#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

using namespace std;
int check=0;

struct Point {
	GLint x;
	GLint y;
};
int n,x,y;
struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

Color getPixelColor(GLint x, GLint y) {
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, Color color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void floodFill(GLint x, GLint y, Color oldColor, Color newColor) {
	Color color;
	color = getPixelColor(x, y);

	if(color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b)
	{
		setPixelColor(x, y, newColor);
		floodFill(x+1, y, oldColor, newColor);
		floodFill(x-2, y, oldColor, newColor);
		floodFill(x, y+2, oldColor, newColor);
		floodFill(x, y-2, oldColor, newColor);


		/* for 8 connected 
		   setPixelColor(x, y, newColor);
        floodfill(x + 1, y, oldColor, newColor);
        floodfill(x, y + 1, oldColor, newColor);
        floodfill(x - 1, y, oldColor, newColor);
        floodfill(x, y - 1, oldColor, newColor);
        floodfill(x - 1, y - 1, oldColor, newColor);
        floodfill(x - 1, y + 1, oldColor, newColor);
        floodfill(x + 1, y - 1, oldColor, newColor);
        floodfill(x + 1, y + 1, oldColor, newColor);



		*/
	}
	return;
}

void onMouseClick(int btn, int state, int x, int y)
{  y=480-y;
	Color newColor = {1.0f, 0.0f, 0.0f};
	Color oldColor = {1.0f, 1.0f, 1.0f};
    
    if(btn==GLUT_LEFT_BUTTON && check==1)
    {
        if(state==GLUT_DOWN && check==1)
        {
            
            //glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,intCol);
            floodFill(x, y, oldColor, newColor);
            cout<<" x = "<<x<<" y = "<<y<<endl;
            check=0;
        }
    }
	
}


void world(){
    glLineWidth(3);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    cout<<" enter value of n : ";
    cin>>n;
    cout<<" enter ( "<<n<<" ) coordinates of shape : \n";
    glBegin(GL_LINE_LOOP);
     for(int i=0;i<n;i++){
        cin>>x>>y;
        glVertex2i(x,y);
        
    }
    
    glEnd();
    check=1;
    glFlush();
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open GL floodFill");
	init();
	glutDisplayFunc(world);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}