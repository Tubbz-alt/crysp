CXX=g++
CXXFLAGS_BASE=-Wall -Wextra  -march=native

all:
	$(CXX) -O3 $(CXXFLAGS_BASE) $(CXXFLAGS) *.cpp -o main

debug:
	$(CXX) -g  $(CXXFLAGS_BASE) $(CXXFLAGS) *.cpp -o main.debug

clean:
	rm -f main main.debug *.o *~
