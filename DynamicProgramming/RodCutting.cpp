#include <iostream>
#include <vector>

#define MAX 2147483647

using namespace::std;

int CutRod(const vector<int> &p, int n);
int MemoizedCutRod(const vector<int> &p, int n);
int MemoizedCutRodAux(const vector<int> &p, int n, vector<int> &r);
int BottomUpCutRod(const vector<int> &p, int n);

int main()
{
	vector<int> a{1, 5, 8, 9, 10, 17, 17, 20, 24, 30, 60, 10, 20, 30 , 50 , 64, 28, 34, 61};
	
	for (unsigned int i = 0; i != a.size() + 1; ++i)
	{
		cout << BottomUpCutRod(a, i) << '\n';
	}
	
	return 0;
}

int CutRod(const vector<int> &p, int n)
{
	if (n == 0)
	{
		return 0;
	}
	
	int q = -MAX;
	
	for (int i = 0; i != n; ++i)
	{
		q = q > (p[i] + CutRod(p, n - i - 1)) ? q : (p[i] + CutRod(p, n - i - 1));
	}
	
	return q;
}

int MemoizedCutRod(const vector<int> &p, int n)
{
	vector<int> r(n + 1, -MAX);
	
	return MemoizedCutRodAux(p, n, r);
}

int MemoizedCutRodAux(const vector<int> &p, int n, vector<int> &r)
{
	if (r[n] >= 0)
	{
		return r[n];
	}
	
	int q = 0;
	
	if (n == 0)
	{
		q = 0;
	}
	else
	{
		q = -MAX;
		
		for (int i = 0; i != n; ++i)
		{
			q = q > (p[i] + MemoizedCutRodAux(p, n - i - 1, r)) ? q : (p[i] + MemoizedCutRodAux(p, n - i - 1, r));
		}
	}
	
	r[n] = q;
	
	return q;
}

int BottomUpCutRod(const vector<int> &p, int n)
{
	vector<int> r(n + 1, 0);
	
	for (int j = 1; j != n + 1; ++j)
	{
		int q = -MAX;
		
		for (int i = 0; i != j; ++i)
		{
			q = q > (p[i] + r[j - i - 1]) ? q : (p[i] + r[j - i - 1]);
		}
		
		r[j] = q;
	}
	
	return r[n];
}
