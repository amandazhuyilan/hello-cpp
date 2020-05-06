#include <iostream>
#include <cstring>

//int find_max(int x, int y) {
//	return x > y ? x : y;
//}

template<typename T>
T Max(T x, T y){
	return x > y ? x : y;
}

template<typename T>
T ArraySum(T arraySize, T *pArray) {
	T sum = 0;
	for (int i = 0; i < arraySize; i++) {
		sum = *pArray + sum;
		pArray++;
	}
	return sum;
}

// explicit initialization
template char Max(char x, char y);
// explicit specialization
template<> const char * Max<const char *>(const char * x, const char *y) {
		return strcmp(x,y) > 0 ? x : y;
}

// non-type template arguments
template <typename T, int size>
T Sum(T (&arr)[size]) {
	T sum = 0;
	for (int i = 0; i < size; i++) {
		sum = sum + arr[i];
	}
	return sum;
}

int main() {
	int x = 1, y = 2;
	std::cout << "Max: " << Max(1,2) << std::endl;
	int arr[3] = {1, 2, 4};
	std::cout << "ArraySum: " << ArraySum(3, &arr[0]) << std::endl;

	const char *a = "a", *b = "b";
	std::cout << "char Max: " << Max(a, b) << std::endl;

	int int_array[3] = {1, 2, 3};
	std::cout << "Sum: " << Sum(int_array) << std::endl;
}
