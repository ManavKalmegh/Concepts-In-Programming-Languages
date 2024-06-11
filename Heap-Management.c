//HEAP MANAGEMENT

#include<stdio.h>

#define HEAP_SIZE 1000
typedef enum{FREE,ALLOCATED} Status;
char Heap[HEAP_SIZE];

//meta data struct
typedef struct Meta_Data_Tag
{
    int size;
    Status status;
    struct Meta_Data_Tag* next;
}Meta_Data;

//Free List pointer
Meta_Data* free_ptr=(void*)Heap;

//Initializing Heap
void Initialize()
{
    free_ptr->status = FREE;
    free_ptr->size = HEAP_SIZE - sizeof(Meta_Data);
    free_ptr->next=NULL;

    printf("\nSize available: %d\n",free_ptr->size);
}

//Print Free List
void Print_Free_List()
{
    Meta_Data* ptr=free_ptr;
    printf("\n");

    while(ptr!=NULL)
    {
        printf("Free Block is present at %d of size %d.\n\n",(void*)ptr+sizeof(Meta_Data),ptr->size);
        ptr=ptr->next;
    }
    return;
}

//Split Block
Meta_Data* Split_Block(Meta_Data*ptr,int size)
{
    Meta_Data* new;

    new = (void*)ptr + size +1;
    new->next = ptr->next;
    new->status = FREE;
    new->size = ptr->size-size;

    printf("Block allocated from %d to %d by SPLITTING!!\n\n",(void*)ptr+sizeof(Meta_Data),(void*)ptr+size);

    return (void*)new;
}

//Allocate Memory Function
void* Allocate(int size)
{
    Meta_Data*prev,*ptr;
    
    prev=NULL;
    ptr=free_ptr;

    if(ptr!=NULL)
    {
        int flag=0;
        while(ptr!=NULL && flag==0)
        {
            if(ptr->size >= size)
            {
                flag=1;
            }
            else
            {
                prev=ptr;
                ptr=ptr->next;
                printf("One Block Checked..\n");
            }
        }
        if(flag==1)
        {
            if(ptr->size-size>=sizeof(Meta_Data)+1)
            {   
                Meta_Data*new = Split_Block(ptr,size+sizeof(Meta_Data));
                ptr->size=size;

                if(prev!=NULL)
                {
                    prev->next=new;
                }
                else
                {
                    free_ptr = new;
                }
            }
            else
            {
                printf("Block Allocated WITHOUT SPLITTING from %d to %d!!\n\n",(void*)ptr+sizeof(Meta_Data),(void*)ptr+sizeof(Meta_Data)+ptr->size);
            
                if(prev!=NULL)
                {
                    prev->next=ptr->next;
                }
                else
                {
                    free_ptr=free_ptr->next;
                }
            }
            ptr->status=ALLOCATED;
            ptr->next=NULL;

            ptr=(void*)ptr+sizeof(Meta_Data)+1;
            return (void*)ptr;
        }
        else
        {
            printf("\nEnough Memory Not Present!!\n");
        }
    }
    else
    {
        printf("\nNO FREE BLOCKS AVAILABLE!!\n");
    }

    return NULL;
}

//Free Memory Function
void Free(void* ptr)
{
    if(ptr!=NULL)
    {
    Meta_Data* del;
    del = (void*)ptr-sizeof(Meta_Data)-1;
    del->status=FREE;

    printf("\nptr=%d, del=%d, del size:%d\n",ptr,del,del->size);

    if((free_ptr!=NULL && del<free_ptr) || (free_ptr==NULL))
    {
        if((void*)del+del->size+sizeof(Meta_Data)+1==free_ptr)
        {
            //Merge
            del->size+=free_ptr->size;
            del->next=free_ptr->next;
            printf("Blocks Merged at start of freelist!!\n");
            printf("Merged from %d to %d.\n\n",del,free_ptr);
        }
        else
        {
            del->next=free_ptr;
            printf("New Block added at start of freelist!!\n");
        }
        free_ptr=del;
        printf("FreeList pointer changed!!\n");
    }
    else if(free_ptr!=NULL)
    {
        Meta_Data* front=free_ptr;
        Meta_Data* back=NULL;

        while(front<del)
        {
            back=front;
            front=front->next;
        }
        if((void*)del+del->size+sizeof(Meta_Data)+1==front)
        {
            //Merge Front
            printf("Merging %d with next block at %d....\n",del,front);
            del->size+=front->size+sizeof(Meta_Data);
            del->next=front->next;
            front->next=NULL;

            if(back!=NULL)
            {
                back->next=del;
            }
            printf("Merged with next free block!!\n");
            printf("Merged from %d to %d.\n",del,(void*)del+del->size);
        }
        else
        {
            if(back!=NULL)
            {
                back->next=del;
            }
            del->next=front;
            printf("New Block Added to Free List!!\n");
        }
        if(back!=NULL && (void*)back+back->size+sizeof(Meta_Data)+1==del)
        {
            //Merge Back
            printf("Merging %d with previous bock at %d....\n",del,back);
            back->size+=del->size+sizeof(Meta_Data);
            printf("Blocks Merged from %d to %d\n",back,(void*)back+back->size);
        }
        else
        {
            if(back!=NULL)
            {
                back->next=del;
            }
            del->next=front;
            printf("New Block added to Free List!!\n");
        }
    }
    }
    else
    {
        printf("\nCannot free-invalid pointer!!\n\n");
    }
    return;
}

//Main
int main()
{
    Initialize();

    void *ptr1=NULL,*ptr2=NULL,*ptr3=NULL,*ptr4=NULL;

    printf("Starting Address: %d\n",free_ptr);
    Print_Free_List();

    ptr1=Allocate(20);
    Print_Free_List();

    ptr2=Allocate(20);
    Print_Free_List();

    ptr3=Allocate(20);
    Print_Free_List();

    Free(ptr1);
    Print_Free_List();

    Free(ptr2);
    Print_Free_List();

    ptr4=Allocate(10);
    Print_Free_List();

    return 0;
}
