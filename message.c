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
     {  char rdata[]="";
	MPI_Recv(rdata, 9, MPI_CHAR, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("\nI am a slave (rank %d) and I received %s message from my master...\n", rank,rdata);
     }
   

    //Test whether all have finished execution or not...
    /*
    int res = MPI_Barrier (MPI_COMM_WORLD); // all processes will wait 
    if (res != MPI_SUCCESS)
    {
    		fprintf (stderr, "MPI_Barrier failed\n");
    }
   */
    //printf("Bye from %d\n",rank);
    MPI_Finalize();
    return 0;
}

