#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
using namespace std;

int main(){
	struct sockaddr_in server;
	int sockid = socket(PF_INET, SOCK_STREAM,0);
	if(sockid < 0)
		return cout << "SOCKET FAILED " << endl,0;
		
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int status = connect(sockid,(struct sockaddr*)&server,sizeof(server));
	if(status <0)
		return cout << "Connection Failed" << endl,0;
	
	for(int i=0 ; i<10 ; i++){
		char r[1024] ;
		if(recv(sockid , r , 1024 , 0)!=-1)
				cout << "Server : " << r << endl ;
		else
			return cout << "Communication error" << endl,0 ;
			
		string s1 ;
		char s[1024] ;
		cout << "Client : " ;
		getline(cin , s1) ;
		for(int i=0 ; i<s1.length() ; i++) 
			s[i] = s1[i] ;
		s[s1.length()] = '\0' ;
		
		if(send(sockid , s , sizeof(s) , 0)==-1)
			return cout << "Communication error" << endl,0;
	}
}
