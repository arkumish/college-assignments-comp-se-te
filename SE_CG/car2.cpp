#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
switch (key) {
case 27: //Escape key
exit(0);
}
}

//Initializes 3D rendering
void initRendering() {
glEnable(GL_DEPTH_TEST);
glEnable(GL_COLOR_MATERIAL); //Enable color
glClearColor(0.7f, 0.9f, 1.0f, 1.0f); //Background color is sky blue
}

//Called when the window is resized
void handleResize(int w, int h) {
glViewport(0, 0, w, h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45.0, (double)w / (double)h, 0.01/Min render distance/, 500.0/Max distance/);//Meters
}

float _angle = 30.0f;
float _cameraAngle = 0.0f;

//Draws the 3D scene
void drawScene() {
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glRotatef(-_cameraAngle, 0.0f, 1.0f, 0.0f);
glTranslatef(0.0f, 0.0f, -20.0f);//I have moved the circuit and the car 20 meters under, so now
//the camera is “set” at 20 meters high than the car and the circuit

glBegin(GL_QUADS); //Ferrari
glColor3f(1.0f, 0.0f, 0.0f); //Red Ferrari
glVertex3f(-2.25f, 1.0f, 0.0f); //Meters (4,5m long per 2,25m wide)
glVertex3f(2.25f, 1.0f, 0.0f);
glVertex3f(2.25f, -1.0f, 0.0f);
glVertex3f(-2.25f, -1.0f, 0.0f);	
glEnd();




glBegin(GL_QUADS); //Circuit (A big parking
glColor3f(0.2f, 0.2f, 0.2f); //Asphalt color
glVertex3f(-200.0f, 200.0f, 0.0f); //Meters
glVertex3f(200.0f, 200.0f, 0.0f);
glVertex3f(200.0f, -200.0f, 0.0f);
glVertex3f(-200.0f, -200.0f, 0.0f);
glEnd();


glutSwapBuffers();

}

void update(int value) {
_angle += 2.0f;
if (_angle > 360) {
_angle -= 360;
}

glutPostRedisplay();
glutTimerFunc(25, update, 0);

}

int main(int argc, char** argv) {
//Initialize GLUT
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(320, 240);

//Create the window
glutCreateWindow("Test");
initRendering();

//Set handler functions
glutDisplayFunc(drawScene);
glutKeyboardFunc(handleKeypress);
glutReshapeFunc(handleResize);

glutTimerFunc(25, update, 0); //Add a timer

glutMainLoop();
return 0;
