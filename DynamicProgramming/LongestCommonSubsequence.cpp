#include <iostream>
#include <string>
#include <vector>

using namespace::std;

vector<vector<int>> LCS_Length(const string &X, const string &Y);
void Print_LCS(const vector<vector<int>> &c, const string &X, int i, int j);

int main()
{
	string A{ "ABCBDAB" };
	string B{ "BDCABA" };

	Print_LCS(LCS_Length(A, B), A, A.size(), B.size());

	return 0;
}

vector<vector<int>> LCS_Length(const string &X, const string &Y)
{
	auto m = X.size();
	auto n = Y.size();

	vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));

	for (unsigned i = 1; i != m + 1; ++i)
	{
		for (unsigned j = 1; j != n + 1; ++j)
		{
			if (X[i - 1] == Y[j - 1])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
			}
			else
			{
				c[i][j] = c[i][j - 1];
			}
		}
	}

	return c;
}

void Print_LCS(const vector<vector<int>> &c, const string &X, int i, int j)
{
	if (i == 0 || j == 0)
	{
		return;
	}

	if (c[i][j] == c[i - 1][j - 1] + 1 && c[i][j - 1] < c[i][j] && c[i - 1][j] < c[i][j])
	{
		Print_LCS(c, X, i - 1, j - 1);
		cout << X[i - 1] << ' ';
	}
	else if (c[i][j] == c[i - 1][j])
	{
		Print_LCS(c, X, i - 1, j);
	}
	else
	{
		Print_LCS(c, X, i, j - 1);
	}
}
