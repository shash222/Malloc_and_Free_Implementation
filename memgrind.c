#include "mymalloc.c"
//Memgrind class

void malloc050Times(){
    int i;
    for (i = 0; i < 050; i++){
        char* ptr = (char*) malloc(0);
        printf("%p\n", ptr);
        free(ptr);
    }
}

void malloc050TimesStorePointersArray(){
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

void random0Byte(){
    int mallocCounter = 0;
    char* pointersArr[50];
    int arrIndex = 0;
    while (mallocCounter < 50){
        //even represents malloc
        if (rand() % 2 == 0){
            mallocCounter++;
            pointersArr[arrIndex++] = (char*) malloc(0);
        }
        //odd represents free
        else if (arrIndex > 0) free(pointersArr[arrIndex--]);
    }
    while (arrIndex >= 0) free(pointersArr[arrIndex--]);
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
        else free(pointersArr[arrIndex--]);
    }
}

void workload0(){

}

void workload2(){
    
}

void issue1(){
    int n = 4096/16;
    int i;
    for (i = 0; i < n; i++){
        malloc(8);
    }
    printf("Past Loop: ");
    malloc(8);
    malloc(8);
}

void printPtrData(struct node** arr){
    int i;
    for (i = 0; i < 17; i++){
        printf("%p %d %p\n", arr[i] - 1, (arr[i] - 1) -> dataSize, (arr[i] - 1) -> next);
    }
}

void issue2(){
    struct node* ptr = malloc(4000);
    //4008 should be used
    //408FC8
    malloc(8);
    //4024 should be used
    //408FD8
    malloc(1);
    //4033 should be used
    //408FE1
    malloc(1);
    //4042 should be used
    //408FEA
    malloc(1);
    malloc(50);
}

void test1(){
    struct node* arr[50];
    arr[0] = malloc(8);
    arr[1] = malloc(8);
    arr[2] = malloc(8);
    arr[3] = malloc(8);
    arr[4] = malloc(8);
    arr[5] = malloc(8);
    arr[6] = malloc(8);
    arr[7] = malloc(8);
    arr[8] = malloc(8);
    arr[9] = malloc(8);
    arr[10] = malloc(8);
    arr[11] = malloc(8);
    arr[12] = malloc(8);
    arr[13] = malloc(8);
    arr[14] = malloc(8);
    arr[15] = malloc(8);
    arr[16] = malloc(8);
//    printPtrData(arr);
}

int main(){
//    int arr[6];
//    struct timeval start;
//    gettimeofday(&start, NULL);
//    malloc050Times();
//    malloc050TimesStorePointersArray();
//    random0Byte();
//    randomRandomByte();
//    workload1();
//    workload2();
    issue2();
//    test1();
   // int i;
};
