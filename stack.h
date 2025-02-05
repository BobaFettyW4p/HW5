#ifndef STACK_H
#define STACK_H
#include <vector>
#include <mutex>

namespace mpcs51044 {

    template <typename T>
    class Stack {
    public:
        void push(const T& value) {
            std::lock_guard<std::mutex> guard(mutex_);
            stack_.push_back(value);
        }

        T pop() {
            std::lock_guard<std::mutex> guard(mutex_);
            if (stack_.empty()) {
                throw std::out_of_range("Stack<>::pop(): empty stack");
            }
            T value = stack_.back();
            stack_.pop_back();
            return value;
        }

        T peek() const {
            std::lock_guard<std::mutex> guard(mutex_);
            if (stack_.empty()) {
            throw std::out_of_range("Stack<>::peek(): empty stack");
            }
            return stack_.back();
        }

        bool isEmpty() const {
            std::lock_guard<std::mutex> guard(mutex_);
            return stack_.empty();
        }

        size_t size() const {
            std::lock_guard<std::mutex> guard(mutex_);
            return stack_.size();
        }

    private:
        std::vector<T> stack_;
        mutable std::mutex mutex_;
    };
}
#endif
