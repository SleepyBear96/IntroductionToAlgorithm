#include <iostream>
#include <vector>
#include <cstdlib>

using namespace::std;

int Partition(vector<int> &A, int p, int r);
int RandomizedPartition(vector<int> &A, int p, int r);
void RandomizedQuicksort(vector<int> &A, int p, int r);

int main()
{
	vector<int> A{1, 3, 2, 4, 6, 9, 8};
	
	RandomizedQuicksort(A, 0, 6);
	
	for (auto &i : A)
	{
		cout << i << ends;
	}
	
	cout << endl;
	
	return 0;
}

int Partition(vector<int> &A, int p, int r)
{
	auto x = A[r];
	auto i = p - 1;
	
	for (auto j = p; j != r; ++j)
	{
		if (A[j] <= x)
		{
			++i;
			
			auto tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
		}
	}
	
	auto tmp = A[i+1];
	A[i+1] = A[r];
	A[r] = tmp;
	
	return i + 1;
}

int RandomizedPartition(vector<int> &A, int p, int r)
{
	auto i = rand()%(r - p) + p;
	
	auto tmp = A[i];
	A[i] = A[r];
	A[r] = tmp;
	
	return Partition(A, p, r);
}

void RandomizedQuicksort(vector<int> &A, int p, int r)
{
	if (p < r)
	{
		auto q = RandomizedPartition(A, p, r);
		
		RandomizedQuicksort(A, p, q - 1);
		RandomizedQuicksort(A, q + 1, r);
	}
}
