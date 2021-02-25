#include<iostream>
#include<pcap.h>
#include<net/ethernet.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<netinet/tcp.h>
#include<netinet/udp.h>
#include<netinet/ip_icmp.h>
#include<arpa/inet.h>
using namespace std;
int tcpCount=0,udpCount=0,icmpCount=0;
void packetHandler(u_char *userData,const struct pcap_pkthdr *pkthdr,const u_char* packet){
    const struct ether_header *ethernetHeader;
    const struct ip *ipHeader;
    const struct tcphdr *tcpHeader;
    const struct udphdr *udpHeader;
    const struct icmphdr *icmpHeader;
  //  const struct udp_header *udpHeader;
    char sourceIP [INET_ADDRSTRLEN];
    char destIP [INET_ADDRSTRLEN];
    char sourceAddress[6];
    char destAddress[6];
    u_int sourcePort,destPort;
    //cout<<INET_ADDRSTRLEN<<endl;
    int datalength =0 ;
    string datastr="";
    u_char *data;
    ethernetHeader=(struct ether_header*) packet;
    printf("Source Address : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X \n",ethernetHeader->ether_shost[0],ethernetHeader->ether_shost[1],ethernetHeader->ether_shost[2],ethernetHeader->ether_shost[3],ethernetHeader->ether_shost[4],ethernetHeader->ether_shost[5]);
    printf("Destination Address : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X \n",ethernetHeader->ether_dhost[0],ethernetHeader->ether_dhost[1],ethernetHeader->ether_dhost[2],ethernetHeader->ether_dhost[3],ethernetHeader->ether_dhost[4],ethernetHeader->ether_dhost[5]);
    if(ntohs(ethernetHeader->ether_type) == ETHERTYPE_IP){
        ipHeader = (struct ip*)(packet + sizeof(struct ether_header));
        inet_ntop(AF_INET, &(ipHeader->ip_src), sourceIP, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ipHeader->ip_dst), destIP, INET_ADDRSTRLEN);
        if(ipHeader->ip_p == IPPROTO_TCP){
            cout<<"Protocol Type : TCP"<<endl;
            tcpHeader=(tcphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
            sourcePort=ntohs(tcpHeader->source);
            destPort=ntohs(tcpHeader->dest);
            tcpCount++;
        }else if(ipHeader->ip_p == IPPROTO_UDP){
            cout<<"Protocol Type : UDP"<<endl;
            udpHeader=(udphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
            sourcePort=ntohs(udpHeader->source);
            udpCount++;
            destPort=ntohs(udpHeader->dest);
        }else if(ipHeader->ip_p == IPPROTO_ICMP){
            cout<<"Protocol Type : ICMP"<<endl;
            icmpHeader=(icmphdr*)(packet + sizeof(struct ether_header) + sizeof(struct ip));
            icmpCount++;
        }
    }
    cout<<"Source IP :"<< sourceIP<<endl;
    cout<<"Source Port : "<<sourcePort<<endl;
    cout<<"Destination IP : "<<destIP<<endl;    
    cout<<"Destination Port : "<<destPort<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
}
void printPackets( ){
    cout<<"TCP Packets: "<<tcpCount<<endl;
    cout<<"UDP Packets: "<<udpCount<<endl;
    cout<<"ICMP Packets: "<<icmpCount<<endl;
}
int main(){
    char* dev;
    pcap_t *descr;
    char errbuf[PCAP_ERRBUF_SIZE];
    dev = pcap_lookupdev(errbuf);
        cout<<"pcap_lookupdev() :failed "<<errbuf<<endl;
    if(dev==NULL){
        return 1;
    }
    descr= pcap_open_live (dev, BUFSIZ, 0, -1, errbuf);
    descr= pcap_open_offline ("udp.pcap", errbuf);
    descr= pcap_open_offline ("tcp.cap", errbuf);
    //descr =pcap_open_offline ("4A.pcapng", errbuf);
    if(descr == NULL){
       // cout<<"pcap_open_live() : failed "<<errbuf<<endl;
        cout<<"pcap_open_offline() : failed "<<errbuf<<endl;
        return 1;
    }
    if(pcap_loop(descr,0, packetHandler, NULL)<0){
        cout<<"pcap_loop() : failed "<<pcap_geterr(descr)<<endl;
        return 1;
    }
    cout<<"Packet Capture finished "<<endl;
    cout<<"TCP Packets: "<<tcpCount<<endl;
    cout<<"UDP Packets: "<<udpCount<<endl;
    cout<<"ICMP Packets: "<<icmpCount<<endl;
    return 0;
}
