all: memgrind.c
	gcc -g -O0 memgrind.c -o memgrind.out 

clean:
	$(RM) memgrind.out
