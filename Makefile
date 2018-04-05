akinator: akinator.o Akinator_Data/akinator_data.o main.o Scanf_Tree/Akinator_Parser.o
	g++ akinator.o Akinator_Data/akinator_data.o main.o Scanf_Tree/Akinator_Parser.o -o akinator
akinator.o: akinator.cpp akinator.hpp
	g++ -c akinator.cpp
Akinator_Data/akinator_data.o: Akinator_Data/akinator_data.cpp Akinator_Data/akinator_data.hpp
	g++ -c Akinator_Data/akinator_data.cpp -o Akinator_Data/akinator_data.o
Scanf_Tree/Akinator_Parser.o: Scanf_Tree/Akinator_Parser.cpp Scanf_Tree/Akinator_Parser.hpp
	g++ -c Scanf_Tree/Akinator_Parser.cpp -o Scanf_Tree/Akinator_Parser.o
main.o: main.cpp
	g++ -c main.cpp
clean: 
	rm -rf *.o akinator Akinator_Data/*.o Scanf_Tree/*.o
