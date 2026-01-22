CXX = g++
CXXFLAGS = -std=c++11 -Wall

example.out: example.cpp CGenerator.o
	$(CXX) $(CXXFLAGS) example.cpp -o example.out CGenerator.o

CGenerator.o: CGenerator.cpp CGenerator.h AGenerator.h
	$(CXX) $(CXXFLAGS) -c CGenerator.cpp -o CGenerator.o

clean:
	rm -f *.o example.out
