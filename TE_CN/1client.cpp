#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<unistd.h>

using namespace std;

int main(){

int skid = socket(AF_INET, SOCK_STREAM,0);
if(skid <0)
	cout<<" error";

sockaddr_in addr;

addr.sin_family = AF_INET;
addr.sin_port = htons(8080);
addr.sin_addr.s_addr = inet_addr("127.0.0.1");

int sconnect = connect(skid, (sockaddr *)&addr, sizeof(addr));
if(sconnect <0)
	cout<<" error";
char r[1024];

read(skid, r,1024);
	cout<<r;


	return 0;
}