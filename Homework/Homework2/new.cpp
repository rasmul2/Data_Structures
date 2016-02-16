#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Player{
public:
	int games_won;
	int games_lost;
	string first_name;
	string last_name;

	bool read(in_file, winner, loser, match){
		vector <strings> read;
		in_file >> first_name >> last_name;
		read.push_back(first_name);
		read.push_back(last_name);
		for (int i = 0; i < read.size(); ++i)
		{
			cout >> read[i];		}


	}

};

void parse_set(string &set, int &games_won, int &games_lost) {
	int i = set.find('-');
	games_won = atoi(set.substr(0,i).c_str());
	games_lost = atoi(set.substr(i+1,set.size()-i-1).c_str());
}