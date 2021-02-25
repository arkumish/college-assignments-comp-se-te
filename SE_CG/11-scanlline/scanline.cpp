#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;
struct edge{
	int x[2],y[2],act;
	friend istream & operator >>(istream &in, edge &a){
		cout<<"Enter Starting and ending point : ";
		in>>a.x[0]>>a.y[0]>>a.x[1]>>a.y[1];
		a.act = 0;
		if (a.y[0] > a.y[1]){
			swap(a.x[0],a.x[1]);
			swap(a.y[0],a.y[1]);
		}
		return in;
	}
};
bool comparator(const edge &a, const edge &b){
		if (a.y[0]<b.y[0])
			return true;
		if (b.y[0] < a.y[0])
			return false;
		return a.y[1]<b.y[1];
}
class Polygon{
	private :
	vector<edge> edges;
	int n;
	public :
	Polygon(){
		cout<<"Enter number of edges : ";
		cin>>n;
		for (int i = 0; i<n; i++){
			edge a;
			cin>>a;
			edges.push_back(a);
		}
		sort(edges.begin(), edges.end(),comparator);
	}
	void drawPoly(){
		for (int i =0; i<n; i++){
			cout<<edges[i].x[0]<<" "<<edges[i].y[0]<<" "<<edges[i].x[1]<<" "<<edges[i].y[1]<<endl;
			glBegin(GL_LINES);
				glVertex2i(edges[i].x[0],edges[i].y[0]);
				glVertex2i(edges[i].x[1],edges[i].y[1]);
			glEnd();
		}
		glFlush();
		return;
	}
	void scanFill(){
		int ymin=edges[0].y[0],ymax=0;
		vector<int> xc,xu,xb,emp;
		for (int i = 0; i<n; i++){
			ymax = max(ymax,edges[i].y[1]);
		}
		for (int h = ymin; h<=ymax; h++){
			for (int i =0 ; i<n; i++){
				if (edges[i].act == 2)
					continue;
				if (edges[i].act == 1){
					if (edges[i].y[1]<h)
						edges[i].act = 2;
				}
				else if (edges[i].y[0] == h){
					edges[i].act = 1;
				}
				else
					break;
			}
			for (int i =0; i<n; i++){
				if (edges[i].act!= 1)
					continue;
				edge a = edges[i];
				int x;
				if (a.x[0] == a.x[1])
					x = a.x[0];
				else
					x = (0.5+a.x[0] +  (0.0+a.x[1]-a.x[0]) / (a.y[1]-a.y[0]) * (h-a.y[0]) );
				if (h == a.y[1])
					xb.push_back(x);
				else if (h == a.y[0])
					xu.push_back(x);
				else
					xc.push_back(x);
			}
			for (int i = 0; i<xu.size(); i++){
				if ((i+1)<xu.size() && xu[i] == xu[i+1])
					i++;
				else
					xc.push_back(xu[i]);
			}
			sort(xc.begin(), xc.end());
			for (int i = 1; i<xc.size(); i+=2){
			glBegin(GL_LINES);
				glVertex2i(xc[i-1],h);
				glVertex2i(xc[i],h);
			glEnd();
			}
			glFlush();
			xc = emp;
			xu = emp;
			xb = emp;
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
	//Polygon ;
	Polygon a;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);//set color
	glFlush();
	a.drawPoly();
	a.scanFill();
}
int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitWindowSize (800, 800);
	glutInitWindowPosition (00, 00);
	glutCreateWindow ("scanline");
	init2d();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
