CXXFLAGS := -std=c++11 -Wall -Weverything -Wno-c++98-compat -I..
LDFLAGS  := -lSDL2

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

Sample.out: Sample.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: all clean
all:  Sample.out
clean:
	rm -f *.o *.out
