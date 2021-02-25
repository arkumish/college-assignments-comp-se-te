import java.util.* ;
import java.io.* ;
import java.net.* ;

public class server{
	private Scanner in = null ;	
	public server(int port){
		try{
			in  = new Scanner(System.in) ;
			DatagramSocket ds = new DatagramSocket(port) ;
			System.out.println("Server started..........") ;
			DatagramPacket msg = null ;
			InetAddress ip = InetAddress.getLocalHost() ;
			int cport ;
			byte b_recv[] = new byte[65535] ;
			String s_msg ;
			s_msg = "Connect" ;       //STRING WITH message connect
			b_recv = s_msg.getBytes() ;	//convert string to bytes	
			msg = new DatagramPacket(b_recv , b_recv.length) ;  //a DGRAM packet created
			ds.receive(msg);
			ip = msg.getAddress() ;
			cport = msg.getPort() ;
			b_recv = new byte[65535] ;
			while(true){
				msg = new DatagramPacket(b_recv , b_recv.length) ;
				ds.receive(msg) ;
				s_msg = new String(b_recv) ;
				System.out.println("Client : " + s_msg) ;
				if(s_msg.equals("Bye")){
					break ;
				}
				b_recv = new byte[65535] ;
				s_msg = in.nextLine() ;
				b_recv = s_msg.getBytes() ;
				msg = new DatagramPacket(b_recv , b_recv.length , ip , cport) ;
				ds.send(msg) ;
				System.out.println("Server : " + s_msg) ;
				b_recv = new byte[65535] ;
			}
		}
		catch(Exception ex){
			System.out.println(ex) ;
		}
	}
	public static void main(String args[]){
		server serv = new server(5100) ;
	}
};
