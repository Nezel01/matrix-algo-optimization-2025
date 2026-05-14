PROG=test-acm
CC=gcc
CFLAGS=-Wall -Wfatal-errors -g

all: $(PROG)
test-acm: test-acm.o acm.o graph_mat-2.o

acm.o: acm.c acm.h graph_mat-2.h
graph_mat-2.o: graph_mat-2.c graph_mat-2.h
test-acm.o: test-acm.c graph_mat-2.h acm.h

.PHONY: clean distclean
clean:
	@rm -f *.o
distclean: clean
	@rm -f $(PROG)
