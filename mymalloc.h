
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <ctype.h>
#include <time.h>

#define malloc(param) mymalloc(param, __FILE__, __LINE__)
#define free(param) myfree(param, __FILE__, __LINE__)

static char mem[4096];

void reserveMemory(char* ptr, int size);

void* mymalloc(int size, char* file, int line);

void myfree(char* ptr, char* file, int line);
