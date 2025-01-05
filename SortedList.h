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

        class ConstIterator;
        // Constructor
        SortedList() : head(nullptr), size(0) {}
        
        // Copy constructor
        SortedList(const SortedList& other) : head(nullptr), size(0) {
    try {
        // Create a temporary list
        Node* temp_head = nullptr;
        int temp_size = 0;
        
        // Copy elements from other list
        Node* current = other.head;
        Node* temp_tail = nullptr;
        
        while (current != nullptr) {
            Node* new_node = new Node(current->data);
            
            if (!temp_head) {
                temp_head = new_node;
            } else {
                temp_tail->next = new_node;
            }
            temp_tail = new_node;
            temp_size++;
            current = current->next;
        }
        
        // If we got here, all allocations succeeded
        head = temp_head;
        size = temp_size;
    } catch (...) {
        // Clean up any nodes we created before the exception
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        throw; // Re-throw the exception
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
            try {
        Node* newNode = new Node(value);
        
        // If empty list or new value is larger than head
        if (!head || value > head->data) {
            newNode->next = head;
            head = newNode;
            size++;
            return;
        }
        
        // Find insertion point
        Node* current = head;
        while (current->next && !(value > current->next->data)) {
            current = current->next;
        }
        
        newNode->next = current->next;
        current->next = newNode;
        size++;
    } catch (const std::bad_alloc& e) {
        throw std::runtime_error("Memory allocation failed during insert");
    }
}
           
        
        // Removes element at iterator position
        void remove(ConstIterator iter) {
           if (!head) {
        throw std::out_of_range("List is empty");
    }
    
    // If it's an end iterator, just return
    if (!iter.current) {
        return;
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
    Node* current = this->head;
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

