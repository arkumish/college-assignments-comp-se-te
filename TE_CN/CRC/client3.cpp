
#include<bits/stdc++.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 5502

using namespace std;

string bintoascii(string s){
  int n=s.size();
  int i=0;
  string ans="";
  while(i<n){
    string temp=s.substr(i,8);
    int ts=temp.size();
    int x=0;
    int pow=1;
    for(int j=ts-1;j>=0;j--){
      if(temp[j]=='1')
           x+=pow;
            pow=2*pow;
    }
    
    ans+=char(x);
    i+=8;
  }
  return ans;
}


bool chk(string divisor,string  dividend){
   int i=0;
   int n=dividend.size();
  
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
        rem.push_back(char((temp^'0')+48));
   
        rem.pop_front();
     }
     rem.pop_front();
     if(i<n)rem.push_back(dividend[i]);
     i++;
  }

  bool fans=true;
  for(int i=0;i<rem.size();i++)
    {
      //cout<<rem[i]<<" ";
    if(rem[i]!='0'){fans=false;
      break;
     }
    }

return fans;
}



string numbergenerator(string s){
 int n=s.size();
  srand(time(0));
  int x=rand();
  x=x%n;
  if(s[x]=='0')
    s[x]='1';
 else
    s[x]='0';
  return s;
}

void menu(string r){

   string t;
   int ch;
   cout<<"\nEnter your choice \n 1 for error 2 for without error :";
   cin>>ch;

   if(ch==1){
    t=numbergenerator(r);
   }else{
    t=r;
   }
  
int n=t.size();
string temp=bintoascii(t.substr(0,n-7));
    
    if(chk("10000111",t))
    {
     cout<<temp<<endl;
    }else{
      cout<<"\nERROR MSG IS DAMAGED\n";
      cout<<temp<<endl;
    }
}

int main(int argc,char *argv[]){

int skid=socket(AF_INET,SOCK_STREAM,0);

if(skid<0){
cerr<<"SOCKET FAILED";
return -1;
}

sockaddr_in address;
address.sin_family=AF_INET;
address.sin_port=htons(PORT);
address.sin_addr.s_addr=inet_addr("127.0.0.1");


int new_socket=connect(skid,(sockaddr *)&address,sizeof(address));
if(new_socket <0 ){
cerr<<"UNABLE TO CONNECT";
return -1;
}


 char tt[100000];
 read(skid,tt,100000);
 string r="";
 int l=strlen(tt);
 for(int i=0;i<l;i++){
  r+=tt[i];
 }

 menu(r);

 close(skid);

  return 0;
}
