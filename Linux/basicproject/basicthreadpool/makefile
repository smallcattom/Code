test: test.o threadpool.o
	gcc -o test test.o threadpool.o -lpthread
threadpool.o:threadpool.c threadpool.h
	gcc -c threadpool.c 
test.o: test.c threadpool.h
	gcc -c test.c 
clean:
	rm -f test.o threadpool.o test threadpool

