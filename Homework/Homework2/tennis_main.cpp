#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <vector>
#include "tennis.h"
using namespace std;

int main(int argc, char const *argv[]){
	
	ifstream in_file(argv[1]);

	vector <Match> matches;
	Match a_match;

	while(a_match.read(in_file)){
		matches.push_back(a_match);
	}

	for (int i = 0; i < matches.size(); ++i)
	{
		cout << matches[i] << endl;
	}

}