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
	int prev = 2;		//Holds previous number of processes

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

		if(prev >= numprocs)
			break;

	}
	
    int i,j;

    	int sorted = 0;			//Flag indicating if whether the vector has been sorted
		while(!sorted)													        //While not sorted
		{
			sorted = 1;											        	//Indicated sorted until learning otherwise
			    for(j = 0; j < numprocs; j++)
			    {

					if(j < numprocs-1 && (up[j].sz < up[j+1].sz || strcmp(up[j].name,up[j+1].name) < 0))		//Compare sizes and names of processes
					{
						sorted = 0;										//Indicate array is unsorted
						struct uproc holder;	        						        //Holder uproc for swap
						holder = up[j];										//Swap contents
						strcpy(holder.name,up[j].name);
						up[j] = up[j+1];
						strcpy(up[j].name,up[j+1].name);
						up[j+1] = holder;
						strcpy(up[j+1].name,holder.name);

					}

				}
		}

//Print results
	for(i = 0; i < numprocs; i++)
    {
    	printf(1,"%d  ", up[i].pid);
    	switch (up[i].state)
		{
	    	case 0: 
	    	  printf(1,"%s  ", "UNUSED");
	    	  break;

	    	case 1: 
	    	  printf(1,"%s  ", "EMBRYO");
	    	  break;

	    	case 2: 
	    	  printf(1,"%s  ", "SLEEPING");
	    	  break;

	    	case 3: 
	    	  printf(1,"%s  ", "RUNNABLE");
	    	  break;

	    	case 4: 
	    	  printf(1,"%s  ", "RUNNING");
	    	  break;

	    	case 5: 
	    	  printf(1,"%s  ", "ZOMBIE");
	    	  break;
		}
    	printf(1,"%d  ", up[i].sz);
    	printf(1,"%s\n", up[i].name);

    }
	exit();
}
