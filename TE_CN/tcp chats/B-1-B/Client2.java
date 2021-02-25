import java.io.*;
import java.net.*;
import java.util.*;

class Client implements Runnable{

	Thread send,recieve;
	Socket socket;
	
	Client(){
	try{
	
		socket=new Socket("127.0.0.1",8000);
		} catch(Exception ex){
			System.out.println(ex.getMessage());
		
		}
		send=new Thread(this);
		recieve=new Thread(this);
		send.start();
		recieve.start();
	
	}
	
	public void run(){
	
		if(Thread.currentThread()==send){
		
			sendMessage();
			
		} else{
		
			recieveMessage();
			
		}
	
	}
	
	void sendMessage(){
	
		try{
	
		InputStream in=socket.getInputStream();
		OutputStream out=socket.getOutputStream();
		
		DataInputStream fin=new DataInputStream(in);
		DataOutputStream fout=new DataOutputStream(out);
		
		
		Scanner sc=new Scanner(System.in);
		String msg;
		int i=0;
		while(i<=10){
		System.out.println();
		System.out.println("Client : ");
		msg=sc.nextLine();
		fout.writeUTF(msg);
		System.out.println();
		//msg=fin.readUTF();
		//System.out.print("Server  "+msg);
		
		
		}
		} catch(Exception ex){
			System.out.println(ex.getMessage());
		
		}
	
	}
	
	void recieveMessage(){
		
		try{
	
		InputStream in=socket.getInputStream();
		OutputStream out=socket.getOutputStream();
		
		DataInputStream fin=new DataInputStream(in);
		DataOutputStream fout=new DataOutputStream(out);
		
		
		Scanner sc=new Scanner(System.in);
		String msg;
		int i=0;
		while(i<=10){
		System.out.println();
		//System.out.print("Client : ");
		//msg=sc.nextLine();
		//fout.writeUTF(msg);
		//System.out.println();
		msg=fin.readUTF();
		System.out.print("Recieved message-"+msg);
		
		
		}
		} catch(Exception ex){
			System.out.println(ex.getMessage());
		
		}

	}
}

class Client2{

	public static void main(String args[]){
	
		Client cl=new Client();
	
	}
}




