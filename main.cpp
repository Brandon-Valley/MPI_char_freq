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
//need to wory about going over size of int????????????????????????????


// dont forget to check for mem leaks !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// dont forget to make it not case sensitive !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

const string FILENAMES_FILE_PATH = "data/files.dat";
const string GLOBAL_DATA_SIZE_TXT_FILE_PATH = "globaldata_size.txt";


int main(int argc, char **argv)
{
//	int a[3] = {1,2,3};
//	cout << sizeof(a) / sizeof(*a) << endl;

	int globaldata_size = 0;
	int localdata_size = 0;
	int *global_sum = new int[26];
	int *local_sum = new int[26];

    int size, rank; //size = # of mpi processes

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

//    cout << "size: " << size << endl;

    char *globaldata=NULL;
    char *localdata=NULL;
//    int globaldata_size = 0;

    if (rank == 0) {
    	cout << "\n\n\n\n" << endl;
    	//read in the filenames to be read
    	vector<string> txt_filenames = get_txt_filenames(FILENAMES_FILE_PATH);
    	cout << "txt_filenames: " << txt_filenames << endl;

    	//read the chars from each file and add them all to one big vector
    	vector<char> master_char_vec = build_master_char_vec(txt_filenames);
    	cout << "just built mcv, mcv.size: " << master_char_vec.size() << endl;

    	globaldata_size = find_next_div_size(master_char_vec.size(), size);
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

//    	globaldata = new char[10];
//    	string s = "abcdefghij";
//    	for (int i = 0 ; i < s.size() ; i++)
//    	{
//    		globaldata[i] = s[i];
//    	}
//    	globaldata_size = s.size();


        localdata_size = globaldata_size / size;

        cout << "Processor " << rank << " has all the data" << endl;

//        write_int_to_txt_file(globaldata_size, GLOBAL_DATA_SIZE_TXT_FILE_PATH);
    }

	MPI_Bcast(&localdata_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

//    int g_data_size = read_int_from_txt_file(GLOBAL_DATA_SIZE_TXT_FILE_PATH);
//
////    cout << "outside if:  globaldata_size: " << globaldata_size << endl;
//
//    int num_chars_per_mpi_inst = g_data_size / size;

    localdata =  new char[localdata_size];

    cout << "localdata_size:  " << localdata_size<< endl;

    cout << "about to do scatter" << endl;

    MPI_Scatter(globaldata, localdata_size, MPI_CHAR, localdata,localdata_size, MPI_CHAR, 0, MPI_COMM_WORLD);

//    printf("Processor %d has data %d\n", rank, localdata);

    for (int i=0; i<5; i++)
//        printf("Processor %d has data %d\n", rank, localdata[i]);
    	cout << "Processor " << rank << " has data " << localdata[i] << endl;
////
////    localdata *= 2;
////    printf("Processor %d doubling the data, now has %d\n", rank, localdata);
//
////    MPI_Gather(&localdata, 5, MPI_INT, globaldata, 5, MPI_INT, 0, MPI_COMM_WORLD);
//
//

    sum_chars(local_sum, localdata, localdata_size);


	cout << "local_sum:  [ ";
	for (int i = 0 ; i < 26 ; i++)
	{
		cout << local_sum[i] << " ";
	}
	cout << " ]" << endl;

    MPI_Reduce(local_sum, global_sum, 26, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);



    if (rank == 0)
    {


        cout << "global_sum:  [  ";
        for (int i = 0 ; i < 26 ; i++)
        {
        	cout << global_sum[i] << "  ";
        }
        cout << "  ]" << endl;

    }


//    if (rank == 0)
	delete[] (globaldata);
    delete[] (localdata);
    delete[] (global_sum);
    delete[] (local_sum);


    MPI_Finalize();
    return 0;
}

