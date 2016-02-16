#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <cassert>
#include <sstream>
using namespace std;

#include "MersenneTwister.h"

#include "tile.h"
#include "location.h"
#include "board.h"
#include "mine.h"


// void CheckSides(Board board, int i, int j, const vector <Tile*> tiles, 
// 	int t, vector<Location> locations, int s, int c, vector<Board> & boards, vector<string> & v){
// 	s++;//first increment s off from t


// 	if (i >=0 && i < board.numRows() && j >= 0 && j < board.numColumns() && board.getTile(i, j) == NULL)
// 	{
// 		//pushback first or previous pass
// 		c++;
// 		board.setTile(i,j, tiles[t]);//set first or previous pass
// 	}

// 	if (locations.size() == 0)
// 	{
// 		locations.push_back(Location(i,j,0)); // for the first location
// 	}

// 	if (locations.size() != 1)
// 	{
// 		if (t == 0)
// 		{
// 			locations.pop_back();
// 		}
// 	}
	
	
// 	if (c == tiles.size() && locations.size() == tiles.size())
// 	{
// 		cout << "Solution: ";
// 		string x = "Solution: ";
// 		for (int k = 0; k < locations.size(); ++k)
// 		{
// 			cout << locations[k];
// 			ostringstream points;
// 			points << locations[k];
// 			x+= points.str();
// 		}
// 		v.push_back(x);
// 		cout << endl;
// 		boards.push_back(board);
// 		board.Print();
// 		c = 0;
// 	}
// 	//cout<< i <<','<< j << endl;
// 	//board.Print();

// 	if (locations.size() == tiles.size())
// 	{
// 		//cout << "cleared" << endl;
// 		locations.clear();
// 	}

		
// 	if(s < tiles.size())//to go through each tile one after the other, can't chnage order
// 	{
// 			//cout << t << endl;
// 			//cout << s << endl;
// 			//cout << i << ',' << j << endl;
// 			//check north and south first
// 			if (tiles[t]->getNorth() == tiles[s]->getSouth() && i -1 >= 0){
// 						i--;
// 						locations.push_back(Location(i,j,0));
// 						CheckSides(board, i, j, tiles, s, locations, s, c, boards, v);
				
// 			 } 
// 			 //cout << "Here" << endl;
// 			 if (tiles[t]->getSouth() == tiles[s]->getNorth() && i+1 < board.numRows()){
// 						i++;
// 						locations.push_back(Location(i,j,0));
// 						CheckSides(board, i, j, tiles, s, locations, s, c, boards, v);
				
// 			 }

// 			if (tiles[t]->getEast() == tiles[s]->getWest() && j+1 > board.numColumns()){
// 						j++;
// 						locations.push_back(Location(i,j,0));
// 						CheckSides(board, i, j, tiles, s, locations, s, c, boards, v);
				
// 			 } 

// 			if (tiles[t]->getWest() == tiles[s]->getEast() && j-1 >= 0){
// 						j--;
// 						locations.push_back(Location(i,j,0));
// 						CheckSides(board, i, j, tiles, s, locations, s, c, boards, v);
// 			}

// 			//cout << "here" << endl;
			
// 			if (t > 0)//if it doesn't pass through for anything go to the previous tile
// 			{
// 				//locations.push_back(Location(i,j,0));
// 				i = locations[t-1].getX();
// 				j = locations[t-1].getY();
// 				CheckSides(board, i, j, tiles, t-1, locations, s-1, c, boards, v);// s-1 to offset incrementation so s doesn't move			
// 			}
// 	}

// 	//return v;
// }

string CheckSides(Board board, const int & p, const int & l, const vector <Tile*> tiles, 
 	int t, vector<Location> locations, int s, vector<Board> & boards){
	s++;
	string x ="";
	int i = p;
	int j = l;
	//cout<< i << ' ' << j << endl;
	if (i >=0 && i < board.numRows() && j >= 0 
			&& j < board.numColumns() && board.getTile(i, j) == NULL){
			locations.push_back(Location(i,j, 0));
			board.setTile(i,j, tiles[t]);//set first or previous pass
		}

	
	//cout << "second spot" << endl;
	// cout<< t << 't' << endl;
	// cout << s << 's' << endl;


	if(s < tiles.size())//to go through each tile one after the other, can't chnage order
	{
			//cout << t << endl;
			//cout << s << endl;
			//cout << i << ',' << j << endl;
			//check north and south first
			if (tiles[t]->getNorth() == tiles[s]->getSouth() && i -1 >= 0){
				i--;
				if (i >=0 && i < board.numRows() && j >= 0 
					&& j < board.numColumns() && board.getTile(i, j) == NULL){
						x+=CheckSides(board, i, j, tiles, s, locations, s, boards);
				}
				
			 } 
			 //cout << "Here" << endl;
			 if (tiles[t]->getSouth() == tiles[s]->getNorth() && i+1 < board.numRows()){
				i++;
				if (i >=0 && i < board.numRows() && j >= 0 
				&& j < board.numColumns() && board.getTile(i, j) == NULL){
						x+=CheckSides(board, i, j, tiles, s, locations, s, boards);
				}
			 }

			if (tiles[t]->getEast() == tiles[s]->getWest() && j+1 < board.numColumns()){
				j++;
				if (i >=0 && i < board.numRows() && j >= 0 
				&& j < board.numColumns() && board.getTile(i, j) == NULL){
						x+=CheckSides(board, i, j, tiles, s, locations, s, boards);
				}
			 } 

			if (tiles[t]->getWest() == tiles[s]->getEast() && j-1 >= 0){
				j--;
				if (i >=0 && i < board.numRows() && j >= 0 
				&& j < board.numColumns() && board.getTile(i, j) == NULL){
						x+= CheckSides(board, i, j, tiles, s, locations, s, boards);
				}
			}
			//cout << "here" << endl;
			if (t > 0)//if it doesn't pass through for anything go to the previous tile
			{
				//locations.push_back(Location(i,j,0));
				//cout << t << endl;
				//cout << "did it" << endl;
				i = locations[locations.size()-1].getX();
				j = locations[locations.size()-1].getY(); 
				//cout << i << ' ' << j << endl;
				
				// if (i >=0 && i < board.numRows() && j >= 0 
				// && j < board.numColumns() && board.getTile(i, j) == NULL){
				//cout << i << ' ' << j << endl;
				x += CheckSides(board, i, j, tiles, t-1, locations, s-1, boards);
			}
		
	}

	else {
				if (locations.size() == tiles.size())
				{
					x = "Solution: ";
					int m = 0;
					while (m < locations.size())
					{
						//cout << locations[m];
						ostringstream points;
			 			points << locations[m];
						x+= points.str();
						m++;
					}
					//cout << x << endl;
					//board.Print();
					boards.push_back(board);
					//cout << endl;
					//board.Print();
				}
				// s-1 to offset incrementation so s doesn't move			
				//}
		}


	return x;
}


void PrintPieces(Board board, const std::vector<Tile*> &tiles, std::vector<Location> &locations, 
	bool & all_solutions, bool & allow_rotations){
	int t = 0; // to start first tile 
	int s = 0;
	int c = 0;
	string temp;
	vector<string> v;
	//cout << "start" << endl;
	vector<Board> boards;
	for (int i = 0; i < board.numRows(); ++i)
  	{
	  	for (int j = 0; j < board.numColumns(); ++j)
	  	{
	  		//cout << i << ',' << j << endl;
	    	temp = CheckSides(board, i, j, tiles, t, locations, s, boards);
	    	temp = temp.substr(0, 10 + 7*tiles.size());
			if (temp != "")
			{
				v.push_back(temp);
			}

	  	}
  	}
 //  	cout << "seggy fault" << endl;
 //  	//get rid of double solutions
 //  	for (int n = 0; n < v.size(); ++n)
	// {
	// 	for (int m = n+1; m < v.size(); ++m)
	// 	{
	// 		if (v[n]== v[m])
	// 		{
	// 			v.erase(v.begin()+n);
	// 			boards.erase(boards.begin()+n);
	// 		}
	// 	}
		
	// }
	//cout << "seggy fault" << endl;
	//cout << v.size() << endl;
  	
  	if (all_solutions)
  	{
  		if (v.size() == 0)
	  	{
	  		cout << "No Solution." << endl;
	  	}
	  	
	  	if (v.size() > 0)
	  	{
		  	for (int k = 0; k < v.size() ; ++k)
			{
				cout << v[k];
				cout << endl;
				boards[k].Print();
			}
			cout << endl;
			cout << "Found " << v.size() << " Solutions(s)." << endl;
	  	}
  	}

  	if (!all_solutions)
  	{
  		if (v.size() == 0)
	  	{
	  		cout << "No Solution." << endl;
	  	}
	  	//cout << "seggy fault" << endl;
	  	if (v.size() > 0)
	  	{

			cout<< v[0] << endl;
			cout << endl;			
			boards[0].Print();
			cout << endl;
			cout << "Found 1" << " Solutions(s)." << endl;
	  	}
  	}
	
}



