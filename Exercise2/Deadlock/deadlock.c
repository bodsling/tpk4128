#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define NUM_THREADS  5
#define NUM_MUTEXES  5

int eatTime = 400;//us

pthread_t threadid[NUM_THREADS];
pthread_mutex_t lock[NUM_MUTEXES];

void *eat(void *argc)
{
    int philosofer = (int *) argc;

    int leftFork = philosofer;
    int rightFork;
    if (philosofer != NUM_MUTEXES-1)
    {
        rightFork = leftFork +1;
    } else 
    {
        rightFork = 0;
    }
    while (1)
    {
        
        printf("Philosofer %i is not eating\n",philosofer+1);
        
        pthread_mutex_lock(&lock[leftFork]); //Picking up left fork
        pthread_mutex_lock(&lock[rightFork]);//Picking up right fork
        printf("Philosofer %i is eating\n",philosofer+1);
        usleep(eatTime); //Eating
        pthread_mutex_unlock(&lock[rightFork]); //Putting down right fork
        pthread_mutex_unlock(&lock[leftFork]); //Putting down left fork
    }

}

int main()
{
    int i;
    int error;
    for (i = 0; i < NUM_MUTEXES; i++)
    {
        if (pthread_mutex_init(&lock[i],NULL) != 0)
        {   
            printf("\n Mutex init has failed");
            return 1;
        }
    }

    for (i = 0; i < NUM_THREADS; i++)
    {
        error = pthread_create(&threadid[i], NULL, &eat, (void *) i);
        if (error != 0) 
        {    
            printf("\nThread 1 can't be created :[%s]", strerror(error)); 
            return 1;
        }        
    }
    
    

    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threadid[i],NULL);
    }

    for (i = 0; i < NUM_MUTEXES; i++)
    {
        pthread_mutex_destroy(&lock[i]);
    }
    
    return 0;
    
}