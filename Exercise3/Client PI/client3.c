// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <errno.h>
#include <pthread.h>
#include "../Headers/serverUtils.h"

//Teting GIT command

#define PORT 8080 

pthread_t threadid[3];
   
int main(int argc, char const *argv[]) 
{ 
    int sock = 0;
    struct sockaddr_in serv_addr; 
    functionArgs sendArgs;
    char *name;
    sendArgs.charstring = name;
    sendArgs.socket = &sock;
    int error;
    
   


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
    if(inet_pton(AF_INET, "192.168.1.112", &serv_addr.sin_addr)<=0)  
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

    // nameEnd = name + (int) strlen(name)-1;

    // while (myChar!= nameEnd+1)
    // {
    //     send(sock2, myChar, sizeof(char), 0 );
    //     myChar++;
    //     sleep(1);
    // }

    if((pthread_create(&threadid[0],NULL,&readLetterByLetter,&sendArgs))!=0)
    {
        printf("\nThread can't be created :[%s]", strerror(error)); 
        return 1;
    }
    
    
    

    pthread_join(threadid[0],NULL);
    printf("\n\nFull name is: %s\n",sendArgs.charstring);

    // if((pthread_create(&threadid[0],NULL,&sortString,&sendArgs))!=0)
    // {
    //     printf("\nThread can't be created :[%s]", strerror(error)); 
    //     return 1;
    // }
    // pthread_join(threadid[0],NULL);


    // printf("\n\nName sorted is: %s\n",sendArgs.charstring);
    

    // if((pthread_create(&threadid[0],NULL,&sendLetterByLetter,&sendArgs))!=0)
    // {
    //     printf("\nThread can't be created :[%s]", strerror(error)); 
    //     return 1;
    // }
    
    
    // pthread_join(threadid[0],NULL);

    if((pthread_create(&threadid[0],NULL,&skipOneLetterInStringAndSend,&sendArgs))!=0)
    {
        printf("\nThread can't be created :[%s]", strerror(error)); 
        return 1;
    }
    
    
    

    pthread_join(threadid[0],NULL);

    return 0; 
} 
