#include "stack.h"
#include <iostream>
#include <thread>
#include <sstream>
using namespace mpcs51044;

//This is a debug program for my stack class, located in stack.h
//It has a function StackTest that accepts a stack object, and tests all of it's methods sequentially
//Within the main function, we create a stack object and run StackTest() through 2 separate threads
//The output will run through the methods of the stack class, and will be interleaved between the two threads
//Additionally, we are leveraging std::ostringstream to construct the string before it is printed to std::cout
//This is more efficient than using std::cout directly, as it minimizes the time any individual thread holds the lock
//and has the added benefit of ensuring that our output does not get garbled by interleaving output from different threads


void StackTest(Stack<int>& stack) {

    //initializing an oss object
    std::ostringstream oss;

    // Test pushing elements onto the stack
    stack.push(10);
    stack.push(20);
    stack.push(30);

    //Test size()  method
    oss << "Size of stack: " << stack.size() << " from thread " << std::this_thread::get_id() << "\n"; // Should print 3
    std::cout << oss.str();
    oss.str("");
    oss.clear();

    // Test popping elements from the stack
    oss << "Popped: " << stack.pop() << " from thread " << std::this_thread::get_id() << "\n"; // Should print 30
    std::cout << oss.str();
        oss.str("");
    oss.clear();

    oss << "Popped: " << stack.pop() << " from thread " << std::this_thread::get_id() << "\n"; // Should print 20
    std::cout << oss.str();
        oss.str("");
    oss.clear();


    // Test peeking the top element
    oss << "Peeking at: " << stack.peek() << " from thread " << std::this_thread::get_id() << "\n"; // Should print 10
    std::cout << oss.str();
        oss.str("");
    oss.clear();

    // Test if the stack is empty
    oss << "Is stack empty? " << (stack.isEmpty() ? "Yes" : "No") << " from thread " << std::this_thread::get_id() << "\n"; // Should print No
    std::cout << oss.str();
        oss.str("");
    oss.clear();

    // Test popping the last element
    oss << "Popped: " << stack.pop() << " from thread " << std::this_thread::get_id() << "\n"; // Should print 10
    std::cout << oss.str();
        oss.str("");
    oss.clear();

    // Test if the stack is empty again
    oss << "Is stack empty? " << (stack.isEmpty() ? "Yes" : "No") << " from thread " << std::this_thread::get_id() << "\n"; // Should print Yes
    std::cout << oss.str();
        oss.str("");
    oss.clear();

}

int main() { 
    Stack<int> stack;

    //running StackTest() threaded
    std::jthread thread1(StackTest, std::ref(stack));
    std::jthread thread2(StackTest, std::ref(stack));
    return 0;
}