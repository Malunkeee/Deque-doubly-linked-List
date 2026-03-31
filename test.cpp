#include "deque.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace mydeque;
using namespace std;

ofstream logFile;
int totalTests = 0, passedTests = 0;

void log(const string& line) {
    cout << line << endl;
    logFile << line << endl;
}

void check(bool condition, const string& testName) {
    ++totalTests;
    if (condition){
       ++passedTests; 
    } 
    log((condition ? "Pass  " : "Fail  ") + testName);
}

int main() {
    logFile.open("log.txt");
    if (!logFile.is_open()) {
         cerr << "Could not open log.txt\n"; 
         return 1; 
    }

    log("\nConstruction:");

    Deque dq;
    check(dq.empty(), "New deque is empty");
    check(dq.size() == 0, "New deque size == 0");
    check(dq.toString() == "Deque size = 0 Elements = ", "toString() on empty");

    log("\nPush and Read:");
    dq.push_back(10); 
    dq.push_back(20); 
    dq.push_front(5); 
    dq += 30;
    check(dq.front() == 5,  "front() == 5");
    check(dq.back() == 30, "back() == 30");
    check(dq.at(1) == 10, "at(1) == 10");

    log("\nSearch:");
    check(dq[10]  == 1,  "Search existing num index = 1");
    check(dq[999] == -1, "Search not-exsisting num returns -1");

    log("\nUpdate:");
    dq.update(0, 100);
    check(dq.at(0) == 100, "update(0, 100)");
    dq *= Deque::UpdateArg{0, 5};
    check(dq.at(0) == 5,   "operator*= update");

    log("\nPop:");
    Deque dq2; 
    dq2 += 1; 
    dq2 += 2; 
    dq2 += 3;
    check(dq2.pop_front() == 1, "pop_front() == 1");
    check(dq2.pop_back()  == 3, "pop_back() == 3");
    dq2.pop_front();
    check(dq2.empty(), "Empty after all pops");

    log("\nRemove:");
    Deque dq3; 
    dq3 += 10; 
    dq3 += 20; 
    dq3 += 30;
    dq3.remove(20);
    check(dq3[20] == -1, "after remove(20) not found returns -1");
    dq3 -= 10;
    check(dq3.front() == 30,  "front()==30 after operator-=");

    log("\nClear:");
    !dq3;
    check(dq3.empty(), "empty() after operator!");
    check(dq3.size() == 0, "size()==0 after operator!");

    log("\nDeep Copy:");
    Deque orig; 
    orig += 1; 
    orig += 2; 
    orig += 3;
    
    Deque copied(orig); 
    copied += 999;
    check(orig.size() == 3,  "Original unchanged after copy");
    check(orig[999]   == -1, "999 is not in original");

    Deque assigned; 
    assigned = orig; 
    assigned += 777;
    check(orig.size() == 3,  "Original unchanged after assign");
    check(orig[777]   == -1, "777 not in original");

    log("\nComparisons:");
    Deque a, b; a += 1; b += 10; b += 20;
    check(a == a, "a == a");
    check(a != b, "a != b");
    check(a < b, "a < b");
    check(a <= b, "a <= b");
    check(b > a, "b > a");
    check(b >= a, "b >= a");

    log("\nExceptions:");

    bool c = false; 
        try { 
            Deque d; 
            d.pop_front();      
        } 
        catch(const DequeException&) { 
            c = true; 
        } 
    check(c, "DequeException: pop_front empty"); 
    
    c = false;
    try { 
        Deque d; 
        d.pop_back();       
    } 
    catch(const DequeException&){
         c = true; 
    } 
    check(c, "DequeException: pop_back empty"); 

    c = false;
    try { 
        Deque d; 
        d.front();          
    } 
    catch(const DequeException&){ 
        c=true; 
    } 
    check(c, "DequeException: front empty"); 

    c = false;
    try { 
        Deque d; 
        d.back();           
    } 
    catch(const DequeException&){ 
        c = true; 
    } 
    check(c, "DequeException: back empty"); 

    c = false;
    try { 
        Deque d; 
        d+=1; 
        d.at(99);     
    } 
    catch(const out_of_range&){ 
        c = true; 
    } 
    check(c, "out_of_range: at()"); 

    c = false;
    try { 
        Deque d; 
        d+=1; 
        d.update(99,0);
    } 
    catch(const out_of_range&){ 
        c = true; 
    } 
    check(c, "out_of_range: update()"); 

    c = false;
    try { 
        Deque d; 
        d+=1; 
        d.remove(42); 
    } 
    catch(const invalid_argument&){ 
        c = true; 
    } 
    check(c, "invalid_argument: remove()"); 

    c = false;
    try { 
        Deque d; 
        d+=1; 
        d -= 42;      
    } 
    catch(const invalid_argument&){ 
        c = true; 
    } 
    check(c, "invalid_argument: operator-="); 

    log("");

    stringstream ss;
    ss << "Results: " << passedTests << " / " << totalTests << " passed";
    
    log(ss.str());
    log(passedTests == totalTests ? "All tests passed!" : "Some tests failed!");

    logFile.close();
    return 0;
}