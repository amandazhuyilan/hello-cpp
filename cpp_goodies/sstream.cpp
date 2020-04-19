#include <iostream>
#include <sstream>

int main() {
	std::stringstream ss;
	ss << "12" << "23" << "45" << std::endl;
	std::cout << ss.str() << std::endl;
	
	std::stringstream ss_1;
	std::string data = "22 33 44";
	int a;
	ss_1.str(data);

	while (ss_1 >> a) {
		std::cout << a << std::endl;
	}

}
