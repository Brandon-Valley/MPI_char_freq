// mpirun -np 5 program

#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include <fstream>

#include "utils.h"

using namespace std;


//can we assume all the files in files.dat will exist?
//can we assume the txt files will not be empty?
//can we assume files.dat will never be empty?





const string FILENAMES_FILE_PATH = "data/files.dat";


int main(int argc, char **argv)
{
	//read in the filenames to be read
	vector<string> txt_filenames = get_txt_filenames(FILENAMES_FILE_PATH);
	cout << "txt_filenames: " << txt_filenames << endl;

	//read the chars from each file and add them all to one big vector
	vector<char> master_char_vec = build_master_char_vec(txt_filenames);
	cout << "mcv: " << master_char_vec << endl;



    int size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    cout << "size: " << size << endl;

    int *globaldata=NULL;
    int *localdata=NULL;
    localdata =  new int[5];

    if (rank == 0) {
        globaldata = new int[10];//(size * sizeof(int) );
        for (int i=0; i<10; i++)
            globaldata[i] = i;

        printf("Processor %d has data: ", rank);
        for (int i=0; i<size; i++)
            printf("%d ", globaldata[i]);
        printf("\n");
    }

    cout << "about to do scatter" << endl;

    MPI_Scatter(globaldata, 5, MPI_INT, localdata, 5, MPI_INT, 0, MPI_COMM_WORLD);

//    printf("Processor %d has data %d\n", rank, localdata);

    for (int i=0; i<5; i++)
        printf("Processor %d has data %d\n", rank, localdata[i]);

//    localdata *= 2;
//    printf("Processor %d doubling the data, now has %d\n", rank, localdata);

//    MPI_Gather(&localdata, 5, MPI_INT, globaldata, 5, MPI_INT, 0, MPI_COMM_WORLD);

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

