#include<bits/stdc++.h>
#include<arpa/inet.h>

using namespace std;

int main(){

int skid= socket(AF_INET, SOCK_STREAM, 0);
if(skid <0)
	cout<<" error";

sockaddr_in addr;

addr.sin_family = AF_INET;
addr.sin_port = htons(8080);
addr.sin_addr.s_addr = INADDR_ANY;

int addrlen = sizeof(addr);

int sbind = bind(skid, (sockaddr * )&addr, addrlen);
if(sbind <0)
	cout<<" error";

int slisten = listen(skid,5);
if(slisten <0)
	cout<<" error";

int new_sockid = accept(skid , (sockaddr *)&addr, (socklen_t *)&addrlen);
if(new_sockid <0)
	cout<<" error";

string s1= "hello";

int slen = s1.length();

send(new_sockid, s1.c_str(), slen ,0 );

//close(skid);


	return 0;
}