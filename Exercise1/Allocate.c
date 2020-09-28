#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void Allocate(int value){
	int *ptr = NULL;
	ptr = malloc(100000 * sizeof(int));
	//Modificatgion of function to check for errors
	if (ptr == NULL || *ptr ==-1)
	{
		int errnum = errno;
		printf("Value of errno: %i\n",errnum);
		perror("Error printed by perror:");
		exit(0);

	}
	*ptr = value;
	printf("test of allocated memory: %i\n",value);
}
