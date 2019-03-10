#include "mymalloc.c"
//Memgrind class

void malloc150Times(){
    int i;
    for (i = 0; i < 150; i++){
        char* ptr = (char*) malloc(1);
        printf("%d.   ",i);
        free(ptr);
    }
}

void malloc50TimesStorePointersArray(){
    int i;
    int j;
    char* arr[50];
    for (i = 0; i < 3; i++){
        for (j = 0; j < 50; j++){
            arr[j] = (char*) malloc(0);
            printf("Malloced %p\n", arr[j]);
        }
        for (j = 0; j < 50; j++){
            printf("Freeing %p\n", arr[j]);
            free(arr[j]);
        }
    }
}

//Temp method to test
void printArr(char** arr){
    char* ptr = *arr;
    int i;
    for (i = 0; i < 50; i++){}
    printf("%p\n", ptr + i);
}

void random1Byte(){
    int mallocCounter = 0;
    char* pointersArr[50];
    int arrIndex = 0;
    char* ptr;
    while (mallocCounter < 50){
        //even represents malloc
        int random = (rand() % 2);
        if (random == 0){
            mallocCounter++;
            ptr = (char*) malloc(1);
            pointersArr[arrIndex++] = ptr;
        }
        //odd represents free
        else if (arrIndex > 0) free(pointersArr[--arrIndex]);
    }
    printf("\n\n\n\n\n\n");
    while (arrIndex > 0) free(pointersArr[--arrIndex]);
}

void randomRandomByte(){
    int mallocCounter = 0;
    char* pointersArr[50];
    int arrIndex = 0;
    int randNum;
    while (mallocCounter < 50){
        if (rand() % 2 == 0){
            mallocCounter++;
            randNum = (rand() % 64) + 0;
            pointersArr[arrIndex++] = (char*) malloc(randNum);
        }
        //odd represents free
        else free(pointersArr[--arrIndex]);
    }
}

//mallocs 8 bytes every time up to beyond mem array capacity
//frees all pointers stored at odd indices in array
//tries to free all pointers stored at odd indices in array, but should print error as they no longer point to reserved space
//frees all pointers stored at even indices in array
void workload0(){
    char* arr[200];
    int i;
    // adding 8 below to account for all user data reservation, which is always 8
    for (i = 0; i < 200; i++) arr[i] = (char*) malloc(8);
    for (i = 1; i < 200; i += 2) free(arr[i]);
    for (i = 1; i < 200; i += 2) free(arr[i]);
    for (i = 0; i < 200; i += 2) free(arr[i]);
}

//Mallocs beyond capacity
//mallocs below capacity twice
//Prints addresses off two pointers
//frees first pointer
//mallocs twice below capacity of ptr1 to show that ptr2 and ptr3 malloc using "first fit" algorithm as desired on assignment page
void workload2(){
    malloc(4096);
    char* ptr1 = (char*) malloc(1024);
    char* ptr2 = (char*) malloc(1024);
    printf("%p %p\n", ptr1, ptr2);
    free(ptr1);
    char* ptr3 = (char*) malloc(300);
    char* ptr4 = (char*) malloc(300);
    printf("%p %p %p\n", ptr1, ptr3, ptr4);
}

void issue1(){
    int n = 4096/16;
    int i;
    for (i = 0; i < n; i++){
        malloc(8);
    }
    malloc(8);
    malloc(8);
}


int main(){
    srand(time(NULL));
//    malloc150Times();

    //What exactly do we have to do for this method
//    malloc150TimesStorePointersArray();

    //for some reason, random generator causes code to hang and break?
//    random1Byte();

//    randomRandomByte();
//    workload0();
    workload2();
//    issue2();
//    test1();
   // int i;
};
