#include "GrafDisplay.h"
#include <fstream>

int main()
{
	CGrafDisplay display;
	int **Graf;
	int *Label;
	int *LIFO;
	int N(0), M(0);
	int Start(0), k, p, m;
	std::ifstream input("graf.txt");
	input >> N >> Start;
	Graf = new int *[N];
	for (int i(0); i < N; i++)
	{
		Graf[i] = new int [N];
	}
	for (int i(0); i < N; i++)
		for (int j(0); j < N; j++)
			Graf[i][j] = 0;
	int i(0), j(0);
	while (!input.eof())
	{
		input >> i >> j;
		Graf[i][j] = 1;
		Graf[j][i] = 1;
		M++;
	}
	Label = new int [N];
	LIFO = new int [N];
	for (i = 0; i < N; i++)
	{
		LIFO[i] = 0;
		Label[i] = 0;
	}
	LIFO[0] = Start;
	Label[Start] = 1;
	k = 1;
	m = 1;
	while (k != 0)
	{
		p = 0;
		for (i = 0; i < N; i++)
		{
			if (Graf[LIFO[k -1]][i] == 1)
			{
				p = 1;
				break;
			}
		}
		if (p != 0)
		{
			if (Label[i] == 0)
			{
				LIFO[k] = i;
				m++;
				Label[i] = m;
				Graf[LIFO[k - 1]][i] = 2;
				Graf[i][LIFO[k - 1]] = 2;
				k++;
			}
			else
			{
				Graf[LIFO[k - 1]][i] = 3;
				Graf[i][LIFO[k - 1]] = 3;
			}
		}
		else k--;
	}



	for (int i = 0; i < N; i++)
	{
		std::cout << "Label[" << i << "] = " << Label[i] <<std::endl;
	}

	display.setGraf(Graf, N);
	//display.Draw();

	return 0;
}