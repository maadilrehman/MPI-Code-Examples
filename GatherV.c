
/*
    NOTE: This program is designed for 5 Processes
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>
int main(int argc, char **argv) {

    MPI_Init(&argc, &argv); 

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int nstrings=5; // for 5 different processes
    const char *const strings[5] = {"Hello","from","your Teacher","Muhammad","Aleem"};

    // Everyone gets a string   
    char *mystring = (char *)strings[rank];
    int mylen = strlen(mystring);
    printf("Rank %d: %s\n", rank, mystring);

    //***************************************************************************
    // Now, we Gather the string lengths to the root process, 
    // so we can create the buffer into which we'll receive the strings
    //****************************************************************************

    const int root = 0;
    int *recvcounts = NULL;

    // Only root has the received data
    if (rank == root)
        recvcounts = malloc(size * sizeof(int)) ;
	
    //process 0 gets length values from all other process (everyone sends length of the string they have)
    MPI_Gather(&mylen, 1, MPI_INT,recvcounts, 1, MPI_INT,root, MPI_COMM_WORLD);

    //***************************************************************************
    // Figure out the total length of string and displacements for each rank 
    //***************************************************************************

    int totlen = 0;
    int *displs = NULL;
    char *totalstring = NULL;
    int i=0;

    if (rank == root) {
        displs = malloc(size * sizeof(int));

        displs[0] = 0;
        totlen = totlen + (recvcounts[0]+1); //+1 for space or \0 after words 

        for (i=1; i<size; i++) {
           totlen = totlen + (recvcounts[i]+1);   //+1 for space or \0 after words
           displs[i] = displs[i-1] + recvcounts[i-1] + 1;
        }

        //Allocate string, pre-fill with spaces and null terminator */
        totalstring = malloc(totlen * sizeof(char));            
        for (i=0; i<totlen-1; i++)
            totalstring[i] = ' ';
        totalstring[totlen-1] = '\0';
     }

     //***************************************************************************
     // Now we have the receive buffer, counts, and displacements, and can gather the strings 
     //*************************************************************************** 
     MPI_Gatherv(mystring, mylen, MPI_CHAR, totalstring, recvcounts, displs, MPI_CHAR, root, MPI_COMM_WORLD);

     if (rank == root) {
        printf("Root process %d: <%s>\n", rank, totalstring);
        free(totalstring);
        free(displs);
        free(recvcounts);
    }

    MPI_Finalize();
    return 0;
}
