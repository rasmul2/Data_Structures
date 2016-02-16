#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <cassert>

#include "MersenneTwister.h"

#include "tile.h"
#include "location.h"
#include "board.h"
#include "mine.h"


// this global variable is set in main.cpp and is adjustable from the command line
// (you are not allowed to make your own global variables)
int GLOBAL_TILE_SIZE = 11;


// ==========================================================================
// Helper function that is called when an error in the command line
// arguments is detected.
void usage(int argc, char *argv[]) {
  std::cerr << "USAGE: " << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -board_dimensions <h> <w>" << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -board_dimensions <h> <w>  -all_solutions" << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -board_dimensions <h> <w>  -allow_rotations" << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -all_solutions  -allow_rotations" << std::endl;
  std::cerr << "  " << argv[0] << " <filename>  -tile_size <odd # >= 11>" << std::endl;
  exit(1);
}



// ==========================================================================
// To get you started, this function places tiles on the board and
// randomly and outputs the results (in all likelihood *not* a
// solution!) in the required format
void RandomlyPlaceTiles(Board &board, const std::vector<Tile*> &tiles, std::vector<Location> &locations) {

  // MersenneTwister is an excellent library for psuedo-random numbers!
  MTRand mtrand;

  for (int t = 0; t < tiles.size(); t++) {
    // loop generates random locations until we (eventually) find one
    // that is not occupied
    int i,j;
    do {
      // generate a random coordinate within the range 0,0 -> rows-1,cols-1
      i = mtrand.randInt(board.numRows()-1);
      j = mtrand.randInt(board.numColumns()-1);
    } while (board.getTile(i,j) != NULL);

    // rotation is always 0 (for now)
    locations.push_back(Location(i,j,0));
    board.setTile(i,j,tiles[t]);
  }
}


// ==========================================================================
void HandleCommandLineArguments(int argc, char *argv[], std::string &filename, 
                                int &rows, int &columns, bool &all_solutions, bool &allow_rotations) {

  // must at least put the filename on the command line
  if (argc < 2) {
    usage(argc,argv);
  }
  filename = argv[1];

  // parse the optional arguments
  for (int i = 2; i < argc; i++) {
    if (argv[i] == std::string("-tile_size")) {
      i++;
      assert (i < argc);
      GLOBAL_TILE_SIZE = atoi(argv[i]);
      if (GLOBAL_TILE_SIZE < 11 || GLOBAL_TILE_SIZE % 2 == 0) {
        std::cerr << "ERROR: bad tile_size" << std::endl;
        usage(argc,argv);
      }
    } else if (argv[i] == std::string("-all_solutions")) {
      all_solutions = true;
    } else if (argv[i] == std::string("-board_dimensions")) {
      i++;
      assert (i < argc);
      rows = atoi(argv[i]);
      i++;
      assert (i < argc);
      columns = atoi(argv[i]);
      if (rows < 1 || columns < 1) {
        usage(argc,argv);
      }
    } else if (argv[i] == std::string("-allow_rotations")) {
      allow_rotations = true;
    } else {
      std::cerr << "ERROR: unknown argument '" << argv[i] << "'" << std::endl;
      usage(argc,argv);
    }
  }
}


// ==========================================================================
void ParseInputFile(int argc, char *argv[], const std::string &filename, std::vector<Tile*> &tiles) {

  // open the file
  std::ifstream istr(filename.c_str());
  if (!istr) {
    std::cerr << "ERROR: cannot open file '" << filename << "'" << std::endl;
    usage(argc,argv);
  }
  assert (istr);

  // read each line of the file
  std::string token, north, east, south, west;
  while (istr >> token >> north >> east >> south >> west) {
    assert (token == "tile");
    Tile *t = new Tile(north,east,south,west);
    tiles.push_back(t);
  }
}


// ==========================================================================
int main(int argc, char *argv[]) {

  std::string filename;
  int rows = -1;
  int columns = -1;
  bool all_solutions = false;
  bool allow_rotations = false;
  HandleCommandLineArguments(argc, argv, filename, rows, columns, all_solutions, allow_rotations);


  // load in the tiles
  std::vector<Tile*> tiles;
  ParseInputFile(argc,argv,filename,tiles);


  // confirm the specified board is large enough
  if (rows < 1  ||  columns < 1  ||  rows * columns < tiles.size()) {
    std::cerr << "ERROR: specified board is not large enough" << rows << "X" << columns << "=" << rows*columns << " " << tiles.size() << std::endl;
    usage(argc,argv);
  }


  //for (int i = 0; i < 5; i++) {

    // generate a random tile layouts
    Board board(rows,columns);
    std::vector<Location> locations;
    //RandomlyPlaceTiles(board, tiles, locations);
    PrintPieces(board, tiles, locations, all_solutions, allow_rotations);
    
    // print the solution
    //std::cout << "probably-not-a-Solution: ";
    // for (int i = 0; i < locations.size(); i++) {
    //   std::cout << locations[i];
    // }
    // std::cout << std::endl;

    // print the ASCII art board representation
    //board.Print();
    //std::cout << std::endl;
  //}

  
  // delete the tiles
  for (int t = 0; t < tiles.size(); t++) {
    delete tiles[t];
  }
}
// ==========================================================================
