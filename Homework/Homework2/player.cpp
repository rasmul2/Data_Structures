#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include "player.h"
#include <fstream>
using namespace std;


//clear matches won
Player::Player(){
	matches_won = 0;
	matches_lost = 0;
	games_won = 0;
	games_lost = 0;
}



void Player::print(){
	cout << first_name << ' ' << last_name << ' ' <<  matches_won << ' '<< matches_lost << endl;
}


bool read(ifstream & in_file, Player & player1, Player & player2, vector & players){
	string d; 
	string nf;
	string nl;
	string oponent_nf;
	string oponent_nl;
	string g1;
	string g2;
	string g3;
	string g4;
	string g5;


	if(! (in_file >> nf >> nl >> d >> oponent_nf >> oponent_nl >> g1 >> g2 >> g3 >> g4 >> g5) ){
		return false;
	}
	
	player1.first_name = nf;
	player2.first_name = oponent_nf;
	player1.last_name = nl;
	player2.last_name = oponent_nl;


	bool matching = false;
	
	for(int i = 0; i <players.size(); i++){
			if(player1.first_name == players[i].first_name){
				if(player1.last_name == players[i].last_name){
					matching = true;
				}
			}
		}
	
		if (matching == true){
			cout << player1.first_name << endl;
			player1.matches_won += 1;
		}

		else{
			cout << player1.first_name << endl;
			cout << player1.matches_won << endl;
			mw.push_back(matches_won)
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
			cout << player2.first_name << endl;
			cout << player2.matches_lost << endl;
			player2.matches_lost +=1;
		}

		else{
			cout << player2.first_name << endl;
			cout << player2.matches_lost << endl;
			players.push_back(player2);
			player2.matches_lost +=1;
		}
		
	}
	
	return true;
}

void parse_set(std::string &set, int &games_won, int &games_lost) {
	int i = set.find('-');
	games_won = atoi(set.substr(0,i).c_str());
	games_lost = atoi(set.substr(i+1,set.size()-i-1).c_str());
}