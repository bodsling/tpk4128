// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <errno.h>

#define PORT 8080 
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0, valread; 
    int opt = 0;
    struct sockaddr_in serv_addr; 
    char *ping = "PING"; 
    char buffer[1024] = {0}; 
    char *name = malloc(0);
    char *newName = malloc(strlen(name));

    /*  Creating socket file descriptor server_fd  */
    /* Syntax: int socket_fd = socket(domain, type, protocol) */  
    /* Domain: Communication domain: AF_INET (IPv4 protocol), AF_INET6 (IPv6 protocol) */
    /* Type: Communication type: for TCP: SOCK_STREAM, for UDP: SOCK_DGRAM */
    /* Protocol: 0 for IP */
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
    /* For manipulating options of the socket, helps if we are reusing port or address later */
   
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
    /* Que up for connection with the server with address: serv_addr */
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    while (send(sock , ping , strlen(ping) , 0 ) !=-1)//Sending ping to check if server is up
    {

        valread= read( sock , buffer, sizeof(char)); 
        printf("%s\n", buffer); 

        strcat(newName,buffer);
        free(name);
        name = malloc(strlen(newName));
        strcpy(name,newName);
        free(newName);
        newName = malloc(strlen(name)+1);
        strcpy(newName,name);
        
        printf("%s\n",name);
        sleep(1);
        
    }   
    

    printf("\n\nFull name is: %s\n",name);
    free(name);
    free(newName);

    return 0; 
} 
