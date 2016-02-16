#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <vector>
#include "player.h"
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

	Player player1;
	Player player2;
	vector <Player> players;
	bool matching = false;

	while(read(in_file, player1, player2)){
		for(int i = 0; i <players.size(); i++){
			if(player1.first_name == players[i].first_name){
				if(player1.last_name == players[i].last_name){
					matching = true;
				}
			}
		}
	
		if (matching == true){
			//cout << player1.first_name << endl;
			players[i].matches_won += 1;
		}

		else{
			//cout << player1.first_name << endl;
			//cout << player1.matches_won << endl;
			players.push_back(player1);
		}

		for(int i = 0; i <players.size(); i++){
			if(player2.first_name == players[i].first_name){
				if(player2.last_name == players[i].last_name){
					matching = true;
				}
			}
		}

		if (matching == true){
			//cout << player2.first_name << endl;
			//cout << player2.matches_lost << endl;
			players[i].matches_lost +=1;
		}

		else{
			//cout << player2.first_name << endl;
			//cout << player2.matches_lost << endl;
			players.push_back(player2);
			players[1].matches_lost +=1;
		}
		
	}
	//put player class in vector

	for (int i= 0; i < players.size(); i++){
		players[i].print();
	}

	return 0;
}