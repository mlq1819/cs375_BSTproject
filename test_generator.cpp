//============================================================================
// Name        : Final.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;
int left1(int i){
	return i*2+1;
}
int right(int i){
	return i*2+2;
}
int parent(int i){
	return (i-1)/2;
}

void testBalance(int num){
	int arr[num];
	arr[0]=num/2;
	arr[1]=arr[0]/2;
	arr[2]=arr[0]+arr[1];
	for(int i=3;i<num;i++){
		if(i%2==1)arr[i]=arr[parent(i)]-(arr[parent(parent(i))]-arr[parent(i)])/2;
		if(i%2==0)arr[i]=arr[parent(i)]+(arr[parent(parent(i))]-arr[parent(i)])/2;
	}
	for(int i=0;i<num-1;i++){
	}
}


int main() {
//	testBalance(64);
	ofstream output;
	cout<<"this file will generator <best.txt> and <worst.txt> files"<<endl;
	cout<<"please input the range you want to test"<<endl;
	int p;
	cin>>p;
	output.open("worst.txt");
	for(int i=1;i<=pow(2,p)-1;i++){
		output<<i<<endl;
	}
	output.close();
	output.open("best.txt");
	int num=pow(2,p);
	int arr[num-1];
	arr[0]=num/2;
	arr[1]=arr[0]/2;
	arr[2]=arr[0]+arr[1];
	for(int i=3;i<num-1;i++){
		if(i%2==1)arr[i]=arr[parent(i)]-(arr[parent(parent(i))]-arr[parent(i)])/2;
		if(i%2==0)arr[i]=arr[parent(i)]+(arr[parent(parent(i))]-arr[parent(i)])/2;
	}

	for(int i=0;i<num-1;i++){
		output<<arr[i]<<endl;
		cout<<arr[i]<<endl;
	}

	return 0;
}
