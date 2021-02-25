import java.util.*;
import java.io.*;
import java.net.*;

class Server implements Runnable {

	ServerSocket svrSocket;
	Thread t;
	LinkedList<Socket> clients;

	Server(){
	
		try{
	
		svrSocket=new ServerSocket(8000);
		}catch(Exception ex){
		
			System.out.println(ex.getMessage());
		
		}
		clients=new LinkedList<Socket>();
		t=new Thread(this);
		t.start();
	
	}
	
	public void run(){
	
		try{
		
		while(true){
		
		Socket skt=svrSocket.accept();
		clients.push(skt);
		new Chatting(skt,clients);
		
		
		
		}
		} catch(Exception ex){
			System.out.println(ex.getMessage());
		
		}
		
	}

}

class Chatting extends Thread{

	Socket sc;
	LinkedList<Socket> clients;
	
	
	Chatting(Socket socket, LinkedList<Socket> clients){
	
	
		sc=socket;
		this.clients=clients;
		start();
	
	}
	
	public void run(){
	
		while(true){
		
		try{
	
		InputStream in=sc.getInputStream();
		DataInputStream din=new DataInputStream(in);
		String msg=din.readUTF();
		System.out.println(msg);
		OutputStream out;
		DataOutputStream dout;
		Socket current;

	
		if(clients.size()>1){
		
		
			for(int i=0;i<clients.size();i++){
			
				current=clients.get(i);
				
				out=current.getOutputStream();
			
				dout=new DataOutputStream(out);
				
				dout.writeUTF(msg);
			
			}
		
		}
		}catch(Exception ex){
			System.out.println(ex.getMessage());
		
		}
		}
		
		
	}
	


}

class MultiClientServer{

	public static void main(String args[]){
		
		Server svr=new Server();
	
	}
}
