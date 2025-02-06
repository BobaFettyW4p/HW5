#ifndef STACK_H
#define STACK_H
#include <mutex>
#include <stdexcept>
#include <memory>

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
        Stack() : capacity_(0), size_(0) {} 


        //This is a traditional push method, it pushes the value to the top of the stack
        //We utilize the private mutex_ field to main thread safety
        void push(const T& value) {
            std::lock_guard<std::mutex> guard(mutex_);
            if (size_ == capacity_) {
                resize();
            }
            stack_[size_++] = value;
        }


        //This is a traditional pop method, it pops the value from the top of the stack, removing it permanently from the stack
        //We utilize the private mutex_ field to main thread safety
        T pop() {
            std::lock_guard<std::mutex> guard(mutex_);
            if (size_ == 0) {
                throw std::out_of_range("Stack<>::pop(): empty stack");
            }
            return stack_[--size_];
        }


        //This is a traditional peek method, it returns the value at the top of the stack without removing it
        //We utilize the private mutex_ field to main thread safety
        T peek() const {
            std::lock_guard<std::mutex> guard(mutex_);
            if (size_ == 0) {
                throw std::out_of_range("Stack<>::peek(): empty stack");
            }
            return stack_[size_ - 1];
        }

        //This is a traditional isEmpty method, it returns true if the stack is empty, and false otherwise
        //We utilize the private mutex_ field to main thread safety
        bool isEmpty() const {
            std::lock_guard<std::mutex> guard(mutex_);
            return size_ == 0;
        }


        //This is a traditional size method, it returns the size of the stack
        //We utilize the private mutex_ field to main thread safety
        size_t size() const {
            std::lock_guard<std::mutex> guard(mutex_);
            return size_;
        }

    private:
        /**
         * @brief Resize the stack to double its current capacity.
         * This is a private helper method for our public methods for our stack implementation
         * Once the stack is full, we call this method to double the capacity of the stack
         * I have more familiarity with Python than C++, and in Python, when a list (a mutable data type) is full, it is automatically resized by 2x
         * This ends up being more efficient that simply resizing by 1 as needed due to the overhead associated with resizing the size of the data type
         * I presume it is similar for C++
         */
        void resize() {
            //The below line either sets capacity to 1 if it is currently 0; otherwise, it doubles the capacity
            capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
            //we create a new array to serve as the stack with the new capacity, and the preexisting elements are copied over
            auto newStack = std::make_unique<T[]>(capacity_);
            for (size_t i = 0; i < size_; ++i) {
                newStack[i] = stack_[i];
            }
            //finally, we move the unique_ptr to the new stack, relying on RAII principles to garbage collect the old stack
            stack_ = std::move(newStack);
        }

        std::unique_ptr<T[]> stack_;
        size_t capacity_;
        size_t size_;
        mutable std::mutex mutex_;
    };
}
#endif