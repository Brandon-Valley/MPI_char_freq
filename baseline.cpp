// mpirun -np 5 program

#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//
//	char ch;
//	fstream fin("test.txt", fstream::in);
//	while (fin >> noskipws >> ch) {
//	    cout << ch; // Or whatever
//	}



int main(int argc, char **argv) {
    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    cout << "size: " << size << endl;

    int *globaldata=NULL;
    int localdata;

    if (rank == 0) {
        globaldata = new int[size];//(size * sizeof(int) );
        for (int i=0; i<size; i++)
            globaldata[i] = 2*i+1;

        printf("Processor %d has data: ", rank);
        for (int i=0; i<size; i++)
            printf("%d ", globaldata[i]);
        printf("\n");
    }

    cout << "about to do scatter" << endl;

    MPI_Scatter(globaldata, 1, MPI_INT, &localdata, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Processor %d has data %d\n", rank, localdata);
    localdata *= 2;
    printf("Processor %d doubling the data, now has %d\n", rank, localdata);

    MPI_Gather(&localdata, 1, MPI_INT, globaldata, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Processor %d has data: ", rank);
        for (int i=0; i<size; i++)
            printf("%d ", globaldata[i]);
        printf("\n");
    }

    if (rank == 0)
        delete(globaldata);

    MPI_Finalize();
    return 0;
}

