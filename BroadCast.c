#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
int main(int argc,char*argv[])
{
	char message[20];
	int i, rank, size;
	MPI_Status status;
	int root = 0;
	MPI_Init(&argc, &argv) ;
	MPI_Comm_size (MPI_COMM_WORLD,&size);
	MPI_Comm_rank (MPI_COMM_WORLD,&rank);
	
	//only process 0
	if (rank==root)
		strcpy(message,"Hello, world");
	
	//All will execute this
	MPI_Bcast(message,13,MPI_CHAR,root,MPI_COMM_WORLD);

	printf("\nMessage from %d process : %s",rank, message);
	MPI_Finalize();

printf("\n");
return 0;

}
