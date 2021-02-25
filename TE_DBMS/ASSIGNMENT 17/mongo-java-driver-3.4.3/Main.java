import java.util.Scanner;
import java.io.Console;
import org.json.simple.*;

import java.util.*;

class Main
{
    static Scanner scan = new Scanner(System.in);
    public static void main(String[] args) 
    {
        clearScreen();
        System.out.println(">>>>>>>>Welcome to the NOTE-KEEPER<<<<<<<<");
        try 
        {
            String userObjId = signupLoginUser();
            manageNotes(userObjId);            
        } 
        catch (Exception e) 
        {
            System.out.println(e);
            e.printStackTrace();
        }
    }

    static void clearScreen()
    {
        try
        {
            new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
        }catch (Exception e){}
    }

    //returns ObjId
    static String signupLoginUser() throws Exception
    {
        System.out.println("1.Sign-UP");
        System.out.println("2.Log-IN");
        int ch = scan.nextInt();
        while(ch != 1 && ch!=2)
        {
            System.out.println("Invalid Choice!");
            System.out.print("Re-Enter:" );
            ch = scan.nextInt();
        }
        
        String userObjid = "";
        String username;
        String password;
        System.out.print("Username:");
        username = scan.next();
        password = new String(System.console().readPassword("Password:"));

        switch(ch)
        {
            case 1://SIGN_UP
                userObjid = DBManager.signUpUser(username,password);
                System.out.println("SignUp Successfull");
                break;
            case 2://LOG_IN
                userObjid = DBManager.logInUser(username,password);
                System.out.println("Login Successfull");
                break;
        }//switch
        return userObjid;
    }

    //manage nOtes
    static void manageNotes(String userObjId)throws Exception
    {
        String username = DBManager.getUsername(userObjId);
        String header = ">>>>>>>>>>>>>>>>>> "+username.toUpperCase()+"\'s NOTES " + "<<<<<<<<<<<<<<<<<<";
        while(true)
        {
            clearScreen();
            System.out.println(header);
            System.out.println("1.SAVE Notes");
            System.out.println("2.DISPLAY Notes");
            int ch = scan.nextInt();
            while(ch != 1 && ch!=2)
            {
                System.out.println("Invalid Choice!");
                System.out.print("Re-Enter:" );
                ch = scan.nextInt();
            }

            switch(ch)
            {
                case 1://save notes
                    System.out.print("Enter Tittle: ");
                    String tittle = scan.next();
                    System.out.print("Content: ");
                    while(scan.nextLine().equals("\n")){}

                    String content = scan.nextLine();
                    DBManager.saveNote(userObjId,tittle,content);
                    break;
                case 2://DISPLAY NOTES
                    JSONArray notesArr = DBManager.getNotes(userObjId);
                    Iterator itr2 = notesArr.iterator();
                    Iterator<Map.Entry> itr1;
                    while(itr2.hasNext())
                    {
                        System.out.println(">>>>>>>>>---------------------------<<<<<<<<\n");
                        itr1 = ((Map)itr2.next()).entrySet().iterator();
                        while(itr1.hasNext())
                        {
                            Map.Entry pair = itr1.next();
                            System.out.printf("%-10s" , ((String)pair.getKey()).toUpperCase());
                            System.out.printf("%-2s",":");
                            System.out.println(pair.getValue());
                        }
                        System.out.println("\n>>>>>>>>>---------------------------<<<<<<<<");
                        
                    }
                    System.out.println("Press to Continue...");
                    String pause = scan.next();
                    break;
            }
        }//while
        
    }//manageNotes
}