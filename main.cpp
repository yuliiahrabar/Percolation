// Percolation.cpp

#include "stdafx.h"
#include <random>
#include <iostream>
#include <fstream>
#include "time.h"

using namespace std;
int main()
{
	int N = 150; // number of tries
	const int L = 100; // a square lattice of size LxL
	int a = 5;  // length of a linear segments 
	double p; // given probability
	int lattice[L][L] = {0};
	srand(time(NULL));

	ofstream myfile;
	myfile.open("results.txt");
	myfile << "# x \t y \n";
	for (int i = 0; i < N; i++)
	{
	    int x = (rand() % (L));
	    int y = (rand() % (L));
		if (a > 0)
		{
			int direction = 1 + (rand() % (3));
			int k = 0;
			switch (direction)
			{
			// north east direction
			case 1:
				//if ((x + a) > L && (y + a) > L)
				while (k <= a && (x + k) < L && (y + k) < L)
				{
					lattice[x + k][y + k] = 1;
					myfile << x + k << "\t" << y + k << endl;
					k++;
				}

				if (k < a)
				{
					myfile << endl;
					myfile << endl;
					if (x + a > L && y + a > L) 
					{
						while (k <= a + 1)
						{
							lattice[x + k - L][y + k - L] = 1;
							myfile << x + k - L  << "\t" << y + k - L << endl;
							k++;
						}
					}
					else if (x + a > L)
					{
						while (k <= a + 1)
						{
							lattice[x + k - L][y + k] = 1;
							myfile << x + k - L << "\t" << y + k << endl;
							k++;
						}
					}
					else 
					{
						while (k <= a + 1)
						{
							lattice[x + k][y + k - L] = 1;
							myfile << x + k << "\t" << y + k - L << endl;
							k++;
						}
					}
				}
				break;

			// horizontal direction 
			case 2:
				//if ((x + a) > L)
				while ( k <= a && (x + k) < L)
				{
					lattice[x + k][y] = 1;
					myfile << x + k << "\t" << y << endl;
					k++;
				}
				if (k < a)
				{
					myfile << endl;
					myfile << endl;
					while (k <= a + 1)
					{
						lattice[x + k - L][y] = 1;
						myfile << x + k - L << "\t" << y << endl;
						k++;
					}
				}
				break;
			// south east direction 
			case 3:
				//if ((x + a) > L || (y - a) < 0)
				while (k <= a && (x + k) < L && (y - k) >= 0)
				{
					lattice[x + k][y - k] = 1;
					myfile << x + k << "\t" << y - k << endl;
					k++;
				}
				if (k < a)
				{
					myfile << endl;
					myfile << endl;
					if ((x + a) > L && (y - a) < 0)
					{
						while (k <= a + 1)
						{
							lattice[x + k - L][L - k] = 1;
							myfile << x + k - L << "\t" << L - k << endl;
							k++;
						}
					}
					else if ((x + a) > L)
					{
						while (k <= a + 1)
						{
							lattice[x + k - L][L - k] = 1;
							myfile << x + k - L << "\t" << L - k << endl;
							k++;
						}
					} 
					else
					{
						while (k <= a + 1)
						{
							lattice[x + k][L - k] = 1;
							myfile << x + k << "\t" << L - k << endl;
							k++;
						}
					}
				}
				break;
			}
			
		}
		myfile << endl;
		myfile << endl;
	}
	myfile.close();
}
