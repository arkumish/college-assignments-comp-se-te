#include <bits/stdc++.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT     8080 
#define MAXLINE 1024 

using namespace std;  

int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 

    struct sockaddr_in     servaddr; 
  
  
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    int n, len; 

    ifstream obj;
    obj.open("1.mp3",ios::binary);

    while(!obj.eof()){
      obj.read((char *)&buffer,sizeof(buffer));
      sendto(sockfd, ( char *)&buffer, sizeof(buffer), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    }
   
   obj.close();   
   
    close(sockfd); 
    return 0; 
} 