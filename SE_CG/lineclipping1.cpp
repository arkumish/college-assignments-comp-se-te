#include<bits/stdc++.h>
#include<GL/glut.h>
#define infinity INT_MAX
using namespace std;

struct point{
    float x;
    float y;
};

struct opcode{
    int L,R,A,B;
};

void init2d()
{
	glClearColor(0, 0, 0, 0);

glViewport(0, 0, 500, 500);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

glOrtho(0, 500, 0, 500, 1, -1);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}

void display(opcode o){
    cout<<o.A<<" "<<o.B<<" "<<o.R<<" "<<o.L<<endl;
}

bool check(opcode o){
    if(o.L==0 && o.R==0 && o.A==0 && o.B==0)
    return true;
 return false;
}

opcode Bitwise_OR(opcode c1,opcode c2){
  opcode o;
  o.L=c1.L|c2.L;
  o.R=c1.R|c2.R;
  o.A=c1.A|c2.A;
  o.B=c1.B|c2.B;
 return o;
}

opcode Bitwise_AND(opcode c1,opcode c2){
 opcode o;
  o.L=c1.L&c2.L;
  o.R=c1.R&c2.R;
  o.A=c1.A&c2.A;
  o.B=c1.B&c2.B;
 return o;
}

opcode fx(point vp1,point vp2,point p){
    opcode o;
    o.L=o.A=o.R=o.B=0;
    
    if(p.x <vp1.x)
        o.L=1;
    

    if(p.x >vp2.x)
        o.R=1;
    
    if(p.y < vp1.y)
       o.B=1;
   
    if(p.y > vp2.y)
       o.A=1;
       
    return o; 
}

point above(point vp1,point vp2,point p1,point p2){
point p;

float m=(p2.y-p1.y)/(p2.x-p1.x);
p.y=vp2.y;
 p.x=(p.y-p1.y)/m+p1.x;

return p;
}

point bottom(point vp1,point vp2,point p1,point p2){
point p;

float m=(p2.y-p1.y)/(p2.x-p1.x);
p.y=vp1.y;
p.x=(p.y-p1.y)/m+p1.x;

return p;
}

point left(point vp1,point vp2,point p1,point p2){
point p;
float m=(p2.y-p1.y)/(p2.x-p1.x);
//cout<<m<<endl;
p.x=vp1.x;
p.y=m*(p.x-p1.x)+p1.y;
return p;
}

point right(point vp1,point vp2,point p1,point p2){
point p;

float m=(p2.y-p1.y)/(p2.x-p1.x);
//cout<<m<<endl;
p.x=vp2.x;
p.y=m*(p.x-p1.x)+p1.y;

return p;
}


point clipper(point vp1,point vp2,point p1,point p2,opcode o){
 
   if(o.L==1){
       p2=left(vp1,vp2,p1,p2);
       o=fx(vp1,vp2,p1);
   }
   if(o.R==1){
       p2=right(vp1,vp2,p1,p2); 
       o=fx(vp1,vp2,p1);
   }
   if(o.B==1){
       p2=bottom(vp1,vp2,p1,p2); 
       o=fx(vp1,vp2,p1);
   }
   if(o.A==1){
       p2=above(vp1,vp2,p1,p2);
       o=fx(vp1,vp2,p1);
   }
    

   return p2;
}

void lineclipping(  point vp1,point vp2,point p1,point p2){
 
  opcode op1,op2,o;
  bool flag=true;
 
   glColor3f(0.0,1.0,0.0);
    glFlush(); 
   glBegin(GL_LINES);
       glVertex2f(p1.x,p1.y);
       glVertex2f(p2.x,p2.y); 
  
  
  
 while(flag)
 {  
  op1=fx(vp1,vp2,p1);
  op2=fx(vp1,vp2,p2);
  //display(op1);
  //display(op2);

  o=Bitwise_OR(op1,op2);
  if(check(o)){
      cout<<"\nDraw the line\n";
      cout<<p1.x<<" "<<p1.y<<"  "<<p2.x<<" "<<p2.y<<endl;
       glFlush();
   // glClear(GL_COLOR_BUFFER_BIT);
     
     //glClearColor(1, 0, 0, 0);
     glColor3f(0.0,0.0,1.0);
     
        glVertex2f(p1.x,p1.y);
        glVertex2f(p2.x,p2.y); 
     glEnd();
       glFlush(); 
    
      
      flag=false;
      break;
  }else{
      o=Bitwise_AND(op1,op2);
      //display(o);
      if(!check(o)){
          cout<<"\nLine is completely outside";
          flag=false;
          break;
      }else{
          //L-R,B-A
            

          if(!check(op1))
         { p1=clipper(vp1,vp2,p1,p2,op1);
          cout<<"\nFIRST POINT\n";
          cout<<p1.x<<" "<<p1.y<<endl;
          cout<<p2.x<<" "<<p2.y<<endl;
          continue;
          }
          if(!check(op2))
          {p2=clipper(vp2,vp2,p1,p2,op2);
          cout<<"\nSECOND POINT\n";
           cout<<p1.x<<" "<<p1.y<<endl;
           cout<<p2.x<<" "<<p2.y<<endl;
          continue;
          }
      }
  }
 }
  glEnd();
       glFlush();   

}

void menu(){
    int ch;
    point p1,p2;
    point vp1,vp2;
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(1.0,0.0,0.0);
     glFlush();
     
  cout<<"\nEnter the leftbottom coordinates of viewport:";
  cin>>vp1.x>>vp1.y;
  cout<<"\nEnter the righttop coordinates of the viewport:";
  cin>>vp2.x>>vp2.y;
  
    glBegin(GL_LINE_LOOP);
     
     glVertex2f(vp1.x,vp1.y);
     glVertex2f(vp2.x,vp1.y);
     glVertex2f(vp2.x,vp2.y);
     glVertex2f(vp1.x,vp2.y);
    
    glEnd();
    glFlush();
    
     
    do{
       cout<<"\n0.Exit";
       cout<<"\n1.Input the line";
       cout<<"\nEnter your choice:";
       cin>>ch;

       switch(ch){
           case 0:break;
           case 1:cout<<"\nEnter the coordinates of endpoints of line:";
                  cin>>p1.x>>p1.y>>p2.x>>p2.y;
                  glFlush();
                  lineclipping(vp1,vp2,p1,p2);
                  glFlush();
                  break;

            default:
                   cout<<"\nPLS Enter a Valid Choice...";
                   break;
       }
    }while(ch!=0); 
   glFlush();
}

void draw(){
  menu();
}


void disp(void){
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0,0.0,0.0);
   draw();
}


int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("LINE CLIPPING");
	init2d();
	glutDisplayFunc(disp);
	glutMainLoop();
    return 0;
}
