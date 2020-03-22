#include <iostream>

int main() {
	int i = 5;
	int *ptr = &i;
	std::cout << "The address of i is: " << ptr << std::endl;
	std::cout << "Dereferencing pointer: " << *ptr << std::endl;
	*ptr = 10;

	std::cout << "Pointer new addess is: " << ptr << std::endl;
	std::cout << "The updated value of the pointer is: " << *ptr << std::endl;

	int *null_ptr = nullptr;
	std::cout << "printing null_ptr: " << *null_ptr << std::endl;
	return 0;	
}
