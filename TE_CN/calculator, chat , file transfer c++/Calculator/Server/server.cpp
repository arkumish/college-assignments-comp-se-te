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

		

	char s[1024] = "ENTER OPERATION NEED TO BE PERFORMED BY CALCULATOR \n1. ADD\n2. SUBTRACT\n3.MULTIPLY\n4. DIVIDE \n" ;
	if(send(clientSockid , &s , sizeof(s) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
	
	int choice;
	if(recv(clientSockid , &choice , sizeof(choice) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
		
	char iop1[1024] = "ENTER FIRST OPERAND: " ;
	if(send(clientSockid , &iop1 , sizeof(s) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
		
	int op1;
	if(recv(clientSockid , &op1 , sizeof(op1) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
		
	char iop2[1024] = "ENTER SECOND OPERAND: " ;
	if(send(clientSockid , &iop2 , sizeof(s) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
		
	int op2;
	if(recv(clientSockid , &op2 , sizeof(op2) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
		
	cout << op1 << " " << op2 << " " << choice << endl;
	int ans;
	switch(choice){
		case 1:
			ans = op1+op2;
			break;
		case 2:
			ans = op1-op2;
			break;
		case 3:
			ans = op1*op2;
			break;
		case 4:
			ans = op1/op2;
			break;
		default:
			ans = -1;
	}

	char iop3[1024] = "ANSWER IS: " ;
	if(send(clientSockid , &iop3 , sizeof(s) , 0)==-1)
		return cout << "Communication error" << endl,0 ;

	if(send(clientSockid , &ans , sizeof(ans) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
	
	//char r[1024];
	//if(recv(clientSockid , r , 1024 , 0)==-1)
	//	return cout << "Communication error" << endl,0 ;

	//char s[1024] ;
	//for(int i=0 ; i<s1.length() ; i++) 
	//	s[i] = s1[i] ;
	//s[s1.length()] = '\0' ;
		
		
}
