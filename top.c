//top.c
#include "types.h"
#include "stat.h"
#include "fs.h"
#include "user.h"


int main()
{
	struct uproc up[4];
	int correct = 0;
	int numprocs = 9;
	int prev = 0;
	printf(1, "In top\n");
	//call getprocs, retrieve number of processes and allocate it using malloc
	while(!correct)
	{
		malloc(prev*sizeof(struct uproc));
		//Call getprocs passing parameters
		prev = numprocs;
		numprocs = getprocs(prev,up);
		// getprocs returns active processes
		//Allocate more memory
		printf(1, "%d", numprocs);

		if(prev == numprocs)
			correct = 1;

	}
	exit();
}
