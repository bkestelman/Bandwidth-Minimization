CC = gcc
CFLAGS = -wall -werror -pedantic
DEPS = graph_structs.h
OUT = bandwidth

all: $(OUT) 

bandwidth: bandwidth.o graph_structs.o
	gcc -o $(OUT) $^ 	

bandwidth.o: bandwidth.c $(DEPS) 
	gcc -c $^ 

graph_structs.o: graph_structs.c $(DEPS)
	gcc -c $^

clean:
	rm -rf *.o *.gch *.out $(OUT) 
