#include <mpi.h>
#include <stdio.h>
int main(int argc, char *argv[])
{

	MPI_Init(&argc, &argv);
	
	//Get total processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD,&world_size);

	//Get rank of the currrent process
	int myRank;
	MPI_Comm_rank(MPI_COMM_WORLD,&myRank);

	//Get Processor name
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_length;
 	MPI_Get_processor_name(processor_name,&name_length);


	//Display processor Name
	printf(" Hello PDC class my machine is %s and my rank is %d out of total %d processes \n",processor_name,myRank, world_size);

	  MPI_Finalize();
	  return 0;
}

