#include <iostream>
#include <memory>

using namespace::std;


class HeapData
{
public:
	HeapData();
	~HeapData();
	
	int *A = nullptr;
	int length = 0;
};

int Parent(int i);
int Left(int i);
int Right(int i);
void MaxHeapify(HeapData &Sample, int i);
void BuildMaxHeap(HeapData &Sample);
void Heapsort(HeapData &Sample);

int main()
{
	HeapData Sample;
	
	Heapsort(Sample);
	
	for (int i = 1; i != Sample.length+1; ++i)
	{
		cout << Sample.A[i] << " ";
	}
	
	cout << endl;
	
	return 0;
}

HeapData::HeapData()
{
	cin >> length;
	
	A = new int[length+1];
	
	for (auto i = 1; i != length+1; ++i)
	{
		cin >> A[i];
	}
	
	A[0] = length;
}

HeapData::~HeapData()
{
	delete []A;
}

int Parent(int i)
{
	return i / 2;
}

int Left(int i)
{
	return 2 * i;
}

int Right(int i)
{
	return 2*i + 1;
}

void MaxHeapify(HeapData &Sample, int i)
{
	auto l = Left(i);
	auto r = Right(i);
	int largest = 0;
	
	if (l <= Sample.A[0] && Sample.A[l] > Sample.A[i])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}	
	
	if (r <= Sample.A[0] && Sample.A[r] > Sample.A[largest])
	{
		largest = r;
	}	
	
	if (largest != i)
	{
		auto tmp = Sample.A[i];
		Sample.A[i] = Sample.A[largest];
		Sample.A[largest] = tmp;
		
		MaxHeapify(Sample, largest);
	}	
}

void BuildMaxHeap(HeapData &Sample)
{
	for (auto i = Sample.A[0]/2; i != 0; --i)
	{
		MaxHeapify(Sample, i);
	}
}

void Heapsort(HeapData &Sample)
{
	BuildMaxHeap(Sample);
	
	for (auto i = Sample.length; i != 1; --i)
	{
		auto tmp = Sample.A[1];
		Sample.A[1] = Sample.A[i];
		Sample.A[i] = tmp;
		
		Sample.A[0] -= 1;
		
		MaxHeapify(Sample, 1);	
	}
}
