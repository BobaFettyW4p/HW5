#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>

//This creates a mutex object for std::cout
//This is necessary to ensure that all 3 threads do not write to std::cout at the same time and create garbled output
//This is also created outside of either function to ensure that all threads can access it
std::mutex coutMutex;


/**
 * @brief Function executed by a thread to print its ID and the number of times it has been called.
 *
 * This function runs a loop from 1 to 100, and in each iteraqtion, it prints the ID of the thread and the number of times it has been called, as specified in the requirements 
 * It utilizes a mutex and a lock guard to ensure that only one thread can write to std::cout at a time, both yielding thread safety and preventing interleaving or garbled output
 * We also use std::ostringstream to construct the string before it is printed to std::cout, which is more efficient than using std::cout directly
 * As an added benefit, this minimizes the time any individual thread holds the lock
 * which improves performance, reduces the likelihood of deadlocks, and prevents interleaving output from different threads
 * 
 * @return void
 */
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

/**
 * @brief Main function to create and join 3 threads.
 *
 * This function creates 3 threads, each of which calls the CountToOneHundred() function
 * It then joins each of the threads to ensure that the main() function waits for all 3 threads to finish before exiting
 * 
 * @return int 
 */
int main() {
    std::thread thread1(CountToOneHundred);
    std::thread thread2(CountToOneHundred);
    std::thread thread3(CountToOneHundred);

    thread1.join();
    thread2.join();
    thread3.join();

    return 0;
}