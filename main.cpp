/**
	Percolation problem on the triangular lattice
	percolation.cpp
	Yuliia Hrabar
	Last update 27/04/17
*/

#include "stdafx.h"
#include <random>
#include <iostream>
#include <fstream>
#include "time.h"
#include <string>

using namespace std;

struct  possibleDirections {
	int x;
	int y;
	int direction;
};

// function for drawing the triangular lattice for the background
void draw_lattice(int L)
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

bool check_direction(int **lattice, int L, int x, int y, int row_start, int a, int direction)
{
	int k = 0;
	int kx = 0;
	int ky = 0;

	switch (direction)
	{
	case 1:
		while (k <= a)
		{
			if (x + kx >= L || y + ky >= L)
				a++;
			if (x + kx >= L && y + ky >= L)
			{
				x = 0;
				y = 0;
				kx = 0;
				ky = 0;
			}
			else if (x + kx >= L)
			{
				x = 0;
				kx = 0;
				ky--;
			}
			else if (y + ky >= L)
			{
				y = 0;
				ky = 0;
				kx--;
			}

			if (x + kx == L - 1 && y + ky == L - 1 && lattice[0][0] == 1)
				return false;
			if (x + kx == 0 && y + ky == 0 && lattice[L - 1][L - 1] == 1)
				return false;
			if (x + kx == 0 && lattice[L - 1][y + ky] == 1)
				return false;
			if (y + ky == 0 && lattice[x + kx][L - 1] == 1)
				return false;
			if (x + kx == L - 1 && lattice[0][y + ky] == 1)
				return false;
			if (y + ky == L - 1 && lattice[x + kx][0] == 1)
			return false;

			if (lattice[x + kx][y + ky] == 1)
			{
				return false;
			}
			kx++; ky++;
			k++;
		}
		break;

	case 2:
		while (k <= 2 * a + row_start)
		{
			if (x + kx >= L)
			{
				if (row_start == 0)
					a++;
				x = row_start;
				kx = 0;
			}
			// Checking if point is on boundaries
			if (y == L - 1 && lattice[x + kx][0] == 1)
				return false;
			if (y == 0 && lattice[x + kx][L - 1] == 1)
				return false;
			if (x + kx == L - 1 && lattice[0][y] == 1)
				return false;
			if (x + kx == 0 && lattice[L - 1][y] == 1)
				return false;

			if (lattice[x + kx][y] == 1)
				return false;
			kx = kx + 2;
			k = k + 2;
		}

		break;

	case 3:

		while (k <= a)
		{
			if (x + kx >= L || y - ky < 0)
				a++;
			if (x + kx >= L && y - ky < 0)
			{
				x = 0;
				y = L - 1;
				kx = 0;
				ky = 0;
			}
			else if (x + kx >= L)
			{
				x = 0;
				kx = 0;
				ky--;
			}
			else if (y - ky < 0)
			{
				y = L - 1;
				ky = 0;
				kx--;
			}

			// Checking if point is on boundaries
			if (x + kx == L - 1 && y - ky == L - 1 && lattice[0][0] == 1)
				return false;
			if (x + kx == 0 && y - ky == 0 && lattice[L - 1][L - 1] == 1)
				return false;
			if (x + kx == 0 && lattice[L - 1][y - ky] == 1)
				return false;
			if (y - ky == 0 && lattice[x + kx][L - 1] == 1)
				return false;
			if (x + kx == L - 1 && lattice[0][y - ky] == 1)
				return false;
			if (y - ky == L - 1 && lattice[x + kx][0] == 1)
				return false;

			if (lattice[x + kx][y - ky] == 1)
				return false;
			kx++; ky++;
			k++;
		}

		break;
	}
	return true;
}

void write_in_file(ofstream& pos_file, int **lattice, int L, int x, int y, int row_start, int a, int direction)
{
	int k = 0, kx = 0, ky = 0;
	bool out_x = false;
	bool out_y = false;

	switch (direction)
	{
	case 1:

		while (k <= a)
		{
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
			// Checking if point is on boundaries
			if (x + kx == L - 1 && y + ky == L - 1)
				lattice[0][0] = 1;
			if (x + kx == 0 && y + ky == 0)
				lattice[L - 1][L - 1] = 1;
			if (x + kx == 0)
				lattice[L - 1][y + ky] = 1;
			if (y + ky == 0)
				lattice[x + kx][L - 1] = 1;
			if (x + kx == L - 1)
				lattice[0][y + ky] = 1;
			if (y + ky == L - 1)
				lattice[x + kx][0] = 1;

			lattice[x + kx][y + ky] = 1;
			pos_file << x + kx << "\t" << y + ky << endl;
			kx++; ky++;
			k++;
		}

		pos_file << endl;
		pos_file << endl;
		break;


	case 2:	

		k = 0;
		while (k <= 2 * a + row_start)
		{
			if (x + kx >= L)
			{
				if (row_start == 1)
				{
					pos_file << L - 1 << "\t" << y << endl;
					pos_file << endl;
					pos_file << endl;
					pos_file << 0 << "\t" << y << endl;
				}
				else
				{
					a++;
					pos_file << endl;
					pos_file << endl;
				}

				x = row_start;
				kx = 0;
			}
			// Checking if point is on boundaries
			if (y == L - 1)
				lattice[x + kx][0] = 1;
			if (y == 0)
				lattice[x + kx][L - 1] = 1;
			if (x + kx == L - 1)
				lattice[0][y] = 1;
			if (x + kx == 0)
				lattice[L - 1][y] = 1;

			lattice[x + kx][y] = 1;
			pos_file << x + kx << "\t" << y << endl;
			kx = kx + 2;
			k = k + 2;
		}

		pos_file << endl;
		pos_file << endl;
		break;

	case 3:																
		while (k <= a)
		{
			if (x + kx >= L || y - ky < 0)
				a++;
			if (x + kx >= L && y - ky < 0)
			{
				x = 0;
				y = L - 1;
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
			else if (y - ky < 0)
			{
				y = L - 1;
				ky = 0;
				kx--;
				pos_file << endl;
				pos_file << endl;
			}
			// Checking if point is on boundaries
			if (x + kx == L - 1 && y - ky == L - 1)
				lattice[0][0] = 1;
			if (x + kx == 0 && y - ky == 0)
				lattice[L - 1][L - 1] = 1;
			if (x + kx == 0)
				lattice[L - 1][y - ky] = 1;
			if (y - ky == 0)
				lattice[x + kx][L - 1] = 1;
			if (x + kx == L - 1)
				lattice[0][y - ky] = 1;
			if (y - ky == L - 1)
				lattice[x + kx][0] = 1;

			lattice[x + kx][y - ky] = 1;
			pos_file << x + kx << "\t" << y - ky << endl;
			kx++; ky++;
			k++;
		}

		pos_file << endl;
		pos_file << endl;
		break;
	}
}

//void find_cluster(int **t, int N, int i, int j, int num)
//{
//	t[i][j] = num;
//
//	// direction 1
//	if (i < N - 1 && j < N - 1 && t[i + 1][j + 1] == 1)
//		find_cluster(t, N, i + 1, j + 1, num);
//	if (i < N - 1 && j > 0 && t[i + 1][j - 1] == 1)
//		find_cluster(t, N, i + 1, j - 1, num);
//
//	// direction 2
//	if (i > 1 && t[i - 2][j] == 1)
//		find_cluster(t, N, i - 2, j, num);
//	if (i < N - 2 && t[i + 2][j] == 1)
//		find_cluster(t, N, i + 2, j, num);
//
//	// direction 3
//	if (i < N - 1 && j > 0 && t[i + 1][j - 1] == 1)
//		find_cluster(t, N, i + 1, j - 1, num);
//	if (i > 1 && j > 0 && t[i - 1][j - 1] == 1)
//		find_cluster(t, N, i - 1, j - 1, num);
//}


void find_cluster(int **t, int N, int i, int j, int num)
{
	t[i][j] = num;

	// direction 1 
	// x and y in range of lattice 
	if (i + 1 < N && j + 1 < N && t[i + 1][j + 1] == 1)
		find_cluster(t, N, i + 1, j + 1, num);
	// both x and y are out of range
	/*else*/ if (i + 1 >= N && j + 1 >= N && t[0][0] == 1)
		find_cluster(t, N, 0, 0, num);
	// only x is out of range
	/*else*/ if (i + 1 >= N && j + 1 < N && t[0][j + 1] == 1)
		find_cluster(t, N, 0, j + 1, num);
	// only y is out of range 
	/*else*/ if (i + 1 < N && j + 1 >= N && t[i + 1][0] == 1)
		find_cluster(t, N, i + 1, 0, num);

	// direction -1 
	if (i - 1 >= 0 && j - 1 >= 0 && t[i - 1][j - 1] == 1)
		find_cluster(t, N, i - 1, j - 1, num);
	// both x and y are out of range
	/*else*/ if (i - 1 < 0 && j - 1 < 0 && t[N - 1][N - 1] == 1)
		find_cluster(t, N, N - 1, N - 1, num);
	// only x is out of range
	/*else*/ if (i - 1 < 0 && j - 1 >= 0 && t[N - 1][j - 1] == 1)
		find_cluster(t, N, N - 1, j - 1, num);
	// only y is out of range 
	/*else*/ if (i - 1 >= 0 && j - 1 < 0 && t[i - 1][N - 1] == 1)
		find_cluster(t, N, i - 1, N - 1, num);

	// direction 2
	if (i + 1 < N - 1  && t[i + 1][j] == 1)
		find_cluster(t, N, i + 1, j, num);
	/*else*/ if (i + 1 >= N - 1  && t[0][j] == 1)
		find_cluster(t, N, 0, j, num);

	// direction -2
	if (i - 1 >= 0 && t[i - 1][j] == 1)
		find_cluster(t, N, i - 1, j, num);
	/*else*/ if (i - 1 <= 0 && t[N - 1][j] == 1)
		find_cluster(t, N, N - 1, j, num);

	// direction 3
	if (i + 1 < N && j - 1 >= 0 && t[i + 1][j - 1] == 1)
		find_cluster(t, N, i + 1, j - 1, num);
	// both x and y are out of range
	/*else*/ if (i + 1 >= N && j - 1 < 0 && t[0][N - 1] == 1)
		find_cluster(t, N, 0, N - 1, num);
	// only x is out of range
	/*else*/ if (i + 1 >= N && j - 1 >= 0 && t[0][j - 1] == 1)
		find_cluster(t, N, 0, j - 1, num);
	// only y is out of range 
	/*else*/ if (i + 1 < N && j - 1 < 0 && t[i + 1][N - 1] == 1)
		find_cluster(t, N, i + 1, N - 1, num);

	// direction -3
	if (i - 1 >= 0 && j + 1 < N && t[i - 1][j + 1] == 1)
		find_cluster(t, N, i - 1, j + 1, num);
	// both x and y are out of range
	/*else*/ if (i - 1 < 0 && j + 1 >= N && t[N - 1][0] == 1)
		find_cluster(t, N, N - 1, 0, num);
	// only x is out of range
	/*else */if (i - 1 < 0 && j + 1 < N && t[N - 1][j + 1] == 1)
		find_cluster(t, N, N - 1, j - 1, num);
	// only y is out of range 
	/*else*/ if (i - 1 >= 0 && j + 1 >= N && t[i - 1][0] == 1)
		find_cluster(t, N, i - 1, 0, num);
}


//void find_cluster(int **t, int N, int i, int j, int num)
//{
//	t[i][j] = num;
//
//	// direction 1 
//	// x and y in range of lattice 
//	if (i + 1 < N && j + 1 < N && t[i + 1][j + 1] == 1)
//		find_cluster(t, N, i + 1, j + 1, num);
//	// both x and y are out of range
//	else if (i + 1 >= N && j + 1 >= N && t[0][0] == 1)
//		find_cluster(t, N, 0, 0, num);
//	// only x is out of range
//	else if (i + 1 >= N && j + 1 < N && t[0][j + 1] == 1)
//		find_cluster(t, N, 0, j + 1, num);
//	// only y is out of range 
//	else if (i + 1 < N && j + 1 >= N && t[i + 1][0] == 1)
//		find_cluster(t, N, i + 1, 0, num);
//	
//	// direction -1 
//	if (i - 1 >= 0 && j - 1 >= 0 && t[i - 1][j - 1] == 1)
//		find_cluster(t, N, i - 1, j - 1, num);
//	// both x and y are out of range
//	else if (i - 1 < 0 && j - 1 < 0 && t[N - 1][N - 1] == 1)
//		find_cluster(t, N, N - 1, N - 1, num);
//	// only x is out of range
//	else if (i + 1 < 0 && j - 1 >= 0 && t[N - 1][j - 1] == 1)
//		find_cluster(t, N, N - 1, j - 1, num);
//	// only y is out of range 
//	else if (i - 1 >= 0 && j - 1 < 0 && t[i - 1][N - 1] == 1)
//		find_cluster(t, N, i - 1, N - 1, num);
//
//	// direction 2
//	if (i + 2 < N && t[i + 2][j] == 1)
//		find_cluster(t, N, i + 2, j, num);
//	else if (i + 2 >= N) 
//	{
//		// row is even so it starts from index 0
//		if (j % 2 == 0 && t[0][j] == 1)
//			find_cluster(t, N, 0, j, num);
//		// row is odd and starts from 1
//		else if (j % 2 != 0 && t[1][j] == 1)
//			find_cluster(t, N, 1, j, num);
//	}
//	
//	// direction -2
//	if (i - 2 >= 0 && t[i - 2][j] == 1)
//		find_cluster(t, N, i - 2, j, num);
//	else if (i - 2 < 0)
//	{
//		// row is even
//		if (j % 2 == 0 && t[N - 1][j] == 1)
//			find_cluster(t, N, N - 1, j, num);
//		// row is odd 
//		else if (j % 2 != 0 && t[N - 2][j] == 1)
//			find_cluster(t, N, N - 2, j, num);
//	}
//
//	// direction 3
//	if (i + 1 < N && j - 1 >= 0 && t[i + 1][j - 1] == 1)
//		find_cluster(t, N, i + 1, j - 1, num);
//	// both x and y are out of range
//	else if (i + 1 >= N && j - 1 < 0 && t[0][N - 1] == 1)
//		find_cluster(t, N, 0, N - 1, num);
//	// only x is out of range
//	else if (i + 1 >= N && j - 1 >= 0 && t[0][j - 1] == 1)
//		find_cluster(t, N, 0, j - 1, num);
//	// only y is out of range 
//	else if (i + 1 < N && j - 1 < 0 && t[i + 1][N - 1] == 1)
//		find_cluster(t, N, i + 1, N - 1, num);
//
//	// direction -3
//	if (i - 1 >= 0 && j + 1 < N && t[i - 1][j + 1] == 1)
//		find_cluster(t, N, i - 1, j + 1, num);
//	// both x and y are out of range
//	else if (i - 1 < 0 && j + 1 >= N && t[N - 1][0] == 1)
//		find_cluster(t, N, N - 1, 0, num);
//	// only x is out of range
//	else if (i - 1 < 0 && j + 1 < N && t[N - 1][j + 1] == 1)
//		find_cluster(t, N, 0, j - 1, num);
//	// only y is out of range 
//	else if (i - 1 >= 0 && j + 1 >= N && t[i - 1][0] == 1)
//		find_cluster(t, N, i - 1, 0, num);
//}


void print_table(int **t, int N, string file_name)
{
	ofstream my_file;
	my_file.open(file_name.c_str());
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			my_file << t[i][j] << " ";
		}
		my_file << endl;
	}
	my_file.close();
}

void copy_table(int **t1, int **t2, int N)
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			t2[i][j] = t1[i][j];
}

int check_start_x(int L, int x, int y, int row_start)
{
	if (y % 2 != 0 && x == 0)
		x = 1;

	if (y % 2 != 0 && x % 2 == 0)
	{
		if (x + 1 >= L)
			x = row_start;
		else
			x++;
	}

	if (y % 2 == 0 && x % 2 != 0)
	{
		if (x + 1 >= L)
			x = row_start;
		else
			x++;
	}
	return x;
}

int main()
{
	double concentration = 0.2; // concentration of needles on lattice
	double con_update = 0;
	double needles_mass = 0;
	const int L = 36 + 1; // a square lattice of size LxL (can only be even number, cause we need odd number for our lattice)
	int a = 5;  // length of a linear segments 
	double p; // given probability

	int **lattice; // the parameter is a a pointer to a pointer 
	lattice = new int *[L];
	for (int i = 0; i < L; i++)
		lattice[i] = new int[L];

	for (int i = 0; i < L; i++)
		for (int j = 0; j < L; j++)
			lattice[i][j] = 0;

	srand(time(NULL));

	ofstream pos_file;
	pos_file.open("position.txt"); // file which contains position of all the needles
	pos_file << "# x \t y \n";

	// draw_lattice(L);

	///////////////// Main loop
	int free;
	while (con_update <  concentration)
	{
		int y = (rand() % (L));
		int x = (rand() % (L));
		int direction = 1 + (rand() % (3));												

		int row_start = 0;
		if (y % 2 == 0) // even 
			row_start = 0;
		else
			row_start = 1;

		x = check_start_x(L, x, y, row_start);
		free = check_direction(lattice, L, x, y, row_start, a, direction);				// If direction is free then go to case otherwise just pass 
		if (free)
		{
			needles_mass += a;
			write_in_file(pos_file, lattice, L, x, y, row_start, a, direction);
		}
		con_update = needles_mass / (L * L);
	}

	print_table(lattice, L, "table1.txt");

	int **lattice_copy; // the parameter is a a pointer to a pointer 
	lattice_copy = new int *[L];
	for (int i = 0; i < L; i++)
		lattice_copy[i] = new int[L];

	copy_table(lattice, lattice_copy, L);
	//print_table(lattice_copy, L, "table_copy.txt");
	
	int cluster_num = 2;
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			if (lattice_copy[i][j] == 1)
			{
				find_cluster(lattice_copy, L, i, j, cluster_num);
				cluster_num++;
			}
		}
	}
	
	////// Checking if adges are the same 
	cout << "Left edge:" << endl;
	for (int i = 0; i < L; i++) 
	{
		cout << lattice[0][i] << " ";
	}
	cout << endl;
	cout << "Right edge:" << endl;
	for (int i = 0; i < L; i++)
	{
		cout << lattice[L-1][i] << " ";
	}
	cout << endl;
	cout << endl;
	cout << "Down edge:" << endl;
	for (int i = 0; i < L; i++)
	{
		cout << lattice[i][0] << " ";
	}
	cout << endl;
	cout << "Upper edge:" << endl;
	for (int i = 0; i < L; i++)
	{
		cout << lattice[i][L-1] << " ";
	}
	cout << endl;


	print_table(lattice_copy, L, "clusters.txt");
	
	///////////////////////////////////////
	////////// Part two after filling half of table

	vector<possibleDirections> posDir;

	int idx = 0;
	int row_start;
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			if ((j % 2 > 0 && i % 2 > 0) || (j % 2 == 0 && i % 2 == 0))
			{

				if (j % 2 == 0) // even 
					row_start = 0;
				else
					row_start = 1;
				if (check_direction(lattice, L, i, j, row_start, a, 1))
				{
					//Push back new subject created with default constructor
					posDir.push_back(possibleDirections());
					posDir[idx].x = i;
					posDir[idx].y = j;
					posDir[idx].direction = 1;
					idx++;
				}
				if (check_direction(lattice, L, i, j, row_start, a, 2))
				{
					//Push back new subject created with default constructor
					posDir.push_back(possibleDirections());
					posDir[idx].x = i;
					posDir[idx].y = j;
					posDir[idx].direction = 2;
					idx++;
				}
				if (check_direction(lattice, L, i, j, row_start, a, 3))
				{
					//Push back new subject created with default constructor
					posDir.push_back(possibleDirections());
					posDir[idx].x = i;
					posDir[idx].y = j;
					posDir[idx].direction = 3;
					idx++;
				}
			}
		}
	}

	/*for (int i = 0; i < posDir.size(); i++)
	{
		cout << posDir[i].x << " " << posDir[i].y << " " << posDir[i].direction << endl;
	}*/
	
	int rand_idx, x, y, direction;
	while (!posDir.empty())
	{
		rand_idx = (rand() % (posDir.size()));
		x = posDir[rand_idx].x;
		y = posDir[rand_idx].y;
		direction = posDir[rand_idx].direction;
		if (y % 2 == 0) 
			row_start = 0;
		else
			row_start = 1;
		direction = posDir[rand_idx].direction;
		write_in_file(pos_file, lattice, L, x, y, row_start, a, direction);
		
		posDir.erase(posDir.begin() + rand_idx);
		for (int i = 0; i < posDir.size(); i++)
		{
			x = posDir[i].x;
			y = posDir[i].y;
			direction = posDir[i].direction;
			if (check_direction(lattice, L, x, y, row_start, a, direction) == false)
			{
				posDir.erase(posDir.begin() + i);
			}
		}
		//cout << posDir.size() << endl;

	}
	print_table(lattice, L, "table2.txt");
	pos_file.close();

}
