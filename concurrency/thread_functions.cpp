#include <iostream>
#include <thread>

void Process() {
    std::this_thread::get_id();
    for (int i = 0; i < 10; ++i){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << i << std::endl;
    }
}

int main() {
    std::thread thread1(Process);
    std::thread::id thread1_id = thread1.get_id();
    std::cout << "thread1_id: " << thread1_id << std::endl;

    // get number of cores in the CPU
    int cores = std::thread::hardware_concurrency();
    std::cout << "num of cores: " << cores << std::endl;
    thread1.join();

}