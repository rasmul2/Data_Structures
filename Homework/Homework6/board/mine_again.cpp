#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

#include "MersenneTwister.h"

#include "tile.h"
#include "location.h"
#include "board.h"
#include "mine.h"

// void CheckSides(Board board, int i, int j, const vector <Tile*> tiles, 
// 	int t, vector<Location> & locations){
// 	int s = t;
// 	s++;//first increment s off from t
// 	locations.push_back(Location(i,j,0));//pushback first or previous pass
// 	board.setTile(i,j, tiles[t]);//set first or previous pass

// 	while(s < tiles.size())//to go through each tile one after the other, can't chnage order
// 	{
// 			cout << t << endl;
// 			cout << s << endl;
// 			cout << i << ',' << j << endl;
// 			//check north and south first
// 			if (tiles[t]->getNorth() == tiles[s]->getSouth() &&
// 				i -1 >= 0 && i < board.numRows() && //order of i check before getTile is important for no seg fault
// 				board.getTile(i-1, j) == NULL &&
// 				j -1 >= 0 &&  j+1 < board.numColumns()){
// 				if(board.getTile(i-1, j-1) == NULL || 
// 					board.getTile(i-1, j-1)->getEast() == tiles[s]->getWest() &&
// 					board.getTile(i-1, j+1) == NULL || 
// 					board.getTile(i-1, j+1)->getWest() == tiles[s]->getEast()){
// 						i--;
// 						CheckSides(board, i, j, tiles, s, locations);
// 				}
				
// 			 } 
// 			 //cout << "Here" << endl;
// 			 if (tiles[t]->getSouth() == tiles[s]->getNorth() &&
// 				i +1 < board.numRows() && i >= 0 && 
// 				board.getTile(i+1, j) == NULL &&
// 				j -1 >= 0 &&  j+1 < board.numColumns()){
// 				if(board.getTile(i+1, j-1) == NULL || 
// 					board.getTile(i+1, j-1)->getEast() == tiles[s]->getWest() &&
// 					board.getTile(i+1, j+1) == NULL || 
// 					board.getTile(i+1, j+1)->getWest() == tiles[s]->getEast()){
// 						i++;
// 						CheckSides(board, i, j, tiles, s, locations);
// 				}
				
// 			 }

// 			if (tiles[t]->getEast() == tiles[s]->getWest() &&
// 				j +1 <board.numColumns() && j >= 0 && 
// 				board.getTile(i, j+1) == NULL &&
// 				i-1 >= 0 &&  i+1 < board.numRows()){
// 				if(board.getTile(i-1, j+1) == NULL || 
// 					board.getTile(i-1, j+1)->getSouth() == tiles[s]->getNorth() &&
// 					board.getTile(i+1, j+1) == NULL || 
// 					board.getTile(i+1, j+1)->getNorth() == tiles[s]->getSouth()){
// 						j++;
// 						CheckSides(board, i, j, tiles, s, locations);
// 				}
				
// 			 } 

// 			if (tiles[t]->getWest() == tiles[s]->getEast() &&
// 				j -1 >= 0 &&  j < board.numColumns() && 
// 				board.getTile(i, j-1) == NULL &&
// 				i-1 >= 0 &&  i+1 < board.numRows()){
// 				if(board.getTile(i-1, j-1) == NULL || 
// 					board.getTile(i-1, j-1)->getSouth() == tiles[s]->getNorth() &&
// 					board.getTile(i+1, j-1) == NULL || 
// 					board.getTile(i+1, j-1)->getNorth() == tiles[s]->getSouth()){
// 						j--;
// 						CheckSides(board, i, j, tiles, s, locations);
// 				}
// 			}


// 	}
// }