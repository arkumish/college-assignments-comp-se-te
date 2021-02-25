import java.util.* ;
import java.net.* ;
import java.io.* ;

public class Client2{
	static public Scanner in = null ;
	
	public Client2(String addr , int port){
		try{
			InetAddress ip = InetAddress.getByName(addr) ;
			DatagramSocket ds = new DatagramSocket() ;
			in = new Scanner(System.in) ;
			DatagramPacket msg = null ;
			byte b_recv[] = new byte[65535] ;
			String inp ;
			inp = "Connect" ;
			b_recv = inp.getBytes() ;	
			msg = new DatagramPacket(b_recv , b_recv.length , ip , port) ;
			ds.send(msg) ;
			Thread r = new read(ds) ;
			Thread w = new write(ds , ip , port) ;
			r.start() ;
			w.start() ;
		}
		catch(Exception ex){
			System.out.println(ex) ;
		}
	}
	public static void main(String args[]){
		Client2 client = new Client2("127.0.0.1" , 5100) ;
	}
};

class read extends Thread{
	DatagramSocket ds = null ;
	DatagramPacket msg = null ;
	byte b_recv[] = new byte[65535] ;
	String inp ;
	public read(DatagramSocket ds){
		this.ds = ds ;
	}
	public void run(){
		while(true){
			try{
				msg = new DatagramPacket(b_recv , b_recv.length) ;
				ds.receive(msg) ;
				inp = new String(b_recv) ;
				System.out.println(inp) ;
				b_recv = new byte[65535] ;
			}
			catch(Exception ex){
				System.out.println(ex) ;
			}
		}
	}
}

class write extends Thread{
	InetAddress ip = null ;
	int port ;
	DatagramSocket ds = null ;
	DatagramPacket msg = null ;
	byte b_recv[] = new byte[65535] ;
	String inp ;
	public write(DatagramSocket ds , InetAddress ip , int port){
		this.ds = ds ;
		this.ip = ip ;
		this.port = port ;
	}
	public void run(){
		while(true){
			try{
				inp = Client2.in.nextLine() ;
				inp = "Client 2 : " + inp ;
				b_recv = inp.getBytes() ;
				msg = new DatagramPacket(b_recv , b_recv.length , ip , port) ;
				ds.send(msg) ;
				if(inp.equals("Bye")){
					break ;
				}
				b_recv = new byte[65535] ;
			}
			catch(Exception ex){
				System.out.println(ex) ;
			}
		}
	}
}
