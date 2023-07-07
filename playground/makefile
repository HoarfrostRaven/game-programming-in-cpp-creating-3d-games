hello: hello.o
	g++ -o hello hello.o
hello.o: hello.cpp
	g++ -c -Wall --std=c++17 hello.cpp
clean:
	rm -rf *.o hello main
