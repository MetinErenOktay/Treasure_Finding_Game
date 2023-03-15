program: main 
	g++ -std=c++11 main.o -fbounds-check -o findtreasure
main:
	g++ -std=c++11 -c main.cpp -o main.o
