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



        class ConstIterator;
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
        
         // Inserts new element maintaining sorted order (largest to smallest)
        void insert(const T& value) {
            Node* newNode = new Node(value);
            
            // If empty list or new value is larger than head
            if (!head || value > head->data) {
                newNode->next = head;
                head = newNode;
                size++;
                return;
            }
            
            // Find insertion point - stop when we find a smaller value
            Node* current = head;
            while (current->next && !(value > current->next->data)) {
                current = current->next;
            }
            
            // Insert the new node
            newNode->next = current->next;
            current->next = newNode;
            size++;
        }
        
        // Removes element at iterator position
        void remove(ConstIterator iter) {
            if (!head) {
                throw std::out_of_range("List is empty");
            }
            
            Node* current = head;
            Node* prev = nullptr;
            
            // Find node to remove
            while (current != nullptr && current != iter.current) {
                prev = current;
                current = current->next;
            }
            
            if (current == nullptr) {
                throw std::out_of_range("Iterator not found in list");
            }
            
            // Remove the node
            if (prev == nullptr) {  // Removing head
                head = current->next;
            } else {                // Removing non-head node
                prev->next = current->next;
            }
            
            delete current;
            size--;
        }
        
        // Return list length
        int length() const {
            return size;
        }

template<typename Predicate>
        SortedList filter(Predicate pred) const {
            SortedList filtered;
            Node* current = head;
            while (current != nullptr) {
                if (pred(current->data)) {
                    filtered.insert(current->data);
                }
                current = current->next;
            }
            return filtered;
        }
        
        // Apply operation to all elements
        template<typename Operation>
        SortedList apply(Operation op) const {
            SortedList result;
            Node* current = head;
            while (current != nullptr) {
                result.insert(op(current->data));
                current = current->next;
            }
            return result;
        }
        
        // Iterator methods
        ConstIterator begin() const {
            return ConstIterator(head);
        }
        
        ConstIterator end() const {
    if (!head) {
        return ConstIterator(nullptr);
    }
    Node* current = this.head;
    while (current->next) {
        current = current->next;
    }
    return ConstIterator(current->next);  
}
    };

    template <class T>
    class SortedList<T>::ConstIterator {
         friend class SortedList;
    private:
        Node* current;
        
    public:
        // Constructor
        ConstIterator(Node* ptr) : current(ptr) {}
        
        // Copy constructor
        ConstIterator(const ConstIterator& other) : current(other.current) {}
        
        // Assignment operator
        ConstIterator& operator=(const ConstIterator& other) {
            if (this != &other) {
                current = other.current;
            }
            return *this;
        }
        
        // Destructor
        ~ConstIterator() = default;
        
        // Dereference operator
        const T& operator*() const {
            if (!current) {
                throw std::out_of_range("Iterator points to null");
            }
            return current->data;
        }
        
        // Prefix increment operator
        ConstIterator& operator++() {
            if (!current) {
                throw std::out_of_range("Cannot increment end iterator");
            }
            current = current->next;
            return *this;
        }
        
        // Inequality operator
        bool operator!=(const ConstIterator& other) const {
            return current != other.current;
        }
    };

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
}

