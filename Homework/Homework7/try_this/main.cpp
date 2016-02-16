// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;



// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef map <string , map< string, map <string, int> > >  MY_MAP;

// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
	// break words at whitespace
	return true;
      }
    } else if (c == '"') {
      // double quotes are a delimiter and a special "word"
      if (word == "") {
	istr.get(c);
	word.push_back(c);
      }
      return true;
    } else if (isalpha(c)) {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}



// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP &data, const std::string &filename, int window, const std::string &parse_method) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }


  //
  // ASSIGNMENT:SETUP YOUR MAP DATA AS NEEDED
  //
  string word;
  string prev_word;
  string prev_prev_word;
  
  

  while (ReadNextWord(istr,word)) {
    // skip the quotation marks (not used for this part)
    if (word == "\"") continue;

    //
    // ASSIGNMENT: PROCESS ALL THE NON PUNCTUATION WORDS
    // INSERTING THESE WORDS INTO THE DATA STRUCTURE
    //
    else{
          //cout << word;
          //cout << prev_prev_word << ' ' << prev_word << ' ' << word << endl;
          data[prev_prev_word][prev_word][word]+=1;
          //cout << data[prev_prev_word][prev_word][word] << ' ';
          //cout << data[prev_word] [word] << ' ';
          prev_prev_word = prev_word;
          prev_word = word;
            
        }
  }



    return;

}



int main () {

  // ASSIGNMENT: THE MAIN DATA STRUCTURE
  MY_MAP data;

  // Parse each command
  std::string command;    
  while (std::cin >> command) {

    // load the sample text file
    if (command == "load") {
      std::string filename;
      int window;
      std::string parse_method;
      std::cin >> filename >> window >> parse_method;      

      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      //
      LoadSampleText(data, filename, window, parse_method);

    } 

    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);


      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      //

    
      for (MY_MAP::iterator i = data.begin(); i !=data.end(); ++i)
      {
        if (i->first == sentence[0])
        {
          if (sentence.size() == 1)
          {
            cout << i->first << ' ' << '(' << data[sentence[0]].size() << ')' << endl;
          }
          for (map<string, map <string, int> >::iterator k = data[sentence[0]].begin(); k != data[sentence[0]].end(); ++k)
          {
            if (sentence.size() ==1)
            {
              cout << i-> first << ' ' << k-> first << ' ' << '(' << data[sentence[0]][k->first].size() << ')' << endl;
            }
          }


          if (sentence.size() == 2)
          {
            for (map<string, map <string, int> >::iterator k = data[sentence[0]].begin(); k != data[sentence[0]].end(); ++k)
            {
              if (k->first == sentence[1])
              {
                cout << i->first << ' ' << k->first << ' ' << 
                '(' << data[sentence[0]][sentence[1]].size() << ')'<< endl;
                for (map <string, int>::iterator h = data[sentence[0]][sentence[1]].begin(); h != data[sentence[0]][sentence[1]].end(); ++h)
                {
                  cout << i-> first << ' ' << k-> first << ' ' <<
                  h->first << ' ' << '(' << h->second << ')' << endl;
                }
                
              }
            }
            
          }
        }

      }
      
      
    }


    // generate the specified number of words 
    else if (command == "generate") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      // how many additional words to generate
      int length;
      std::cin >> length;
      std::string selection_method;
      std::cin >> selection_method;
      bool random_flag;
      if (selection_method == "random") {
	random_flag = true;
      } else {
	assert (selection_method == "most_common");
	random_flag = false;
      }


      
      //ASSIGNMENT: ADD YOUR COMMANDS HERE
      
      if (random_flag == false)
      {
        if (sentence.size() == 1)
        {
          for (int j = 0; j < sentence.size(); ++j)
          { 
            for (MY_MAP::iterator i = data.begin(); i !=data.end();++i)
            {
              if (i->first == sentence[0])
              {
                string x = i->first;
                while(length >= 0)
                {
                  for (MY_MAP::iterator l = data.begin(); l !=data.end();++l)
                  {
                    if (l->first == x)
                    {
                      cout << x << ' ';
                      string largest;
                      int max = 0;
                      for (map<string, map<string, int> >::iterator k = data[x].begin(); k != data[x].end(); ++k)
                      {
                        if (data[x][k->first].size() > max)
                        {
                          max = data[x][k->first].size();
                          largest = k->first;
                        }
                      }

                      x = largest;
                      length --;
                  }
                }
              }
              cout << endl;
            }
          }
        }
      }
    }
          

        if (random_flag == true)
      {
        if (sentence.size() ==1)
        {
          for (int j = 0; j < sentence.size(); ++j)
          { 
            for (MY_MAP::iterator i = data.begin(); i !=data.end();++i)
            {
              if (i->first == sentence[j])
              {
                string x = i->first;
                while(length >= 0)
                {
                  for (MY_MAP::iterator l = data.begin(); l !=data.end();++l)
                  {
                    if (l->first == x)
                    {
                      cout << x << ' ';
                      string chosen;
                      std::vector<string> choices;
                      for (map<string, map<string, int> >::iterator k = data[x].begin(); k != data[x].end(); ++k)
                      {
                        int r = data[x][k->first].size();
                        while(r >= 0)
                        {
                          choices.push_back(k->first);
                          r--;
                        }
                      }
                      int n = rand()% choices.size();
                      random_shuffle(choices.begin(), choices.end());
                      //quitcout << choices[n] << endl;
                      x = choices[n];
                      length --;
                  }
                }
              }
              cout << endl;
            }
          }
        }
      }
        }
          


    } else if (command == "quit") {
      break;
    } else {
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}
