import java.net.*;
import java.util.*;
import java.io.*;

public class server{
    public static void main(String args[]){
      //  System.out.print.ln("Waiting for Client...");
        try{
            ServerSocket servsock;
            Socket sock;
            DataInputStream in ; 
            DataOutputStream out;
            servsock=new ServerSocket(8000);
            System.out.println("Server started");
            
            System.out.println("Waiting for a client ..."); 
            
            sock = servsock.accept(); 
            System.out.println("Client accepted\n"); 
            
            InputStream input=sock.getInputStream();
            OutputStream output=sock.getOutputStream();
            
            in= new DataInputStream(input);
            out= new DataOutputStream(output);
            Scanner sc=new Scanner(System.in);
            
            String message;
            message=in.readUTF();
            while(!message.equals("bye")){
                System.out.println("Client: "+message);
                System.out.print("Server: ");
                message=sc.nextLine();
                out.writeUTF(message);
                System.out.println();
                message=in.readUTF();
            }
        }
        catch(Exception ex){
            System.out.println("Error... "+ ex);
        }  
    }
}
