CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

deque.o: deque.cpp deque.h
	$(CXX) $(CXXFLAGS) -c deque.cpp -o deque.o

demo: demo.cpp deque.o
	$(CXX) $(CXXFLAGS) demo.cpp deque.o -o demo

run_demo: demo
	./demo

test: test.cpp deque.o
	$(CXX) $(CXXFLAGS) test.cpp deque.o -o test

run_test: test
	./test

clean:
	rm -f deque.o demo test log.txt

rebuild: clean deque.o demo test
