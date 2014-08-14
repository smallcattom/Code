Object=test.o threadpool.o
test: $(Object)
	gcc -o test $(Object) -lpthread
threadpool.o:threadpool.h
test.o: threadpool.h
.PHONY:clean
clean:
	-rm -f test.o threadpool.o test threadpool

