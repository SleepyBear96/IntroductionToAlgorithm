#include <iostream>
#include <vector>

#define MAX 2147483647

using namespace::std;

class Ans
{
public:
    Ans() = default;

    vector<vector<double>> e;
    vector<vector<int>> root;
};

Ans OptimalBST(const vector<double> &p, const vector<double> &q, int n);

int main()
{
    vector<double> p{0.00, 0.15, 0.10, 0.05, 0.10, 0.20};
    vector<double> q{0.05, 0.10, 0.05, 0.05, 0.05, 0.10};

    auto t = OptimalBST(p, q, p.size());

    for (int i = 0; i != p.size() + 1; ++i)
    {
        for (int j = 0; j != p.size(); ++j)
        {
            cout << t.e[i][j] << ' ';
        }

        cout << '\n';
    }

    for (int i = 0; i != p.size(); ++i)
    {
        for (int j = 0; j != p.size(); ++j)
        {
            cout << t.root[i][j] << ' ';
        }

        cout << '\n';
    }

    return 0;

}

Ans OptimalBST(const vector<double> &p, const vector<double> &q, int n)
{
    vector<vector<double>> e(n + 2, vector<double> (n + 1, 0.0));
    vector<vector<double>> w(n + 2, vector<double> (n + 1, 0.0));
    vector<vector<int>> root(n + 1, vector<int> (n + 1, 0));

    for (int i = 1; i != n + 2; ++i)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int l = 1; l != n + 1; ++l)
    {
        for (int i = 1; i != n - l + 2; ++i)
        {
            auto j = i + l - 1;

            e[i][j] = MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r != j + 1; ++r)
            {
                auto t = e[i][r - 1] + e[r + 1][j] + w[i][j];

                if (t < e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    return {e, root};
}
