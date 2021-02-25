import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Scanner;
 
public class dns {
  public static void main(String args[]) {
    try {
      System.out.println("Choose"+'\n'+"1. DNS Lookup"+'\n'+"2. Reverse DNS Lookup");
      InetAddress host;
      Scanner in=new Scanner(System.in);
      int n=in.nextInt();
      in.nextLine();
      if(n==1)
	System.out.println("URL : ");
      else
	System.out.println("IP : ");
      String[] url=in.nextLine().split(" ");
      if (url.length == 0) {
       	host = InetAddress.getLocalHost();
        	System.out.println("Host:'" + host.getHostName()+ "' has IP: " + host.getHostAddress()); 
      } 
      else {
        	for (int i = 0; i < url.length; ++ i) {
         		InetAddress hosts[] = InetAddress.getAllByName(url[i]);
		if(n==1)
         		     System.out.println("Host:'" + hosts[i].getHostName()+ "' has IP: " + hosts[i].getHostAddress());    
		else
		     System.out.println("IP:'" + hosts[i].getHostAddress()+ "' has Domain Name: " + hosts[i].getHostName());    
        		}
      	}
    } 
    catch (UnknownHostException e) {
      e.printStackTrace();
    }
 }
}
