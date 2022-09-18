all: parse_file

parse_file: main.o settings.o processing.o
	g++ main.o processing.o settings.o -o parse_file

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

processing.o: processing.cpp
	g++ -std=c++17 -c processing.cpp

settings.o: settings.cpp
	g++ -std=c++17 -c settings.cpp

clean:
	rm -rf *.o parse_file
