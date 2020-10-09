#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <pthread.h>
#include <string.h> 
#include "serverUtils.h"



void *sendLetterByLetter(void * args)
{
    functionArgs *actualArgs = args;

    int lengthOfString = (int) strlen(actualArgs->charstring);
    send(*actualArgs->socket, &lengthOfString, sizeof(int), 0 );
    sleep(1);
    for (int i = 0; i<(int) strlen(actualArgs->charstring);i++)
    {
        send(*actualArgs->socket , actualArgs->charstring+i, sizeof(char), 0 );
    }
}

void *sortString(void * args)
{
    functionArgs *actualArgs = args;
    char temp;

    for (int i = 0; i < (int) strlen(actualArgs->charstring)-1; i++)
    {
        for (int j = i+1; j < (int) strlen(actualArgs->charstring); j++)
        {
            if(actualArgs->charstring[i] > actualArgs->charstring[j])
            {
                temp = actualArgs->charstring[i];
                actualArgs->charstring[i] = actualArgs->charstring[j];
                actualArgs->charstring[j] = temp; 
            }
        }
        
    }
}

void *readLetterByLetter(void *args)
{
    functionArgs *actualArgs = args;
    int valread;
    int numberBuffer;
    char *returnName;
    char buffer[1024] = {0}; 
    actualArgs->charstring = malloc(0);
    char *newName = malloc(strlen(actualArgs->charstring));

    valread = read( *actualArgs->socket , &numberBuffer, sizeof(int)); 
    printf("%i\n", numberBuffer);

    for (int i = 0;i< numberBuffer;i++)
    {

        valread= read( *actualArgs->socket , buffer, sizeof(char)); 
        printf("%s\n", buffer); 

        strcat(newName,buffer);
        free(actualArgs->charstring);
        actualArgs->charstring = malloc(strlen(newName));
        strcpy(actualArgs->charstring,newName);
        free(newName);
        newName = malloc(strlen(actualArgs->charstring)+1);
        strcpy(newName,actualArgs->charstring);
        
        printf("\n%s\n",actualArgs->charstring);
        sleep(1);
        
    }  
    free(newName);
    
}

void * skipOneLetterInStringAndSend(void *args)
{
    functionArgs *actualArgs = args;
    for (int i = 0; i < (int) strlen(actualArgs->charstring); i++)
    {
        printf("%c",actualArgs->charstring[i]);
        actualArgs->charstring[i] = actualArgs->charstring[i]+1;
        printf("%c\n",actualArgs->charstring[i]);
    }
    int lengthOfString = (int) strlen(actualArgs->charstring);
    send(*actualArgs->socket, &lengthOfString, sizeof(int), 0 );
    send(*actualArgs->socket, actualArgs->charstring, strlen(actualArgs->charstring), 0 );

}

void * recieveString(void *args)
{
    functionArgs *actualArgs = args;
    int valread;
    int numberBuffer;
    valread = read( *actualArgs->socket , &numberBuffer, sizeof(int)); 
    actualArgs->charstring = malloc((numberBuffer+5) * sizeof(char));
    valread = read( *actualArgs->socket , actualArgs->charstring, (size_t) numberBuffer); 
}