// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <array>

int main()
{
	const int MAX = 11;
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");
	std::array<std::array<char, MAX>, MAX> inArr;
	std::array<std::array<int, MAX>, MAX> result;

	int n, m;
	input >> n >> m;

	for (size_t i = 0; i <= n + 1; i++)
	{
		for (size_t j = 0; j <= m + 1; j++)
		{
			if (i == 0 or j == 0 or i == n+1 or j == m+1)
			{
				inArr[i][j] = '+';
			}
			else
			{
				input >> inArr[i][j];
			}
		}
	}

	int dx[8] = { 1, 0, -1, 0 , 1, -1, 1, -1 };   // смещения, соответствующие соседям ячейки
	int dy[8] = { 0, 1, 0, -1, 1, -1 , -1, 1 };

	int count = 0;

	for (int x = 1; x <= n; x++)
	{
		for (int y = 1; y <= m; y++)
		{
			if (inArr[x][y] != '*')
			{
				for (int k = 0; k < 8; k++)
				{
					int iy = y + dy[k], ix = x + dx[k];
					if (iy >= 0 && iy <= m + 1 && ix >= 0 && ix <= n + 1 &&
						inArr[ix][iy] == '*')
					{
						count++;
					}
				}
				result[x][y] = count;
			}
			else
			{
				result[x][y] = -1;
			}
			count = 0;
		}
	}
	
	
	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = 1; j <= m ; j++)
		{
			if (result[i][j] == -1)
			{
				output << '*';
			}
			else
			{
				output << result[i][j];
			}
			
		}
		output << "\n";
	}

    return 0;
}

