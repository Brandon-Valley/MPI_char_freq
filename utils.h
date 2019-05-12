#ifndef UTILS
#define UTILS


#include <iostream>
//#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include <fstream>

using namespace std;







// to print vec
std::ostream & operator << (std::ostream &out, vector<char> &vec)
{
    out << "[";

    for(int i = 0; i < vec.size(); i++)
    {
    	if ( i < vec.size() - 1 )
    		out << "\'" << vec.at(i) << "\'" << ", ";
    	else
    		out << "\'" << vec.at(i) << "\'";
    }
    out << "]";

    return out;
}




// get vec of all chars from given txt file
vector<char> get_chars_from_txt_file(const string txt_file_path)
{
	vector<char> txt_file_chars = {};

	char ch;
	fstream fin("test.txt", fstream::in);
	while (fin >> noskipws >> ch)
	{
		if (ch != ' ' and ch != '\n')
			txt_file_chars.push_back(ch);
	}

	return txt_file_chars;
}


vector<string> get_txt_filenames(const string filename_file_path)
{
	cout << "in get filenames" << endl;
	vector<string> filenames = {};

	std::string item_name;
	std::ifstream nameFileout;

	nameFileout.open(filename_file_path);
	while (std::getline(nameFileout, item_name))
	{
	    std::cout << item_name;
	}
	nameFileout.close();


	return filenames;
}





#endif
