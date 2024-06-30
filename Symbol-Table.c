#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 101

//Symbol structure
typedef struct Symbol_Tag
{
    int value;
    char name[5];
    struct Symbol_Tag *next;
}Symbol;

//Hash Table Node Structure
typedef struct Hash_Table_Node_Tag
{
    Symbol *symbol_ptr[SIZE];
    struct Hash_Table_Node_Tag* next;
}Hash_Table_Node;

//Hash Function-djb2 hash function
int Hash(char str[])
{
    int hash_value = 5381;
    int i = 0;

    while(i < strlen(str))
    {
        hash_value = (hash_value<<5) + str[i++];
    }

    return hash_value%SIZE;
}

//Begin Function
Hash_Table_Node* Begin(Hash_Table_Node* H_lptr)
{
    Hash_Table_Node* h_ptr = (Hash_Table_Node*)malloc(sizeof(Hash_Table_Node));
    int i=0;

    if(H_lptr==NULL)
    {
        H_lptr=h_ptr;
        h_ptr->next=NULL;
    }
    else
    {
        h_ptr->next=H_lptr;
        H_lptr=h_ptr;
    }

    //Initializing all symbol pointer in hash node to NULL
    while(i<SIZE)
    {
        h_ptr->symbol_ptr[i] = NULL;
        i++;
    }
    
    printf("New Scope Begins..!!\n");
    return H_lptr;
}

//Lookup Function to search in current scope only
//returns the symbol node if found
Symbol* Lookup_In_Scope(Hash_Table_Node *H_lptr,int hash,char name[])
{
    Hash_Table_Node* hptr = H_lptr;
    Symbol*s_ptr = hptr->symbol_ptr[hash];
    Symbol* ret_val=NULL;
    int flag=0;
    
    while(s_ptr!=NULL && flag==0)
    {
        //Search all symbol nodes for that hash value
        if(strcmp(s_ptr->name,name)==0)
        {
            ret_val=s_ptr;
            flag=1;
        }
        s_ptr=s_ptr->next;
    }

    return ret_val;
}

//Lookup function to search print values
Symbol* Lookup(Hash_Table_Node* H_lptr,int hash,char name[])
{
    Hash_Table_Node* h_ptr = H_lptr;
    Symbol* s_ptr = NULL,*ret_val=NULL;

    int flag=0;

    while(h_ptr!=NULL && flag==0)
    {
        s_ptr=h_ptr->symbol_ptr[hash];

        while(s_ptr!=NULL && flag==0)
        {
            if(strcmp(s_ptr->name,name)==0)
            {
                flag=1;
                ret_val=s_ptr;
            }
            s_ptr=s_ptr->next;
        }
        h_ptr=h_ptr->next;
    }

    return ret_val;
}

//Insert Fucntion to insert new symbol
void Insert(Hash_Table_Node*H_lptr,int hash,char name[],int x)
{
    //Insert the the current scope only so no need to worry about other scopes
    if(H_lptr!=NULL)
    {
        Symbol* s = (Symbol*)malloc(sizeof(Symbol));
        Symbol*ptr = H_lptr->symbol_ptr[hash];
        strcpy(s->name,name);
        s->value=x;
        s->next=NULL;

        if(ptr==NULL)
        {
            H_lptr->symbol_ptr[hash]=s;
        }
        else
        {
            //Insert At Start
            s->next = ptr;
            ptr = s;
        }
    }
    else
    {
        printf("Error Assigning %s (No scopes Found)!!\n",name);
    }
}

//Assign Function
void Assign(Hash_Table_Node*H_lptr,char name[],int x)
{
    if(name[0]!='\0' && H_lptr!=NULL)
    {
        int hash=Hash(name);

        Symbol* s_ptr=Lookup_In_Scope(H_lptr,hash,name);
        //Look up if already value exists or not in current scope itself

        if(s_ptr!=NULL)
        {
            s_ptr->value=x;          //assign new value
            printf("Successfully Assigned New Value!!\n");
        }
        else
        {
            Insert(H_lptr,hash,name,x);
        }
    }
    else
    {
        printf("ERROR(Assign): Assignment of variable unsuccessfull!!\n");
    }
}

//Print Fucntion
void Print(Hash_Table_Node*H_lptr,char name[])
{
    if(name[0]!='\0' && H_lptr!=NULL)
    {
        int hash = Hash(name);
        Symbol *s_ptr = Lookup(H_lptr,hash,name);

        if(s_ptr!=NULL)
        {
            printf("\n%s = %d\n",s_ptr->name,s_ptr->value);
        }
        else
        {
            printf("ERROR(Print()): No valid definition for the variable found!!\n");
        }
    }
    else
    {
        if(H_lptr==NULL)
        {
            printf("ERROR(Print()): Print statement out of program scope!!\n");
        }
        else if(name[0]=='\0')
        {
            printf("ERROR(Print()): Invalid variable name!!\n");
        }
    }
}

//End Function
//Freeing memory is remaining
Hash_Table_Node* End(Hash_Table_Node* H_lptr)
{
    Hash_Table_Node*h_ptr=H_lptr;

    if(h_ptr!=NULL)
    {
        Symbol* sptr,*ptr;
        int i=0;

        while(i<SIZE)
        {
            sptr=H_lptr->symbol_ptr[i];
            while(sptr!=NULL)
            {
                ptr=sptr;
                sptr=sptr->next;
                free(ptr);
            }
            i++;
        }

        H_lptr = H_lptr->next;
        free(h_ptr);
        printf("Scope ended successfully..!!\n");
    }

    return H_lptr;
}

int main() 
{
    FILE *file;
    char row[20];

    file = fopen("cpl.txt", "r");

    if (file == NULL) 
    {
        printf("Error opening file!!\n");
    }
    else
    {
        Hash_Table_Node*H_lptr=NULL;

        while (fgets(row,sizeof(row),file) != NULL) {
        
            char*token=strtok(row," ");

            if(strcmp(token,"begin")==0)
            {
                H_lptr = Begin(H_lptr);
            }
            else if(strcmp(token,"assign")==0)
            {
                char name[5];
                int value;

                token = strtok(NULL," ");
                strcpy(name,token);

                token = strtok(NULL," ");
                value = atoi(token);
                
                Assign(H_lptr,name,value);
            }   
            else if(strcmp(token,"print")==0)
            {
                token = strtok(NULL," ");
                Print(H_lptr,token);
            }
            else if(strcmp(token,"end")==0)
            {
                H_lptr = End(H_lptr);
            }
            else
            {
                printf("Syntax Error!!\n");
            }
            printf("\n");
        }
        if(H_lptr != NULL)
        {
            printf("Program not ended properly!!\n");
        }
    }
    fclose(file);

    return 0;
}
