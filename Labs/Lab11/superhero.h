#ifndef _SUPERHERO_H_
#define _SUPERHERO_H_

#include <string>
#include <iostream>
#include <list>
#include <ostream>
using namespace std;

class Superhero {
public:
	Superhero(){
		good = true;
		first_name = "";
		power = "";
		superhero_name = "";
	}

	Superhero (const string & identity, const string& f_name, const string& powowo){
		first_name = f_name;
		power = powowo;
		superhero_name = identity;
	}
	
	bool operator ==(const string& a) const{
		return first_name == a;
	}
	bool operator ==(const Superhero& a) const{
		return a.superhero_name == superhero_name;
	}
	bool operator !=(const string& a) const{
		return !(first_name ==a);
	}

	void operator-() {
		if (good)
			good = false;
		else
			good = true; }

	bool operator>(const Superhero& hero){
		if(power == "Fire"){
			if(hero.power == "Wood")
				return true; }
		else if(power == "Wood"){
			if(hero.power == "Water")
				return true; }
		else if(power == "Water"){
			if(hero.power == "Fire")
				return true; }
		else if(power == "Flexible"){
			if(hero.power == "Laser")
				return true; }
		else if(power == "Laser"){
			if(hero.power == "Flying")
				return true; }
		else
			return false;
	}

	friend ostream& operator <<(ostream & ostr, const Superhero & a) {
		if(a.isGood()){
			ostr << "Superhero " << a.superhero_name << " has super power " << a.power << endl;
		}
		else{
			ostr << "Supervillian "<< a.superhero_name<<" has super power "<< a.power<<std::endl;
		return ostr;
		}
		
		return ostr;
	}

	string getName() const {return superhero_name;}
	string getTrueIdentity() const {return first_name;}
	string getPower() const {return power;}
	const bool isGood() const {return good;}

private:

	string first_name;
	string power;
	string superhero_name;
	bool good;

};




#endif