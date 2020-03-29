#include <iostream>
#include "math.h"

int main() {
	int x, y;
	std::cout << "Please input two integers: " << std::endl;
	std::cin >> x >> y;

	int *x_ptr = &x;
	int *y_ptr = &y;

	int result = Add(x_ptr, y_ptr);
	std::cout << "Sum is: " << result << std::endl;

	Swap(x_ptr, y_ptr);

	int a = 10;
	int result_fac = 1;

	int *a_ptr = &a;
	int *result_fac_ptr = &result_fac;

	Factorial(a_ptr, result_fac_ptr);
	std::cout << "Factorial result is: " << *result_fac_ptr << std::endl;

	return 0;
}
