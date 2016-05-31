#include <iostream>
#include <vector>
#include <stdexcept>

#define MAX 2147483647

using namespace::std;

class Matrix
{
public:
	Matrix() = default;
	unsigned int columns;
	unsigned int rows;
	vector<vector<int>> data;
};

class Two
{
public:
	Two() = default;
	vector<vector<int>> m;
	vector<vector<int>> s;
};

Matrix MatrixMultiply(const Matrix &A, const Matrix &B);
Two MatrixChainOrder(const vector<Matrix> &p);
void PrintOptimalParens(const vector<vector<int>> &s, int i, int j);

int main()
{
	auto m = MatrixChainOrder({ {35, 30}, {15, 35}, {5, 15}, {10, 5}, {20, 10}, {25, 20} });

	PrintOptimalParens(m.s, 0, 5);

	return 0;
}


Matrix MatrixMultiply(const Matrix &A, const Matrix &B)
{
	if (A.columns != B.rows)
	{
		throw runtime_error("incompatible dimensions");
	}
	else
	{
		Matrix C;
		C.rows = A.rows;
		C.columns = B.columns;

		for (unsigned int i = 0; i != A.rows; ++i)
		{
			C.data.push_back(vector<int>());

			for (unsigned int j = 0; j != B.columns; ++j)
			{
				C.data[i].push_back(0);

				for (unsigned int k = 0; k != A.columns; ++k)
				{
					C.data[i][j] += A.data[i][k] * B.data[k][j];
				}
			}
		}

		return C;
	}
}

Two MatrixChainOrder(const vector<Matrix> &p)
{
	auto n = p.size();

	vector<vector<int>> m(n);
	vector<vector<int>> s(n);

	for (int i = 0; i != n; ++i)
	{
		for (int j = 0; j != n; ++j)
		{
			m[i].push_back(0);
			s[i].push_back(0);
		}
	}

	for (int l = 2; l != n + 1; ++l)
	{
		for (int i = 0; i != n - l + 1; ++i)
		{
			int q = 0;
			auto j = i + l - 1;

			m[i][j] = MAX;

			for (auto k = i; k != j; ++k)
			{
				q = m[i][k] + m[k+1][j] + (p[i].rows * p[k].columns * p[j].columns);

				if (q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}

	return {m, s};
}

void PrintOptimalParens(const vector<vector<int>> &s, int i, int j)
{
	if (i == j)
	{
		cout << 'A' << i << ' ';
	}
	else
	{
		cout << '(';
		PrintOptimalParens(s, i, s[i][j]);
		PrintOptimalParens(s, s[i][j] + 1, j);
		cout << ')';
	}
}
