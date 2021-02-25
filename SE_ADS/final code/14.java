
class PersonalDataException extends Exception
{
 String message;

 PersonalDataException(String s)
 {
  message = s;
 } 

 //custom methods
 void display()
 {
  System.out.println("PersonalDataException :" + message);
 }

 //popular overrides
 public String toString()
 {
  return "PersonalDataException : "+ message; 
 } 

 public String getMessage()
 {
  return message;
 }

}//PersonalDataException


class Person
{
 String name;
 int age;

 Person(String n, int a)throws PersonalDataException
 {
  setName(n);
  setAge(a);
 }

 void setName(String n)throws PersonalDataException
 {//business rules / validations
  int i;
  String temp = n.toUpperCase();
  int l = temp.length();
  char q;

  for(i = 0; i < l; i++)
  {
   //temp.charAt(i) == temp[i]
   q = temp.charAt(i);   

   if(q < 65 || q >90)
   {//non alphabetic content in name
    //raise an exception
    PersonalDataException pe = new PersonalDataException("Invalid Name : " + n);   
    throw(pe);
   }

  }//for
  //through the filters

  name = n; 
 }

 void setAge(int a) throws PersonalDataException
 {//business rules / validations
  
  if(a < 0 || a > 100)
  {//invalid age
   //raise an exception
   PersonalDataException pe = new PersonalDataException("Invalid Age : " + a);   
   throw(pe);
  }

  //through the filters
  age = a; 

 }

 void display()
 {
  System.out.println(name + " " + age);
 }
}

class CustomException
{
 public static void main(String args[])
 {
  try
  {
   String s = args[0];
   int a = Integer.parseInt(args[1]);
   Person p = new Person(s, a);
   p.display();

  }
  catch(ArrayIndexOutOfBoundsException ex)
  {
   System.out.println("Usage : java CustomException <name> <age>");
  }
  catch(PersonalDataException pde)
  {
    pde.display();
    //System.out.println(pde);
  }
  catch(Exception ex)
  {
   System.out.println(ex);
  }
 }
}
