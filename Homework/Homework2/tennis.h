#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Match{
public:
	string p1f;
	string p1l;
	string p2f;
	string p2l;

	int p1_mw;
	int p1_ml;
	int p2_mw;
	int p2_ml;

	bool read(istream & in_file);

};

