akinator: akinator.o akinator_data.o main.o
	g++ akinator.o akinator_data.o main.o -o akinator
akinator.o: akinator.cpp akinator.hpp
	g++ -c akinator.cpp
akinator_data.o: akinator_data.cpp akinator_data.hpp
	g++ -c akinator_data.cpp
main.o: main.cpp
	g++ -c main.cpp

clean: 
	rm -rf *.o akinator
