#include <algorithm>
#include <iostream>
#include <string>

enum class Case{INSENSITIVE, SENSITIVE};

// return position of the first character of the substring, else std::string::npos

size_t Find(
	std::string &source,	// source string to be searched
	std::string &search_string,	// string to search for
	Case SearchCase = Case::INSENSITIVE,	// choose case-sensitive
	std::size_t offset = 0) {	// where to start the search from
	if (SearchCase == Case::INSENSITIVE) {	
		std::for_each(source.begin(), source.end(),[](char &c) {
			c = ::toupper(c);
		});
		std::for_each(search_string.begin(), search_string.end(), [](char &c_search) {
			c_search = ::toupper(c_search);
		});
	}
        std::size_t found_str = source.find(search_string, offset);
        if (found_str != std::string::npos) {
		return found_str;
           }
	return std::string::npos;
}

int main() {
	std::string source_string = "Hello Beautiful World";
	std::string substring1 = "HELLO";
	std::string substring2 = "world";

	std::size_t find_result = Find(source_string, substring1);
	if (find_result != std::string::npos) {
		std::cout << "Found substring!" << std::endl;
	}
}
