//This is a template Program For All(most) CG Programs

//#include "pch.h"
#include<GL/glut.h>
#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<random>
using namespace std;
const int height = 700;
const int width = 700;

int modr = 250;
int modg = 100;
int modb = 100;

void ColorChanger()
{
	unsigned char r = rand() % modr;
	unsigned char g = rand() % modg;
	unsigned char b = rand() % modb;
	glColor3ub(r, g, b);
}
void Clear();
void MouseFunc(int button, int state, int x, int y);

void Delay(int x)
{
	while (--x)
	{
		cout << "" << endl;
	}
}

///////----------------------------------------
struct Vector2
{
	int x, y;
	Vector2(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}
};

enum EdgeState { INACTIVE, ACTIVE };

struct Edge
{

	Vector2 first;	  //first vertex
	Vector2 second;   //second vertex
	EdgeState state;		 //state of edge
	
	Edge() { state = INACTIVE; }
	Edge(Vector2 p1, Vector2 p2)
	{
		Store(p1, p2);
		state = INACTIVE;
	}
	void Store(Vector2 p1, Vector2 p2)
	{
		first = p1.y <= p2.y ? p1 : p2;
		second = p1.y > p2.y ? p1 : p2;
	}

	double X_intercept(int y)
	{
		double x = first.x + (y - first.y)*(second.x - first.x) / (double)(second.y - first.y);
		return x;
	}

	/*bool operator< (const Edge &b)
	{
		if (first.y < b.first.y)
			return true;
		else if (first.y > b.first.y)
			return false;

		if (second.y < b.second.y)
			return true;
		else
			return false;
	}*/
};

//CLASS POLYGON
class PolyGon
{
	vector<Vector2> vertex;

public:
	void AddVertex(double x, double y);
	int GetSides() { return vertex.size(); }
	void Draw();
	//scan_line	
	void Fill();
	void Clear() { vertex.clear(); }
};

//addvertex
void PolyGon::AddVertex(double x, double y)
{
	//prevent from having same point again and again (Basic 1 Level Protection)
	int n = vertex.size();
	if (n > 0 && x == vertex[n - 1].x && y == vertex[n - 1].y) return;

	Vector2 temp(x, y);
	vertex.push_back(temp);
}

//draw
void PolyGon::Draw()
{
	if (GetSides() < 3) return;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < vertex.size(); ++i)
		glVertex2d(vertex[i].x, vertex[i].y);
	glEnd();
}

//SCAN LINE
void PolyGon::Fill()
{
	Draw();
	//create edge table
	vector<Edge> edgeTable;
	int n = vertex.size();
	for (int i = 0; i < n; ++i)
	{
		Edge temp(vertex[i], vertex[(i + 1) % n]);
		edgeTable.push_back(temp);
	}

	//sort these edges based on the y values
	//sort(edgeTable.begin(), edgeTable.end());

	//find h_min & h_max
	int h_min = edgeTable[0].first.y;
	int h_max = edgeTable[0].second.y;
	
	for (int i = 0; i < edgeTable.size(); ++i)
	{
		h_min = edgeTable[i].first.y < h_min ? edgeTable[i].first.y : h_min;
		h_max = edgeTable[i].second.y > h_max ? edgeTable[i].second.y : h_max;
	}

	//main algo
	int ne = edgeTable.size();
	for (int h = h_min; h <= h_max; ++h)
	{
		//check states of edges
		for (int i = 0; i < ne; ++i)
		{
			if (edgeTable[i].first.y == edgeTable[i].second.y) //horizontal line
				continue;

			if (edgeTable[i].first.y == h)
				edgeTable[i].state = ACTIVE;
			else if (edgeTable[i].second.y == h)
				edgeTable[i].state = INACTIVE;
		}

		//find x_intercept of active edges
		vector<double> x_intercept;
		for (int i = 0; i < ne; ++i)
			if (edgeTable[i].state == ACTIVE) 
				x_intercept.push_back( edgeTable[i].X_intercept(h) );

		//draw lines beetween valid x_intercept
		sort(x_intercept.begin(), x_intercept.end());
		int nx = x_intercept.size();
		
		glBegin(GL_LINES);
		for (int i = 0; i < nx-1 ; i += 2)
		{
			if (x_intercept[i] == x_intercept[i + 1])
				continue;
			glVertex2d(x_intercept[i], h);
			glVertex2d(x_intercept[i + 1], h);
		}
		glEnd();
	}
	glFlush();

	
}

vector<Vector2> point;
PolyGon poly;

//CallBacks Functions
void Display()
{
}
void ReshapeFunc(int w, int h)
{
	if (width == w && height == h) return;
	glutReshapeWindow(width, height);
}
//keyoard func
void Keyboard(unsigned char key, int, int)
{
	MouseFunc(0, 0, 0, 0);
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'd':
		Clear();
		poly.Clear();
		break;
	}

}
//mouse func
void MouseFunc(int button, int state, int x, int y)
{
	if (state == GLUT_UP)  return;

	y = -y + height;

	if (button == GLUT_LEFT_BUTTON)
	{
		poly.AddVertex(x,y);
		Clear();
		glColor3f(1,1,1);
		poly.Draw();
		glFlush();
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		glColor3f(1,0,0);
		poly.Fill();
	}
}

void MouseMotionFunc(int x, int y)
{
}

//clear the screen
void Clear()
{
	glClearColor(0.01, 0.01, 0.01, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	point.clear();
	glFlush();
}

//This Function Initialize the Window and viewport
void Initialize()
{
	//This will Create Window
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("scan line");

	//this will initialize the ViewPort
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, width, 0, height);

	Clear();
	glFlush();
}

//Register All Callback Function here
void InitCallBacks()
{
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MouseMotionFunc);
	glutReshapeFunc(ReshapeFunc);
}
//this Function is used to DiaplatText
void DisplayText(string text, int x, int y, int font)
{
	void *p = NULL;
	if (font < 8 && font>1)	p = ((void *)font);
	else				    p = ((void *)5);

	glColor3f(1, 1, 0);
	glRasterPos2f(x, y);
	size_t len = text.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(p, (int)text[i]);

	glColor3f(1, 0, 0);
}
//====================================================================//
//                              PROGRAM                               //
//====================================================================//


//====================================================================//
//                              MAIN                                  //
//====================================================================//
void Help()
{
	cout << "****************[HELP]***************\n" << endl;

	cout << "Press 'Left  Mouse Button' For DDA_LINE" << endl;
	cout << "Press 'Right Mouse Button' For Bresenham_LINE\n" << endl;

	cout << "Esc to Exit" << endl;
	cout << "'d' to Clear The Screen\n" << endl;

	cout << "First Click  = FIRST POINT OF THE LINE" << endl;
	cout << "Second Click = SECOND POINT OF THE LINE" << endl;
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	Initialize();
	InitCallBacks();
	Help();

	srand(200);
	glutMainLoop();
	return 0;
}
