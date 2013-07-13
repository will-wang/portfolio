CFLAGS2110 = -ansi -pedantic -Wall -Werror -O2

Run : main.o io.o
	gcc main.o io.o -o Run
	./Run
main.o : main.c io.h
	gcc -c $(CFLAGS2110) main.c
io.o : io.c io.h
	gcc -c $(CFLAGS2110) io.c
%.o : %.c
	gcc -c $(CFLAGS2110) $<
