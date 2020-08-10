#include <iostream>
#include <vector>
#include <functional>

// this template function takes in lambda function object as input and implement it on each element of the input vector
template<typename T, typename Callback>
std::vector<T> for_each(std::vector<T> input_vec, Callback lambda_fn) {
    std::vector<T> result_vec;
    for (auto &element : input_vec) {
        result_vec.push_back(lambda_fn(element));
        }
    return result_vec;
}

int main() {
    auto sum = [](int a, int b)->int{
        return a + b;
        }; 
    // std::cout << "sum is " << sum(1, 4) << std::endl;


    std::vector<int> test_vector_int {1, 2, 3, 4, 5};
    std::vector<int> result_vector_int_1;

    // test 1 - add 1 to each element
    auto add_one = [](int a) {
        return a + 1;
    };

    result_vector_int_1 = for_each(test_vector_int, add_one);

    std::cout << "[TestCase1]" << std::endl;
    for (auto &i : test_vector_int) {
        std::cout << i << std::endl;
    }

    // test 2 - increase each element by using the offset value via capture
    std::vector<int> result_vector_int_2;

    // captures will be made a copy when passed into lambda, and cam be made mutable via the "mutable" keyword
    int offset = 1;
    result_vector_int_2 = for_each(test_vector_int, [offset](int &x) mutable {
        offset++;
        return x+offset;
    });

    std::cout << "[TestCase2]" << std::endl;
    for (auto &i : result_vector_int_2) {
        std::cout << i << std::endl;
    }

    // test 3 access capture value by reference
    int sum_3{};
    std::vector<int> result_vector_int_3;
    result_vector_int_3 = for_each(test_vector_int, [&sum_3](int &x) {
        sum_3 = sum_3 + x;
        return x;
    });

    std::cout << "[TestCase3]: sum_3 = " << sum_3 << std::endl;

    // test 4; lambda within lambda
    [](int x) {
        x *= 2;
        [](int x) {
            std::cout << "[TestCase4] lambda within lambda: " << x << std::endl;
        }(x);
    }(5);
    return 0;
}