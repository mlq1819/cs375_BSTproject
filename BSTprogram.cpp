#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "BSTree.h"
#ifndef DEBUG
#define DEBUG true
#endif

using namespace std;

void usage(char * arg0){
	cout << "./" << arg0 << " <input file> <output file>" << endl;
}

void sanatize(string * str){
	bool whitespace = true;
	size_t idx = 0;
	size_t index = 0;
	while(index<str->length()){
		char c = (*str)[index];
		if(c==' '){
			if(whitespace){
				str->erase(index, 1);
				continue;
			}
			whitespace=true;
			index++;
			continue;
		}
		if(c=='\t' || c=='\n'){
			(*str)[index]=' ';
			continue;
		}
		
		
		if(c<'0' || c>'9'){
			(*str)[index]=' ';
			continue;
		}
		idx=0;
		stoi(str->substr(index, string::npos), &idx, 10);
		index+=idx;
	}
	str->shrink_to_fit();
}

int main(int argc, char ** argv){
#if DEBUG
cout << "Entered into main: " << argc << " arguments" << endl;
#endif
	if(argc<3){
		usage(argv[0]);
		return 0;
	}
	ifstream ifp;
	ifp.open(argv[1]);
	if(!ifp.is_open() || !ifp.good()){
		cout << "Bad Input File Name: \"" << argv[1] << "\"" << endl;
		return 1;
	}
	FileReader reader = FileReader(&ifp);
	if(!reader.readFile()){
		cout << "Reader Failure" << endl;
		ifp.close();
		return 1;
	}
	ifp.close();
	ofstream ofp;
	ofp.open(argv[2]);
	if(!ofp.is_open() || !ifp.good()){
		cout << "Bad Output File Name: \"" << argv[2] << "\"" << endl;
		return 1;
	}
	vector<int> nums = vector<int>();
	reader.start();
#if DEBUG
cout << "Parsing File..." << endl;
#endif
	do{
#if DEBUG
cout << "\tLine " << reader.getIndex() << ":";
#endif
		string input = reader.current();
		sanatize(&input);
		size_t idx = 0;
		while(idx<input.size()){
			nums.push_back(stoi(input.substr(idx, string::npos)), &idx, 10);
#if DEBUG
cout << " " << nums.back();
#endif
			idx++;
		}
#if DEBUG
cout << endl;
#endif
	} while (reader.next());
	nums.shrink_to_fit();
#if DEBUG
cout << "Completed parsing of file!" << endl;
for(unsigned int i=0; i<nums.size(); i++)
	cout << nums[i] << " ";
cout << "\n" << endl;
#endif
	
	return 0;
}
