#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "BSTree.h"
#ifndef DEBUG
#define DEBUG true
#endif

using namespace std;

void usage(){
	
}

char * sanatize(char * input){
	
}

int main(int argc, char ** argv){
#if DEBUG
cout << "Entered into main: " << argc << " arguments" << endl;
#endif
	if(argc<3){
		usage();
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
		cout << "bad Output File Name: \"" << argv[2] << "\"" << endl;
		return 1;
	}
	vector<int> nums = vector<int>();
	
	return 0;
}
