// mpirun -np 5 program

#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include <fstream>

#include <array>

#include "utils.h"

using namespace std;


//can we assume all the files in files.dat will exist?
//can we assume the txt files will not be empty?
//can we assume files.dat will never be empty?


// dont forget to check for mem leaks !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// dont forget to make it not case sensitive !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

const string FILENAMES_FILE_PATH = "data/files.dat";
const string GLOBAL_DATA_SIZE_TXT_FILE_PATH = "globaldata_size.txt";


int main(int argc, char **argv)
{
//	int a[3] = {1,2,3};
//	cout << sizeof(a) / sizeof(*a) << endl;

	int globaldata_size = 0;
	int *global_sum = new int[26];
	int *local_sum = new int[26];

    int size, rank; //size = # of mpi processes

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

//    cout << "size: " << size << endl;

    char *globaldata=NULL;
    char *localdata=NULL;
    localdata =  new char[5];

    if (rank == 0) {
    	cout << "\n\n\n\n" << endl;
    	//read in the filenames to be read
    	vector<string> txt_filenames = get_txt_filenames(FILENAMES_FILE_PATH);
    	cout << "txt_filenames: " << txt_filenames << endl;

    	//read the chars from each file and add them all to one big vector
    	vector<char> master_char_vec = build_master_char_vec(txt_filenames);
    	cout << "just built mcv, mcv.size: " << master_char_vec.size() << endl;

    	int globaldata_size = find_next_div_size(master_char_vec.size(), size);
    	cout << "globaldata_size: " << globaldata_size << endl;


    	// create and file globaldata, if globaldata is larger than master_char_vec, add 0's to the end to fill
        globaldata = new char[globaldata_size];
        for (int i = 0 ; i < globaldata_size ; i++)
        {
        	if (i < master_char_vec.size())
        		globaldata[i] = master_char_vec[i];
        	else
        		globaldata[i] = '0';
//        	cout << i << ":  " << globaldata[i] << endl;
        }




//        printf("Processor %d has all the data: ", rank);
        cout << "Processor " << rank << " has all the data" << endl;
//        printf("Processor %d has data: ", rank);
//        for (int i=0; i<size; i++)
//            printf("%d ", globaldata[i]);
//        printf("\n");

        cout << "real globadata size: " << sizeof(globaldata) << endl;

        write_int_to_txt_file(globaldata_size, GLOBAL_DATA_SIZE_TXT_FILE_PATH);
    }

    cout << "outside if:  globaldata_size: " << globaldata_size << endl;

    int num_chars_per_mpi_inst = sizeof(globaldata) / sizeof(*globaldata) / size;
    cout << "num_chars_per_mpi_inst:  " << num_chars_per_mpi_inst << endl;

    cout << "about to do scatter" << endl;

    MPI_Scatter(globaldata, num_chars_per_mpi_inst, MPI_INT, localdata, num_chars_per_mpi_inst, MPI_INT, 0, MPI_COMM_WORLD);

//    printf("Processor %d has data %d\n", rank, localdata);

    for (int i=0; i<num_chars_per_mpi_inst; i++)
//        printf("Processor %d has data %d\n", rank, localdata[i]);
    	cout << "Processor " << rank << " has data " << localdata[i] << endl;
//
////    localdata *= 2;
////    printf("Processor %d doubling the data, now has %d\n", rank, localdata);
//
////    MPI_Gather(&localdata, 5, MPI_INT, globaldata, 5, MPI_INT, 0, MPI_COMM_WORLD);
//
//
//    MPI_Reduce(&local_sum, &global_sum, 26, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//
//    if (rank == 0) {
//        printf("Processor %d has data: ", rank);
//        for (int i=0; i<size; i++)
//            printf("%d ", globaldata[i]);
//        printf("\n");
//    }

    if (rank == 0)
        delete(globaldata);

    MPI_Finalize();
    return 0;
}

