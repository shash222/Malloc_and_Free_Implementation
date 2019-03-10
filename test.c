#include <stdio.h>
#include <stdlib.h>

struct a{
    int a;
    int x;
    char c;
};

int main(){
    struct a b;
    printf("Size of struct: %d", sizeof(b));
    return 0;
}