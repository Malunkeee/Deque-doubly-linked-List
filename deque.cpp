#include "deque.h"
#include <sstream>
#include <stdexcept>

using namespace std;
namespace mydeque {


struct Node {
    int   value;
    Node *prev;
    Node *next;

    Node(int val) : value(val), prev(nullptr), next(nullptr) {}
};


struct Deque::Impl {
    Node *head;
    Node *tail;
    int count;

    Impl() : head(nullptr), tail(nullptr), count(0) {}

    Impl(const Impl& other) : head(nullptr), tail(nullptr), count(0) {
        Node *cur = other.head;

        while (cur) {
            push_back(cur->value);
            cur = cur->next;
        }
    }

    ~Impl() {
        clear();
    }

    void push_back(int value) {
        Node *n = new Node(value);

        if (!tail) {
            head = tail = n;
        } 
        else {
            n->prev = tail;
            tail->next = n;
            tail = n;
        }

        ++count;
    }

    void push_front(int value) {
        Node *n = new Node(value);
        
        if (!head) {
            head = tail = n;
        } 
        else {
            n->next = head;
            head->prev = n;
            head = n;
        }
        ++count;
    }

    int pop_front() {
        Node *n = head;
        int val = n->value;
        
        head = head->next;
        
        if (head){
           head->prev = nullptr; 
        } 
        else{
           tail = nullptr;
        }

        delete n;
        --count;

        return val;
    }

    int pop_back() {
        Node *n = tail;

        int val = n->value;
        tail = tail->prev;

        if (tail) {
            tail->next = nullptr;
        }
        else{
           head = nullptr; 
        }  

        delete n;
        --count;

        return val;
    }

    Node *node_at(int index) const {
        if (index >= count){
           return nullptr; 
        } 

        Node* cur = head;
        for (int i = 0; i < index; ++i){
             cur = cur->next;
        }
    
        return cur;
    }

    void unlink(Node *n) {
        if (n->prev){
            n->prev->next = n->next;
        } 
        else {
            head = n->next;
        }  
        if (n->next){
            n->next->prev = n->prev;
        } 
        else {
            tail = n->prev;
        }
        delete n;
        --count;
    }

    void clear() {
        Node *cur = head;
        while (cur) {
            Node *temp = cur->next;
            delete cur;
            cur = temp;
        }
        head  = nullptr;
        tail  = nullptr;
        count = 0;
    }

    bool empty() const { 
        return count == 0; 
    }
};

Deque::Deque() : pImpl(new Impl()) {}

Deque::Deque(const Deque& other) : pImpl(new Impl(*other.pImpl)) {}

Deque& Deque::operator=(const Deque& other) {
    if (this != &other) {
        delete pImpl;
        pImpl = new Impl(*other.pImpl);
    }
    return *this;
}

Deque::~Deque() {
    delete pImpl;
}


void Deque::push_front(int value) {
    pImpl->push_front(value);
}

void Deque::push_back(int value) {
    pImpl->push_back(value);
}

Deque& Deque::operator+=(int value) {
    pImpl->push_back(value);
    return *this;
}


int Deque::front() const {
    if (pImpl->empty()){
        throw DequeException("Function front() called on an empty deque.");
    }
    return pImpl->head->value;
}

int Deque::back() const {
    if (pImpl->empty()){
        throw DequeException("Function back() called on an empty deque.");
    }
        
    return pImpl->tail->value;
}

int Deque::at(int index) const {
    if (index >= pImpl->count || index < 0){
        throw out_of_range("Function at(): index " + to_string(index) + " is out of range."); 
    }
    return pImpl->node_at(index)->value;
}

int Deque::operator[](int value) const {
Node* cur = pImpl->head;
    int pos = 0;
    while (cur) {
        if (cur->value == value){
            return pos;
        } 
        cur = cur->next;
        ++pos;
    }
    return -1;
}

int Deque::size() const {
    return pImpl->count;
}

bool Deque::empty() const {
    return pImpl->empty();
}

string Deque::toString() const {
    stringstream ss;
    ss << "Deque size = " << pImpl->count << " Elements = ";
    Node* cur = pImpl->head;
    while (cur) {
        ss << cur->value;
        if (cur->next) {
            ss << ", ";
        }
        cur = cur->next;
    }
    return ss.str();
}

void Deque::update(int index, int value) {
    if (index >= pImpl->count){
        throw out_of_range("Function update(): index " + to_string(index) + " is out of range.");
    }
    pImpl->node_at(index)->value = value;
}

Deque& Deque::operator*=(const UpdateArg& arg) {
    update(arg.index, arg.value);
    return *this;
}


int Deque::pop_front() {
    if (pImpl->empty()){
        throw DequeException("Function pop_front() called on an empty deque.");
    }
    return pImpl->pop_front();
}

int Deque::pop_back() {
    if (pImpl->empty()){
        throw DequeException("pop_back() called on an empty deque.");
    }
    return pImpl->pop_back();
}

void Deque::remove(int value) {
    Node* cur = pImpl->head;
    while (cur) {
        if (cur->value == value) {
            pImpl->unlink(cur);
            return;
        }
        cur = cur->next;
    }
    throw invalid_argument("Function remove(): value " + to_string(value) + " not found in deque.");
}

Deque& Deque::operator-=(int value) {
    remove(value);
    return *this;
}

Deque& Deque::operator!() {
    pImpl->clear();
    return *this;
}


bool Deque::operator==(const Deque& other) const {
    return pImpl->count == other.pImpl->count;
}

bool Deque::operator!=(const Deque& other) const {
    return pImpl->count != other.pImpl->count;
}

bool Deque::operator<(const Deque& other) const {
    return pImpl->count < other.pImpl->count;
}

bool Deque::operator<=(const Deque& other) const {
    return pImpl->count <= other.pImpl->count;
}

bool Deque::operator>(const Deque& other) const {
    return pImpl->count > other.pImpl->count;
}

bool Deque::operator>=(const Deque& other) const {
    return pImpl->count >= other.pImpl->count;
}

}
