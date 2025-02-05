#include "stack.h"
#include <iostream>
#include <thread>
#include <sstream>
using namespace mpcs51044;

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