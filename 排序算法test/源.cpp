#include <iostream>
#include <time.h>
#define  LENGTH 10
using namespace std;

void print_which_sort(const int i);
void init_array(int* array);//初始化数组, 初始的范围为1~1000
void show_array(int* array);//打印数组
double random(const double start, const double end);//随机数, 来初始化数组
void shell_sort(int* array, const int* dlta, const int dlta_count);//希尔排序
void shell_insert(int* array, const int dk);
void bubble_sort(int* array);//冒泡
void insert_sort(int* array);//直接插入
void binary_insertion_sort(int* array);//折半插入
int quick_sort_partition(int* array, int low, int high);
void quick_sort(int* array, int low, int high);
void quick_sort(int* array);//快速排序
int select_min_key(int* array, const int i);//找出最小的下标
void select_sort(int* array);//简单选择排序
void heap_adjust(int* array, int s, int m);
void heap_sort(int* array);//堆排序
int main()
{
	clock_t start = 0, finish = 0;
	//int array[LENGTH] = { 4, 9, 8, 3, 6, 7, 5, 0, 2, 1 };
	int array[LENGTH];
	int dlta[] = { 1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905 };//希尔排序增量

	//OK shell_sort(array, dlta, 10);
	//OK bubble_sort(array);
	//OK insert_sort(array);
	//OK binary_insertion_sort(array);
	//OK quick_sort(array);
	//OK select_sort(array);
	//show_array(array);
	for (int i = 6; i < 7; ++i)
	{
		init_array(array);
		show_array(array);
		print_which_sort(i);
		switch (i)
		{
		case 0:
			start = clock();
			bubble_sort(array);
			finish = clock();
			break;
		case 1:
			start = clock();
			insert_sort(array);
			finish = clock();
			break;
		case 2:
			start = clock();
			binary_insertion_sort(array);
			finish = clock();
			break;
		case 3:
			start = clock();
			quick_sort(array);
			finish = clock();
			break;
		case 4:
			start = clock();
			select_sort(array);
			finish = clock();
			break;
		case 5:
			start = clock();
			shell_sort(array, dlta, 10);
			finish = clock();
			break;
		case 6:
			start = clock();
			heap_sort(array);
			finish = clock();
			break;
		default:
			std::cout << "There is no such choice..." << endl;
			break;
		}
		std::cout << "cost time: " << double(finish - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
		start = 0; finish = 0;
		show_array(array);
		std::cout << endl << endl << endl;
	}

	std::cout << "Please input any key to exit..." << endl;
	getchar();
	getchar();
	return 0;
}

void print_which_sort(const int i)
{
	switch (i)
	{
	case 0:
		std::cout << "bubble_sort----------------" << endl;
		break;
	case 1:
		std::cout << "insert_sort-------------------" << endl;
		break;
	case 2:
		std::cout << "binary_insertion_sort------------------" << endl;
		break;
	case 3:
		std::cout << "quick_sort-------------------------" << endl;
		break;
	case 4:
		std::cout << "select_sort------------------" << endl;
		break;
	case 5:
		std::cout << "shell_sort------------------" << endl;
		break;
	case 6:
		std::cout << "heap_sort------------------" << endl;
		break;
	default:
		std::cout << "There is no such choice..." << endl;
		break;
	}
}
void init_array(int* array)
{
	srand(unsigned(time(nullptr)));//时间种
	for (int i = 0; i < LENGTH; ++i)
	{
		array[i] = int(random(0, 1000));
	}
}
double random(const double start,const double end)
{
	
	return start + (end - start)*rand() / (RAND_MAX + 1.0);
}
void show_array(int* array)
{
	for (auto i = 0; i < LENGTH; i++)
	{
		std::cout << array[i] << "  ";
	}
	std::cout << endl;
}

void shell_sort(int* array, const int* dlta, const int dlta_count)
{
	for (int i = 0; i < dlta_count; ++i)
	{
		shell_insert(array, dlta[i]);
	}
}
void shell_insert(int* array, const int dk)
{
	auto temp = 0, j = 0;
	for(auto i = dk + 1; i < LENGTH; ++i)
	{
		if (array[i] < array[i-dk])
		{
			array[0] = array[i];
			for ( j = i - dk; j > 0 && (array[0] < array[j]); j-=dk)
				array[j + dk] = array[j];
			array[j + dk] = array[0];
		}
	}
}

void bubble_sort(int* array)
{
	int temp = 0;
	for (int j = 0; j < LENGTH - 1; ++j)
		for (int i = 0; i < LENGTH - 1 - j; ++i)
			if (array[i]>array[i+1])
			{
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
}

void insert_sort(int* array)
{
	int j = 0, temp = 0;
	for (int i = 2; i < LENGTH; ++i)
		if (array[i]<array[i-1])
		{
			temp = array[i];
			array[i] = array[i - 1];
			for (j = i-2; temp < array[j]; --j)
				array[j + 1] = array[j];
			array[j + 1] = temp;
		}
}

void binary_insertion_sort(int* array)
{
	int temp = 0, low = 0, high = 0, middle = 0;
	for (int i = 2; i < LENGTH; ++i)
	{
		temp = array[i];
		low = 1; high = i - 1;
		while (low<=high)
		{
			middle = (low + high) / 2;
			if (temp < array[middle])
			{
				high = middle - 1;
			}
			else
				low = middle + 1;
		}
		for (int j = i - 1; j >=high + 1; --j)
		{
			array[j + 1] = array[j];
		}
		array[high + 1] = temp;
	}
}

int quick_sort_partition(int* array, int low, int high)
{
	const auto pivot_key = array[low];
	while (low<high)
	{
		while (low<high&&(array[high]>=pivot_key))
		{
			--high;
		}
		array[low] = array[high];
		while (low<high&&(array[low]<=pivot_key))
		{
			++low;
		}
		array[high] = array[low];
	}
	array[low] = pivot_key;
	return low;
}
void quick_sort(int* array,const int low,const int high)
{
	if(low < high)
	{
		const auto pivotloc = quick_sort_partition(array, low, high);
		quick_sort(array, low, pivotloc - 1);
		quick_sort(array, pivotloc + 1, high);
	}
}
void quick_sort(int* array)
{
	//此处为需要排序的数组的在计算机内部的地址"排头"和"结尾"
	quick_sort(array, 0, LENGTH - 1);
}

void select_sort(int* array)
{
	auto j = 0, temp = 0;
	for (auto i = 0; i < LENGTH; ++i)
	{
		j = select_min_key(array, i);
		if(i != j)
		{
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
	}
}
int select_min_key(int* array,const int i)
{
	auto min = i;//默认第一个最小
	for (auto j = i; j < LENGTH; ++j)
	{
		if (array[min] < array[j])
			continue;
		else
			min = j;
	}
	return min;
}

void heap_sort(int* array)
{
	auto temp = 0;
	for (int i = LENGTH/2; i > 0 ; --i)
	{
		heap_adjust(array, i, LENGTH);
	}
	for (int i = LENGTH; i > 1; --i)
	{
		temp = array[1];
		array[1] = array[i];
		array[i] = temp;
		heap_adjust(array, 1, i - 1);
	}
}
void heap_adjust(int* array, int s, int m)
{
	auto rc = array[s];
	for (auto i = 2*s; i <= m; i*=2)
	{
		if (i < m && (array[i] < array[i + 1]))
			++i;
		if (!(rc < array[i]))
			break;
		array[s] = array[i];
		s = i;
	}
	array[s] = rc;
}