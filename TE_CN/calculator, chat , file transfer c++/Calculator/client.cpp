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

	char s[1024];
	if(recv(sockid , &s , sizeof(s) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
	else
		cout << s << endl;
	
	int choice; cin >> choice;
	if(send(sockid , &choice , sizeof(choice) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
		
	char opm1[1024];
	if(recv(sockid , &opm1 , sizeof(opm1) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
	else
		cout << opm1 << endl;
		
	int op1; cin >> op1;
	if(send(sockid , &op1 , sizeof(op1) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
		
	char opm2[1024];
	if(recv(sockid , &opm2 , sizeof(opm2) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
	else
		cout << opm2 << endl;
		
	int op2; cin >> op2;
	if(send(sockid , &op2 , sizeof(op2) , 0)==-1)
		return cout << "Communication error" << endl,0 ;

	char opm3[1024];
	if(recv(sockid , &opm3 , sizeof(opm3) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
	else
		cout << opm3 << endl;

	int ans;
	if(recv(sockid , &ans , sizeof(ans) , 0)==-1)
		return cout << "Communication error" << endl,0 ;
	else 
		cout << ans << endl;
}
