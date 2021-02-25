#include<bits/stdc++.h>
#include<GL/glut.h>
#define MAX 100
using namespace std;

int n;
int trans[3][3];
int rot[3][3];
int shear[3][3];
int scaling[3][3];
int matrix[MAX][3];

void init(){
   glClearColor (1.0,1.0,1.0,0.0);
   glMatrixMode(GL_PROJECTION);
   gluOrtho2D(0.0,500.0,0.0,500.0);
}

void disp(){
	glBegin(GL_LINE_LOOP);
	 for(int i=0;i<n;i++){
	 	glVertex2i(matrix[i][0],matrix[i][1]);
	 }
	glEnd();
	glFlush();
}

void  initialize(int n){

	for(int i=0;i<n;i++){
		trans[i][i]=1;
		rot[i][i]=1;
		scaling[i][i]=1;
		shear[i][i]=1;
		matrix[i][2]=1;
	}
}



void multiply(int ar[][3]){

	for(int i=0;i<n;i++){
		for(int j=0;j<3;j++){
         for(int k=0;k<3;k++){
         	matrix[i][j]+=matrix[i][k]*ar[k][j];
         }
		}
	}
}

void translate(int tx,int ty){
	trans[2][0]=tx;
	trans[2][1]=ty;
	multiply(trans);
	disp();
}

void rotate(int theta){
	theta=(M_PI/180)*theta;
	rot[0][0]=cos(theta);
	rot[0][1]=sin(theta);
	rot[1][0]=-sin(theta);
	rot[1][1]=cos(theta);
	multiply(rot);
	disp();
}

void scale(int sx,int sy){
	scaling[0][0]=sx;
	scaling[1][1]=sy;
	multiply(scaling);
	disp();
}

void shearing(int a,int b){
shear[0][1]=a;
shear[1][0]=b;
multiply(shear);
disp();
}



void input(){
	cout<<"\nEnter the number of vertices:";
	cin>>n;
	initialize(n);
	for(int i=0;i<n;i++){
		cin>>matrix[i][0]>>matrix[i][1];
	}
   
   rotate(60);	
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    input();
}

int main(int argc,char **argv){
glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
	glutInitWindowPosition(50,100);
	glutInitWindowSize(500,500);
    glutCreateWindow("Transformation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();


return 0;
}
