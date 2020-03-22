#include <iostream>

int main() {
//	std::cout << "What is your age?" << std::endl;
//	int user_age;
//	std::cin >> user_age;

	char name_buff[152];
	std::cout << "What is your name?" << std::endl;
	std::cin.getline(name_buff, 64, '\n');
	std::cout << "Hello " << name_buff << std::endl;

	return 0;
}
