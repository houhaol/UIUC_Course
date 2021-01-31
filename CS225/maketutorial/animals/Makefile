# dog_program : dog.o main.o
dog_program :
		g++ dog.o main.o -o dog_program

# dog.o : dog.cpp dog.hpp
dog.o :
		g++ -c dog.cpp

main.o : main.cpp
		g++ -c main.cpp

clean : 
		rm dog_program *.o