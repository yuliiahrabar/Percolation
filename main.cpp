/**
	Percolation problem on the triangular lattice
	percolation.cpp
	Yuliia Hrabar
	Last update 10/06/17
*/

#include "stdafx.h"
#include <random>
#include <iostream>
#include <fstream>
#include "time.h"
#include <string>
#include <iomanip>.
#include "UnionFind.h"

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
	lattice_file.open("lattice.txt");						// file that contains points for drawing the whole lattice
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


void copy_file(string infile_name, string outfile_name)
{
	ifstream infile(infile_name);
	ofstream outfile(outfile_name);
	string content = "";
	while (!infile.eof()) // get content of infile
		content += infile.get();
	content.erase(content.end() - 1);     // erase last character
	infile.close();
	outfile << content;                 
	outfile.close();
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

//void write_in_file(ofstream& pos_file, int **lattice, int L, int x, int y, int row_start, int a, int direction)
//{
//	int k = 0, kx = 0, ky = 0;
//	bool out_x = false;
//	bool out_y = false;
//
//	switch (direction)
//	{
//	case 1:
//
//		while (k <= a)
//		{
//			if (x + kx >= L || y + ky >= L)
//				a++;
//			if (x + kx >= L && y + ky >= L)
//			{
//				x = 0;
//				y = 0;
//				kx = 0;
//				ky = 0;
//				pos_file << endl;
//				pos_file << endl;
//			}
//			else if (x + kx >= L)
//			{
//				x = 0;
//				kx = 0;
//				ky--;
//				pos_file << endl;
//				pos_file << endl;
//			}
//			else if (y + ky >= L)
//			{
//				y = 0;
//				ky = 0;
//				kx--;
//				pos_file << endl;
//				pos_file << endl;
//			}
//			if (x + kx == L - 1 && y + ky == L - 1)
//				lattice[0][0] = 1;
//			if (x + kx == 0 && y + ky == 0)
//				lattice[L - 1][L - 1] = 1;
//			if (x + kx == 0)
//				lattice[L - 1][y + ky] = 1;
//			if (y + ky == 0)
//				lattice[x + kx][L - 1] = 1;
//			if (x + kx == L - 1)
//				lattice[0][y + ky] = 1;
//			if (y + ky == L - 1)
//				lattice[x + kx][0] = 1;
//
//			lattice[x + kx][y + ky] = 1;
//			pos_file << x + kx << "\t" << y + ky << endl;
//			kx++; ky++;
//			k++;
//		}
//
//		pos_file << endl;
//		pos_file << endl;
//		break;
//
//
//	case 2:	
//
//		k = 0;
//		while (k <= 2 * a + row_start)
//		{
//			if (x + kx >= L)
//			{
//				if (row_start == 1)
//				{
//					pos_file << L - 1 << "\t" << y << endl;
//					pos_file << endl;
//					pos_file << endl;
//					pos_file << 0 << "\t" << y << endl;
//				}
//				else
//				{
//					a++;
//					pos_file << endl;
//					pos_file << endl;
//				}
//
//				x = row_start;
//				kx = 0;
//			}
//			if (y == L - 1)
//				lattice[x + kx][0] = 1;
//			if (y == 0)
//				lattice[x + kx][L - 1] = 1;
//			if (x + kx == L - 1)
//				lattice[0][y] = 1;
//			if (x + kx == 0)
//				lattice[L - 1][y] = 1;
//
//			lattice[x + kx][y] = 1;
//			pos_file << x + kx << "\t" << y << endl;
//			kx = kx + 2;
//			k = k + 2;
//		}
//
//		pos_file << endl;
//		pos_file << endl;
//		break;
//
//	case 3:																
//		while (k <= a)
//		{
//			if (x + kx >= L || y - ky < 0)
//				a++;
//			if (x + kx >= L && y - ky < 0)
//			{
//				x = 0;
//				y = L - 1;
//				kx = 0;
//				ky = 0;
//				pos_file << endl;
//				pos_file << endl;
//			}
//			else if (x + kx >= L)
//			{
//				x = 0;
//				kx = 0;
//				ky--;
//				pos_file << endl;
//				pos_file << endl;
//			}
//			else if (y - ky < 0)
//			{
//				y = L - 1;
//				ky = 0;
//				kx--;
//				pos_file << endl;
//				pos_file << endl;
//			}
//			if (x + kx == L - 1 && y - ky == L - 1)
//				lattice[0][0] = 1;
//			if (x + kx == 0 && y - ky == 0)
//				lattice[L - 1][L - 1] = 1;
//			if (x + kx == 0)
//				lattice[L - 1][y - ky] = 1;
//			if (y - ky == 0)
//				lattice[x + kx][L - 1] = 1;
//			if (x + kx == L - 1)
//				lattice[0][y - ky] = 1;
//			if (y - ky == L - 1)
//				lattice[x + kx][0] = 1;
//
//			lattice[x + kx][y - ky] = 1;
//			pos_file << x + kx << "\t" << y - ky << endl;
//			kx++; ky++;
//			k++;
//		}
//
//		pos_file << endl;
//		pos_file << endl;
//		break;
//	}
//}

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

void union_sets(int **lattice, int L, UnionFind& myUnion)
{
	for (int i = 0; i < L; i++)
		for (int j = 0; j < L; j++)
		{
			if (lattice[i][j] == 1)
			{
				//direction 1
				// x and y are out of range
				if (i + 1 >= L - 1 && j + 1 >= L - 1 && lattice[0][0] == 1)
					myUnion.Union(i * L + j, 0);
				// x is out of range
				if (i + 1 >= L - 1 && j + 1 < L - 1 && lattice[0][L - 1] == 1)
					myUnion.Union(i * L + j, L - 1);
				// y is out of range
				if (i + 1 < L - 1 && j + 1 >= L - 1 && lattice[i + 1][0] == 1)
					myUnion.Union(i * L + j, 0);
				// both inside
				if (i + 1 < L - 1 && j + 1 < L - 1 && lattice[i + 1][j + 1] == 1)
					myUnion.Union(i * L + j, (i + 1) * L + j + 1);

				//direction -1
				// x and y are smaller than 0
				if (i - 1 <= 0 && j - 1 <= 0 && lattice[L - 1][L - 1] == 1)
					myUnion.Union(i * L + j, (L - 1)*L + L - 1);
				// x is smaller than 0
				if (i - 1 <= 0 && j - 1 > 0 && lattice[L - 1][j - 1] == 1)
					myUnion.Union(i * L + j, (L - 1)*L + j - 1);
				// y is smaller than 0
				if (i - 1 > 0 && j - 1 <= 0 && lattice[i - 1][L - 1] == 1)
					myUnion.Union(i * L + j, (i - 1)*L + L - 1);
				// both inside
				if (i - 1 > 0 && j - 1 > 0 && lattice[i - 1][j - 1] == 1)
					myUnion.Union(i * L + j, (i - 1)*L + j - 1);

				//direction 2
				// x is out of range 
				if (i + 2 >= L - 1 && lattice[0][j] == 1)
					myUnion.Union(i * L + j, j);
				// inside
				if (i + 2 < L - 1 && lattice[i + 2][j] == 1)
					myUnion.Union(i * L + j, (i + 2)*L + j);

				//direction -2
				// x is smaller that 0
				if (i - 2 <= 0 && lattice[L - 1][j] == 1)
					myUnion.Union(i * L + j, (L - 1)*L + j);
				// inside
				if (i - 2 > 0 && lattice[i - 2][j] == 1)
					myUnion.Union(i * L + j, (i - 2)*L + j);

				//direction 3
				// x and y are out of range
				if (i + 1 >= L - 1 && j - 1 <= 0 && lattice[0][L - 1] == 1)
					myUnion.Union(i * L + j, L - 1);
				// if x is larger than N-1
				if (i + 1 >= L - 1 && j - 1 > 0 && lattice[0][j - 1] == 1)
					myUnion.Union(i * L + j, j - 1);
				// if y is smaller than 0
				if (i + 1 < L - 1 && j - 1 <= 0 && lattice[i + 1][L - 1] == 1)
					myUnion.Union(i * L + j, (i + 1)*L + L - 1);
				// both inside
				if (i + 1 < L - 1 && j - 1 > 0 && lattice[i + 1][j - 1] == 1)
					myUnion.Union(i * L + j, (i + 1)*L + j - 1);

				//direction -3
				// x and y are out of range
				if (i - 1 <= 0 && j + 1 >= L - 1 && lattice[L - 1][0] == 1)
					myUnion.Union(i * L + j, (i - 1)*L);
				// if x is smaller than 0
				if (i - 1 <= 0 && j + 1 < L - 1 && lattice[L - 1][j + 1] == 1)
					myUnion.Union(i * L + j, (i - 1)*L + j + 1);
				// if y is larger than N-1
				if (i - 1 > 0 && j + 1 >= L - 1 && lattice[i - 1][0] == 1)
					myUnion.Union(i * L + j, (i - 1)*L);
				// both inside 
				if (i - 1 > 0 && j + 1 < L - 1 && lattice[i - 1][j + 1] == 1)
					myUnion.Union(i * L + j, (i - 1)*L + j + 1);
			}
		}
}

void check_percolation(int **lattice, int L, UnionFind& myUnion)
{
	for (int i = 0; i < L; i++)
	{
		if (lattice[0][i] == 1)
		{	
			bool has = true;
			for (int y = 1; y < L; y++)
			{
				bool in_row = false;
				for (int x = 0; x < L; x++)
				{
					if (myUnion.Find(i) == myUnion.Find(y * L + x))
						in_row = true;
				}
				if (!in_row)
					has = false;
			}
			if (has)
			{
				cout << "There is a path (y) !" << endl;
				cout << myUnion.Find(i) << endl;
				return;
			}
				
		}
	}
	cout << "There is no path!" << endl;

	for (int i = 0; i < L; i++)
	{
		if (lattice[i][0] == 1)
		{
			bool has = true;
			for (int x = 1; x < L; x++)
			{
				bool in_column = false;
				for (int y = 0; y < L; y++)
				{
					if (myUnion.Find(i) == myUnion.Find(y * L + x))
						in_column = true;
				}
				if (!in_column)
					has = false;
			}
			if (has)
			{
				cout << "There is a path (x) !" << endl;
				cout << myUnion.Find(i) << endl;
				return;
			}

		}
	}
	cout << "There is no path!" << endl;
}

void filling_rest(ofstream& pos_file, int **lattice, int L, int a, double needles_mass, UnionFind& myUnion)
{
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

				for (int dir = 1; dir <= 3; dir++)
				{
					if (check_direction(lattice, L, i, j, row_start, a, dir))
					{
						posDir.push_back(possibleDirections());
						posDir[idx].x = i;
						posDir[idx].y = j;
						posDir[idx].direction = dir;
						idx++;
					}
				}
			}
		}
	}

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
		needles_mass += a;

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

	}
	cout << "Needles mass: " << needles_mass << ", number of needles: " << needles_mass / 2 << endl;
	cout << "Jamming concentration: " << needles_mass * 1.4 / (L * L * 0.5) << endl;
}

void print_representative(int L, UnionFind& myUnion)
{
	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			cout << setw(3) << myUnion.Find(i*L + j) << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	double concentration = 0.2;															 // concentration of needles on lattice
	const int L = 24 + 1;																 // a square lattice of size LxL (can only be even number, cause we need odd number for our lattice)
	int a = 5;																			 // length of a linear segments 


	double con_update = 0;
	double needles_mass = 0;


	int **lattice;																		 // the parameter is a a pointer to a pointer 
	lattice = new int *[L];
	for (int i = 0; i < L; i++)
		lattice[i] = new int[L];

	for (int i = 0; i < L; i++)
		for (int j = 0; j < L; j++)
			lattice[i][j] = 0;

	//srand(time(NULL));

	ofstream pos_file;
	string file_name = "position.txt";
	pos_file.open(file_name);														 // file which contains position of all the needles
	pos_file << "# x \t y \n";

	draw_lattice(L);

	/////////////////////////////////////////////////////////////////
	///////////////// Main loop /////////////////////////////////////
	/////////////////////////////////////////////////////////////////

	int needles_num = 0;
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
			if (check_direction(lattice, L, x, y, row_start, a, direction))					 // If direction is free then go to case otherwise just pass
			{
				needles_num++;
				needles_mass += a + 1;
				write_in_file(pos_file, lattice, L, x, y, row_start, a, direction);
				//copy_file(file_name, "movie/p" + to_string(needles_num) + ".txt");
			}
			con_update = needles_mass * 1.41 / (L * L * 0.5);
	}
	cout << "First concentration: " << con_update << endl;

	
	UnionFind myUnion(L * L);
	//filling_rest(pos_file, lattice, L, a, needles_mass, myUnion);
	
	
	union_sets(lattice, L, myUnion);
	print_table(lattice, L, "my_table.txt");
	
	check_percolation(lattice, L, myUnion);
	print_representative(L, myUnion);
	pos_file.close();
}
