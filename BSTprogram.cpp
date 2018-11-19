#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include "BSTree.h"
#ifndef DEBUG
#define DEBUG true
#endif

using namespace std;

void usage(char * arg0){
	cout << "./" << arg0 << " <output file> <input file> [<input file>...]" << endl;
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
	ofstream ofp;
	ofp.open(argv[1]);
	if(!ofp.is_open() || !ofp.good()){
		cout << "Bad Output File: \"" << argv[2] << "\"; Sending to \"output.txt\"" << endl;
		ofp.open("output.txt");
		if(!ofp.is_open() || !ofp.good()){
			cout << "Output File cannot be generated" << endl;
			return 1;
		}
	}
	for(int argno=2; argno<argc; argno++){
#if DEBUG
cout << "Starting " << argv[argno] << "..." << endl;
#endif
		ifstream ifp;
		ifp.open(argv[argno]);
		if(!ifp.is_open() || !ifp.good()){
			cout << "Bad Input File: \"" << argv[argno] << "\"" << endl;
			ofp.close();
			return 1;
		}
		FileReader reader = FileReader(&ifp);
		if(!reader.readFile()){
			cout << "Reader Failure" << endl;
			ifp.close();
			ofp.close();
			return 1;
		}
		ifp.close();
		
		vector<int> nums = vector<int>();
		reader.start();
#if DEBUG
cout << "Parsing File..." << endl; 			//Begin Parsing
#endif
		do{						//start Parser Loop
#if DEBUG
cout << "\tLine " << reader.getIndex() << ":";
#endif
			string input = reader.current();
			sanatize(&input);
			size_t idx = 0;
			size_t index = 0;
			while(index<input.size()){
				nums.push_back(stoi(input.substr(index, string::npos), &idx, 10));
#if DEBUG
cout << " " << nums.back();
#endif
				index+=idx;
			}
#if DEBUG
cout << endl;
#endif
		} while (reader.next());			//End Parser Loop
		nums.shrink_to_fit();
#if DEBUG
cout << "Completed parsing of file!" << endl;
for(unsigned int i=0; i<nums.size(); i++)
	cout << nums[i] << " ";
cout << "\n" << endl;
#endif
		BSTree BST = BSTree();
		clock_t start_time, end_time;
		unsigned long runtime;
#if DEBUG
cout << "Starting clock for insert..." << endl;
#endif
		start_time=clock();				//Begin Timer Phase - Insert
		for(unsigned int i=0; i<nums.size(); i++)
			BST.insert(nums[i]);
		end_time=clock();				//End Timer Phase - Insert
		runtime = (unsigned long) (((double)(end_time-start_time))/CLOCKS_PER_SEC*1000);
		ofp << argv[argno] << ": Insert: " << runtime << " milliseconds" << endl;
#if DEBUG
cout << "Ended clock for insert: " << runtime << " milliseconds for " << argv[argno] << endl;
cout << "starting clock for find..." << endl;
#endif
		start_time=clock();
		for(unsigned int i=0; i<nums.size(); i++)
			BST.find(nums[i]);
		end_time=clock();
		runtime = (unsigned long) (((double)(end_time-start_time))/CLOCKS_PER_SEC*1000);
		ofp << argv[argno] << ": Find: " << runtime << " milliseconds" << endl;
#if DEBUG
cout << "Ended clock for find: " << runtime << " milliseconds for " << argv[argno] << endl;
cout << "starting clock for delete..." << endl;
#endif
		start_time=clock();
		for(unsigned int i=0; i<nums.size(); i++)
			BST.remove(nums[i]);
		end_time=clock();
		runtime = (unsigned long) (((double)(end_time-start_time))/CLOCKS_PER_SEC*1000);
		ofp << argv[argno] << ": Delete: " << runtime << " milliseconds" << endl;
#if DEBUG
cout << "Ended clock for delete: " << runtime << " milliseconds for " << argv[argno] << endl;
cout << "Finished with " << argv[argno] << "!" << endl;
#endif
	}
	ofp.close();
	
	return 0;
}
