#include <stdio.h>
#include <string.h>
#include <iostream>
#ifndef DEBUG
#define DEBUG true
#endif

using namespace std;

int main(int argc, char ** argv){
#if DEBUG
cout << "Entered into main: " << argc << " arguments" << endl;
#endif
	
	return 0;
}
