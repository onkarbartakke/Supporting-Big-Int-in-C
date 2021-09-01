#include<stdio.h>
#include<string.h>
#define SIZE 310
#define PLUSE 1
#define MINUS -1

//NAME- BARTAKKE ONKAR SUHAS     ENROLL- BT19CSE012

//  Assignment Question, says to implement, Big int data type for supporting 1024 Bits and do operations
//  like addition, subtraction and Multiplication on it. 

//  Now, if we utilize all 1024 Bits, maximum lenghth of the Number we can represent is 308, since 2^(1023)=8.9*10^307
//  So to support 1024 Bit number and to do those operations on it, we need character array whoes lenghth is greater than 308

typedef struct bigint_tag 
{
    char digits[SIZE];
    int Sign_Bit;           //struct for Big Int tag
    int last_digit;
    
}big_int;

int max(int a, int b)
{
    if(a>b)
    return a;
    else
    return b;
}

void Initialise_big_int(big_int *num)
{
    num->digits[SIZE-1]='\0';               //Initialisation
    num->last_digit=SIZE-1;
}

void  string_to_big_int(char n1[], big_int *num)
{
    int i,j,l,z=0;
    if(n1[0]=='-')
    {
        num->Sign_Bit=MINUS;
        z=1;                                    //Taking the big int as string input from user, and then Converting it into
    }                                           // the big_int data type according to fields taken the structure defined above
    else
    num->Sign_Bit=PLUSE;
    l=strlen(n1);
    j=SIZE-1;
    num->digits[SIZE-1]='\0';
    for(i=l-1;i>=z;i--)
    {
        j--;
        num->digits[j]=n1[i];
    }
    num->last_digit=j;
    
}

void Print_Big_int(big_int num)
{
    int i;
    int f=0;
    for(i=num.last_digit;i<=SIZE-2;i++)
    {
        if(num.digits[i]!='0')                  //Prints the big_int
        {
            f=1;
            break;
        }
    }
    if(f==0)
    num.Sign_Bit=PLUSE;

    if(num.Sign_Bit==MINUS)
    {
        printf("-");
    }

    for(i=num.last_digit;i<=SIZE-2;i++)
    {
        printf("%c",num.digits[i]);
    }
}

int max_magnitude(big_int num1, big_int num2)
{
    if(num1.last_digit<num2.last_digit)
    return 0;
    else if(num2.last_digit<num1.last_digit)
    return 1;
    else                                         //This number irrespective of sign compares the magnitude(modulus value), and returns 0 if 1st
    {                                            // number is greater else 1,
        int i=num1.last_digit;
        while(num1.digits[i]==num2.digits[i] && i<=SIZE-2)
        {
            i++;
        }

        if(num1.digits[i]>num2.digits[i])
        return 0;
        else
        return 1;
    }
}
big_int Add(big_int num1, big_int num2);   //Decalration of Add, because it is used in subtract depending on the cases

big_int subtract(big_int num1, big_int num2)  //Subtraction
{
    big_int a;
    Initialise_big_int(&a);
    if(num1.Sign_Bit!=num2.Sign_Bit)
    {
        if(num1.Sign_Bit==PLUSE && num2.Sign_Bit==MINUS)
        {
            num2.Sign_Bit=PLUSE;
            a=Add(num1,num2);
            return a;
        }
        else if(num1.Sign_Bit==MINUS && num2.Sign_Bit==PLUSE)
        {
            num1.Sign_Bit=PLUSE;
            a=Add(num1,num2);
            a.Sign_Bit=MINUS;
            return a;
        }
    }
    else
    {
        int f=max_magnitude(num1,num2);
        if(f==1)
        {
            if(num1.Sign_Bit==PLUSE)
            a.Sign_Bit=MINUS;
            else
            a.Sign_Bit=PLUSE;
            big_int temp;
            Initialise_big_int(&temp);
            temp=num1;
            num1=num2;
            num2=temp;
            
        }
        else
        {
            a.Sign_Bit=num1.Sign_Bit;
        }
        int sub,i,carry;
        carry=0;
        for(i=SIZE-2;i>=num2.last_digit;i--)
        {
            sub=((num1.digits[i]-'0')-(num2.digits[i]-'0'))-carry;
            if(sub<0)
            {
                sub=sub+10;
                carry=1;
            }
            else
            {
                carry=0;
            }
            (a.last_digit)--;
            a.digits[a.last_digit]=48+sub;
        }

        for(;i>=num1.last_digit;i--)
        {
            sub=(num1.digits[i]-'0')-carry;
            if(sub<0)
            {
                sub=sub+10;
                carry=1;
            }
            (a.last_digit)--;
            a.digits[a.last_digit]=48+sub;
        }
    }
    return a;
}

big_int Add(big_int num1, big_int num2)  //Addition
{
    big_int a;
    Initialise_big_int(&a);
    if(num1.Sign_Bit==num2.Sign_Bit)
    {
        a.Sign_Bit=num1.Sign_Bit;
    }
    else
    {
        if(num1.Sign_Bit==PLUSE && num2.Sign_Bit==MINUS)
        {
            num2.Sign_Bit=PLUSE;
            a=subtract(num1,num2);
            int f=max_magnitude(num1,num2);
            if(f==1)
            a.Sign_Bit=MINUS;
            else
            a.Sign_Bit=PLUSE;
            return a;
        }
        else if(num1.Sign_Bit==MINUS && num2.Sign_Bit==PLUSE)
        {
            num1.Sign_Bit=PLUSE;
            a=subtract(num1,num2);
            int f=max_magnitude(num1,num2);
            if(f==1)
            a.Sign_Bit=PLUSE;
            else
            a.Sign_Bit=MINUS;
            return a;
        }
    }

    int n,i,l,carry=0;
    l=max(num1.last_digit,num2.last_digit);

    for(i=SIZE-2;i>=l;i--)
    {
        n=(num1.digits[i]-'0')+(num2.digits[i]-'0')+carry;
        (a.last_digit)--;
        a.digits[a.last_digit]=48+n%10;
        carry=n/10;
    }

    if(num1.last_digit<num2.last_digit)
    {
        for(;i>=num1.last_digit;i--)
        {
            n=(num1.digits[i]-'0')+carry;
            (a.last_digit)--;
            a.digits[a.last_digit]=48+n%10;
            carry=n/10;
        }

    }
    else if(num2.last_digit<num1.last_digit)
    {
        for(;i>=num2.last_digit;i--)
        {
            n=(num2.digits[i]-'0')+carry;
            (a.last_digit)--;
            a.digits[a.last_digit]=48+n%10;
            carry=n/10;
        }
    }
    
    if(carry>0)
    {
        (a.last_digit)--;
        a.digits[a.last_digit]=48+carry;
    }
    return a;
}

big_int Multiply(big_int num1, big_int num2)  //Multiplication
{
    big_int a;
    Initialise_big_int(&a);
    int i,j;
    int mul[SIZE];
    for(i=0;i<SIZE;i++)
    {
        mul[i]=0;
    }

    if(num1.Sign_Bit!=num2.Sign_Bit)
    a.Sign_Bit=MINUS;
    else
    a.Sign_Bit=PLUSE;

    int f=max_magnitude(num1,num2);
    if(f==1)
    {
        big_int temp;
        Initialise_big_int(&temp);
        temp=num1;
        num1=num2;
        num2=temp;
    }

    int carry,sum,n1,n2,m1,m2;
    carry=0;
    m1=0;
    m2=0;
    for(i=SIZE-2;i>=num2.last_digit;i--)
    {
        carry=0;
        n1=num2.digits[i]-'0';
        m1=0;
        for(j=SIZE-2;j>=num1.last_digit;j--)
        {
            n2=num1.digits[j]-'0';

            sum=(n1*n2) + mul[m1+m2] + carry;
            carry=sum/10;

            mul[m1+m2]=sum%10;
            m1++;
        }

        if(carry>0)
        mul[m1+m2]+=carry;

        m2++;
    }

    i=SIZE-1;
    while(i>=0 && mul[i]==0)
    i--;

    j=i;
    if(i==-1)
    {
        (a.last_digit)--;
        a.digits[a.last_digit]='0';
    }
    else
    {
        i=0;
        while(i<=j)
        {
            (a.last_digit)--;
            a.digits[a.last_digit]=48+mul[i];
            i++;
        }
    }
    return a;
}

int main()
{ 
    char n1[SIZE],n2[SIZE];
    big_int num1,num2,ans1,ans2,ans3;

    printf("Enter the First Number : ");
    scanf("%s",n1);

    printf("Enter the Second Number : ");
    scanf("%s",n2);

    Initialise_big_int(&num1);
    Initialise_big_int(&num2);
    Initialise_big_int(&ans1);
    Initialise_big_int(&ans2);
    Initialise_big_int(&ans3);

    string_to_big_int(n1,&num1);
    string_to_big_int(n2,&num2);

    printf("\n\n");
    Print_Big_int(num1);
    printf("  +  ");
    Print_Big_int(num2);
    ans1=Add(num1,num2);
    printf("  =  ");
    Print_Big_int(ans1);

    printf("\n\n");
    Print_Big_int(num1);
    printf("  -  ");
    Print_Big_int(num2);
    printf("  =  ");
    ans2=subtract(num1,num2);
    Print_Big_int(ans2);


    printf("\n\n");
    Print_Big_int(num1);
    printf("  *  ");
    Print_Big_int(num2);
    printf("  =  ");
    ans3=Multiply(num1,num2);
    Print_Big_int(ans3);

    return 0;
}