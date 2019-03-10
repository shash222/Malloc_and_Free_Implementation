#include "mymalloc.h"

struct node{
    short dataSize;//number of blocks being referred to
    struct node* next;
};
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
    return NULL;
}

//Pointers point to address of next metadata, not next free address
void* spaceAvailable(int size){
    int spaceAvailable;
    int spaceNeeded = sizeOfStruct + size;
    if (memAvailable - spaceNeeded < 0){
        printf("Memavailable is too little: %d %d\n", memAvailable, spaceNeeded);
        return NULL;
    }
    if (firstCall == 1) return mem;
    if (head -> dataSize == 0) return (head + 1);
    struct node* ptr = head;
    char* dataEndPtr;
    //spaceNeeded refers to space needed to reserve
    spaceNeeded = size + sizeOfStruct;
    
    //No metadata will fit after address stored in lastAddress variable
    while(ptr <= (struct node*) lastAddress && ptr != NULL){
        dataEndPtr = (((char*) (ptr + 1)) + (ptr -> dataSize));
        spaceAvailable = (char*) (ptr -> next) - dataEndPtr;
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
    memAvailable -= (size + sizeOfStruct);

    //If head pointer has been freed, metadata still remains but dataSize for head pointer is 0
    //Below if statement is the only exception to what prev represents
    if (prev == head + 1){
        head -> dataSize = size;
        return head + 1;
    }
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
        printf("Cannot free pointer, pointer does not exist!\n");
        return;
    }
    if (mdPtr == head && mdPtr -> dataSize == 0){
        printf("Cannot free pointer, pointer does not exist!\n");
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