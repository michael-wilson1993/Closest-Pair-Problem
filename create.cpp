/*
 - Michael Wilson
 - november 7/2015
 - Data structures and algorithms
 - John Zhang
*/

#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <time.h>
using namespace std;


string int_to_string(int val);

int main()
{
	srand(time(NULL));
	int n;
	cout << "what is the n amount of elements you want?" << endl << "n = ";
	cin >> n;
	ofstream fout;
	// next four lines create the file name that will be saved.
	string filename = "output", nNumber;
	nNumber = int_to_string(n);
	filename += nNumber;
	filename += ".txt";


	int rx, ry;
	fout.open(filename);
	for (int x = 0; x < n; x++)
	{
		rx = (rand() % 1000000);
		ry = (rand() % 1000000);
		if (rand() % 2 == 1)
			rx *= -1;
		if (rand() % 2 == 1)
			ry *= -1;

		fout << rx << "," << ry << endl;
	}


}


string int_to_string(int val)
{
	string number, temp;
	// converts the number into a string - problem is its backwards
	while (val != 0)
	{
		temp += (val % 10 + 48);
		val /= 10;
	}
	// this turns the number around
	for (int x = temp.size()-1; x >= 0; x--)
	{
		number += temp.at(x);
	}
	return number;
}