all: process

process: main.o settings.o processing.o
	g++ main.o processing.o settings.o -o parse_file

main.o: main.cpp processing.h settings.h
	g++ -std=c++17 -c main.cpp processing.cpp settings.cpp

processing.o: processing.cpp processing.h settings.h
	g++ -std=c++17 -c processing.cpp settings.cpp

settings.o: settings.cpp settings.h
	g++ -std=c++17 -c settings.cpp

clean:
	rm -rf *.o process
