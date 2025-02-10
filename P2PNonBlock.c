#include      "mpi.h"
#include<stdio.h>
int   main(int   argc,char*argv[])
{
	int rank,size;
	int flag=0; //for testing send recev status...
        int tag, destination,count;
        int buffer;   
        tag = 1234;
        destination = 1;   
        count = 1;   
        MPI_Status status;
        MPI_Request request = MPI_REQUEST_NULL;
        MPI_Init(&argc,   &argv);
        MPI_Comm_size(MPI_COMM_WORLD,&size);   
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);   

        if(rank==0)   {   /*   master   process   */
           buffer = 9999;
           MPI_Isend(&buffer,count,MPI_INT,destination,tag,MPI_COMM_WORLD,&request);
        }

        if (rank ==  destination)      /*   slave   process   */
		MPI_Irecv(&buffer,count,MPI_INT, 0, tag,MPI_COMM_WORLD,&request);   

    	MPI_Test(&request, &flag, &status);
	printf("\nCommunication event status of process %d is %d",rank,flag);

        MPI_Wait(&request,&status);   //Everyone   wait   here   (both   sender   &   receiver)
        if(rank == 0)   
      		printf("\nProcess   %d   sent   %d\n",   rank,   buffer);

        if(rank == destination)   
        	printf("\nProcess   %d   rcv   %d\n",   rank,   buffer);

        MPI_Finalize();
        return   0;
}

