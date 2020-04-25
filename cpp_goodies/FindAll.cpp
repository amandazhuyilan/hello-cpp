#include<iostream>
#include<string>
#include<vector>

/*
 Implement a function called FindAll() that:
- returns the starting indices of all the found substrings in a target string in a vector
- allows users to define index of the first character in the string to be considered in the search.
- supports case sensitive/insensitive search.

requirements: 
- do not use std::string.find() and or std::string.substring() functions.
- no extra header file to be added.
*/

enum class Case{SENSITIVE, INSENSITIVE};

// helper functions to convert strings to upper case
std::string toUpper(const std::string &str) {
	std::string result_str = str;
	for(int i = 0; i < str.length(); i++) {
  		if(str[i] <= 'z' && str[i] >= 'a') {
			result_str[i] = str[i] - 32;
		}
	}

	return result_str;
}

std::vector<int> FindAll(
	const std::string &target_str,	// target string to be searched
	const std::string &sub_str,	// the string to search for
	Case searchCase = Case::INSENSITIVE,
	size_t offset = 0) {		// start the search for in the target string from this offset character	
	std::vector<int> result;
	// return early if the target string size if smaller than search string size.
	int target_len = target_str.length(), sub_len = sub_str.length();
	if (target_len < sub_len) {
		return result;
	}

	// need to create copies of target and sub strings since they are consts
	std::string processed_target_str, processed_sub_str;
	// convert inplace to all upper case for insensitive find 
	if (searchCase == Case::INSENSITIVE) {	
		processed_target_str = toUpper(target_str);
		processed_sub_str = toUpper(sub_str);
	}
	else {	
		processed_target_str = target_str;
		processed_sub_str = sub_str;
	}

	// sliding substring one by one on the target str
	for (int target_idx = offset; target_idx < target_len; target_idx++) {
		int sub_idx;
		// check for match for current index
		for (sub_idx = 0; sub_idx < sub_len; sub_idx++) {
			if (processed_target_str[target_idx + sub_idx] != processed_sub_str[sub_idx]) {
				break;
			}
		}
		
		if (sub_idx == sub_len) {
			result.push_back(target_idx);
		}
	}	
		
}

int main() {
	std::string target_str_1 = "AABAACAADAABAAABAA";
	std::string search_str_1 = "baa";
	std::vector<int> result = FindAll(target_str_1, search_str_1, Case::INSENSITIVE, 2);

	for (auto x: result) {
		std::cout << x << std::endl;
	}
	
}

