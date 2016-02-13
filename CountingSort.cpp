#include <iostream>
#include <vector>

using namespace::std;

void CountingSort(const vector<int> &A, vector<int> &B, int k);

int main()
{
	vector<int> A{6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2};
	vector<int> B(A.size());
	
	CountingSort(A, B, 6);
	
	for (auto &i : B)
	{
		cout << i << ends;
	}
	
	cout << endl;
	
	return 0;
}

void CountingSort(const vector<int> &A, vector<int> &B, int k)
{
	vector<int> C(k+1);
	
	
	for (auto j = 0; j != A.end() - A.begin(); ++j)
	{
		C[A[j]] += 1;
	}
	//C[i] now contains the number of elements equal to i.
	
	
	for (int i = 1; i != k + 1; ++i)
	{
		C[i] += C[i-1];
	}
	//C[i] now contains the number of elements less than or equal to i.
	
	
	for (auto j = A.end() - A.begin() - 1; j != -1; --j)
	{
		B[C[A[j]]-1] = A[j];
		C[A[j]] -= 1;
	}
}
