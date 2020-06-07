#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <thread>

std::mutex g_mutex;
std::list<int> shared_list;
const int SIZE = 1000000;

void Download1() {
    for (int i = 0; i < SIZE; ++i) {
        // use lock_guard to safely lock and unlock mutex
        std::lock_guard<std::mutex> mtx(g_mutex);
        // g_mutex.lock();
        shared_list.push_back(i);
        // g_mutex.unlock();
    }
}

void Download2() {
    for (int i = 0; i < SIZE; ++i) {
        std::lock_guard<std::mutex> mtx(g_mutex);
        // g_mutex.lock();
        shared_list.push_back(i);
        // g_mutex.unlock();
    }
}

int main() {
    std::thread thd_download1(Download1);
    std::thread thd_download2(Download2);

    thd_download1.join();
    thd_download2.join();

    return 0;
}