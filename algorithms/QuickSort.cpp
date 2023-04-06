#include <iostream>
using namespace std;

int partition(int list[], int start, int pivot)
{
	int i = start;
	while(i < pivot)
	{
		if(list[i] > list[pivot] && i == pivot-1)
		{
			swap(list[i], list[pivot]);
			pivot--;
		}
		
		else if(list[i] > list[pivot])
		{
			swap(list[pivot - 1], list[pivot]);
			swap(list[i], list[pivot]);
			pivot--;
		}
		
		else i++;
	}
	return pivot;
}

void quickSort(int list[], int start, int end)
{
	if(start < end)
	{
		int pivot = partition(list, start, end);
		
		quickSort(list, start, pivot - 1);
		quickSort(list, pivot + 1, end);
	}
}

int main()
{
	int* list;
	int n = 0;
	cin >> n;
	list = new int[n];
	for (int i = 0; i < n; i++)
		cin >> list[i];
	cout<<"Input array ...\n";
	for (int i = 0; i < 6; i++)
	{
	   cout<<list[i]<<"\t";
	}
	
	quickSort(list, 0, 6);
	
	cout<<"\n\nSorted array ... \n";
	for (int i = 0; i < 6; i++)
	{
	   cout<<list[i]<<"\t";
	}
	
	return 0;
}