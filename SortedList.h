#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {

    private:
        struct Node {
            T data;
            Node* next;
            Node(const T& value) : data(value), next(nullptr) {}
        };
        
        Node* head;
        int size;



    public:
        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */
        // Constructor
        SortedList() : head(nullptr), size(0) {}
        
        // Copy constructor
        SortedList(const SortedList& other) : head(nullptr), size(0) {
            Node* current = other.head;
            while (current != nullptr) {
                insert(current->data);
                current = current->next;
            }
        }
        
        // Assignment operator
        SortedList& operator=(const SortedList& other) {
            if (this != &other) {
                SortedList temp(other);
                Node* tempHead = head;
                head = temp.head;
                temp.head = tempHead;
                size = temp.size;
            }
            return *this;
        }
        
        // Destructor
        ~SortedList() {
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
        
        // Insert new element
        void insert(const T& value) {
            Node* newNode = new Node(value);
            if (!head || value > head->data) {
                newNode->next = head;
                head = newNode;
                size++;
                return;
            }
            
            Node* current = head;
            while (current->next && !(value > current->next->data)) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            size++;
        }
        
        // Remove element at iterator position
        void remove(ConstIterator iter) {
            if (!head) {
                throw std::out_of_range("List is empty");
            }
            
            Node* current = head;
            Node* prev = nullptr;
            
            while (current != nullptr && current != iter.current) {
                prev = current;
                current = current->next;
            }
            
            if (current == nullptr) {
                throw std::out_of_range("Iterator not found in list");
            }
            
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            
            delete current;
            size--;
        }
        
        // Return list length
        int length() const {
            return size;
        }

    };

    template <class T>
    class SortedList<T>::ConstIterator {
    /**
     * the class should support the following public interface:
     * if needed, use =defualt / =delete
     *
     * constructors and destructor:
     * 1. a ctor(or ctors) your implementation needs
     * 2. copy constructor
     * 3. operator= - assignment operator
     * 4. ~ConstIterator() - destructor
     *
     * operators:
     * 5. operator* - returns the element the iterator points to
     * 6. operator++ - advances the iterator to the next element
     * 7. operator!= - returns true if the iterator points to a different element
     *
     */
    };
}

