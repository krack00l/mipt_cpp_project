#include <iostream>
#include <algorithm>
#include <fstream>


#define INF 101

using namespace std;

void printMatrix(int** matrix, int numberOfVert)
{
	for (int i = 0; i < numberOfVert; i++)
	{
		for (int j = 0; j < numberOfVert; j++)
		{
			if (matrix[i][j] == INF)
			{
				cout << "INF" << " ";
			}
			else
			{
				cout << matrix[i][j] << " ";
			}
		}
		cout << endl;
	}
}


void FloydWarshal(int** matrix, int numberOfVert)
{
	for (int k = 0; k < numberOfVert; k++)
	{
		for (int i = 0; i < numberOfVert; i++)
		{
			for (int j = 0; j < numberOfVert; j++)
			{
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
			}
		}
	}

	return;
}


int main(int argc, char** argv)
{
	ifstream file("matrix.txt"); //read data from file
	int numberOfVert;
	file >> numberOfVert;
	cout << numberOfVert << endl;


	int** matrix = (int**)malloc(sizeof(int) * numberOfVert);
	for (int i = 0; i < numberOfVert; i++)
	{
		matrix[i] = (int*)malloc(sizeof(int) * numberOfVert);
	}

	for (int i = 0; i < numberOfVert; i++)
	{
		for (int j = 0; j < numberOfVert; j++)
		{
			file >> matrix[i][j];
		}
	}
	file.close();


	cout << "Old matrix" << endl;
	printMatrix(matrix, numberOfVert);

	FloydWarshal(matrix, numberOfVert);

	cout << "New matrix" << endl;

	printMatrix(matrix, numberOfVert);

	return 0;
}