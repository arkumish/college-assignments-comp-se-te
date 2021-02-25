/*Date: august 2019
*/
import java.net.*;
import java.io.*;
import java.util.*;

public class client{
    //initial socket and input output stream
    
    
    public static void main(String args[]){
        try{
            Socket sock ;
            DataInputStream in ;
            DataOutputStream out;
            sock= new Socket("127.0.0.1",8000);
            System.out.println("Connected...\n");
            
            Scanner sc=new Scanner(System.in);
            InputStream input=sock.getInputStream();
            OutputStream output=sock.getOutputStream();
            
            in=new DataInputStream(input);
            out=new DataOutputStream(output);
            
            String message;
            do{
                System.out.print("Client: ");
                message=sc.nextLine();
                out.writeUTF(message);
                message=in.readUTF();
                System.out.println("Server: "+message+"\n");
            }while(!message.equals("bye"));
        }
        catch(Exception ex){
            System.out.println("Error... : "+ex);
        }
    }
}

