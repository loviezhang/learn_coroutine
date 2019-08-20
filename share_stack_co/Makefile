G++_FLAGS = -c -O0

co_main: main.o coroutine.o swap.o
	gcc -o co_main main.o coroutine.o swap.o

main.o: main.cpp
	gcc -c $(G++FLAGS) main.cpp

coroutine.o: coroutine.cpp
	gcc -c $(G++FLAGS) coroutine.cpp

swap.o: swap.S
	gcc -c $(G++FLAGS) swap.S

clean:
	rm -f *.o co_main
