#include <cassert>
#include "superhero.h"
#include "team.h"

bool isvowel(char c) {
  if (!isalpha(c)) return false;
  char c2 = tolower(c);
  return (c2 == 'a' || c2 == 'e' || c2 == 'i' || c2 == 'o' || c2 == 'u');
}

bool isconsonant(char c) {
  return (isalpha(c) && !isvowel(c));
}

std::string Team::getName() const {
  if (superheroes.size() == 0) 
    return "";
  std::string answer;
  std::list<Superhero>::const_iterator itr;
  for (itr = superheroes.begin(); itr != superheroes.end(); itr++) {
    char first_consonant = ' ';
    char first_vowel = ' ';
    std::string true_identity = itr->getTrueIdentity();
    for (int j = 0; j < true_identity.size(); j++) {
      if (first_consonant == ' ' && isconsonant(true_identity[j]))
        first_consonant = tolower(true_identity[j]);
      if (first_vowel == ' ' && isvowel(true_identity[j]))
        first_vowel = tolower(true_identity[j]);
    }
    answer.push_back(first_consonant);
    answer.push_back(first_vowel);
  }

  answer[0] = toupper(answer[0]);
  return answer;
}

void Team::operator+=(const Superhero &a) {
  superheroes.push_back(a);
}

void Team::operator-=(const Superhero &a) {
  list<Superhero>::iterator itr = superheroes.begin();
  while(itr!=superheroes.end()){
    if(*itr == a){
      superheroes.erase(itr);
      break;}
    itr++;
  }
}

const Team operator+(const Team&a, const Team &b){
  Team answer(a);
  list<Superhero>::const_iterator itr = b.superheroes.begin();
  while(itr!=b.superheroes.end()){
    answer+=*itr;
    itr++;
  }
  return answer;
}

const Team operator+(const Team&a, const Superhero &b){
  Team answer (a);
  answer += b;
  return answer;
}

const Team operator+(const Superhero &a, const Superhero &b){
  Team blah;
  blah+=a;
  blah+=b;
  return blah;
}