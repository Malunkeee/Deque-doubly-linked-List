#ifndef DEQUE_H
#define DEQUE_H

#include <string>
#include <stdexcept>

using namespace std;
namespace Mydeque {

     /** Custom exception for Deque-specific errors (operating on empty deque etc.).
     *  Derives from runtime_error so it can be caught as runtime_error too. */
    class DequeException : public runtime_error {
    public:
        explicit DequeException(const string& msg);
    };

    class Deque {

    private:
        /** Hidden implementation*/
        struct Impl;
        Impl *pImpl;

    public:

        /** Constructs an empty deque. */
        Deque();

        /** Copy constructor - performs a deep copy of other. */
        Deque(const Deque& other);

        /** Assignment operator - performs a deep copy of other. */
        Deque& operator=(const Deque& other);

        /** Destructor - frees all nodes and the Impl object. */
        ~Deque();

        /** Inserts value at the front of the deque. */
        void push_front(int value);
        /** Inserts value at the back of the deque. */
        void push_back(int value);
        /** Same as push_back(). */
        Deque& operator+=(int value);

        /** Returns the front element. Throws DequeException if deque is empty. */
        int front() const;
        /** Returns the back element. Throws DequeException if deque is empty. */
        int back() const;
        /** Returns element at index. Throws out_of_range if index is invalid. */
        int at(int index) const;
        /** Returns the index of value, or -1 if not found. */
        int operator[](int value) const;

        /** Returns the number of elements in the deque. */
        int size() const;
        /** Returns true if the deque contains no elements. */
        bool empty() const;

        /** Returns aggregate info: size and all elements in order. */
        string toString() const;

        /** Updates element at index to value. Throws out_of_range if index is invalid. */
        void update(const pair<int, int>& arg);
         /**Same as update(). */
        Deque& operator*=(const pair<int, int>& arg);

         /** Removes and returns the front element. Throws DequeException if deque is empty. */
        int pop_front();
        /** Removes and returns the back element. Throws DequeException if deque is empty. */
        int pop_back();
         /** Removes first occurrence of value. Throws invalid_argument if not found. */
        void remove(int value);
        /** Same as remove(). */
        Deque& operator-=(int value);

        /** Clears all elements from the deque. */
        Deque& operator!();

        /** Comparison operators - compare by number of elements. */
        bool operator==(const Deque& other) const;
        bool operator!=(const Deque& other) const;
        bool operator< (const Deque& other) const;
        bool operator<=(const Deque& other) const;
        bool operator> (const Deque& other) const;
        bool operator>=(const Deque& other) const;

    };

}

#endif
