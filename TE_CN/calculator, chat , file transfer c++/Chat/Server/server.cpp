#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std; 

int main(){
	struct sockaddr_in addr,client;
	int sockid = socket(AF_INET , SOCK_STREAM , 0);
	
	if(sockid < 0)
		return cout << "SOCKET FAILED" << endl,0;
	addr.sin_family = AF_INET ;
	addr.sin_port = htons(8080) ;
	addr.sin_addr.s_addr = htonl(INADDR_ANY) ;
		
	if(bind(sockid , (struct sockaddr *)&addr , sizeof(addr))==-1)
		return cout << "BINDING FILED " << endl,0;
		
	if(listen(sockid , 1)==-1)
		return cout << "LISTEN ERROR" << endl,0;
		
	int clientSockid , clientLength ;
	clientLength = sizeof(client) ;
	if((clientSockid = accept(sockid , (struct sockaddr *)&client , (socklen_t *)&clientLength))<0)
		return cout << "Can't Accept" << endl,0;
		
	for(int i=0 ; i<10 ; i++){	
		cout << "Server: " ;
		
		string s1 ;
		char s[1024] ;
		getline(cin , s1) ;
		for(int i=0 ; i<s1.length() ; i++) 
			s[i] = s1[i] ;
		s[s1.length()] = '\0' ;
		
		if(send(clientSockid , s , sizeof(s) , 0)==-1)
			return cout << "Communication error" << endl,0 ;	
		
		char r[1024];
		if(recv(clientSockid , r , 1024 , 0)!=-1)
			cout << "Client: " << r << endl ;
		else
			return cout << "Communication error" << endl,0 ;
	}
}
