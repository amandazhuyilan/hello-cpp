#include <iostream>

void Add(int a, int b, int &result) {
	result = a + b;
}

void Swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void Print(const int &ref) {
	std::cout << ref << std::endl;
}

int main() {
	int a = 1;
	int b = 2;
	
	int &ref_test = a;
	int *ref_test_ptr = &ref_test;

	std::cout << "&ref_test: " << &ref_test << std::endl;
	std::cout << "ref_test_prt " << ref_test_ptr << std::endl;
	std::cout << "*ref_test_ptr " << *ref_test_ptr << std::endl;

	//int &add_result = a;
	//Add(a, b, add_result);
	//std::cout << add_result << std::endl;
	
	//Swap(a, b);
	//std::cout << "a: " << a << " b: " << b << std::endl;
	
	//Print(100);
	return 0;
}

