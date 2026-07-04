#include<unistd.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdint.h>
typedef struct s_blk blk;
struct s_blk{
    size_t sz;
    bool free;
    blk *nxt;
};
blk* heap_start=NULL;
blk* lst=NULL;


void mini_zero(void* p,size_t size){
    char* ptr=(char*)p;
    size_t i;
    for(i=0;i<size;i++)
        ptr[i]=0;
}

void mini_copymem(void* src,void* dst,size_t size){
    char *p,*q;
    size_t i;
    for(i=0,q=src,p=dst;i<size;i++)
        p[i]=q[i];
}

void* mini_alloc(size_t size){
    blk* p=heap_start;
    blk* prev=NULL;
    while(p){
        if(p->free&&p->sz>=size){
            p->free=0;
            return (void*)(p+1);
        }
        prev=p;
        p=p->nxt;
    }
    blk* new=sbrk(size+sizeof(blk));
    if(new==(void*)-1)
        return (void*)-1;
    new->sz=size;
    new->free=0;
    new->nxt=NULL;
    if(!heap_start)
        heap_start=new;
    else
        prev->nxt=new;

    lst=new;
    printf("LAST : %p \n",lst);
    return (void*)(new+1);

}

void* mini_calloc(size_t n,size_t size)
{
    //size_t maxmimum deger;
    if(size==0||n>SIZE_MAX/size)
        return (void*)-1;

    size_t total=n*size;
    void* p=mini_alloc(total);
    if(p==(void*)-1)
        return (void*)-1;
    mini_zero(p,total);
    return p;

}

void* mini_realloc(void* mem,size_t size){
    if(!mem||size==0)
        return (void*)-1;
    blk* block=(blk*)mem-1;
    if(block==lst){
        sbrk(size-block->sz);
        block->sz=size;
        return (void*)(block+1);
    }else if(block->nxt->free&&block->nxt->sz+block->sz+sizeof(blk)>=size){
        block->nxt=block->nxt->nxt;
        block->sz=size;
        return (void*)(block+1);
    }else{
        void* new=mini_alloc(size);
        mini_copymem(mem,new,block->sz);
        block->free=1;
        return new;
    }
}

void mini_free(void* address){
    if(!address){
        exit(1);
    }
    blk* block=(blk*)address -1;
    block->free=1;
    return;
}

void print_heap(){
    blk* p =heap_start;
    if(!heap_start)
        exit(99);
    while(p){
        printf(" ============================\n");
        printf("Metadat block start : %p\n",p);
        printf("UserData start : %p\n",p+1);
        printf("UserData size : %ld\n",p->sz);
        printf("UserData free flag : %d\n",p->free);
        p=p->nxt;
    }
  
}

void free_all(){
    if(!heap_start)
        exit(1);
    if(brk((void*)heap_start)!=0)
        exit(1);
    else
        heap_start=NULL;
    return;
    
}





int main(){
    int i;
    int* arr=mini_alloc(5*sizeof(int));
    for(i=0;i<5;i++)
        arr[i]=9;
    void* tmp=mini_alloc(16);
    print_heap();
 
    //mini_free(tmp);
 
    arr=mini_realloc(arr,10*sizeof(int));
    //void* tmp2=mini_alloc(8);
    printf("\n-----------------------------\n");
    print_heap();
    printf("ARRAY : \n");
    for(i=0;i<10;i++)
        printf("%d. eleman : %d\n",i,arr[i]);
    /*mini_free((void*)arr);
    int* arr2=mini_alloc(5*sizeof(int));
    printf("arr2 ini elemanlari (mini_alloc) :\n");
        for(i=0;i<5;i++){
        printf("%d. eleman : %d \n",i,arr2[i]);
    }
    mini_free((void*)arr2);
    int* arr3=mini_calloc(5,sizeof(int));
    printf("arr3 ini elemanlari (mini_calloc) :\n");
        for(i=0;i<5;i++){
        printf("%d. eleman : %d \n",i,arr3[i]);
    }

    void* hs=sbrk(0);
    int* x=(int*)mini_alloc(4);
    char* c=(char*)mini_alloc(10);
    printf("heapstrt : %p\n\n--------------\n",hs);
    print_heap();
    
    mini_free((void*)x);
    print_heap();
    int* y=(int*)mini_alloc(4);
    free_all();
    *y=8;
    print_heap();
   // blk* header=(blk*)x-1;


    printf("org break : %p\n",hs);
    printf("blk start : %p\n",header);
    printf("user data : %p\n",x);

    printf("header Info : \nSize : %ld\nFree : %d\nNext : %p",header->sz,header->free,header->nxt);
*/




    return 0;
}