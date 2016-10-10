#include <iostream>
#include <vector>

using namespace::std;

class Greedy
{
public:
    Greedy() = default;

    unsigned k;
    unsigned s;
    unsigned f;
};

vector<Greedy> RecursiveActivitySelector(const vector<Greedy> &A, size_t k, size_t n);
vector<Greedy> GreedyActivitySelector(const vector<Greedy> &A);

int main()
{
    vector<Greedy> sample{{0, 0, 0}, {1, 1, 4}, {2, 3, 5}, {3, 0, 6}, {4, 5, 7}, {5, 3, 9}, {6, 5, 9}, {7, 6, 10}, {8, 8, 11},
                    {9, 8, 12}, {10, 2, 14}, {11, 12, 16}};

    for (auto i : RecursiveActivitySelector(sample, 0, sample.size()))
    {
        cout << i.k << ' ';
    }

    cout << '\n';

    for (auto i : GreedyActivitySelector(sample))
    {
        cout << i.k << ' ';
    }

    cout << '\n';

    return 0;
}

vector<Greedy> RecursiveActivitySelector(const vector<Greedy> &A, size_t k, size_t n)
{
    auto m = k + 1;

    while (m < n && (A.begin() + m)->s < (A.begin() + k)->f)
    {
        ++m;
    }

    if (m < n)
    {
        vector<Greedy> Ans{A[m]};

        auto t = RecursiveActivitySelector(A, m, n);
        Ans.insert(Ans.end(), t.begin(), t.end());

        return Ans;
    }
    else
    {
        return vector<Greedy> ();
    }
}

vector<Greedy> GreedyActivitySelector(const vector<Greedy> &A)
{
    auto n = A.size();

    vector<Greedy> Ans{*(A.begin() + 1)};

    for (int i = 2, k = i - 1; i != n; ++i)
    {
        if ((A.begin() + i)->s >= (A.begin() + k)->f)
        {
            Ans.push_back(*(A.begin() + i));
            k = i;
        }
    }

    return Ans;
}
