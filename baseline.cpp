//
//
//#include <mpi.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//int main(int argc, char **argv) {
//    int size, rank;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    int *globaldata=NULL;
//    int localdata;
//
//    if (rank == 0) {
//        globaldata = new int[size];//(size * sizeof(int) );
//        for (int i=0; i<size; i++)
//            globaldata[i] = 2*i+1;
//
//        printf("Processor %d has data: ", rank);
//        for (int i=0; i<size; i++)
//            printf("%d ", globaldata[i]);
//        printf("\n");
//    }
//
//    MPI_Scatter(globaldata, 1, MPI_INT, &localdata, 1, MPI_INT, 0, MPI_COMM_WORLD);
//
//    printf("Processor %d has data %d\n", rank, localdata);
//    localdata *= 2;
//    printf("Processor %d doubling the data, now has %d\n", rank, localdata);
//
//    MPI_Gather(&localdata, 1, MPI_INT, globaldata, 1, MPI_INT, 0, MPI_COMM_WORLD);
//
//    if (rank == 0) {
//        printf("Processor %d has data: ", rank);
//        for (int i=0; i<size; i++)
//            printf("%d ", globaldata[i]);
//        printf("\n");
//    }
//
//    if (rank == 0)
//        delete(globaldata);
//
//    MPI_Finalize();
//    return 0;
//}






#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
//#include "vector_print.cpp"
using namespace std;






int main() {

//	vector<char> v1 = {'a', 'b'};
//	vector<char> v2 = {'s','e', 'b'};
//
//	cout

//	v2 = v2 + v1;
	char ch;
	fstream fin("test.txt", fstream::in);
	while (fin >> noskipws >> ch) {
	    cout << ch; // Or whatever
	}
}
//
////    int sum = 0;
////    int x;
////    ifstream inFile;
////
////    inFile.open("test.txt");
////    if (!inFile) {
////        cout << "Unable to open file";
////        exit(1); // terminate with error
////    }
////
////    while (inFile >> x) {
////        sum = sum + x;
////    }
////
////    inFile.close();
////    cout << "Sum = " << sum << endl;
////    return 0;
//}
//
//#include "mpi.h"
//#include <stdio.h>
//
//#define MAX_PROCESSES 10
//
//int main( int argc, char **argv )
//{
//    int rank, size, i,j;
//    int table[MAX_PROCESSES][MAX_PROCESSES];
//    int row[MAX_PROCESSES];
//    int errors=0;
//    int participants;
//
//    MPI_Init( &argc, &argv );
//    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
//    MPI_Comm_size( MPI_COMM_WORLD, &size );
//
//    /* A maximum of MAX_PROCESSES processes can participate */
//    if ( size > MAX_PROCESSES ) participants = MAX_PROCESSES;
//    else participants = size;
//    if ( (rank < participants) ) {
//        int send_count = MAX_PROCESSES;
//        int recv_count = MAX_PROCESSES;
//
//        /* If I'm the root (process 0), then fill out the big table */
//        if (rank == 0)
//            for ( i=0; i<participants; i++)
//                for ( j=0; j<MAX_PROCESSES; j++ )
//                    table[i][j] = i+j;
//
//        /* Scatter the big table to everybody's little table */
//        MPI_Scatter(&table[0][0], send_count, MPI_INT,
//                         &row[0] , recv_count, MPI_INT, 0, MPI_COMM_WORLD);
//
//        /* Now see if our row looks right */
//        for (i=0; i<MAX_PROCESSES; i++)
//            if ( row[i] != i+rank ) errors++;
//    }
//
//    MPI_Finalize();
//    return errors;
//}
//
//
//
////mpirun -np 4 program
//
//
//#include <cstdlib>
//#include <iostream>
//#include <fstream>
//#include <cerrno>
//#include <unistd.h>
//#include "mpi.h"
//#include "pomerize.h"
//
//
//const unsigned int ALERT = 1;
//const unsigned int QUIT = 2;
//const unsigned int REQUEST = 0;
//
//using namespace std;
//
//// this is how many poems you want each Phil to construct & save
//const int MAXMESSAGES = 20;
//
//const string fileBase = "outFile";
//
////make poems and output stanzas to files at the same time kind of, at one point both files have same poem
//void write( pomerize &P, ofstream &foutLeft, ofstream &foutRight)
//{
//  //stanza temps
//  string s1;
//  string s2;
//  string s3;
//
//  s1 = P.getLine();
//
//  foutLeft  << s1 << endl;
//  foutRight << s1 << endl;
//
//  s2 = P.getLine();
//
//  foutLeft  << s2 << endl;
//  foutRight << s2 << endl;
//
//  s3 = P.getLine();
//
//  foutLeft  << s3 << endl << endl;
//  foutRight << s3 << endl << endl;
//
//  return;
//}
//
//
//
//void dealWithReceiveMessage( bool &fileAvail, const int msg )
//{
//	//switch case
//  switch (msg)
//  {
//    case ALERT:
//      fileAvail = true;
//      break;
//    case QUIT:
//      fileAvail = false;
//      break;
//  }
//
//
//  return;
//
//}
//
//int main(int argc, char *argv[])
//{
//	cout<< "in proj!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " << endl;
//  int id; // my MPI ID
//  int p;  // total MPI processes
//  MPI::Status status;
//  int tag = 1;
//  int nSrc; //neighbor source
//
//  bool used = true;
//
//  // Initialize MPI.
//  MPI::Init(argc, argv);
//
//  // Get the number of total processes.
//  p = MPI::COMM_WORLD.Get_size();
//
//  // Determine the rank of this process.
//  id = MPI::COMM_WORLD.Get_rank();
//
//
//
//
//  MPI::Scatter()
//
//  bool rightAvail = false; // my right fork's (file's) availability
//  bool leftAvail  = true;  // my left fork's availability
//
//  //last phill gets both forks at the beginning
//  if      ( p - 1 == id)
//    rightAvail = true;
//  else if ( 0 == id )
//    leftAvail  = false;
//
//
//  // Safety check - need at least 2 philosophers to make sense
//  if (p < 2)
//  {
//    MPI::Finalize();
//    std::cerr << "Need at least 2 philosophers! Try again" << std::endl;
//    return 1; // non-normal QUIT
//  }
//
//  srand(id + time(NULL)); // ensure different seeds...
//
//  int msgsWritten = 0;
//
//  // setup message storage locations
//  int msgIn, msgOut;
//  int leftNeighbor = (id == 0 ? p - 1 : id - 1); // compute left neighbor by getting the previous phil's ID (includes wrap-around)
//  int rightNeighbor = (id + 1) % p;
//
//  pomerize P;
//
//  string lFile = fileBase + to_string(leftNeighbor);
//  string rFile = fileBase + to_string(rightNeighbor);
//  ofstream foutLeft(lFile.c_str(), ios::out | ios::app);
//  ofstream foutRight(rFile.c_str(), ios::out | ios::app);
//
//  while (MAXMESSAGES > msgsWritten)
//  {
//    if ( leftAvail == false or rightAvail == false or used == false )
//    {
//    	//need to ask for access to files now
//      if ( leftAvail == false )
//      {
//        MPI::COMM_WORLD.Send(&REQUEST, 1, MPI::INT, leftNeighbor, tag); // want left fork
//        MPI::COMM_WORLD.Recv(&msgIn, 1, MPI::INT, leftNeighbor, tag, status); // waiting to hear back
//        dealWithReceiveMessage(leftAvail, msgIn);
//      }
//
//      if ( rightAvail == false )
//      {
//        MPI::COMM_WORLD.Send(&REQUEST, 1, MPI::INT, rightNeighbor, tag); //want right fork
//        MPI::COMM_WORLD.Recv(&msgIn, 1, MPI::INT, rightNeighbor, tag, status);// waiting to hear back
//        dealWithReceiveMessage(rightAvail, msgIn);
//      }
//
//
//    }
//    used = false; // fork hasnt been used YET
//
//
//    write(P, foutLeft, foutRight);
//
//    msgsWritten++;
//
//
//    used = true;
//
//
//    while (rightAvail or leftAvail )
//    {
//      MPI::COMM_WORLD.Recv(&msgIn, 1, MPI::INT, MPI::ANY_SOURCE, tag, status);
//
//      nSrc = status.Get_source();
//
//      if      (leftNeighbor == nSrc)
//      {
//        leftAvail = false; //gave away left fork
//        msgOut = (msgsWritten == MAXMESSAGES  ?  QUIT  :  ALERT);
//        MPI::COMM_WORLD.Send(&msgOut, 1, MPI::INT, leftNeighbor, tag); // tell left N that fork is available
//      }
//      else if (rightNeighbor == nSrc)
//      {
//        rightAvail = false;//gave away right fork
//        msgOut = (msgsWritten == MAXMESSAGES  ?  QUIT  :  ALERT);
//        MPI::COMM_WORLD.Send(&msgOut, 1, MPI::INT, rightNeighbor, tag);
//
//      }
//
//    }
//
//  }
//
//  foutLeft.close();
//  foutRight.close();
//
//  //  Terminate MPI.
//  MPI::Finalize();
//  return 0;
//}
//
//
