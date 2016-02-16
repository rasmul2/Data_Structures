#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

#include "ds_hashset.h"
using namespace std;

class hash_string_obj {
public:

  // ----------------------------------------------------------
  // EXPERIMENT WITH THE HASH FUNCTION FOR CHECKPOINT 1, PART 2

  unsigned int operator() ( std::string const& key ) const {
    //  This implementation comes from 
    //  http://www.partow.net/programming/hashfunctions/
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++)
      hash ^= ((hash << 5) + key[i] + (hash >> 2));
    return hash;
  }   

};


typedef ds_hashset<std::string, hash_string_obj> ds_hashset_type;



int main(){
	std::unordered_set<std::string> hash_table;
	hash_table.insert("bobby");
	hash_table.insert("brett");
	hash_table.insert("zach");
	hash_table.insert("david");
	hash_table.insert("blah");
	
	for(std::unordered_set<std::string>::iterator itr = hash_table.begin();
	itr!= hash_table.end(); itr++){
		std::cout<<*itr<<std::endl;
	}
	

	ds_hashset_type a;
  	ds_hashset_type set1;
  	std::pair< ds_hashset_type::iterator, bool > insert_result;

	ifstream filename;
	string word;
	filename.open("hansel_and_gretel.txt");
	while(!filename.eof()) {
		filename >> word;
		set1.insert(string(word));
	}
	
	set1.print(cout);

	ds_hashset_type::iterator p = set1.begin();
	ds_hashset_type::iterator q = set1.begin();
	unordered_map <string, int> word_n;
	for ( p = set1.begin(); p != set1.end(); ++p){
		int count = 0;
		for (q = set1.begin(); q!= set1.end(); q++){
			if(*p ==*q){
				count +=1;
			}
			
		}
		word_n[*p] = count;
		
	}

	for(unordered_map<string, int>:: iterator m = word_n.begin(); m != word_n.end(); m++){
		cout << m->first << ' '<< m->second << endl;
	}

 
	
	
	return 0;
}