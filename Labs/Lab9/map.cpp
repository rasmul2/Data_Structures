#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
using namespace std;


int main(int argc, char const *argv[])
{
	map <int, int> mymap;

	mymap [0] = 19;
	mymap [1] = 83;
	mymap [2] = -12;
	mymap [3] = 83;
	mymap [4] = 65;
	mymap [5] = 19;
	mymap [6] = 45;
	mymap [7] = -12;
	mymap [8] = 45;
	mymap [9] = 19;
	mymap [10] = 45;

	int count = 1;
	int max = 0;
	vector<int> map_key;

	for (int i = 0; i < mymap.size(); ++i)
	{
		for (int j = i+1; j < mymap.size(); ++j)
		{
			if (mymap[i]== mymap[j])
			{
				count += 1;
			}
		}

		if (count >= max)
		{
			max = count;
			map_key.push_back(i);
		}
		count = 1;
		

	}

	cout << "The mode numbers are:" << endl;
	for (int k = 0; k < map_key.size(); ++k)
	{
		cout << mymap[map_key[k]] << ' ';
	}

	return 0;
}