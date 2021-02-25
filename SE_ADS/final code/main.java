//main.java
import mypackage.areaCalculation;
import java.util.Scanner;
class main{
    public static void main( String args[]){
        boolean e = true;
        do{
            System.out.println("----------------------------------------------");
            System.out.println("FIND AREA OF FOLLOWING");
            System.out.println("1. CIRCLE ");
            System.out.println("2. RECTANGLE ");
            System.out.println("3. TRIANGLE ");
            System.out.println("0. EXIT ");
            Scanner in = new Scanner(System.in);
            int inp = in.nextInt();
            areaCalculation a = new areaCalculation();
            switch(inp){
                case 1 :
                    System.out.println("ENTER RADIUS FOR CIRCLE ");
                    double radius = in.nextDouble();
                    System.out.println("AREA IS : " + a.calcCircleArea(radius));
                    break;

                case 2 :
                    System.out.println("ENTER WIDTH AND HEIGHT OF RECTANGLE ");
                    double width = in.nextDouble();
                    double height = in.nextDouble();
                    System.out.println("AREA IS : " + a.calcRectangleArea(width,height));
                    break;

                case 3 :
                    System.out.println("ENTER THREE SIDES OF TRIANGLE ");
                    double s1 = in.nextDouble();
                    double s2 = in.nextDouble();
                    double s3 = in.nextDouble();
                    if(s1+s2<s3 || s2+s3<s1 || s1+s3<s2)
                        System.out.println("NO TRIANGLE FORMED");
                    else{ 
                        System.out.println("AREA IS : " + a.calcTriangleArea(s1,s2,s3));
                        break;   
                    }

                case 0:
                    System.out.println("EXITING");
                    e = false;
                    break;

                default:
                    System.out.println("WRONG INPUT");
            }
        }
        while(e);
    }
}


