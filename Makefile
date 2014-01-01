CXX= g++
CXXFLAGS= -g -W -Wall -Werror

all: dijkstras.cc
	$(CXX) dijkstras.cc priority_queue.H $(CXXFLAGS) -o a.out
	
clean:
	rm *~ *.o a.out
