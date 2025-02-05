#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>

/**
 * This is my implementation of the previous homework problem utilizing std::jthread instead of std::thread
 * Removing the need to call join() on the individual threads prevents the programmer from forgetting to call join()
 * Thus, removing it makes code simpler and easier to read. I would assume it would be standard practice
 * to use std::jthread whenever possible, leaving std::thread only for cases where it's newer cousin is not available
 */




std::mutex coutMutex;


void CountToOneHundred() {
    for (int i = 1; i <= 100; i++) {
        std::ostringstream oss;
        oss << "Thread " << std::this_thread::get_id() << " has been called " << i << " times" << "\n";
        {
            std::lock_guard<std::mutex> guard(coutMutex);
            std::cout << oss.str();
        }
    }
}


int main() {
    std::jthread thread1(CountToOneHundred);
    std::jthread thread2(CountToOneHundred);
    std::jthread thread3(CountToOneHundred);

    return 0;
}