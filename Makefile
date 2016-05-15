default: program

all: program


program : mem_ds.o program.o tests.o
	gcc -g -Wall -o alloc bin/program.o bin/tests.o bin/mem_ds.o

program.o: src/ext_alloc.c include/ext_alloc.h
	gcc -g -Wall -o bin/program.o -c src/ext_alloc.c

tests.o: test/tests.c
	gcc -std=c99 -g -Wall -o bin/tests.o -c test/tests.c

mem_ds.o: src/mem_ds.c include/mem_ds.h
	gcc -g -Wall -o bin/mem_ds.o -c src/mem_ds.c

clean:
	 rm -f *.o alloc
