all: memgrind.c
	gcc -g memgrind.c -o memgrind.out 

clean:
	$(RM) memgrind.out
