#include <iostream>
#include <vector>

int main() {
	std::vector<int> vec1 {1, 2, 3};
	// add elements into vector
	vec1.push_back(4);
	std::cout << "Pushed one new element into vector: " << std::endl;
	for (auto x: vec1) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	// access vector element with subscription
	std::cout << "The third element is: " << vec1[2] << std::endl;
	// access vector element with iterators
	auto it = vec1.begin();
	std::cout << "The third element (via iterator) is: " << *(it += 2) << std::endl;

	// delete elements of a vector
	auto it_1 = vec1.begin() + 1;
	vec1.erase(it_1);
	std::cout << "Vector after erase one element: " << std::endl;
	for (auto x: vec1) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	
	// insert an element into a vector
	auto it_2 = vec1.end() - 1;
	vec1.insert(it_2, 100);
	std::cout << "Vector after insert one element: " << std::endl;
	for (auto x: vec1) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
}
