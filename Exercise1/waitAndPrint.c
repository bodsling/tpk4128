#include <stdio.h>
#include <stdlib.h>

#include <unistd.h> //Header file for sleep
#include <pthread.h> //Header file for POSIX Threads

#include <sys/times.h>


void *waitFiveSAndPrint(void *vargp)
{
    //Using sleep fucntion
    printf("Message 1\n");
    sleep(5);
    printf("Message 2\n");
}

void *BusyAndWaitPrint(int *seconds)
{
    printf("Message 1\n");
    int i,temp;
    int tps = sysconf(_SC_CLK_TCK); //Number of clocktics per second (Hz)
    clock_t start; //Declearing a clock
    struct tms exec_time;
    times(&exec_time); //Setting up execution time
    start = exec_time.tms_utime; //Returning the number of clock cycles executed so far

    while ((exec_time.tms_utime - start) < (*seconds * tps))
    {
        for (i=0; i<1000;i++)
        {
            temp= i;
        }     
        times(&exec_time);
    }
        

    printf("Message 2\n");
}

int main()
{
    pthread_t thread_id; //thread_id is an integer used to identify the thread
    int numThreads = 2;
    int numSeconds = 5;

    for (int i = 0;i < numThreads; i++)
    {
        /*Creating a thread. 
        1st argument sets a pointer to thread id
        2nd argument specifies attributes, if NULL default is used
        3rd argument is the name of the function to be executed for the thread to be created
        4th argument is arguments to the function
        */
        //pthread_create(&thread_id,NULL,waitFiveSAndPrint,NULL);
        pthread_create(&thread_id,NULL,BusyAndWaitPrint,&numSeconds);

    }
    pthread_exit(0);

}