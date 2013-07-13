CC = gcc
# If you have a 64-bit computer, you may want to use this instead.
# CC = gcc -m32
CFLAGS = -ansi -pedantic -Wall -Werror -lm
OPTFLAG = -O2

# This is the name of the static archive to produce
# Don't change this line
LIBRARY = malloc

# The C and H files
# Your test file SHOULD NOT be in this line
CFILES = my_malloc.c my_sbrk.c
HFILES = my_malloc.h

PROGRAM = hw14

# Targets:
# test -- runs your test program
# autograde -- runs the sample autograder
# clean -- removes compiled code from the directory


test: $(PROGRAM)-test
	./$(PROGRAM)-test

autograde: $(PROGRAM)-autograder
	@for i in 1 2 3 4; do \
		./$(PROGRAM)-autograder $$i && exit; \
	done; \
	echo "Passed all cases"

$(PROGRAM)-test: lib$(LIBRARY).a test.c
	$(CC) $(CFLAGS) $(OPTFLAG) test.c -L. -l$(LIBRARY) -o $@

$(PROGRAM)-autograder: student_grader.o lib$(LIBRARY).a
	$(CC) $(CFLAGS) $(OPTFLAG) $< -L. -l$(LIBRARY) -o $@

OFILES = $(patsubst %.c,%.o,$(CFILES))

lib$(LIBRARY).a: $(OFILES)
	ar -cr lib$(LIBRARY).a $(OFILES)
%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) $(OPTFLAG) -c $<

clean:
	rm -rf lib$(LIBRARY).a $(PROGRAM)-test $(PROGRAM)-autograder $(OFILES)
