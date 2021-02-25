#include <bits/stdc++.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>

using namespace std;

  
#define PORT     8080 
#define MAXLINE 1024 
  
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 

    struct sockaddr_in servaddr, cliaddr; 
      

    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      

    servaddr.sin_family    = AF_INET; 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      

    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    ofstream obj;
    obj.open("temp.mp3",ios::binary);

    int n,len;
   while( n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                (socklen_t*)&len) ){
      cout<<"YES"<<endl;

      obj.write((char *)buffer,sizeof(buffer));

   } 
    obj.write((char *)buffer,sizeof(buffer));
    cout<<"BYE";

   obj.close();

    return 0; 
} 