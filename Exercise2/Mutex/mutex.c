#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

//Global variables
bool running = 1;
int var1 = 0;
int var2 = 0;

//Threads
pthread_t threadid[2];
pthread_mutex_t lock;

void *operation1(void * argc)
{
    while (running)
    {
        pthread_mutex_lock(&lock);
        var1++;
        var2 = var1;
        pthread_mutex_unlock(&lock);
    }
    
}

void *operation2(void *argc)
{
    for (int i = 0; i < 20; i++)
    {
        pthread_mutex_lock(&lock);
        printf("Number 1 is % i, number 2 is %i\n",var1,var2);
        pthread_mutex_unlock(&lock);
        usleep(100000);
    }
    running = 0;   
}

int main()
{
    int i;
    int error;
    if (pthread_mutex_init(&lock,NULL) != 0)
    {
        printf("\n Mutex init has failed");
        return 1;
    }

    error = pthread_create(&threadid[0], NULL, &operation1, NULL);
    if (error != 0) 
    {    
        printf("\nThread 1 can't be created :[%s]", strerror(error)); 
        return 1;
    }
    error = pthread_create(&threadid[1], NULL, &operation2, NULL);
    if (error != 0) 
    {    
        printf("\nThread 2 can't be created :[%s]", strerror(error)); 
        return 1;
    }

    pthread_join(threadid[0],NULL);
    pthread_join(threadid[1],NULL);
    pthread_mutex_destroy(&lock);

    return 0;

}


