#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rank=-1; 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Hello from %d\n",rank);

    if (rank == 0)
    {
        char sdata[] = "Hello PDC";
        MPI_Send(sdata, 9, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    } 
    else if (rank==1)
     { 
	int number_amount;
	MPI_Status status;
	
	// Probe for an incoming message from process 0, tag 0
	MPI_Probe(0, 0, MPI_COMM_WORLD, &status); 

	// When probe returns, the status object has the size and other
	// attributes of the incoming message. Get the message size
	MPI_Get_count(&status, MPI_CHAR, &number_amount);

	printf("number of characters to receive are... %d\n",number_amount);

	// Allocate a buffer to hold the incoming numbers
	char* buf = (char*)malloc(sizeof(char) * number_amount);

	MPI_Recv(buf, 9, MPI_CHAR, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        //printf("\nI am a slave (rank %d) and I received %s message from my master...\n", rank,rdata);
     }
   

    
    //printf("Bye from %d\n",rank);
    MPI_Finalize();
    return 0;
}

