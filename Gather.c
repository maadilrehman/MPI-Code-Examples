#include<mpi.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char*argv[])
{
	int i,rank,nproc;
	int sendBuf[3];
	int recvBuf[12]; //for 4 processes, 3 ints for each
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	//Each process prepare send buff data
	for (i=0;i<3;i++) 
		sendBuf[i]=rank;

	//Everyone executes this, process 0 gathers from all 
	MPI_Gather(sendBuf,3,MPI_INT,recvBuf,3,MPI_INT,0,MPI_COMM_WORLD);
	
	if(rank==0) {
		for(i=0;i<12;i++) {
			printf("\nProcess number %d send data : %d",i/3, recvBuf[i]);
		}
	}

	MPI_Finalize();
	printf("\nBye from %d\n",rank);
return 0;
}
