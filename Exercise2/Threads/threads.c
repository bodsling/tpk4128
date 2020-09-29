#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>


pthread_t tid[2]; 
int globalVar;
pthread_mutex_t lock; 
  
void* incrementVars(void* localPtr) 
{ 
    pthread_mutex_lock(&lock); 
  
    globalVar ++; 
    int localVar = *((int *)localPtr);
    localVar ++;
    printf("Locale Variable: %i\nGlobal Variable: %i\n",localVar,globalVar);
    pthread_mutex_unlock(&lock); 
    
    return NULL; 
} 
  
int main(void) 
{ 
    int i = 0; 
    int error; 
    int *localVar = 0;
    void *localPtr = localVar;

    //Checking that pthread is initiated properly
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    } 
  
    while (i < 2) { 
        error = pthread_create(&(tid[i]), NULL, &incrementVars, &localPtr); 
        if (error != 0) 
        {    
            printf("\nThread can't be created :[%s]", strerror(error)); 
        }
        i++; 
    } 
  
    pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 
    pthread_mutex_destroy(&lock); 
    return 0; 
} 