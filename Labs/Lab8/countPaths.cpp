#include <iostream>
#include <cmath>
using namespace std;

int countPaths(int x, int y){
	int count = 0;

	if(x>= 0){
		if(x== 0 && y == 0){
			count += 1;
		}
		if( y >= 0){
			count += countPaths(x, y-1);
		}
		count += countPaths(x-1, y);
	}
	return count;

}



int main(int argc, char const *argv[])
{
	int answer; 
	answer = countPaths(2,2);
	cout << answer << endl;
	int answer2;
	answer2 = countPaths(1,2);
	cout << answer2 << endl;
	return 0;
}

