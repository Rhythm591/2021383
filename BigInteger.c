#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"BIGINTEGER.h"
typedef struct node
{
  int data;
  struct node *next;
}sn;
typedef struct BigInteger
{
  sn *head;
  int length;
  int sign;
}SBI;

void Insert(SBI *temp, int num)
{
  sn *p=(sn*)malloc(sizeof(sn));
  if(!p)
  {
    printf("Memory Allocation failed");
    return;
  }
  p->data=num;
  p->next=NULL;
  if(temp->head==NULL)
  {
    temp->head=p;
  }
  else{
    p->next=temp->head;
    temp->head=p;
  }
  return ;
}
SBI initialize(char *s)
{
  SBI temp;
  int n=strlen(s);
  int i=0;
  temp.head=NULL;
  temp.length=0;
  if(s[i]=='-')
  {
    temp.sign=1;
    i++;
  }
  for(i=0;i<n;i++)
  {
    Insert(&temp,s[i]-'0');
    temp.length++;
  }
  return temp;
}
void truncate(SBI *temp)
{
  sn *p=temp->head;
  sn *nonzero=p;
  while(p!=NULL)
  {
    if(p->data!=0)
    {
      nonzero=p;
    }
    p=p->next;
  }
  sn *q=nonzero;
  while(q->next!=NULL)
  {
    temp->length--;
    q=q->next;
  }
  if(nonzero)
  {
    nonzero->next=NULL;
  }
}
int compare(SBI a,SBI b)
{
  truncate(&a);
  truncate(&b);
  if(a.length>b.length)
  return 1;
  if(a.length< b.length)
  return -1;
  int res=0;
  sn *itr1=a.head, *itr2=b.head;
  while(itr1!=NULL)
  {
    if(itr1->data>itr2->data )
    res=1;
    else if(itr1->data<itr2->data)
    res=-1;
    itr1=itr1->next;
    itr2=itr2->next;
  }
  return res;
}
SBI add(SBI a, SBI b)
{
  sn *ptr1=a.head;
  sn *ptr2=b.head;
  SBI c;
 int carry=0,sum;
 while(ptr1||ptr2)
  {
    sum=0;
    if(ptr1!=NULL)
     sum=sum + ptr1->data;
    if(ptr2!=NULL)
     sum=sum + ptr2->data;
    sum=sum+carry;
    carry=sum/10;
    sum=sum%10;
   Insert(&c,sum);
     if(ptr1!=NULL)
     ptr1=ptr1->next;
    if(ptr2!=NULL)
     ptr2=ptr2->next;
 }
if(carry!=0)
  Insert(&c,carry);
     return c; 
}
SBI sub(SBI a, SBI b) {
  SBI c;
  sn *ptr1 = a.head;
  sn *ptr2 = b.head;
  int borrow = 0, diff;
  while (ptr1) {
    if (ptr2)
      diff = borrow + ptr1->data - ptr2->data;
    else
      diff = borrow + ptr1->data - 0;
    if (diff < 0) {
      borrow = -1;
      diff += 10;
    } else
      borrow = 0;
    Insert(&c, diff);
    if (ptr1 != NULL)
      ptr1 = ptr1->next;
    if (ptr2 != NULL)
      ptr2 = ptr2->next;
  }
  return c;
}
SBI mul(SBI a, SBI b) {
  SBI result;
  result.head = NULL;
  result.length = 0;
  result.sign = a.sign ^ b.sign; 

  sn *ptr1 = a.head;
while (ptr1) {
  SBI temp; 
  temp.head = NULL;
  temp.length = 0;
  temp.sign = 0;

  int carry = 0;

  sn *ptr2 = b.head;

  while (ptr2) {
    int product = (ptr1->data) * (ptr2->data) + carry;
    Insert(&temp, product % 10);
    temp.length++;
    carry = product / 10;
    ptr2 = ptr2->next;
  }

  while (carry > 0) {
    Insert(&temp, carry % 10);
    temp.length++;
    carry = carry / 10;
  }

  int i = 0;
  for (i = 0; i < result.length; i++) {
    Insert(&temp, 0);
    temp.length++;
  }

  result = add(result, temp);
  result.length++;

  ptr1 = ptr1->next;
}
return result;
}
  
SBI div1(SBI a, SBI b) {
    SBI quotient, remainder;
    SBI zero = initialize("0");
    SBI one = initialize("1");
    SBI ten = initialize("10");

    if (compare(b, zero) == 0) {
        printf("Division by zero is not allowed.\n");
        return zero;
    }

    if (compare(a, zero) == 0) {
        return zero; 
    }

    if (compare(a, b) < 0) {
        return zero; 
    }
    quotient = zero;
    remainder = a;

    while (compare(remainder, zero) > 0) {
        SBI temp = zero;
        SBI divisor = b;

        while (compare(remainder, divisor) >= 0) {
            temp = add(temp, one);
            divisor = mul(b, temp);
        }

        temp = sub(temp, one);
        divisor = mul(b, temp);

        remainder = sub(remainder, divisor);
        quotient = add(quotient, temp);
    }

   truncate(&quotient);

    return quotient;
}

void display(SBI p) {
  sn *itr = p.head;
  while (itr != NULL) {
    printf("%d\n", itr->data);
    itr = itr->next;
}}



