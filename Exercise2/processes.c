#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void* createSharedMemory(size_t size)
{
    //Readable and writable file
    int protection = PROT_WRITE | PROT_READ;

    //Possible to use by parent and child, but not third party processes
    int visibility = MAP_SHARED | MAP_ANONYMOUS;

    return mmap(NULL, size, protection, visibility,-1,0);

}

int globalVar = 0;

int main()
{
    int pid = fork();

    // if (pid == )
    // {

    // }

    int localVar = 0;
    

    

    globalVar++;
    localVar++;      

    printf("Global variable: %i\nLocal Variable: %i\n",globalVar,localVar);

    if(pid==0)
    {
        exit(0); //Make sure the child process exits 
    }

    return 0;

}

// int main()
// {

//     void* shmem = createSharedMemory(sizeof(int));

    
//     int *localVar = (int *) malloc(sizeof(int));
//     int *globalVar = (int *) malloc(sizeof(int));
//     *localVar =  0;
//     *globalVar = 0;

//     memcpy(shmem, globalVar, sizeof(globalVar));

//     int pid = fork();

//     if (pid == 0)//Child process
//     {
//         memcpy(globalVar,shmem,sizeof(globalVar));
//         *globalVar += 17;
//         *localVar +=20;
//         memcpy(shmem,globalVar,sizeof(globalVar));
//         printf("Child process: \n");
//     }else
//     {
//         memcpy(globalVar,shmem,sizeof(globalVar));
//         *globalVar += 100;
//         *localVar +=200;
//         memcpy(shmem,globalVar,sizeof(globalVar));
//         printf("Parent process: \n");
//     }

//     printf("Global variable: %i\nLocal Variable: %i\n",*globalVar,*localVar);
    
//     free(globalVar);
//     free(localVar);

    
//     return 0;

// }
