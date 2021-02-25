#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;

double P1[3][3],T[3][3],P2[3][3];

void prod(double P1[3][3],double T[3][3])
{
    double a;
    
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            a=0;
            for(int k=0;k<3;k++)
            {
                a+=P1[i][k]*T[k][j];
            }
            P2[i][j]=a;
        }
    }
}

void init(void)
{
    glClearColor(0.0,0.5,0.5,0);
    glColor3f(1.0,1.0,1.0);
    //Size(4.0);
    gluOrtho2D(-320,320,-240,240);
}

void poly(double P[3][3])
{
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<3;i++)
    {
        glVertex2d(P[i][0],P[i][1]);
    }
    glEnd();
    glFlush();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glBegin(GL_LINES);
        glVertex2d(-320,0);
        glVertex2d(320,0);
        glVertex2d(0,-240);
        glVertex2d(0,240);
    glEnd();
    
    glColor3f(0.0,0.0,1.0);
    poly(P1);
    glFlush();
}

void scaling(void)
{
    double sx,sy;
    cout<<"\nScaling";
    cout<<"\nsx: ";
    cin>>sx;
    cout<<"\nsy: ";
    cin>>sy;
    
    T[0][0]=sx;
    T[0][1]=0;
    T[0][2]=1;
    T[1][0]=0;
    T[1][1]=sy;
    T[1][2]=1;
    T[2][0]=0;
    T[2][1]=0;
    T[2][2]=1;
    
    prod(P1,T);
    glColor3f(1.0,0.0,0.0);
    poly(P2);
}

void translate(void)
{
    double tx,ty;
    cout<<"\nTranslation";
    cout<<"\ntx: ";
    cin>>tx;
    cout<<"\nty: ";
    cin>>ty;
    
    T[0][0]=1;
    T[0][1]=0;
    T[0][2]=1;
    T[1][0]=0;
    T[1][1]=1;
    T[1][2]=1;
    T[2][0]=tx;
    T[2][1]=ty;
    T[2][2]=1;
    
    prod(P1,T);
    glColor3f(1.0,0.0,0.0);
    poly(P2);
}

void rotate(void)
{
    double x,y,angle,rad;
    cout<<"\nRotation";
    cout<<"\nArbitrary podouble: ";
    cout<<"\nx: ";
    cin>>x;
    cout<<"\ny: ";
    cin>>y;
    cout<<"\nAngle in degrees: ";
    cin>>angle;
    
    rad=angle*(3.14/180);
    
    T[0][0]=cos(rad);
    T[0][1]=sin(rad);
    T[0][2]=0;
    T[1][0]=-sin(rad);
    T[1][1]=cos(rad);
    T[1][2]=0;
    T[2][0]=(-(x*cos(rad))+(y*sin(rad))+x);
    T[2][1]=(-(x*sin(rad))-(y*cos(rad))+y);
    T[2][2]=1;
    
    prod(P1,T);
    glColor3f(1.0,0.0,0.0);
    poly(P2);
}

void reflect(void)
{
    int choice;
    cout<<"\nReflection";
    cout<<"\n1.About x-axis";
    cout<<"\n2.About y-axis";
    cout<<"\n3.About origin";
    cout<<"\n4.About y=x";
    cout<<"\n5.About y=-x";
    cout<<"\nChoice: ";
    cin>>choice;
    
    switch(choice)
    {
        case 1:
        {
            T[0][0]=1;
            T[0][1]=0;
            T[0][2]=0;
            T[1][0]=0;
            T[1][1]=-1;
            T[1][2]=0;
            T[2][0]=0;
            T[2][1]=0;
            T[2][2]=1;
            break;
        }        
        case 2:
        {
            T[0][0]=-1;
            T[0][1]=0;
            T[0][2]=0;
            T[1][0]=0;
            T[1][1]=1;
            T[1][2]=0;
            T[2][0]=0;
            T[2][1]=0;
            T[2][2]=1;
            break;
        }
        case 3:
        {
            T[0][0]=-1;
            T[0][1]=0;
            T[0][2]=0;
            T[1][0]=0;
            T[1][1]=-1;
            T[1][2]=0;
            T[2][0]=0;
            T[2][1]=0;
            T[2][2]=1;
            break;
        }
        case 4:
        {
            T[0][0]=0;
            T[0][1]=1;
            T[0][2]=0;
            T[1][0]=1;
            T[1][1]=0;
            T[1][2]=0;
            T[2][0]=0;
            T[2][1]=0;
            T[2][2]=1;
            break;
        }
        case 5:
        {
            T[0][0]=0;
            T[0][1]=-1;
            T[0][2]=0;
            T[1][0]=-1;
            T[1][1]=0;
            T[1][2]=0;
            T[2][0]=0;
            T[2][1]=0;
            T[2][2]=1;
            break;
        }
    }
    
    
    
    prod(P1,T);
    glColor3f(1.0,0.0,0.0);
    poly(P2);
}

void shearing()
{
	double xs,ys;
	int choice;
	cout<<"\nShearing";
	cout<<"\n1.X - Shear";
	cout<<"\n2.Y - Shear";
	cout<<"\nChoice";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
			cout<<"\n\tX-shear value : ";
			cin>>xs;
			
			T[0][0]=1;
			T[0][1]=0;
			T[0][2]=0;
			T[1][0]=xs;
			T[1][1]=1;
			T[1][2]=0;
			T[2][0]=0;
			T[2][1]=0;
			T[2][2]=1;
			break;

			case 2:
			cout<<"\n\tY-shear value : ";
			cin>>ys;
			T[0][0]=1;
			T[0][1]=ys;
			T[0][2]=0;
			T[1][0]=0;
			T[1][1]=1;
			T[1][2]=0;
			T[2][0]=0;
			T[2][1]=0;
			T[2][2]=1;
			break;
	}
	
	prod(P1,T);
	glColor3f(0.0,1.0,0.0);
	poly(P2);
}

void menu(int item)
{
    switch(item)
    {
        case 1:
            scaling();
            break;
        case 2:
            translate();
            break;      
        case 3:
            rotate();
            break;   
        case 4:
            reflect();
            break;    
        case 5:
            shearing();
            break;
        case 6:
            exit(0);
    }
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    
        P1[0][0]=0;
        P1[0][1]=0;
        P1[0][2]=1;
        P1[1][0]=100;
        P1[1][1]=0;
        P1[1][2]=1;
        P1[2][0]=50;
        P1[2][1]=100;
        P1[2][2]=1;
    
    glutCreateWindow("2-d transformation!");
    init();
    glutDisplayFunc(display);
    
    glutCreateMenu(menu);
        glutAddMenuEntry("1.Scaling",1);
        glutAddMenuEntry("2.Translation",2);
        glutAddMenuEntry("3.Rotation",3);
        glutAddMenuEntry("4.Reflection",4);
        glutAddMenuEntry("5.Shearing",5);
        glutAddMenuEntry("6.EXIT",6);
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMainLoop();
    return 0;
}
