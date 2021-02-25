#include <iostream>
#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

using namespace std ;

int udp , tcp , icmp , dns ;

//Prints the hardware address of source and destination
void print_eth_hdr(const u_char* pkt , int size){
	struct ethhdr * ethr = (struct ethhdr *) pkt ;
	printf("Source Address : %.2X - %.2X - %.2X - %.2X - %.2X - %.2X \n" , ethr->h_source[0] , ethr->h_source[1] ,ethr->h_source[2] , ethr->h_source[3] , ethr->h_source[4] , ethr->h_source[5]) ;
	printf("Destination Address : %.2X - %.2X - %.2X - %.2X - %.2X - %.2X \n" , ethr->h_dest[0] , ethr->h_dest[1] ,ethr->h_dest[2] , ethr->h_dest[3] , ethr->h_dest[4] , ethr->h_dest[5]) ;
}

//Prints the ip address of source and destination
void print_ipheader(const u_char* pkt , int size){
	print_eth_hdr(pkt , size) ;
	struct sockaddr_in src ,dst;
	struct iphdr * iph =(struct iphdr*)(pkt + sizeof(ethhdr)) ;
	src.sin_addr.s_addr = iph->saddr ;
	dst.sin_addr.s_addr = iph->daddr ;
	cout << "Source Ip Address : " << inet_ntoa(src.sin_addr) << endl ;
	cout << "Destination Ip Address : " << inet_ntoa(dst.sin_addr) << endl ;
	int iphdrlen = iph->ihl * 4 ;
}

//Prints the details of tcp packet
void print_tcp(const u_char* pkt , int size){
	cout << "--------------------TCP PACKET--------------------\n";
	print_ipheader(pkt , size) ;
	struct iphdr * iph =(struct iphdr*)(pkt + sizeof(ethhdr)) ;
	int iphdrlen = iph->ihl * 4 ;
	struct tcphdr *tcph = (struct tcphdr *)(pkt + iphdrlen + sizeof(ethhdr)) ;
	cout << "Source Port  -> " << ntohs(tcph->source) << endl ;
	cout << "Destination Port  -> " << ntohs(tcph->dest) << endl ;
}

//Prints the details of udp packet
void print_udp(const u_char* pkt , int size){
	cout << "--------------------UDP PACKET----------------\n";
	print_ipheader(pkt , size) ;
	struct iphdr * iph =(struct iphdr*)(pkt + sizeof(ethhdr)) ;
	int iphdrlen = iph->ihl * 4 ;
	struct udphdr *udph = (struct udphdr *)(pkt + iphdrlen + sizeof(ethhdr)) ;
	u_int src_prt = ntohs(udph->source) ;
	u_int dst_prt = ntohs(udph->dest) ;	
	if(src_prt == 53 || dst_prt == 53){
		dns++ ;
	}
	cout << "Source Port  -> " << ntohs(udph->source) << endl ;
	cout << "Destination Port  -> " << ntohs(udph->dest) << endl ;
}


//Prints the details of icmp packet
void print_icmp(const u_char* pkt, int size){
	cout << "--------------------ICMP PACKET--------------------\n";
	print_ipheader(pkt , size) ;
	struct iphdr * iph =(struct iphdr*)(pkt + sizeof(ethhdr)) ;
	int iphdrlen = iph->ihl * 4 ;
	struct icmphdr *tcph = (struct icmphdr *)(pkt + iphdrlen + sizeof(ethhdr)) ;
}

//handler function for capturing and analysing the packet
void packethandler(u_char *usrdata , const struct pcap_pkthdr * hdr , const u_char* pkt){
	int size = hdr->len ;
	struct iphdr * iph =(struct iphdr*)(pkt + sizeof(ethhdr)) ;
	switch(iph->protocol){
		case 1 :
			++icmp ;
			print_icmp(pkt ,size) ;
			break ;
		case 6 :
			++tcp ;
			print_tcp(pkt , size) ;
			break ;
		case 17 :
			++udp ;
			print_udp(pkt , size) ;
			break ;
	}
}

int main(){
	char *dev ;
	pcap_t *desc ;
	char errbf[PCAP_ERRBUF_SIZE] ;
	dev = pcap_lookupdev(errbf) ; //Gets the name of the interface which has to be sniffed
	cout << dev << endl ;
	if(dev == NULL){	//If no interface found
		cout << "No dev found" << errbf << endl ;
	}
	desc = pcap_open_live(dev , BUFSIZ , 0 , -1 , errbf) ;
	if(desc == NULL){
		cout << "Pacap open live failed" <<  errbf << endl ;
		return 1 ;
	}
	if(pcap_loop(desc , 100 , packethandler , NULL)<0){ //Capturing the packets (No of packets captured will be 100)
		cout << "Pcap loop failed" << endl ; 
	}
	cout << "Capture finished " << endl ;
	cout << "---------------------------------------------------------------" << endl ;
	cout << "Capture Summary" << endl ;
	cout << "1. TCP Packets " << tcp << endl;
	cout << "2. UDP Packets " << udp << endl;
	cout << "3. ICMP Packets " << icmp << endl;
	cout << "4. DNS Lookup Packets " << dns << endl; 
	return 0 ;
}
