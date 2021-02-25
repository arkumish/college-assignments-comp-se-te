import java.util.* ;
import java.io.* ;
import java.net.* ;

public class Client{
	private Scanner in = null ;	
	public Client(String addr , int port){
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
			while(true){
				inp = in.nextLine() ;
				b_recv = inp.getBytes() ;
				msg = new DatagramPacket(b_recv , b_recv.length , ip , port) ;
				ds.send(msg) ;
				System.out.println("Client : " + inp) ;
				if(inp.equals("Bye")){
					break ;
				}
				b_recv = new byte[65535] ;
				msg = new DatagramPacket(b_recv , b_recv.length) ;
				ds.receive(msg) ;
				inp = new String(b_recv) ;
				System.out.println("Server : " + inp) ;
				b_recv = new byte[65535] ;
			}
		}
		catch(Exception ex){
			System.out.println(ex) ;
		}
	}
	public static void main(String args[]){
		Client client = new Client("127.0.0.1" , 5100) ;
	}
};
