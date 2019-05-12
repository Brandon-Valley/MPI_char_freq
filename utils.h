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





vector<string> split(string str, string token){
    vector<string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}





template <typename T>
std::ostream & operator << (std::ostream &out, vector<T> &vec)
{
    out << "[";

    for(int i = 0; i < vec.size(); i++)
    {
    	if ( i < vec.size() - 1 )
    		out << vec.at(i) << ", ";
    	else
    		out << vec.at(i);
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
	vector<string> filenames = {};

	std::string item_name;
	std::ifstream nameFileout;

	nameFileout.open(filename_file_path);
//	string filenames_str = getline(nameFileout, item_name);
	while (std::getline(nameFileout, item_name))
	{
	    filenames.push_back(item_name);
	}
	nameFileout.close();


	return filenames;
}


// read in the chars from all files and put them all in one big vec
vector<char> build_master_char_vec(const vector<string> txt_filenames)
{
	vector<char> master_char_vec = {};

	for (string filename : txt_filenames)
	{
//		cout << filename << endl;
		vector<char> chars_from_file = get_chars_from_txt_file(filename);

		//add the chars from the txt file that you just read to the master char vec
		master_char_vec.insert( master_char_vec.end(), chars_from_file.begin(), chars_from_file.end() );

	}

	return master_char_vec;
}















#endif
