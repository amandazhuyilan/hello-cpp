#include <iostream>

void Print(int count, char c) {
	for (int i = 0; i < count; i++) {
		std::cout << c;
	}
	std::cout << std::endl;
}


int AddThree(int a, int b, int c) {
	int result = a + b + c;
	return result;
}

void ExitMsg(){
	std::cout << "Exiting Program!" << std::endl;
}

int main() {
	void(*print_ptr) (int, char) = Print;
	int(*add_three_ptr) (int, int, int) = AddThree;

	print_ptr(10, '@');
	int result = add_three_ptr(1, 2, 3);
	std::cout << "add three: " << result << std::endl;
	
	atexit(ExitMsg);
	return 0;
}
