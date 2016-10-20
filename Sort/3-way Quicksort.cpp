#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <typeinfo>
#include <map>
#include <random>
#include <Windows.h>

using namespace::std;

template <typename T>
class Sort
{
public:
	Sort() = default;
	Sort(initializer_list<T> il) : elements(il) {}
	Sort(vector<T> &vec) : elements(vec) {}
	void qsort1(int A, int B);
	void qsort2(int A, int B);
	void qsort3(int A, int B);

	vector<T> elements;
};

template <typename T>
void presentation(Sort<T> &A);
void test(uniform_int_distribution<int> &u);

map<decltype(typeid(int).name()), std::string> type{{typeid(int).name(), "INT"}, {typeid(double).name(), "DOUBLE"}, {typeid(char).name(), "CHAR"},
        {typeid(std::string).name(), "STRING"}};

int main()
{

    uniform_int_distribution<int> u1(0, 50);
    uniform_int_distribution<int> u2(0, 5000);

    test(u1);
    cout << '\n';

    test(u2);

	return 0;
}

template <typename T>
void Sort<T>::qsort1(int A, int B)
{
    if (A < B)
    {
        auto x = elements[B];
        auto i = A - 1;

        for (auto j = A; j != B; ++j)
        {
            if (elements[j] <= x)
            {
                ++i;

                auto tmp = elements[i];
                elements[i] = elements[j];
                elements[j] = tmp;
            }
        }

        auto tmp = elements[i+1];
        elements[i+1] = elements[B];
        elements[B] = tmp;

        qsort1(A, i);
        qsort1(i + 2, B);
    }
}

template <typename T>
void Sort<T>::qsort2(int A, int B)
{
    if (A < B)
    {
        auto x = elements.at(A);
        auto i = A - 1;
        auto j = B + 1;

        while (true)
        {
            do
            {
                --j;
            }while (elements[j] > x);

            do
            {
                ++i;
            }while (elements[i] < x);

            if (i < j)
            {
                auto tmp = elements[i];
                elements[i] = elements[j];
                elements[j] = tmp;
            }
            else
            {
                break;
            }
        }

        qsort2(A, j - 1);
        qsort2(j + 1, B);

    }
}

template <typename T>
void Sort<T>::qsort3(int A, int B)
{
	if (A < B)
	{
		auto a = elements.begin() + A;
		auto b = a;
		auto x = *a;
		auto c = elements.begin() + B;
		auto d = c;

		for (; ;)
		{
			while (b <= c && *b <= x)
			{
				if (*b == x)
				{
					auto tmp = *b;
					*b = *a;
					*a = tmp;

					++a;
				}

				++b;
			}

			while (b <= c && *c >= x)
			{
				if (*c == x)
				{
					auto tmp = *c;
					*c = *d;
					*d = tmp;

					--d;
				}

				--c;
			}

			if (b > c)
			{
				break;
			}

			auto tmp = *b;
			*b = *c;
			*c = tmp;

			++b;
			--c;
		}

		auto s = (a - elements.begin() - A) < (b - a) ? (a - elements.begin() - A) : (b - a);

		for (auto l = elements.begin() + A, h = b - s; s != 0; --s)
		{
			auto tmp = *l;
			*l = *h;
			*h = tmp;

			++l;
			++h;
		}

		s = (d - c) < (elements.begin() + B - d) ? (d - c) : (elements.begin() + B - d);

		for (auto l = b, h = elements.begin() + B - s + 1; s != 0; --s)
		{
			auto tmp = *l;
			*l = *h;
			*h = tmp;

			++l;
			++h;
		}

		qsort3(A, A + (b - a));
		qsort3(A + (elements.begin() + B - d) + (b - elements.begin() - A), B);
	}
}

template <typename T>
void presentation(Sort<T> &A)
{
    auto B(A);
    auto C(A);

    LARGE_INTEGER stime;
    LARGE_INTEGER ftime;
    LARGE_INTEGER frequency;
    cout << "The number of the elements to sort: " << A.elements.size() << '\n';

    QueryPerformanceFrequency(&frequency);

    QueryPerformanceCounter(&stime);
    A.qsort1(0, A.elements.size() - 1);
    QueryPerformanceCounter(&ftime);
    cout << "The run time of the Quicksort with the random " << type.find(typeid(T).name())->second << " input: " << ((ftime.QuadPart - stime.QuadPart) * 1000) / frequency.QuadPart <<  "ms\n";


    QueryPerformanceCounter(&stime);
    B.qsort2(0, B.elements.size() - 1);
    QueryPerformanceCounter(&ftime);
    cout << "The run time of the Hoare's Quicksort with the random " << type.find(typeid(T).name())->second << " input: " << ((ftime.QuadPart - stime.QuadPart) * 1000) / frequency.QuadPart <<  "ms\n";

    QueryPerformanceCounter(&stime);
    C.qsort3(0, C.elements.size() - 1);
    QueryPerformanceCounter(&ftime);
    cout << "The run time of the New Quicksort with the random " << type.find(typeid(T).name())->second << " input: " << ((ftime.QuadPart - stime.QuadPart) * 1000) / frequency.QuadPart <<  "ms\n";
}
void test(uniform_int_distribution<int> &u)
{
    uniform_real_distribution<double> d(0, 1000.0);
    default_random_engine e;

    cout << "The range of integer-like type input is:" << u.min() << '~' << u.max() << '\n';
	Sort<int> A;
	Sort<double> B;
	Sort<char> C;
	Sort<string> D;

	for (int i = 0; i != 30000; ++i)
    {
        A.elements.push_back(u(e));
    }

	presentation(A);
	cout << "\n\n";

	for (int i = 0; i != 30000; ++i)
    {
        B.elements.push_back(d(e));
    }

    presentation(B);
    cout << "\n\n";

    for (int i = 0; i != 30000; ++i)
    {
        C.elements.push_back(u(e) % 127);
    }

    presentation(C);
    cout << "\n\n";

    for (int i = 0; i != 30000; ++i)
    {
        D.elements.push_back(to_string(u(e)));
    }

    presentation(D);
    cout << "\n\n";

}
