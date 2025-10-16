#include <stdio.h>
#define bubble_sort

void print_arr(int* arr, int n){
	for (size_t i = 0; i < n; i++)
	{
		printf("%2d ", arr[i]);
	}
}

void swap(int* a, int* b){
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

#ifdef bubble_sort
int main(int argc, char const *argv[])
{
	int n = 10;
	int arr[] = {8,2,1,6,7,0,3,5,4,9};

	printf("Array desordenado: ");
	print_arr(arr, n);

	for (int i = 0; i < n-1; i++)
	{
		for (int j = n-1; j > i; j--)
		{
			if (arr[j] < arr[j-1])
			{
				swap(&arr[j], &arr[j-1]);
			}
		}
	}
	
	printf("\nArray ordenado:    ");
	print_arr(arr, n);

	return 0;
}
#endif

#ifdef insertion_sort
int main(int argc, char const *argv[])
{
	int n = 10;
	int arr[] = {8,2,1,6,7,0,3,5,4,9};

	printf("Array desordenado: ");
	print_arr(arr, n);

	for (size_t i = 1; i < n-1; i++)
	{
		int key = arr[i];
		int j = i-1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j+1] = arr[j];
			j = j-1;
			arr[j+1] = key;
		}
	}

	printf("\nArray ordenado:    ");
	print_arr(arr, n);

	return 0;
}
#endif

#ifdef selection_sort
int main(int argc, char const *argv[])
{
	int n = 10;
	int arr[] = {8,2,1,6,7,0,3,5,4,9};

	printf("Array desordenado: ");
	print_arr(arr, n);

	for (size_t i = 0; i < n-2; i++)
	{
		int min_idx = i;
		for (size_t j = i+1; j < n-1; j++)
		{
			if (arr[j] < arr[min_idx])
			{
				min_idx = j;
			}
		}
		if (arr[i] != arr[min_idx])
		{
			swap(&arr[i], &arr[min_idx]);
		}
	}

	printf("\nArray ordenado:    ");
	print_arr(arr, n);

	return 0;
}
#endif