#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include <utility>
#include <stdlib.h>
#include <algorithm> 
#include <time.h>
using namespace std;


	// graph is the container we pass around!
struct graph
{
	void push(int xins, int yins)
	{
		p.push_back(make_pair(xins, yins));
	}
	bool pairCompare(int i, int j)
	{
		return p[i].first < p[j].first;
	}
	pair < int, int > p1;
	pair < int, int > p2;
	float distance;
	float time;

	vector < pair < int, int > > p;
};

	// this will load the graph with the coordinates 
void loadVector(graph &pass, string name);
	// tests brute force version of closest pair problem.
float BruteForce(graph &g, int i, int j);
	// devide and counqour version for closest pair
float divideAndConqour( graph &g, int i, int j);
	// converts the string to an integer
int stringToInt(string pass, bool neg = false);
	// converts the int to a string
string intToString(int pass);

void sorter(graph &g);




int main()
{
	double duration;
	clock_t start;
	graph g;
	g.distance = 800000001;
	g.p1.first = 0;
	g.p1.second = 0;
	g.p2.first = 0;
	g.p2.second = 0;

	
	loadVector(g, "create/output40000.txt");
	sort(g.p.begin(), g.p.end());


	//for(int x = 0; x < g.p.size(); x++)
	//	cout << g.p[x].first << " " << g.p[x].second << endl;
	//sorter(g);
	//for(int x = 0; x < g.p.size();x++)
	//	cout << g.p[x].first << " " << g.p[x].second << endl;
	start = clock();
	BruteForce(g, 0 , g.p.size()-1);
	duration = (clock() - start) / (double)(CLOCKS_PER_SEC / 1000);

	cout << endl << "time : " << duration << endl 
	<< "p1 = " << g.p1.first << " , " << g.p1.second << endl  << "p2 = "<< g.p2.first << " , " << g.p2.second << endl 
	<< "distance = " << g.distance << endl;


	g.distance = 800000001;
	g.p1.first = 0;
	g.p1.second = 0;
	g.p2.first = 0;
	g.p2.second = 0;


	// divide and counqour

	start = clock();
	
	divideAndConqour(g, 0, g.p.size()-1);
	duration = (clock() - start) / (double)(CLOCKS_PER_SEC / 1000);
	
	cout << endl << "time : " << duration << endl 
	<< "p1 = " << g.p1.first << " , " << g.p1.second << endl  << "p2 = "<< g.p2.first << " , " << g.p2.second << endl 
	<< "distance = " << g.distance << endl;
	
	return 0;
}


string intToString(int pass)
{
	string number, temp;
		// converts the number into a string - problem is its backwards
	while (pass != 0)
	{
		temp += (pass % 10 + 48);
		pass /= 10;
	}
		// this turns the number around
	for (int x = temp.size()-1; x >= 0; x--)
	{
		number += temp.at(x);
	}
	return number;
}


int stringToInt(string pass, bool neg)
{
	int ret = 0; // return value
	for(int x = 0; x < pass.size(); x++)
	{
		ret *= 10;
		ret += pass.at(x) - 48;
	}
	if(neg)
	{
		ret *= -1;
	}
	return ret;
}

void loadVector(graph &pass, string name)
{
	ifstream fin;
	fin.open(name.c_str());
	string temp;
	string xx,yy;
	int size = 0;
	bool first = true, xflag = false, yflag = false;
	if(name.size() != 0)
	{
		while(!fin.eof())
		{
			temp = "";
			fin >> temp;
			if(temp.size()!= 0)
			{
				first = true;
				xx=""; 
				yy="";
				size = temp.size();
				for (int x = 0; x < size; ++x)
				{
					if(temp.at(x) == ',')
					{
						first = false;
					}
					if(temp.at(x) == '-')
					{
						if(first)
						{
							xflag = true;
						}
						else
						{
							yflag = true;
						}	
					}	
					if(temp.at(x)-48 > -1 && temp.at(x)-48 < 10) // checks if it is a number
					{
						if(first)
						{
							xx += temp.at(x);
						}
						else
						{
							yy += temp.at(x);
						}
					}
				}
				//cout << xx << " " << yy << endl;

				pass.push(stringToInt(xx,xflag), stringToInt(yy,yflag));
				xflag = false;
				yflag = false;

			}
		}
	}
	else 
		cout << endl << "file contains nothing!" << endl;
}

float BruteForce(graph &g, int i, int j)
{
	if(i < 0)
		i = 0;
	if(j > g.p.size()-1)
		j = g.p.size();

	long int xdis, ydis , dist;
	for(int x = i; x <= j;x++)
	{
		for(int y = x+1; y <= j; y++)
		{

   			//cout << g.p[x].first << "-" << g.p[y].first << endl << g.p[x].second << "-" << g.p[y].second << endl << endl;
			xdis = g.p[x].first - g.p[y].first;
			ydis = g.p[x].second - g.p[y].second;
			dist =  (xdis*xdis) + (ydis*ydis);
   			if(sqrt(dist) < g.distance) //(p1x-p2x) + (p1y-p2y)
   			{
   				g.distance = sqrt(dist);
   				g.p1.first = g.p[x].first;
   				g.p1.second = g.p[x].second;
   				g.p2.first = g.p[y].first;
   				g.p2.second = g.p[y].second;
   			}
   		}
   		//cout << g.distance << endl;
   		
   	}
   	return g.distance;
}


float divideAndConqour(graph &g, int i, int j)
{

    // If there are 2 or 3 points, then use brute force
    if (j-i <= 3)
        return BruteForce(g, i,j);
 
    // Find the middle point
    int mid = ((j-i)/2)+i;
    pair< int , int > midPoint = g.p[mid];
 
    // Consider the vertical line passing through the middle point
    // calculate the smallest distance dl on left of middle point and
    // dr on right side
    float dl = divideAndConqour(g, i, mid);
    float dr = divideAndConqour(g, mid+1, j);
 
    // Find the smaller of two distances
    float d = min(dl, dr);

 	//cout << d << endl;
    // Build an array strip[] that contains points close (closer than d)
    // to the line passing through the middle point
    graph shortPoints;
    int high = midPoint.first + (d) , low = midPoint.first - (d);
    int II, JJ;
    for(int x = i; x < j; x++)
    {
	    if(g.p[x].first >= low)
	    {
	    	II = i;
	    }
	    if(g.p[x].first <= high)
	    {

	    	JJ = i;
    	}
   		//shortPoints.push(g.p[x].first, g.p[x].second);	
    }
    //cout << d << endl;
    //cout << low << " " << high << endl;
    //sort shortGraph by Y coord
    /*
	    if(g.p[x].first >= low && g.p[x].first <= high)
    		shortPoints.push(g.p[x].first, g.p[x].second);
    */
    // Find the closest points in strip.  Return the minimum of d and closest
    // distance is strip[]
    return min(d, BruteForce(g, II, JJ) );
}
 




	/*
	float divideAndConqour(graph &g, int i, int j)
{
	float one, two;
	long int xdis, ydis , dist;
	//cout << "hi";
	if(i >= j)
	{

		return -1;
   	}
   	if((i+1) == j)
   	{
   		//cout << i << "," << j << endl;
   		xdis = g.p[i].first - g.p[j].first;
   		ydis = g.p[i].second - g.p[j].second;
   		dist =  (xdis*xdis) + (ydis*ydis);
   		if(sqrt(dist) < g.distance) //(p1x-p2x) + (p1y-p2y)
   		{
   			g.distance = sqrt(dist);
   			g.p1.first = g.p[i].first;
   			g.p1.second = g.p[i].second;
   			g.p2.first = g.p[j].first;
   			g.p2.second = g.p[j].second;
   		}
   		return sqrt(dist);
   	}
   	

   	int mid = ((j - i)/2);

   	mid+=i;

   	int iterator = mid, iteratorUp = mid;
   	


   	one = divideAndConqour(g,  i, mid);
   	two = divideAndConqour(g, mid+1, j); 

   	bool LorR = true; 
   	int shortest=0;

   	if(one == -1 || two == -1)
   	{

   	}



   	if(two < one)
   		shortest = two;
   	else if(one < two)
   		shortest = one;
   	cout << shortest << endl;
   	shortest /= 2;
   	int midDownTemp = g.p[mid].first - shortest;
   	int midUpTemp = g.p[mid].first + shortest;
   	bool flag = true;
   	
   	while(g.p[iterator-1].first >= midDownTemp)
   	{
   		iterator--;
   	}
   	while(g.p[iteratorUp+1].first <= midUpTemp)
   	{
   		iteratorUp++;
   	}



   	for(int x = midDownTemp; x < midUpTemp; x++)
   	{
   		for(int y = x+1; y < midUpTemp; y++)
   		{

   			xdis = g.p[x].first - g.p[y].first;
   			ydis = g.p[x].second - g.p[y].second;
   			dist =  (xdis*xdis) + (ydis*ydis);
   			if(sqrt(dist) < g.distance) //(p1x-p2x) + (p1y-p2y)
   			{
   				g.distance = sqrt(dist);
   				g.p1.first = g.p[x].first;
   				g.p1.second = g.p[x].second;
   				g.p2.first = g.p[y].first;
   				g.p2.second = g.p[y].second;
   			}


   		}
   	}

   	return g.distance;
}
*/

void sorter(graph &g)
{
	bool sorted = false;
	int it = 0; 
	while (!sorted)
	{
		sorted = true;
		for(int x = 0; x < g.p.size()-1; x++)
		{
			if(g.p[x].first > g.p[x+1].first)
				sorted = false;
		}

		for(int x = it+1 ; x < g.p.size();x++)
		{
			if(g.p[it].first > g.p[x].first)
			{
				int temp = g.p[x].first;
				g.p[x].first = g.p[it].first;
				g.p[it].first = temp;

				int temp1 = g.p[x].second;
				g.p[x].second = g.p[it].second;
				g.p[it].second = temp1;
			}
		}
		it++;
	}
}

/*

	
	while(iterator - 1 >= i && g.p[iterator - 1].first == g.p[mid].first)//&& iterator != i)
	{
		iterator--;
	}


	int k, condition = g.p[mid].first;
	k = iterator+1;
	bool extend = true;


	while((g.p[iterator].first == condition || extend) && iterator != j+1)
	{
		if(iterator == j || g.p[iterator].first != condition)
			break;

		if((g.p[k].first != condition || k == j+1) && extend == true)
		{
			iterator++;
			k = iterator+1;
			extend = true;
		}

		if(g.p[iterator].first != condition)
			extend = false;

		long int xdis = g.p[iterator].first - g.p[k].first;
   		long int ydis = g.p[iterator].second - g.p[k].second;
   		long int dist =  (xdis*xdis) + (ydis*ydis);
		float distance = sqrt(dist);
		if(distance < g.distance)
		{
			g.distance = distance;
			g.p1 = g.p[iterator];
			g.p2 = g.p[k];
		}
		k++;
	}
*/