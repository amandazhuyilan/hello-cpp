// high level concurrencies - future and promises
#include <future>
#include <iostream>
#include <thread>

// int Operation(int size) {
int Operation(std::promise<int> &size) {
    std::thread::id id = std::this_thread::get_id();
    std::cout << "[Task] Running thread: " << id << "..." << std::endl;

    // the following two lines will block the current thread until the future is got.
    auto f = size.get_future();
    std::cout << "[Task] Waiting for future from main thread.." << std::endl;

    auto count = f.get();
    std::cout << "[Task] Future acquired." << std::endl;

    int sum = 0;
    for (int i = 0; i < count; ++i){
        sum += i;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    return sum;
}

int main() {
    std::promise<int> shared_data;
    std::future<int> result = std::async(Operation, std::ref(shared_data));
    if (result.valid()) {
        auto status = result.wait_for(std::chrono::seconds(5));
        switch(status) {
            case std::future_status::deferred:
                std::cout << "[Main] Task is deferred!" << std::endl;
                break;

            case std::future_status::ready:
                std::cout << "[Main] Task is ready!" << std::endl;
                break;

            case std::future_status::timeout:
                std::cout << "[Main] Task is still running..." << std::endl;
                break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "[Main] Set promise data." << std::endl;
        shared_data.set_value(10);
        auto sum = result.get();   // similar to join() in threads, used to get task state
        std::cout << "[Main] Final result: " << sum << std::endl;
    } 
}