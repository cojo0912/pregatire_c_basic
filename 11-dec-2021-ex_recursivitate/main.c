#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

int ex1(int n)
{
  if(n==0)
    return 0;

  return n%10 + ex1(n/10);
}

int ex2(int n)
{
  if(n==0)
    return 0;
  
  return 1 + ex2(n/10);
}

int ex3(int n)
{
  if(n==0)
    return 0;
  
  if(n%2==1)
  {
    return 1 + ex3(n/10);
  }
  else
  {
    return 0 + ex3(n/10);
  }
}

void ex4(int n)
{
  if(n==0)
    return;

  ex4(n-1);
  printf("%d ", n);
  
}

int ex5(int n)
{
  if(n==0)
    return 0;

  return ex5(n-1) + n;
}

int aparitii(int * v, int numar ,int poz)
{
  if(poz < 0)
    return 0;
  
  if(v[poz]==numar)
    return 1 + aparitii(v,numar,poz-1);
  else
    return 0 + aparitii(v,numar,poz-1);
}

int main()
{
  printf("%d\n", ex1(1234));
  printf("%d\n", ex2(1230));
  printf("%d\n", ex3(1230));
  ex4(10); printf("\n");
  printf("%d\n", ex5(4));

  int v[] = {1,1,1,1,2,3,4,5,6};
  printf("%d\n", aparitii(v,1,8));

  getc(stdin);
  return 0;
}

