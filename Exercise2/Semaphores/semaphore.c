#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

sem_t sem; //A atomic unsigned int


void *semaphoreFun(void *arg)
{
    sem_wait(&sem);//Decrementing semaphore by one
    for (int i = 0; i < 4; i++)
    {
        printf("Thread number %i is accessing the resources, loop index %i\n",((int *) arg),i);
        sleep(1);
    }
    
    sem_post(&sem);//Incrementing semaphore by one
}

int main()
{   
    int numThreads = 5;
    int numResources = 3;
    sem_init(&sem,0,numResources);
    pthread_t thread[numThreads];

    for (int i = 0; i < numThreads; i++)
    {
        pthread_create(&thread[i],NULL,&semaphoreFun,(void *) i+1);

    }
    
    
    for (int i = 0; i < numThreads; i++)
    {
        pthread_join(thread[i],NULL);

    }

    return 0;

}