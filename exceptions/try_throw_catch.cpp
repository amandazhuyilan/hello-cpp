#include <iostream>
#include <limits>
#include <memory>
#include <vector>

class Test{
public:
    Test() {std::cout << "Test()" << std::endl;}
    ~Test() {std::cout << "~Test()" << std::endl;}

};

int ProcessRecords(int count) {
    // // the following code uses manual memory management and is not recommended
    // std::unique_ptr<Test> t(new Test);  // use smart pointers instead of raw pointers to ensure that memory won't be leaked if there is an excepction thrown and objects allocated on the heap is destroyed properly.
    // int *pArray = (int*)malloc(count * sizeof(int));
    // if (count < 10) {
    //     throw std::out_of_range("Count should be greater than 10!");
    // }
    // if (pArray == nullptr) {
    //     throw std::runtime_error("failed to allocate memory!");
    // }
    // for (int i = 0; i < count; ++i) {
    //     pArray[i] = i;
    // }

    // free(pArray);

    if (count < 10) {
        throw std::out_of_range("Input count should be greater than 10!");
    }

    std::vector<int> records;
    records.reserve(count);
    // process records
    for (int i = 0; i < count; ++i) {
        records.push_back(i);
    }

    int num_of_errors = 0;
    for (int i = 0; i < count; ++i) {
            try {
                std::cout << "Processing num: " << i << std::endl;
                if (i/2 == 0) {
                    ++num_of_errors;
                    throw std::runtime_error("Cannot process record!");
                }
            }
            catch (std::runtime_error &ex) {
                std::cout << "[ERROR] " << ex.what() << "]" << std::endl;
                if (num_of_errors > 5) {
                    std::runtime_error err("Too many errors - aborting operation!");
                    // modify the original exception and re-throw the exception
                    ex = err;
                    // rethrow the modified expection
                    throw;
                }
            }

    return 0;
}

int main() {
    try {
        // ProcessRecords(std::numeric_limits<int>::max());
        ProcessRecords(5);

    }

    // catch multiple specific exceptions
    // catch (std::runtime_error &exc) {
    //     std::cout << exc.what() << std::endl;
    // }
    catch (std::out_of_range &exc) {
        std::cout << exc.what() << std::endl;
    }

    // catch all std:exception
    catch (std::exception &exc) {
        std::cout << "Caught as all exceptions: " << exc.what() << std::endl;
    }

    // all other implicit catches with no specific documentation - should be avoid using this catch pattern
    catch (...) {
        std::cout << "An unexpected error happened!" << std::endl;
    }
}