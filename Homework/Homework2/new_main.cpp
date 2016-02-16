#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "new.cpp"
using namespace std;

int main(int argc, char* argv[]){

	if (argc !=3) {
		cout << "Invalid" << endl;
		return 1;
	}

	ifstream in_file(argv[1]);
	if (!in_file){
		cout << "Couldn't open." << endl;
		return 1;
	}

	ofstream out_file(argv[2]);
	if(!out_file){
		cout << "Couldn't make new file." << endl;
		return 1;
	}

	string winner;
	string loser;
	string set;
	in_file >> winner >> loser >> set;
	vector <Player> players;
	Player a_player;

	while(a_player.read(in_file, winner, loser, set)){
		players.push_back(a_player);
	}

	return 0;
}