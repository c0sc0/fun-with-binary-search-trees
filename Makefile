project3: main.o Employee.o
	g++ -O main.o Employee.o -o project3
	
main.o: main.cpp BinarySearchTemplate.h BinaryTreeNode.h
	g++ -O -c main.cpp
	
Employee.o: Employee.cpp Employee.h
	g++ -O -c Employee.cpp
	
clean:
	rm *.o