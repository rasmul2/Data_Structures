#include <iostream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <vector>
#include "tennis.h"
using namespace std;

bool Match::read(istream & in_file){

	string d; 
	string m1;
	string m2;
	string m3;
	string m4;
	string m5;

	vector <string> file;
	
	while(in_file >> p1f >> p1l >> d >> p2f >> p2l 
			>> m1 >> m2 >> m3 >> m4 >> m5 ){
		vector <string> sets;

		cout << p1f << p1l << endl;
		cout << p2f << p2l << endl;
		sets.push_back(m1);
		sets.push_back(m2);
		sets.push_back(m3);
		sets.push_back(m4);
		sets.push_back(m5);

		int p1_mw  = 0;
		int p1_ml = 0;
		int p2_mw = 0;
		int p2_ml = 0;

		int j= 0;
		while(j < sets.size()){
			for (int i = 0; i < 2; i++){
				
			 	i = sets[j].find('-');
				int p1_s = atoi(sets[j].substr(0,i).c_str());
				int p2_s = atoi(sets[j].substr(i+1,sets[j].size()-i-1).c_str());
				cout << p1_s << ' ' << p2_s << endl;
				cout << endl;

				if(p1_s > p2_s){
					p1_mw +=1;
					p2_ml +=1;
				}

				else{
					p2_mw +=1;
					p1_ml += 1;
				}


				j+=1;
			 }

		}
		
		cout << p1_mw << ' ' << p1_ml << endl;
		cout << p2_mw << ' ' << p2_ml << endl;
		cout << endl;


	}

}