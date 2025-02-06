#ifndef STACK_H
#define STACK_H
#include <vector>
#include <mutex>

namespace mpcs51044 {
    /**
     * @brief A thread-safe stack implementation.
     * This is an implementation of a traditional stack data structure that accepts any type of data.
     * We have implemented push, pop, peek (view the top element of the stack), isEmpty (check if the stack is empty), and size (get the size of the stack) methods.
     * The private stack_ field contains the actual items within the stack, and the private mutex_ method is utilized by all public methods to ensure thread safety.
     */
    template <typename T>
    class Stack {
    public:
        //This is a traditional push method, it pushes the value to the top of the stack
        //We utilize the private mutex_ field to main thread safety
        void push(const T& value) {
            std::lock_guard<std::mutex> guard(mutex_);
            stack_.push_back(value);
        }
        //This is a traditional pop method, it pops the value from the top of the stack, removing it permanently from the stack
        //We utilize the private mutex_ field to main thread safety
        T pop() {
            std::lock_guard<std::mutex> guard(mutex_);
            if (stack_.empty()) {
                throw std::out_of_range("Stack<>::pop(): empty stack");
            }
            T value = stack_.back();
            stack_.pop_back();
            return value;
        }

        //This is a traditional peek method, it returns the value at the top of the stack without removing it
        //We utilize the private mutex_ field to main thread safety
        T peek() const {
            std::lock_guard<std::mutex> guard(mutex_);
            if (stack_.empty()) {
            throw std::out_of_range("Stack<>::peek(): empty stack");
            }
            return stack_.back();
        }

        //This is a traditional isEmpty method, it returns true if the stack is empty, and false otherwise
        //We utilize the private mutex_ field to main thread safety
        bool isEmpty() const {
            std::lock_guard<std::mutex> guard(mutex_);
            return stack_.empty();
        }

        //This is a traditional size method, it returns the size of the stack
        //We utilize the private mutex_ field to main thread safety
        size_t size() const {
            std::lock_guard<std::mutex> guard(mutex_);
            return stack_.size();
        }

    private:
        //In this implementation, we have made the stack_vector, and mutex_ private members of the class
        //This is to ensure that the stack is only accessible through the public methods of the class
        std::vector<T> stack_;
        mutable std::mutex mutex_;
    };
}
#endif
