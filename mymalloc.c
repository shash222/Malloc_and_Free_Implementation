#include "mymalloc.h"

struct node{
    short dataSize;//number of blocks being referred to
    struct node* next;
};
static int i = 0;
static int firstCall = 1;
static struct node* head = (struct node*) mem;
static int memAvailable = 4096;
static int sizeOfStruct = sizeof(struct node);
// lastAddress points to the last address that can be reserved (with a data size of 0)
// Accounts for only enough space for meta data to fit
static char* lastAddress = &mem[4096];// - sizeof(struct node);


// Returns pointer to metadata right before sufficient free space
struct node* getPrevPtr(struct node* targetPtr){
    if (head + 1 == targetPtr) return head;
    struct node* ptr = head;
    if (((ptr -> next) + 1) == targetPtr) return ptr;
}

//Pointers point to address of next metadata, not next free address
void* spaceAvailable(int size){
    printf("%d\n", size);
    int spaceAvailable;
    int spaceNeeded = sizeOfStruct + size;
    if (memAvailable - spaceNeeded < 0){
        return NULL;
    }
    if (firstCall == 1) return mem;
    if (head -> dataSize == 0) return (head + 1);
    struct node* ptr = head;
    char* dataEndPtr;
    struct node* next = ptr -> next;
    //spaceNeeded refers to space needed to reserve
    spaceNeeded = size + sizeOfStruct;
    
    //No metadata will fit after address stored in lastAddress variable
    while(ptr <= (struct node*) lastAddress && ptr != NULL){
        dataEndPtr = (((char*) (ptr + 1)) + (ptr -> dataSize));
        spaceAvailable = (char*) (ptr -> next) - dataEndPtr;
//        printf("%p %p %d %p %d %d\n", ptr -> next, (ptr +1), ptr -> dataSize, dataEndPtr, spaceAvailable, spaceNeeded);
        if (spaceAvailable >= spaceNeeded) return ptr;
        ptr = ptr -> next;
    }
    return NULL;
}

void* mymalloc(int size, char* file, int line){
    //prev refers to address of metadata that's going to point to the pointer being created
    struct node* prev = (struct node*) spaceAvailable(size);
    if (prev == NULL){
        printf("Not enough memory available!\n");
        return NULL;
    }

    //If head pointer has been freed, metadata still remains but dataSize for head pointer is 0
    //Below if statement is the only exception to what prev represents
    if (prev == head + 1){
        head -> dataSize = size;
        printf("%p\n", head + 1);
        return head + 1;
    }
    memAvailable -= (size + sizeOfStruct);
    struct node* ptr;
    struct node* temp;
    if (firstCall == 1){
        ptr = prev;
        firstCall--;
        ptr -> next = (struct node*) lastAddress;
    }
    else{
        temp = prev -> next;
        prev -> next = (struct node*) (((char*) ptr) + prev -> dataSize);
        ptr = prev -> next;
        ptr -> next = temp;
    }
    ptr -> dataSize = size;

    // returning ++ptr because ptr is address at beginning of metadata, but ++ptr is address at beginning of user data (after metadata)
    struct node* usrData = ++ptr;
    printf("%p\n", usrData);
    return usrData;
}

 
//Checks if there is some metadata that points to user data address submitted
struct node* findMD(char* address){
    if(head + 1 == (struct node*) address){
        return head;
    }
    struct node* ptr = head;
    //Returning address of metadata (previous) before the metadata of data that needs to be deleted
    //(previous) metadata will point to metadata after next metadata
    while((ptr -> next) + 1 < (struct node*) lastAddress){
        if ((ptr -> next) + 1 == (struct node*) address) return ptr;
        ptr = ptr -> next;
    }
    return NULL;
    /*
    while(ptr <= lastAddress){
        if (ptr + 1 == address) return ptr;
        if (ptr + 1 > address) return NULL;
        ptr = ptr -> next;
    }
    */
}

//If freeing first pointer, need to replace pointer's metadata with metadata that points to next reserved metadata but current should
//have dataSize of 0
void myfree(char* ptr, char* file, int line){
    //metadata pointer;
    struct node* mdPtr = findMD(ptr);
    if (mdPtr == NULL){ 
        printf("Cannot free pointer, pointer does not exist!");
        return;
    }
    printf("Freed ptr at %p\n", ptr);
    if (mdPtr == head){
        memAvailable += head -> dataSize;
        head -> dataSize = 0;
        return;
    }
    memAvailable += mdPtr -> next -> dataSize;;
    mdPtr -> next = mdPtr -> next -> next;
}




/*
//int value of 0 denotes last item for stored value

void reserveMemory(char* ptr, size_t size){
    int i;
//    for (i = 0; i < size; i++) ptr[i] = size - i;
    //i < size - 1 because if size is 4, only 3 will be marked with 'b', and last will be marked with 'l'
    for (i = 0; i < size - 1; i++) ptr[i] = 'b';
    ptr[i] = 'l'
}

void printReserved(){
    int i;
    for (i = 0; i < 4096; i++){
        printf("%d: %d |", i, mem[i]);
    }
    printf("\n");
}

void* mymalloc(size_t size){
//    printf("Address from mymalloc: %p\n", &mem);
    int i;
    int max = 0;
    int consecutiveFree = 0;
     for (i = 0; i < 4096; i++){
        consecutiveFree = (mem[i] == 0) ? (consecutiveFree + 1) : 0;
        if (consecutiveFree > max) max = consecutiveFree;
        if (consecutiveFree == size){
            reserveMemory(&mem[i - consecutiveFree + 1], size);
//            printReserved();
//            printf("Allocated %d bytes\nMemory remaining %d\n", size, 4096 - size);
            return &mem[i - consecutiveFree + 1];
        }
    }
    printf("Cannot allocate enough memory. \nMax size available: %d\nAmount Needed: %d\n", max, size);
    return NULL;
}

void myfree(char* ptr){
    if (*ptr == 0){
        printf("Pointer points to null\n");
        return;
    }
    int i = 0;
    while (ptr[i] != 'b'){
        ptr[i] = 0;
        i++;
    }
    ptr[i] = 0;
//    printf("Memory was freed successfully\n");
}*/
