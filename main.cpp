// Percolation.cpp

#include "stdafx.h"
#include <random>
#include <iostream>
#include <fstream>
#include "time.h"

using namespace std;

// function for drawing the triangular lattice for the background
void drawLattice(int L)
{

	ofstream lattice_file;
	lattice_file.open("lattice.txt"); // file that contains points for drawing the whole lattice
	lattice_file << "# x \t y \n";

	for (int i = 0; i < L; i = i + 1)
	{
		lattice_file << 0 << "\t" << i << endl;
		lattice_file << L - 1 << "\t" << i << endl;
		lattice_file << endl;
		lattice_file << endl;
	}

	for (int i = 2; i < L - 2; i = i + 2)
	{
		lattice_file << i << "\t" << 0 << endl;
		lattice_file << L - 1 << "\t" << L - 1 - i << endl;
		lattice_file << endl;
		lattice_file << endl;

		lattice_file << i << "\t" << 0 << endl;
		lattice_file << 0 << "\t" << i << endl;
		lattice_file << endl;
		lattice_file << endl;
	}

	for (int i = L - 1; i >= 0; i = i - 2)
	{
		lattice_file << i << "\t" << L - 1 << endl;
		lattice_file << 0 << "\t" << L - 1 - i << endl;
		lattice_file << endl;
		lattice_file << endl;

		lattice_file << i << "\t" << L - 1 << endl;
		lattice_file << L - 1 << "\t" << i << endl;
		lattice_file << endl;
		lattice_file << endl;

	}
	lattice_file.close();
}


int main()
{
	int N = 100; // number of tries 
	const int L = 50 + 1; // a square lattice of size LxL (can only be even number, cause we need odd number for our lattice)
	int length = 5;  // length of a linear segments 
	double p; // given probability
	int lattice[L][L] = {0};
	srand(time(NULL));

	ofstream pos_file;
	pos_file.open("position.txt"); // file which contains position of all the needles
	pos_file << "# x \t y \n";

	// drawLattice(L);

	///////////////// Main loop
	for (int i = 0; i < N; i++)
	{
		pos_file << endl;
		pos_file << endl;

		int y = (rand() % (L));
	    int x = (rand() % (L));


		////////// Check if x position corresponds to lattice 
		/* 
		
		0 *   *   * for odd y is only odd x allowed 
		1   *   *   for even y only even x allowed 
		2 *   *   *
		3   *   *

		*/
		
		// check if y is odd
		if (y % 2 == 0)
		{
			if (x % 2 != 0)
			{
				if (x + 1 >= L)
					x = x + 1 - L;
				else
					x++;
			}
				
		}
		else
		{
			if (x % 2 == 0)
			{
				if (x + 1 >= L)
					x = x + 1 - L;
				else
					x++;
			}
		}
		////////////

		
		///////////  Placing the needle in the right direction

		//int direction = 1 + (rand() % (3));

		int direction = 1;

		int row_start=0;

		if (y % 2 != 0)
			row_start = 1;

		bool free = true;
		int k=0;
		int x0 = x;
		int y0 = y;
		int kx=0;
		int ky=0;
		int a = length;
		int a0 = length;
		bool stop = false;
		switch (direction)
		{

		// north east direction
		case 1:
			//if ((x + a) > L && (y + a) > L)
			// check if some positions are already occupied 
			k = 0;
			kx = 0;
			ky = 0;
			cout << "new one:" << endl;

			while (k <= a0)
			{
				if (x0 + kx >= L || y0 + ky >= L)
					a0++;
				if (x0 + kx >= L && y0 + ky >= L)
				{
					x0 = 0;
					y0 = 0;
					kx = 0;
					ky = 0;
				}
				else if (x0 + kx >= L)
				{
					x0 = 0;
					kx = 0;
					ky--;
				}
				else if (y0 + ky >= L)
				{
					y0 = 0;
					ky = 0;
					kx--;
				}
				if (lattice[x0 + kx][y0 + ky] == 1)
				{
					free = false;
					break;
				}
				kx++; ky++;
				k++;
			}

			k = 0; kx = 0; ky = 0;
			if (free)
				while (k <= a)
				{
					cout << kx << " " << ky << endl;
					if (x + kx >= L || y + ky >= L)
						a++;
					if (x + kx >= L && y + ky >= L)
					{
						x = 0;
						y = 0;
						kx = 0;
						ky = 0;
						pos_file << endl;
						pos_file << endl;
					}
					else if (x + kx >= L)
					{
						x = 0;
						kx = 0;
						ky--;
						pos_file << endl;
						pos_file << endl;
					}
					else if (y + ky >= L)
					{
						y = 0;
						ky = 0;
						kx--;
						pos_file << endl;
						pos_file << endl;
					}
					lattice[x + kx][y + ky] = 1;
					pos_file << x + kx << "\t" << y + ky << endl;
					kx++; ky++;
					k++;
				}

			pos_file << endl;
			pos_file << endl;
			/*

			while (k <= a && (x + k) < L && (y + k) < L)
			{
				if (lattice[x + k][y + k] == 1)
				{
					free = false;
					break;
				}
				k++;
			}

			if (k < a)
			{
				if (x + a >= L && y + a >= L)
				{
					int new_k = 0;
					while (new_k <= a + 1 - k)
					{
						if (lattice[new_k][new_k] == 1)
						{
							free = false;
							break;
						}
						new_k++;
					}
				}
				else if (x + a >= L)
				{
					int new_k = 0;
					while (new_k <= a + 1 - k)
					{
						if (lattice[new_k][y + k + new_k - 1] == 1)
						{
							free = false;
							break;
						}
						new_k++;
					}
				}
				else
				{
					int new_k = 0;
					while (new_k <= a + 1 - k)
					{
						if (lattice[x + k + new_k - 1][new_k] == 1)
						{
							free = false;
							break;
						}
						new_k++;
					}
				}
			}
			
			k = 0;
			if (free)
			{
				
				while (k <= a && (x + k) < L && (y + k) < L)
				{
					lattice[x + k][y + k] = 1;
					pos_file << x + k << "\t" << y + k << endl;
					k++;
				}

				if (k < a)
				{
					pos_file << endl;
					pos_file << endl;
					if (x + a >= L && y + a >= L)
					{
						int new_k = 0;
						while (new_k <= a + 1 - k)
						{
							lattice[new_k][new_k] = 1;
							pos_file << new_k << "\t" << new_k << endl;
							new_k++;
						}
					}
					else if (x + a >= L)
					{
						int new_k = 0;
						while (new_k <= a + 1 - k)
						{
							lattice[new_k][y + k + new_k] = 1;
							pos_file << new_k << "\t" << y + k + new_k - 1 << endl;
							new_k++;
						}
					}
					else
					{
						int new_k = 0;
						while (new_k <= a + 1 - k)
						{
							lattice[x + k + new_k - 1][new_k ] = 1;
							pos_file << x + k + new_k - 1 << "\t" << new_k<< endl;
							new_k++;
						}
					}
				}
			}
			*/
			break;

		// horizontal direction 
		case 2:
			// check if some positions are already occupied 
			k = 0;
			while (k <= 2 * a + row_start && (x + k) < L)
			{
				if (lattice[x + k][y] == 1)
				{
					free = false;
					break;
				}
				k = k + 2;
			}
			
			if (k < 2 * a + row_start)
			{
				int new_k = 0;
				while (new_k <= 2 * a - k + 2)
				{
					if (lattice[new_k][y] == 1) 
					{
						free = false;
						break;
					}
					new_k = new_k + 2;
				}
			}

			if (free) 
			{
				int k = 0;
				while (k <= 2 * a && (x + k) < L)
				{
					lattice[x + k][y] = 1;
					pos_file << x + k << "\t" << y << endl;
					k = k + 2;
				}
				
				if (k < 2 * a)
				{
					if (row_start == 1)
						pos_file << L-1 << "\t" << y << endl;
					
					pos_file << endl;
					pos_file << endl;
					
					if (row_start == 1)
						pos_file << 0 << "\t" << y << endl;
					
					int new_k = row_start;
					while (new_k <= 2 * a - k + 2)
					{
						lattice[new_k][y] = 1;
						pos_file << new_k << "\t" << y << endl;
						new_k = new_k + 2;
					}
					pos_file << endl;
					pos_file << endl;
				}
				else 
				{
					pos_file << endl;
					pos_file << endl;
				}

			}
			break;

		// south east direction 
		case 3:
			//if ((x + a) > L || (y - a) < 0)

			k = 0;
			pos_file << endl;
			pos_file << endl;
			while (k <= a && (x + k) < L && (y + k) >= 0)
			{
				if (lattice[x + k][y - k] == 1)
				{
					free = false;
					break;
				}
				k++;
			}
			if (k < a)
			{
				if ((x + a) > L && (y - a) < 0)
				{
					int new_k = 0;
					while (new_k <= a + 1 - k)
					{
						if (lattice[new_k][L - 1 - new_k] == 1)
						{
							free = false;
							break;
						}
						new_k++;
					}
				}
				else if ((x + a) > L)
				{
					int new_k = 0;
					while (new_k <= a + 1 - k)
					{
						if (lattice[new_k][y - k - new_k + 1] == 1)
						{
							free = false;
							break;
						}
						new_k++;
					}
				}
				else
				{
					int new_k = 0;
					while (new_k <= a + 1 - k)
					{
						if (lattice[x + row_start + new_k][L - 1 - new_k] == 1)
						{
							free = false;
							break;
						}
						new_k++;
					}
				}
			}
			pos_file << endl;
			pos_file << endl;

			if (true) 
			{
				k = 0;
				while (k <= a && (x + k) < L && (y - k) >= 0)
				{
					lattice[x + k][y - k] = 1;
					pos_file << x + k << "\t" << y - k << endl;
					k++;
				}
				if (k < a)
				{
					pos_file << endl;
					pos_file << endl;
					if ((x + a) > L && (y - a) < 0)
					{
						int new_k = 0;
						while (new_k <= a + 1 - k)
						{
							lattice[new_k][L - 1 - new_k] = 1;
							pos_file << new_k << "\t" << L - 1 - new_k << endl;
							new_k++;
						}
					}
					else if ((x + a) > L)
					{
						int new_k = 0;
						while (new_k <= a + 1 - k)
						{
							lattice[new_k][y - k - new_k + 1] = 1;
							pos_file << new_k << "\t" << y - k - new_k + 1 << endl;
							new_k++;
						}
					}
					else
					{
						int new_k = 0;
						while (new_k <= a + 1 - k)
						{
							lattice[x + row_start + new_k][L - 1 - new_k] = 1;
							pos_file << x + row_start + new_k << "\t" << L - 1 - new_k << endl;
							new_k++;
						}
					}
					pos_file << endl;
					pos_file << endl;
				}
			}
			
			
			break;
			
		}
	}
	
	pos_file.close();
}
