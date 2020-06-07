#include <iostream>
#include <list>
#include <string>
#include <thread>

const int LIST_SIZE = 6000000;
std::list<int> big_list;
void Download(std::string &file_name) {
    std::cout << "[Download] starting download " << file_name << "..." << std::endl;
    for (int i = 0; i < LIST_SIZE; i++) {
        big_list.push_back(i);
    }

    std::cout << "[Download] finished download!" << std::endl;
}

int main() {
    std::cout << "[Main] starting main" << std::endl;
    std::string test_file_name = "test.cpp";

    std::thread thd_downloader(Download, std::ref(test_file_name));
    // use detach() if the child thread is expected to run in the background and the main thread will not wait for the child thread to finish.
    // detached threads will not be joinable.
    //thd_downloader.detach();

    std::cout << "[Main] starting new thread" << std::endl;
    if (thd_downloader.joinable()) {
        // join() will make the main thread wait for the child thread to finish.
        thd_downloader.join();
    }
    std::cout << "[Main] finished" << std::endl;
    return 0;
}
