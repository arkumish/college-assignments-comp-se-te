#include<bits/stdc++.h>
#include<GL/glut.h>

using namespace std;


struct vector2{

 int x,y;
 vector2(int x1=0,int y1=0)
 {
 	this.x=x1;
 	this.y=y1;
 }


};

enum EdgeState { INACTIVE , ACTIVE };

struct Edge {

vecto



};


void init(void){
    glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,700,0,700);
	
    glFlush();
}

int main(int argc , char** argv){

glutInit(&argc , argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(100,100);
glutInitWindowSize(700,700);

glutCreateWindow(" scan line");

init();





glutMainLoop();



	return 0;
}