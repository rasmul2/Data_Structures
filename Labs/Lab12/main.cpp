#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>





int main(){
	std::unordered_set<std::string> hash_table;
	hash_table.insert("bobby");
	hash_table.insert("brett");
	hash_table.insert("zach");
	hash_table.insert("david");
	hash_table.insert("blah");
	
	for(std::unordered_set<std::string>::iterator itr = hash_table.begin();
	itr!= hash_table.end(); itr++)
		std::cout<<*itr<<std::endl;

	unordered_map <string> hash_table;
	string filename = "hansel_and_gretel.txt";
	std::ifstream istr(filename.c_str());
	ds_hashset_type a;
  	ds_hashset_type set1;
  	std::pair< ds_hashset_type::iterator, bool > insert_result;
	while(istr){
		set1.insert(string(istr));
	}
 
	
	
	return 0;
}