#include <iostream>

int Add(int *x, int *y) {
	int sum = *x + *y;
	return sum;
}

void Swap(int *a, int *b) {
	std::cout << "original: " << *a << " , " << *b << std::endl;
	int i = *b;
	*b = *a;
	*a = i;
	std::cout << "after swap: " << *a << " , " << *b << std::endl;
}

void Factorial(int *a, int *result_ptr) {
	int result = 1;
	
	for (int i = 1; i <= *a; i++) {
		result = i * result;
	}
	*result_ptr = result;
}
