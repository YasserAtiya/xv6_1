//top.c
#include "types.h"
#include "stat.h"
#include "fs.h"
#include "user.h"


int main()
{
	//ptr to uproc struct. used to allocate memory 
	struct uproc *up;
	int numprocs = 4;
	int prev = 2;
	printf(1, "In top\n");
	//call getprocs, retrieve number of processes and allocate it using malloc
	while(1)
	{
		//if up != null free up
		if(up != 0) free(up);

		prev = numprocs;
		
		up = malloc(prev*sizeof(struct uproc));
		//Call getprocs passing parameters
		
		numprocs = getprocs(prev,up);
		// getprocs returns active processes
		//Allocate more memory
		printf(1, "%d\n", numprocs);

		if(prev >= numprocs)
			break;

	}
    int i;
	for(i = 0; i < numprocs; i++)
    {
    	printf(1,"%s\n", up[i].name);
    }
	exit();
}
