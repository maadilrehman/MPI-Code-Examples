#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int rank; 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    printf("Hello from %d\n",rank);

    if (rank == 0)
    {
        char sdata[] = "Hello PDC";
        MPI_Send(sdata, 9, MPI_CHAR, 1, 20, MPI_COMM_WORLD);
    } 
    else if (rank==1)
     {  char rdata[]="";
	MPI_Recv(rdata, 100, MPI_CHAR, 0, 20, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("\nI am a slave and I received %s message from my master...\n",rdata);
     }
    printf("Bye from process-->%d\n",rank);
    MPI_Finalize();
    return 0;
}

