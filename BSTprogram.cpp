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

#ifndef TIME_TO_RUN
#define TIME_TO_RUN 1
#endif

using namespace std;

unsigned long max(unsigned long a, clock_t b){
	if(a>(unsigned long) b)
		return a;
	return (unsigned long) b;
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
		unsigned int insert_averages[TIME_TO_RUN];
		unsigned int insert_worsts[TIME_TO_RUN];
		unsigned long insert_totals[TIME_TO_RUN];
		unsigned int search_averages[TIME_TO_RUN];
		unsigned int search_worsts[TIME_TO_RUN];
		unsigned long search_totals[TIME_TO_RUN];
		unsigned int delete_averages[TIME_TO_RUN];
		unsigned int delete_worsts[TIME_TO_RUN];
		unsigned long delete_totals[TIME_TO_RUN];
		for(unsigned int runs=0; runs<TIME_TO_RUN; runs++){
			BSTree BST = BSTree();
			clock_t start_time, end_time, one_time;
#if DEBUG
cout << "Starting clock for Insert..." << endl;
#endif
			insert_averages[runs]=0;
			insert_worsts[runs]=0;
			insert_totals[runs]=0;
			start_time=clock();				//Begin Timer Phase - Insert
			for(unsigned int i=0; i<nums.size(); i++){
				one_time=clock();
				BST.insert(nums[i]);
				one_time=clock()-one_time;
				insert_worsts[runs]=max(insert_worsts[runs], one_time);
			}
			end_time=clock();				//End Timer Phase - Insert
			insert_totals[runs] = (unsigned long) end_time-start_time;
			insert_averages[runs] = (unsigned long) (((double)insert_totals[runs])*1000/CLOCKS_PER_SEC/nums.size());
			
#if DEBUG
cout << argv[argno] << " (" << runs+1 << ")" << ": Insert" << endl;
cout << "\tAverage: " << insert_averages[runs] << " milliseconds" << endl;
cout << "\tWorst: " << insert_worsts[runs] << " milliseconds" << endl;
cout << "\tTotal: " << insert_totals[runs] << " milliseconds" << endl;
cout << "starting clock for Search..." << endl;
#endif
			search_averages[runs]=0;
			search_worsts[runs]=0;
			search_totals[runs]=0;
			start_time=clock();				//Begin Timer Phase - Search
			for(unsigned int i=0; i<nums.size(); i++){
				one_time=clock();
				BST.find(nums[i]);
				one_time=clock()-one_time;
				search_worsts[runs]=max(search_worsts[runs], one_time);
			}
			end_time=clock();				//End Timer Phase - Search
			search_totals[runs] = (unsigned long) end_time-start_time;
			search_averages[runs] = (unsigned long) (((double)search_totals[runs])*1000/CLOCKS_PER_SEC/nums.size());
			
#if DEBUG
cout << argv[argno] << " (" << runs+1 << ")" << ": Search" << endl;
cout << "\tAverage: " << search_averages[runs] << " milliseconds" << endl;
cout << "\tWorst: " << search_worsts[runs] << " milliseconds" << endl;
cout << "\tTotal: " << search_totals[runs] << " milliseconds" << endl;
cout << "starting clock for Delete..." << endl;
#endif
			delete_averages[runs]=0;
			delete_worsts[runs]=0;
			delete_totals[runs]=0;
			start_time=clock();				//Begin Timer Phase - Delete
			for(unsigned int i=0; i<nums.size(); i++){
				one_time=clock();
				BST.remove(nums[i]);
				one_time=clock()-one_time;
				delete_worsts[runs]=max(delete_worsts[runs], one_time);
			}
			end_time=clock();				//End Timer Phase - Delete
			delete_totals[runs] = (unsigned long) end_time-start_time;
			delete_averages[runs] = (unsigned long) (((double)delete_totals[runs])*1000/CLOCKS_PER_SEC/nums.size());
			
#if DEBUG
cout << argv[argno] << " (" << runs+1 << ")" << ": Delete" << endl;
cout << "\tAverage: " << delete_averages[runs] << " milliseconds" << endl;
cout << "\tWorst: " << delete_worsts[runs] << " milliseconds" << endl;
cout << "\tTotal: " << delete_totals[runs] << " milliseconds" << endl;
cout << "Finished with " << argv[argno] << "!\n" << endl;
#endif
		}
		unsigned int insert_average=0;
		unsigned int insert_worst=0;
		unsigned long insert_total=0;
		unsigned int search_average=0;
		unsigned int search_worst=0;
		unsigned long search_total=0;
		unsigned int delete_average=0;
		unsigned int delete_worst=0;
		unsigned long delete_total=0;
		
		for(unsigned int i=0; i<TIME_TO_RUN; i++){
			insert_average+=insert_averages[i];
			insert_worst+=insert_worsts[i];
			insert_total+=insert_totals[i];
			search_average+=search_averages[i];
			search_worst+=search_worsts[i];
			search_total+=search_totals[i];
			delete_average+=delete_averages[i];
			delete_worst+=delete_worsts[i];
			delete_total+=delete_totals[i];
		}
		
		ofp << argv[argno] << ": Insert" << endl;
		ofp << "\tAverage: " << insert_average/TIME_TO_RUN << " milliseconds" << endl;
		ofp << "\tWorst: " << insert_worst/TIME_TO_RUN << " milliseconds" << endl;
		ofp << "\tTotal: " << insert_total/TIME_TO_RUN << " milliseconds" << endl;
		ofp << argv[argno] << ": Search" << endl;
		ofp << "\tAverage: " << search_average/TIME_TO_RUN << " milliseconds" << endl;
		ofp << "\tWorst: " << search_worst/TIME_TO_RUN << " milliseconds" << endl;
		ofp << "\tTotal: " << search_total/TIME_TO_RUN << " milliseconds" << endl;
		ofp << argv[argno] << ": Delete" << endl;
		ofp << "\tAverage: " << delete_average/TIME_TO_RUN << " milliseconds" << endl;
		ofp << "\tWorst: " << delete_worst/TIME_TO_RUN << " milliseconds" << endl;
		ofp << "\tTotal: " << delete_total/TIME_TO_RUN << " milliseconds" << endl;
#if DEBUG
cout << argv[argno] << ": Insert" << endl;
cout << "\tAverage: " << insert_average/TIME_TO_RUN << " milliseconds" << endl;
cout << "\tWorst: " << insert_worst/TIME_TO_RUN << " milliseconds" << endl;
cout << "\tTotal: " << insert_total/TIME_TO_RUN << " milliseconds" << endl;
cout << argv[argno] << ": Search" << endl;
cout << "\tAverage: " << search_average/TIME_TO_RUN << " milliseconds" << endl;
cout << "\tWorst: " << search_worst/TIME_TO_RUN << " milliseconds" << endl;
cout << "\tTotal: " << search_total/TIME_TO_RUN << " milliseconds" << endl;
cout << argv[argno] << ": Delete" << endl;
cout << "\tAverage: " << delete_average/TIME_TO_RUN << " milliseconds" << endl;
cout << "\tWorst: " << delete_worst/TIME_TO_RUN << " milliseconds" << endl;
cout << "\tTotal: " << delete_total/TIME_TO_RUN << " milliseconds" << endl;
#endif
	}
	ofp.close();
	
	return 0;
}
