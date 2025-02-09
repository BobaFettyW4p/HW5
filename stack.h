#ifndef STACK_H
#define STACK_H
#include <mutex>
#include <stdexcept>
#include <memory>

namespace mpcs51044 {
    
    /**
     * @brief A struct that defines a Node class
     * This is used in the Stack class to allow for the creation of a custom container, as opposed to any pre-existing container, to store stack elements per the requirements
     * Our constructor initializes a new instance of the Node class with two fields:
     * - value: This is the value of the node, which is of type T. It is a const field as in a stack, values cannot be changed once they are added; they must be popped off the stack and replaced with new values instead
     * - next: This is a pointer to the next node in the stack. It is initialized to nullptr, but our Stack class will update this pointer as necessary to create an underlying linked list to store our stack's elements
     */
    template <typename T>
    struct Node {
        T const value;
        std::unique_ptr<Node<T>> next;
        Node(const T& val) : value(val), next(nullptr) {}
    };
    
    /**
     * @brief A thread-safe stack implementation.
     * This is an implementation of a traditional stack data structure that accepts any type of data.
     * We have implemented push, pop, peek (view the top element of the stack), isEmpty (check if the stack is empty), and size (get the size of the stack) methods.
     * We have also implemented a constructor that initializes the stack with an initializer list of values, and a constructor that takes no arguments. Our debug program, located in HW5-3.cpp, tests all of these methods.
     * The head_ field points to the top node of the stack, and the private mutex_ method is utilized by all public methods to ensure thread safety.
     */

    template <typename T>
    class Stack {
    public:
        Stack() {} 

        /**
         * @brief A constructor that initializes the stack with an initializer list of values
         * This constructor iterates through the initializer list, and pushes each value onto the stack
         */
        Stack(std::initializer_list<T> init) {
        for (const T& value : init) {
            push(value);
            }
        }

        //This is a traditional push method, it pushes the value to the top of the stack
        //Our linked list sets the "top" value of the stack to the head of the linked list. This saves time with the pop and peek methods, which can now access the top value without traversing the entire linked list
        void push(const T& value) {
            std::lock_guard<std::mutex> guard(mutex_);
            auto newNode = std::make_unique<Node<T>>(value);
            newNode->next = std::move(head_);
            head_ = std::move(newNode);
        }

        //This is a traditional pop method, it pops the value from the top of the stack, removing it permanently from the stack
        //Since the head of the linked list is the top value of the stack, we can simply move the head pointer to the next node in the list
        //As an added bonus, once the pointer to the old head is moved, the old head is automatically deleted due to the unique_ptr destructor
        T pop() {
            std::lock_guard<std::mutex> guard(mutex_);
            if (GetSize() == 0) {
            throw std::out_of_range("Stack<>::pop(): empty stack");
            }
            T value = head_->value;
            head_ = std::move(head_->next);
            return value;
        }

        //This is a traditional peek method, it returns the value at the top of the stack without removing it
        T peek() const {
            std::lock_guard<std::mutex> guard(mutex_);
            if (GetSize() == 0) {
                throw std::out_of_range("Stack<>::peek(): empty stack");
            }
            return head_->value;
        }

        //This is a traditional isEmpty method, it returns true if the stack is empty, and false otherwise
        bool isEmpty() const {
            std::lock_guard<std::mutex> guard(mutex_);
            return GetSize() == 0;
        }

        //This is a traditional size method, it returns the size of the stack
        size_t size() const {
            std::lock_guard<std::mutex> guard(mutex_);
            return GetSize();
        }

    private:
        //Our implementation utilizes two private fields:
        //The head_ field is a pointer to the top node of the stack
        //The mutex_ field is used to ensure thread safety for the stack
        std::unique_ptr<Node<T>> head_;
        mutable std::mutex mutex_;

        /**
         * @brief A helper method to calculate the size of the stack
         * Since our stack is implemented as a linked list, we have to traverse the linked list to calculate its size
         */
        size_t GetSize() const {
            size_t count = 0;
            auto current = head_.get();
            while (current != nullptr) {
                count++;
                current = current->next.get();
            }
            return count;
        }
    };
}
#endif