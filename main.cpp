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



const string FILENAMES_FILE_PATH = "data/files.dat";


int main(int argc, char **argv)
{
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
    	//read in the filenames to be read
    	vector<string> txt_filenames = get_txt_filenames(FILENAMES_FILE_PATH);
//    	cout << "txt_filenames: " << txt_filenames << endl;

    	//read the chars from each file and add them all to one big vector
    	vector<char> master_char_vec = build_master_char_vec(txt_filenames);
//    	cout << "just built mcv, mcv.size: " << master_char_vec.size() << endl;

    	globaldata_size = find_next_div_size(master_char_vec.size(), size);
//    	cout << "globaldata_size: " << globaldata_size << endl;


    	// create and file globaldata, if globaldata is larger than master_char_vec, add 0's to the end to fill
        globaldata = new char[globaldata_size];
        for (int i = 0 ; i < globaldata_size ; i++)
        {
        	if (i < master_char_vec.size())
        		globaldata[i] = master_char_vec[i];
        	else
        		globaldata[i] = '0';
        }

        // split the load up evenly between the mpi inst's
        localdata_size = globaldata_size / size;
    }

    // send localdata_size to everyone
	MPI_Bcast(&localdata_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    localdata =  new char[localdata_size];


    MPI_Scatter(globaldata, localdata_size, MPI_CHAR, localdata,localdata_size, MPI_CHAR, 0, MPI_COMM_WORLD);



    // calculate the sum of how many times each char showed up in the txt files
    sum_chars(local_sum, localdata, localdata_size);


    MPI_Reduce(local_sum, global_sum, 26, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);


    if (rank == 0)
    {
    	cout << " " << endl;
        cout << " " << endl;
        cout << "MAKE SURE TO PUT YOUR INPUT TXT FILES IN A DATA FOLDER JUST LIKE IN THE EXAMPLE!" << endl;
        cout << " " << endl;
        print_output(global_sum);
    }



//    if (rank == 0)
	delete[] (globaldata);
    delete[] (localdata);
    delete[] (global_sum);
    delete[] (local_sum);


    MPI_Finalize();
    return 0;
}

