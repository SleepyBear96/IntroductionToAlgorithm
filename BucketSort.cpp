#include <iostream>
#include <vector>
#include <list>

using namespace::std;

class Link
{
public:
	list<double> data;
};

void BucketSort(vector<double> &A);

int main()
{
	vector<double> A{0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
	
	BucketSort(A);
	
	return 0;
}


void BucketSort(vector<double> &A)
{
	Link B[A.size()];
	
	auto n = A.size();
	
	for (unsigned int i = 0; i != n; ++i)
	{
		B[static_cast<int> (n*A[i])].data.push_back(A[i]);
	}
	
	for (unsigned int i = 0; i != n; ++i)
	{
		for (auto j = ++(B[i].data.begin()); j != B[i].data.end(); ++++j)
		{
			auto key = *j;
			auto k = --j;
			
			for (; k != --B[i].data.begin() && *k > key; --k)
			{
				auto tmp = *(--k);  
				*(++k) = tmp;		
			}
			
			*(++k) = key;
		}
	}
	
	for (unsigned int i = 0; i != n; ++i)
	{
		if (!B[i].data.empty())
		{
			for (auto &j : B[i].data)
			{
				cout << j << " ";
			}
		}
	}
	
	cout << endl;
}
