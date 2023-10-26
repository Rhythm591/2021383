#ifndef BIGINTEGER_H
#define BIGINTEGER_H
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
SBI initialize(char *);
SBI add(SBI, SBI);
SBI sub(SBI, SBI);
SBI mul(SBI, SBI);
SBI div(SBI, SBI);

#endif