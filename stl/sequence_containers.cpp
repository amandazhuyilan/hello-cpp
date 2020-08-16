#include <iostream>
#include <array>
#include <forward_list>
#include <list>
#include <vector>

int main() {
    // array
    std::array<int, 2> arr_1 = {1, 2};
    // vectors
    std::vector<int> vec_1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    vec_1.insert(vec_1.begin(), 11);
    vec_1.erase(vec_1.end() - 1);
    vec_1.pop_back();

    auto vec_itr = vec_1.begin();
    // while (vec_itr != vec_1.end()) {
    //     std::cout << *vec_itr++ << std::endl;
    // }
    // lists
    std::list<int> list_1;
    for (int i = 0; i < 5; i++) {
        list_1.push_back(i * 10);
    }
    
    // access list only via iterators 
    auto list_iter = list_1.begin();
    // while (list_iter != list_1.end()) {
    //     std::cout << *list_iter++ << std::endl;
    // }

    // forward_list
    std::forward_list<int> forward_list_1;
    for (int j = 0; j < 10; j ++) {
        forward_list_1.push_front(j);
    }

    auto iter_foward_list = forward_list_1.begin();
    while (iter_foward_list != forward_list_1.end()) {
        std::cout << *iter_foward_list++ << std::endl;
    }

    // you can erase and insert anywhere in the forward list, as long you know the iterator
    forward_list_1.insert_after(forward_list_1.begin(), 10);
    forward_list_1.erase_after(forward_list_1.begin());
    return 0;
}
