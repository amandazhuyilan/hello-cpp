#include <iostream>
int main() {
	int test_arr[] = {1,2,3,4,5};
	for (const auto &x: test_arr) {
		std::cout << x << std::endl;
	}
}
