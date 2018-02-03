build:
	gcc my_prog.c -o my_prog
	gcc my_prog1.c -o my_prog1

run: 
	./my_prog 
	./my_prog1

all: build run

clean: rm_files all

rm_files:
	-rm -f my_prog my_prog1