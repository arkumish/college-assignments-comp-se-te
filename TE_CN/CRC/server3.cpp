

#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 5502

using namespace std;

string binary(string s){
string ans="";
string temp="";

int n=s.size();

for(int i=0;i<n;i++){
 int x=(int)s[i];
 temp="";

  for(int j=0;j<8;j++){
    int r=x%2;
    temp+=char(r+48);
    x=x/2; 
  }
  
 reverse(temp.begin(),temp.end());
 ans+=temp;
}

return ans;
}


string remain(string divisor,string dividend){
  int i=0;
  int n=divisor.size();

  for(int j=0;j<n-1;j++){
    dividend+='0';
  }
  
  cout<<dividend<<endl;
  n=dividend.size();

  deque<char>rem;
  for(int i=0;i<8;i++){
  	rem.push_back(dividend[i]);
  }
 
  i+=8;

  while(i<=n){
  	char t=rem[0];
      for(int j=0;j<8;j++){
        char temp=rem.front();
        if(t=='1')
        rem.push_back(char((divisor[j]^temp)+48));
      else
        rem.push_back(char((temp^t)+48));
         rem.pop_front();
     }
     rem.pop_front();
     //cout<<rem.size()<<endl;
    if(i<n)rem.push_back(dividend[i]);
     i++;
  }

//for(int i=0;i<rem.size();i++)cout<<rem[i]<<" ";

int j=0;
 for(int i=n-7;i<n;i++){
  dividend[i]=rem[j];
  j++;
 }

return dividend;
}



int main()
{  

int skid=socket(AF_INET,SOCK_STREAM,0);


if(skid<0){
cerr<<"SOCKET FAILED";
return -1;
}

sockaddr_in address;
address.sin_family=AF_INET;
address.sin_port=htons(PORT);
address.sin_addr.s_addr=htonl(INADDR_ANY);


int s=bind(skid,(sockaddr *)&address,sizeof(address));
if(s<0){
cerr<<"BINDING FAILED"<<endl;
return -1;
}

int st=listen(skid,5);
if(st<0){
cout<<"LISTENING FAILED";
return -1;
}

int new_socket=accept(skid,(sockaddr *)&address,(socklen_t*)&address);
if(new_socket <0 ){
cerr<<"UNABLE TO ACCEPT";
return -1;
}


	string ss;
  cout<<"\nEnter the message to be send to the client:";
	getline(cin,ss);
  
  //FOR CONVERSION TO BINARY
  string ans=binary(ss);
  string r=remain("10000111",ans);
  
  //MSG SENT IN BINARY WITH CRC;
  cout<<"DATA WITH CRC:"<<r<<endl;
  //SENDING IT TO CLIENT
  int l=r.size();
  send(new_socket,r.c_str(),l,0);
  
  close(skid);

	return 0;
}
