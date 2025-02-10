
/*
    NOTE: This program is designed for 3 Processes
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    // Get number of processes and check that 3 processes are used
    int size,i;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 3)
    {
        printf("This application is meant to be run with 3 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    // Determine root's rank
    int root_rank = 0;
 
    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
    switch(my_rank)
    {
        case 0:
        {
            // Define my value
            int my_value;
 
            // Declare the buffer
            int buffer[7] = {100, 0, 101, 102, 0, 0, 103};
 
            // Declare the counts
            int counts[3] = {1, 2, 1};
 
            // Declare the displacements
            int displacements[3] = {0, 2, 6};
 
            printf("Values in the buffer of root process:");
            for(i = 0; i < 7; i++)
            {
                printf(" %d", buffer[i]);
            }
            printf("\n");
            MPI_Scatterv(buffer, counts, displacements, MPI_INT, &my_value, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
            printf("Process %d received value %d.\n", my_rank, my_value);
            break;
        }
        case 1:
        {
            // Declare my values
            int my_values[2];
 
            MPI_Scatterv(NULL, NULL, NULL, MPI_INT, my_values, 2, MPI_INT, root_rank, MPI_COMM_WORLD);
            printf("Process %d received values %d and %d.\n", my_rank, my_values[0], my_values[1]);
            break;
        }
        case 2:
        {
            // Declare my values
            int my_value;
 
            MPI_Scatterv(NULL, NULL, NULL, MPI_INT, &my_value, 1, MPI_INT, root_rank, MPI_COMM_WORLD);
            printf("Process %d received value %d.\n", my_rank, my_value);
            break;
        }
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}
