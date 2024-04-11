#include <iostream>
#include <vector>

using namespace std;


template <typename T>
void max_heapify(vector<T>& heap, size_t index, size_t size)
{
	size_t left = (index * 2) + 1;
	size_t right = (index * 2) + 2;

	size_t biggest = index;

	if (left < size && heap[left] > heap[biggest])
		biggest = left;

	if (right < size && heap[right] > heap[biggest])
		biggest = right;

	if (biggest != index)
	{
		std::swap(heap[biggest], heap[index]);

		max_heapify(heap, biggest, size);
	}
}


template <typename T>
void build_max_heap(vector<T>& heap)
{
	for (int i = heap.size() / 2; i >= 0; i--)
	{
		max_heapify(heap, i, heap.size());
	}
}

template <typename T>
void heap_sort(vector<T>& heap)
{
	build_max_heap(heap);

	for (int i = heap.size() - 1; i > 0; i--)
	{
		std::swap(heap[0], heap[i]);
		max_heapify(heap, 0, i);
	}
}


int main()
{
	vector<int> vec = {3, 1, 0, -9, 8, 666, 2, 7};

	heap_sort(vec);

	for (auto i : vec)
		cout << i << "  ";
	cout << endl;

	return 0;
}
