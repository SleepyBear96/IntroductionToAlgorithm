#include <iostream>
#include <vector>
#include <string>

using namespace::std;

void RadixSort(vector<string> &A, vector<string> &B, int d);
void CountingSort(vector<string> &A, vector<string> &B, int k, int d);

int main()
{
	vector<string> A{"329", "457", "657", "839", "436", "720", "355"};
	vector<string> B(A.size());
	
	RadixSort(A, B, 3);
	
	for (auto &i : A)
	{
		cout << i << endl;
	}
	
	return 0;
}

void CountingSort(vector<string> &A, vector<string> &B, int k, int d)
{
	vector<int> C(k+1);
	
	
	for (auto j = 0; j != A.end() - A.begin(); ++j)
	{
		C[static_cast<int> (A[j][d] - '0')] += 1;
	}
	//C[i] now contains the number of elements equal to i.
	
	
	for (int i = 1; i != k + 1; ++i)
	{
		C[i] += C[i-1];
	}
	//C[i] now contains the number of elements less than or equal to i.
	
	
	for (auto j = A.end() - A.begin() - 1; j != -1; --j)
	{
		B[C[static_cast<int> (A[j][d] - '0')]-1] = A[j];
		C[static_cast<int> (A[j][d] - '0')] -= 1;
	}
	
	A.assign(B.begin(), B.end());
}

void RadixSort(vector<string> &A, vector<string> &B, int d)
{
	for (int i = d - 1; i != -1; --i)
	{
		CountingSort(A, B, 9, i);
	}
}
