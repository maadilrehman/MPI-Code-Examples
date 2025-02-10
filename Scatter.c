#include<mpi.h>
#include <stdio.h>
#include<stdlib.h>
int main(int argc,char*argv[])
{
	int i,rank,nproc,irecv;
	int* isend;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	//Master process prepare message
	if (rank==0) {
		isend = (int*)(malloc(sizeof(int)*nproc));
		for (i=0;i<nproc;)
			isend[i]= ++i;
	}
	
	//Everyone executes this, process 0 scaters data
	MPI_Scatter(isend,1,MPI_INT,&irecv,1,MPI_INT,0,MPI_COMM_WORLD);
        printf("Process with rank %d has received data %d\n",rank,irecv);

	MPI_Finalize();
	printf("Bye from %d\n",rank);

return 0;
}
