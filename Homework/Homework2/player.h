#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Player {

public:

	Player();
	//string GetAthleteName(){return athlete_name const};
	int matches_won;
	int matches_lost;
	int games_won;
	int games_lost;

	string first_name;
	string last_name;
	vector <int> mw;
	vector <int> ml;
	
	void print();

private:

	void parse_set(std::string &set, int &games_won, int &games_lost);
	

	//vector <int> games_won;
	//vector <int> games_lost;

};

bool read(ifstream & in_file, Player & player1, Player & player2);