import java.util.* ;
import java.io.* ;
import java.net.* ;

public class server{
	private Scanner in = null ;
	static HashMap<clienthandler , Integer> map = new HashMap<>() ;
	static int n = 1 ;
	static DatagramSocket ds = null ;
	boolean flag = false ;
	public server(int port){
		try{
			in = new Scanner(System.in) ;
			ds = new DatagramSocket(port);
			DatagramPacket msg = null , s_msg = null ;
			byte b_recv[] = new byte[65535] ;
			byte b_send[] = new byte[65535] ;
			System.out.println("Server Created..........") ;
			while(true){
				try{
					flag = false ;
					msg = new DatagramPacket(b_recv , b_recv.length) ;
					ds.receive(msg) ;
					clienthandler curr = new clienthandler(msg.getAddress() , msg.getPort()) ;
					Iterator itr = map.entrySet().iterator() ;
					while(itr.hasNext()){
						Map.Entry mele = (Map.Entry)itr.next() ;
						clienthandler c = (clienthandler)(mele.getKey()) ;
						if(c.port==curr.port){
							flag = true ;
						}
					}
					if(!flag){
						System.out.println("Client " + server.n + " is connected") ;
						map.put(curr , n) ;
						server.n+=1 ;		
					}
					else{
						itr = map.entrySet().iterator() ;
						System.out.println(new String(msg.getData())) ;
						while(itr.hasNext()){
							Map.Entry mele = (Map.Entry)itr.next() ;
							clienthandler c = (clienthandler)(mele.getKey()) ;
							if(c.port!=curr.port){
								String data = new String(msg.getData()) ;
								String s_data = "" ;
								for(int i=0 ; i<data.length() ; i++){
									if(data.charAt(i) == (char)0){
										break ;
									}
									s_data += data.charAt(i) ;
								}
								b_send = s_data.getBytes() ;
								s_msg = new DatagramPacket(b_send , b_send.length , c.ip , c.port) ;
								ds.send(s_msg) ;
								b_send = new byte[65535] ;
							}
						}
					}
					b_recv = new byte[65535] ;
				}
				catch(Exception ex){
					System.out.println(ex) ;
				}
			}
		}
		catch(Exception ex){
			System.out.println(ex) ;
		}
	}
	public static void main(String args[]){
		server serv = new server(5100) ;
	}
}

class clienthandler{
	InetAddress ip = null ;
	int port ;
	boolean status , flag ;
	byte b_recv[] = new byte[65535] ;
	DatagramPacket msg = null ;
	public clienthandler(InetAddress ip , int port){
		try{
			this.ip = ip ;
			this.port = port ;
			this.status = true ;
			flag = false ;
		}
		catch(Exception ex){
			System.out.println(ex) ;
		}		
	}
	public void send(String msg){
		try{
			b_recv = msg.getBytes() ;
			this.msg= new DatagramPacket(this.b_recv , this.b_recv.length , ip , port) ;
			System.out.println(b_recv.length) ;
			server.ds.send(this.msg) ;
			this.b_recv = new byte[65535] ;
		}
		catch(Exception ex){
			System.out.println(ex) ;
		}
	}
}
