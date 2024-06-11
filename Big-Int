//BIG INT IMPLEMENTATION

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 310

typedef enum{MINUS,PLUS} SIGN;

typedef struct BigInt_tag{
    int *digits;
    SIGN sign;
    int size;
}BigInt;

BigInt Sub(BigInt a,BigInt b);

//create bigint
BigInt CreateBigInt(char *str){

    BigInt n;
    n.sign=(str[0]=='-') ? MINUS : PLUS;

    //determining actual size of bigint
    int i=0;
    if(n.sign==MINUS){
        i=1;
        while(str[i]=='0'){
            i++;
        }
    }
    else{
        while(str[i]=='0'){
            i++;
        }
    }
    n.size=strlen(str)-i;

    n.digits=(int *)malloc(sizeof(int)*n.size);

    for(int j=n.size-1;j>=0;j--){
        n.digits[j]=str[i++]-'0';
    }

    return n;
}

//print big int
void Print(BigInt n){

    if(n.sign==MINUS){
        printf("-");
    }
    if(n.size<SIZE){
        int i=n.size-1;
        while(n.digits[i]=='0'){
            i--;
        }
        if(i==-1){
            printf("0");
        }
        while(i>=0){
            printf("%d",n.digits[i--]);
        }
        printf("\n");
    }
    else{
        printf("\nBig Integer limit exceeded!!\n");
    }
}

//compare big ints
//0 if a==b,>0 if a>b,<0 if a<b
int Compare(BigInt a,BigInt b){

    int ret,i=0;

    if(a.size==b.size){
        i=b.size-1;
        while(i>=0 && a.digits[i]==b.digits[i]){
            i--;
        }
        if(i<0){
            ret=0;
        }
        else{
            ret=a.digits[i]-b.digits[i];
        }
    }
    else{
        ret=a.size-b.size;
    }
    return ret;
}

//add two bigints
BigInt Add(BigInt a,BigInt b){

    BigInt sum;

    sum.size=(a.size>b.size)?(a.size+1):(b.size+1);
    sum.digits=(int *)malloc(sizeof(int)*sum.size);

    for(int i=0;i<sum.size;i++){
        sum.digits[i]=0;
    }

    int carry=0;
    int ans=Compare(a,b);

    if(a.sign==b.sign){
        int i=0;
        while(i<a.size && i<b.size){
            int add=a.digits[i]+b.digits[i];
            sum.digits[i]=(add+carry)%10;
            carry=add/10;
            i++;
        }
        sum.digits[i]+=carry;
        while(i<a.size){
            sum.digits[i]+=a.digits[i];
            i++;
        }
        while(i<b.size){
            sum.digits[i]+=b.digits[i];
            i++;
        }
        sum.sign=a.sign;
    }
    else if(a.sign==MINUS){
        a.sign=PLUS;
        sum=(ans>0)?Sub(a,b):Sub(b,a);
        sum.sign=(ans>0)?MINUS:PLUS;
        a.sign=MINUS;
    }
    else{
        b.sign=PLUS;
        sum=(ans>0)?Sub(a,b):Sub(b,a);
        sum.sign=(ans>0)?PLUS:MINUS;
        b.sign=MINUS;
    }
    return sum;
}

//subtract two big int
BigInt Sub(BigInt a,BigInt b){                                  //a-b

    BigInt diff;
    diff.size=(a.size>b.size)?a.size:b.size;
    diff.digits=(int *)malloc(sizeof(int)*diff.size);

    for(int i=0;i<diff.size;i++){
        diff.digits[i]=0;
    }

    int ans=Compare(a,b);

    if(b.sign==PLUS && a.sign==PLUS){
        int borrow=0;
        if(ans>0){
            diff.sign=PLUS;
            int i=0;
            while(i<b.size){
                int sub=a.digits[i]-borrow-b.digits[i];
                if(sub<0){
                    sub+=10;
                    borrow=1;
                }
                else{
                    borrow=0;
                }
                diff.digits[i]=sub;
                i++;
            }
            while(i<a.size){
                int sub=a.digits[i]-borrow;
                if(sub<0){
                    sub+=10;
                    borrow=1;
                }
                else{
                    borrow=0;
                }
                diff.digits[i]=sub;
                i++;
            }
        }
        else if(ans<0){
            diff.sign=MINUS;
            int i=0;
            while(i<a.size){
                int sub=b.digits[i]-borrow-a.digits[i];
                if(sub<0){
                    sub+=10;
                    borrow=1;
                }
                else{
                    borrow=0;
                }
                diff.digits[i]=sub;
                i++;
            }
            while(i<b.size){
                int sub=b.digits[i]-borrow;
                if(sub<0){
                    sub+=10;
                    borrow=1;
                }
                else{
                    borrow=0;
                }
                diff.digits[i]=sub;
                i++;
            }
        }
    }
    else if(a.sign==MINUS && b.sign==PLUS){
        a.sign=PLUS;
        diff=Add(a,b);
        diff.sign=MINUS;
    }
    else if(a.sign==PLUS && b.sign==MINUS){
        b.sign=PLUS;
        diff.sign=PLUS;
        diff=Add(a,b);
    }
    else{
        int borrow=0;

        if(ans>0){
            diff.sign=MINUS;
            int i=0;
            while(i<b.size){
                int sub=a.digits[i]-borrow-b.digits[i];
                if(sub<0){
                    sub+=10;
                    borrow=1;
                }
                else{
                    borrow=0;
                }
                diff.digits[i]=sub;
                i++;
            }
            while(i<a.size){
                int sub=a.digits[i]-borrow;
                if(sub<0){
                    sub+=10;
                    borrow=1;
                }
                else{
                    borrow=0;
                }
                diff.digits[i]=sub;
                i++;
            }
        }
        else if(ans<0){
            diff.sign=PLUS;
            int i=0;
            while(i<a.size){
                int sub=b.digits[i]-borrow-a.digits[i];
                if(sub<0){
                    sub+=10;
                    borrow=1;
                }
                else{
                    borrow=0;
                }
                diff.digits[i]=sub;
                i++;
            }
            while(i<b.size){
                int sub=a.digits[i]-borrow;
                if(sub<0){
                    sub+=10;
                    borrow=1;
                }
                else{
                    borrow=0;
                }
                diff.digits[i]=sub;
                i++;
            }
        }
    }
    return diff;
}

//mul two big int
BigInt Mul(BigInt a,BigInt b){

    BigInt mul;
    mul.size=a.size+b.size;
    if(mul.size<SIZE){
        mul.digits=(int *)malloc(sizeof(int)*mul.size);

        for(int i=0;i<mul.size;i++){
            mul.digits[i]=0;
        }
        for(int i=0;i<a.size;i++){
            int carry=0;
            int j=0;
            for(j=0;j<b.size;j++){
                
                int prod = (a.digits[i]*b.digits[j])+carry;
                carry=prod/10;
                mul.digits[i+j]+=(prod%10);

                if(mul.digits[i+j]>9){
                    mul.digits[i+j+1]+=1;
                    mul.digits[i+j]%=10;
                }
            }
            while(carry!=0){
                mul.digits[i+j]+=(carry%10);
                if(mul.digits[i+j]>9){
                    mul.digits[i+j+1]+=1;
                    mul.digits[i+j]%=10;
                }
                carry/=10;
                j++;
            }
        }
        mul.sign=(a.sign==b.sign)?PLUS:MINUS;
    }
    return mul;
}

int main(){

    char *a,*b;

    a=(char*)malloc(sizeof(char)*SIZE);
    b=(char*)malloc(sizeof(char)*SIZE);

    printf("\nEnter num 1: ");
    gets(a);
    BigInt n=CreateBigInt(a);
    //Print(n);

    printf("\nEnter num 2: ");
    gets(b);
    BigInt m=CreateBigInt(b);
    //Print(m);
    
    BigInt sum=Add(n,m);
    printf("\nSUM OF THE TWO NOS: ");
    Print(sum);

    BigInt sub=Sub(n,m);
    printf("\nSUBSTRACTION OF THE TWO NOS: ");
    Print(sub);

    BigInt mul=Mul(n,m);
    printf("\nMULTIPLICATION OF THE TWO NOS: ");
    Print(mul);

    return 0;
}
