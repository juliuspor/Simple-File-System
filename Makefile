all: test

test: test.o fs.o fs.h
	$(CC) -o test test.o fs.o

test.o: test.c fs.h
	$(CC) -c test.c
fs.o: fs.c fs.h
	$(CC) -c fs.c