#include "deque.h"
#include <iostream>

using namespace std;
using namespace mydeque;


int main() {
    cout << "push_front / push_back / operator+=" << endl;

    Deque dq;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_back(30);
    dq.push_front(5);
    dq += 40;                     

    cout << "After pushes: " << dq.toString() << endl;
    cout << "size = " << dq.size() << "  empty = " << dq.empty() << endl;

    cout << "\nfront() / back() / at()" << endl;

    cout << "front() = " << dq.front() << endl;
    cout << "back() = " << dq.back()  << endl;
    cout << "at(0) = " << dq.at(0)   << endl;
    cout << "at(2) = " << dq.at(2)   << endl;

    cout << "\noperator[]" << endl;

    cout << "dq[20]  = " << dq[20]  << "  expected 2\n";
    cout << "dq[999] = " << dq[999] << "  expected -1\n";

    cout << "\nupdate() / operator*=" << endl;

    dq.update(0, 1);                        
    dq *= Deque::UpdateArg{4, 100};         

    cout << "After update(0,1) and *={4,100}: " << dq.toString() << endl;

    cout << "\npop_front() / pop_back()" << endl;

    int pf = dq.pop_front();
    int pb = dq.pop_back();
    cout << "pop_front() = " << pf << endl;
    cout << "pop_back() = " << pb << endl;
    cout << "After both pops: " << dq.toString() << endl;

    cout << "\nremove() / operator-=" << endl;

    dq.push_back(50);
    dq.push_back(60);
    cout << "Before remove: " << dq.toString() << endl;

    dq.remove(20);          
    dq -= 50;              
    cout << "After remove: " << dq.toString() << endl;

 
    cout << "\nDeep copy" << endl;

    Deque dq2(dq);                 
    dq2 += 999;
    cout << "Original: " << dq.toString()  << endl;
    cout << "Copy: " << dq2.toString() << endl;

    Deque dq3;
    dq3 = dq;                       
    dq3 += 777;
    cout << "Assigned: " << dq3.toString() << endl;


    cout << "\nComparison operators" << endl;

    Deque small, large;
    small += 1;
    large += 1; 
    large += 2; 
    large += 3;

    cout << "small: " << small.toString() << endl;
    cout << "large: " << large.toString() << endl;
    cout << "small == large : " << (small == large) << endl;
    cout << "small != large : " << (small != large) << endl;
    cout << "small < large : " << (small < large) << endl;
    cout << "small <= large : " << (small <= large) << endl;
    cout << "small > large : " << (small > large) << endl;
    cout << "small >= large : " << (small >= large) << endl;


    cout << "operator!" << endl;

    cout << "Before: " << dq2.toString() << endl;
    !dq2;
    cout << "After: " << dq2.toString() << endl;


    cout << "\nException handling" << endl;

    try {
        Deque empty;
        empty.pop_front();
    } 
    catch (const DequeException& e) {
        cout << "DequeException caught: " << e.what() << endl;
    }

    try {
        Deque empty;
        empty.front();
    } 
    catch (const DequeException& e) {
        cout << "DequeException caught: " << e.what() << endl;
    }

    try {
        Deque d;
        d += 1;
        d.at(99);
    } 
    catch (const out_of_range& e) {
        cout << "out_of_range caught:   " << e.what() << endl;
    }

    try {
        Deque d;
        d += 1;
        d.remove(42);
    } 
    catch (const invalid_argument& e) {
        std::cout << "invalid_argument caught: " << e.what() << endl;
    }


    return 0;
}
