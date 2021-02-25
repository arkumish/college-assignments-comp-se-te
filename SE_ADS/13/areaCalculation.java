package mypackage;

import java.lang.Math; 

interface shape{
    double pie = 22.00/7.00;
    public double area();    
}

class Triangle implements shape{
    double a,b,c;
    double s;
    Triangle(){
        a = b = c = 0;
        s=0;
    }
    Triangle(double a,double b,double c){
        this.a = a;
        this.b = b;
        this.c = c;
        s = (a+b+c)/2;
    }

    public double area(){
        return  Math.sqrt(s*(s-a)*(s-b)*(s-c));
    }
}

class Rectangle implements shape{
    double  w,h;
    Rectangle(){
        w = h = 0;
    }
    Rectangle(double w, double h){
        this.w = w;
        this.h = h;
    }

    public double area(){
        return  w*h;
    }
}

class Circle implements shape{
    double r;
    Circle(){
        r = 0;
    }
    Circle(double r){
        this.r = r;
    }

    public double area(){
        return shape.pie*r*r;
    }
}
public class areaCalculation{

        public double calcCircleArea(double radius){
            Circle c = new Circle(radius);
            return c.area();
        }

        public double calcRectangleArea(double width, double height){
            Rectangle r = new Rectangle(width,height); 
            return r.area();
        }

        public double calcTriangleArea(double s1, double s2 , double s3){
            Triangle t =  new Triangle(s1,s2,s3);
            return t.area();
        }
                   
}
