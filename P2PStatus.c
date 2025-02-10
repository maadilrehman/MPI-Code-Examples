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
        MPI_Send(sdata, 9, MPI_CHAR, 1,99, MPI_COMM_WORLD);
    } 
    else if (rank==1)
     {  
	char rdata[]="";
	MPI_Status status;
	int totalRec=0;
	MPI_Recv(rdata, 100, MPI_CHAR, 0, 99, MPI_COMM_WORLD,&status);
        printf("\nI am a slave and I received %s message from my master...\n",rdata);
	MPI_Get_count(&status,MPI_CHAR,&totalRec);
	printf("Slave process received %d characters from process %d, with tag %d\n",totalRec,status.MPI_SOURCE,status.MPI_TAG);
	
     }
    printf("Bye...\n");
    MPI_Finalize();
    return 0;
}

