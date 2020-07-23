#include <iostream>
#include <functional>
#include <memory>

enum type {less, greater};

template <typename T, type e>
void mergeSort(T arr[], int n) {
	std::function<bool(T, T)> predicate;

	switch (e) 
	{
		case greater:
			predicate = [](T x, T y) {return x < y ? true : false; };
		break;
		case less:
			predicate = [](T x, T y) {return x > y ? true : false; };
		break;
	}

	if (n > 1)
	{
		int const left_size = n / 2;
		int const right_size = n - left_size;

		mergeSort<T, e>(&arr[0], left_size);
		mergeSort<T, e>(&arr[left_size], right_size);

		int lidx = 0, ridx = left_size, idx = 0;
		std::unique_ptr<T[]> tmp_arr(new T[n]);

		while (lidx < left_size || ridx < n) {
			if (predicate(arr[lidx], arr[ridx])) {
				tmp_arr[idx++] = std::move(arr[lidx]);
				lidx++;
			}
			else {
				tmp_arr[idx++] = std::move(arr[ridx]);
				ridx++;
			}

			if (lidx == left_size) {
				std::copy(std::make_move_iterator(&arr[ridx]),
					std::make_move_iterator(&arr[n]),
					&tmp_arr[idx]);
				break;
			}
			if (ridx == n)
			{
				std::copy(std::make_move_iterator(&arr[lidx]),
					std::make_move_iterator(&arr[left_size]),
					&tmp_arr[idx]);
				break;
			}
		}
		std::copy(&tmp_arr[0], &tmp_arr[n], arr);
	}

	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << ", ";
	}
	std::cout << std::endl;
}

int main()
{
	{
		int arr[] = { 41, 58, 32, 64, 85, 73, 20 };
		mergeSort<int, greater>(arr, 7);
		std::cout << std::endl;
	}
	{
		int arr[] = { 35, 58, 32, 45, 85, 73, 201 };
		mergeSort<int, greater>(arr, 7);
		std::cout << std::endl;
	}
	{
		int arr[] = { 41, 58, 32, 64, 85, 73, 20 };
		mergeSort<int, less>(arr, 7);
		std::cout << std::endl;
	}
	{
		int arr[] = { 35, 58, 32, 45, 85, 73, 120 };
		mergeSort<int, less>(arr, 7);
		std::cout << std::endl;
	}
}

