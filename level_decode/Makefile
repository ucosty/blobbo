all: level_decode

level_decode: level_decode.o
	$(CXX) level_decode.o -o level_decode

level_decode.o: level_decode.cpp
	$(CXX) -c level_decode.cpp

clean:
	rm *o level_decode

