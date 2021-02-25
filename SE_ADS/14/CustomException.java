class DataException extends Exception
{
    String message;
    
    DataException(String s){
        message = s;
    } 

    void display(){
        System.out.println("DataException :" + message);
    }
}

class Student{
    String name;
    int age;

    Student(String n, int a)throws DataException{
        setName(n);
        setAge(a);
    }   

    void setName(String n)throws DataException{
        String t = n.toUpperCase();
        int l = t.length();

        for(int i = 0; i < l; i++) {
            char q = t.charAt(i);   
            if(q < 65 || q >90){
                DataException pe = new DataException("Student Name Invalid : " + n);   
                throw(pe);
            }
        }   
            name = n; 
    }

    void setAge(int a) throws DataException{
        if(a < 0 || a > 100) {
            DataException pe = new DataException("Student Age Invalid: " + a);   
            throw(pe);
        }
        age = a; 
    }

    void display(){
        System.out.println(name + " " + age);
    }
}

class CustomException{
    public static void main(String args[]){
        try{
                String s = args[0];
                int a = Integer.parseInt(args[1]);
                Student p = new Student(s, a);
                p.display();
        }
        catch(DataException pde){
                pde.display();
        }
        catch(ArrayIndexOutOfBoundsException ex) {
            System.out.println("Only 2 arguments allowed NAME AND AGE");
        }
        catch(Exception ex){
                System.out.println(ex);
        }
    }
}