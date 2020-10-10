// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <pthread.h>
#include "../Headers/serverUtils.h"
#include <netinet/in.h>
#include <netdb.h>
#define PORT 8080
#define IP_PI 192.168.1.1



/* Run server and client in different terminals, run server executable first */

//Threads
pthread_t threadid[2];

int main(int argc, char const *argv[]) 
{ 

    int server_fd, new_socket; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char *myname = "Eirik Bodsberg"; 
    int error;
    functionArgs sendArgs;
    sendArgs.charstring = myname;
    sendArgs.socket = &new_socket;

    /*  Creating socket file descriptor server_fd  */
    /* Syntax: int socket_fd = socket(domain, type, protocol) */  
    /* Domain: Communication domain: AF_INET (IPv4 protocol), AF_INET6 (IPv6 protocol) */
    /* Type: Communication type: for TCP: SOCK_STREAM, for UDP: SOCK_DGRAM */
    /* Protocol: 0 for IP */

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    /* For manipulating options of the socket, helps if we are reusing port or address later */
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    /* Describing internet socket address */
    address.sin_family = AF_INET; /* IPv4 */
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    //inet_aton("192.168.1.147",&address.sin_addr.s_addr);
    //address.sin_addr.s_addr = INADDR_ANY; /* Localhost */
    address.sin_port = htons( PORT ); /*3 Binding to port 8080 */
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    /* Passive mode of the server socket -> waiting for client to make a connection */
    /* The number 3 (backlog) defines the length of the queue that the server can have before it sends error to the client(s) */
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 

    /* Extract the first connection in the queue of the listening socket, and creates a new connected socket. Returns a file 
    descriptor that reffers to the new connected socket. The sockets are now ready for data transfer */
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

   
    if((pthread_create(&threadid[0],NULL,&sendLetterByLetter,&sendArgs))!=0)
    {
        printf("\nThread can't be created :[%s]", strerror(error)); 
        return 1;
    }
    
    
    pthread_join(threadid[0],NULL);

    // if((pthread_create(&threadid[0],NULL,&readLetterByLetter,&sendArgs))!=0)
    // {
    //     printf("\nThread can't be created :[%s]", strerror(error)); 
    //     return 1;
    // }
    
    
    

    // pthread_join(threadid[0],NULL);

    if((pthread_create(&threadid[0],NULL,&recieveString,&sendArgs))!=0)
    {
        printf("\nThread can't be created :[%s]", strerror(error)); 
        return 1;
    }
    
    
    

    pthread_join(threadid[0],NULL);

    printf("\n\nLetters skipped one place gives: %s\n",sendArgs.charstring);
   
    return 0; 
} 
