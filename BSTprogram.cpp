#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include "BSTree.h"
#include "Filereader.h"
#ifndef DEBUG
#define DEBUG true
#endif

using namespace std;

clock_t max(clock_t a, clock_t b){
	if(a>b)
		return a;
	return b;
}

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
		clock_t start_time, end_time, one_time, max_diff;
		unsigned long average;
#if DEBUG
cout << "Starting clock for Insert..." << endl;
#endif
		max_diff=0;
		start_time=clock();				//Begin Timer Phase - Insert
		for(unsigned int i=0; i<nums.size(); i++){
			one_time=clock();
			BST.insert(nums[i]);
			one_time=clock()-one_time;
			max_diff=max(max_diff, one_time);
		}
		end_time=clock();				//End Timer Phase - Insert
		average = (unsigned long) (((double)(end_time-start_time))/CLOCKS_PER_SEC*1000/nums.size());
		ofp << argv[argno] << ": Insert\n\tAverage: " << average << " milliseconds\n\tWorst: " << max_diff << endl;
#if DEBUG
cout << "Ended clock for "<< argv[argno] << ": Insert\n\tAverage: " << average << " milliseconds\n\tWorst: " << max_diff << endl;
cout << "starting clock for Search..." << endl;
#endif
		max_diff=0;
		start_time=clock();				//Begin Timer Phase - Search
		for(unsigned int i=0; i<nums.size(); i++){
			one_time=clock();
			BST.find(nums[i]);
			one_time=clock()-one_time;
			max_diff=max(max_diff, one_time);
		}
		end_time=clock();				//End Timer Phase - Search
		average = (unsigned long) (((double)(end_time-start_time))/CLOCKS_PER_SEC*1000/nums.size());
		ofp << argv[argno] << ": Search\n\tAverage: " << average << " milliseconds\n\tWorst: " << max_diff << endl;
#if DEBUG
cout << "Ended clock for "<< argv[argno] << ": Search\n\tAverage: " << average << " milliseconds\n\tWorst: " << max_diff << endl;
cout << "starting clock for Delete..." << endl;
#endif
		max_diff=0;
		start_time=clock();				//Begin Timer Phase - Delete
		for(unsigned int i=0; i<nums.size(); i++){
			one_time=clock();
			BST.remove(nums[i]);
			one_time=clock()-one_time;
			max_diff=max(max_diff, one_time);
		}
		end_time=clock();				//End Timer Phase - Delete
		average = (unsigned long) (((double)(end_time-start_time))/CLOCKS_PER_SEC*1000/nums.size());
		ofp << argv[argno] << ": Delete\n\tAverage: " << average << " milliseconds\n\tWorst: " << max_diff << endl;
#if DEBUG
cout << "Ended clock for "<< argv[argno] << ": Delete\n\tAverage: " << average << " milliseconds\n\tWorst: " << max_diff << endl;
cout << "Finished with " << argv[argno] << "!" << endl;
#endif
	}
	ofp.close();
	
	return 0;
}
