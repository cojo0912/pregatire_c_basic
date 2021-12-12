#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

void generare(char * cuv_format, char * alfabetul_multime, int litere_de_adaugat)
{
  if(litere_de_adaugat==0)
  {
    printf("%s\n", cuv_format);
    return;
  }

  for(int i = 0; i<strlen(alfabetul_multime); i++)
  {
    cuv_format[litere_de_adaugat-1] = alfabetul_multime[i];
    generare(cuv_format, alfabetul_multime,litere_de_adaugat-1);
  }
}

void generare_ordine(char * cuv_format, char * alfabetul_multime, int poz, int max)
{
  if(poz == max)
  {
    cuv_format[max] = '\0';
    printf("%s\n", cuv_format);
    return;
  }

  for(int i = 0; i<strlen(alfabetul_multime); i++)
  {
    cuv_format[poz] = alfabetul_multime[i];
    generare_ordine(cuv_format, alfabetul_multime,poz+1, max);
  }
}

int isVocala(char a)
{
  if(strchr("aeiou",a)!=NULL)
    return 1;
  else 
    return 0;
}

void generare_ordine_2_vocale(char * cuv_format, char * alfabetul_multime, int poz, int max)
{
  if(poz == max)
  {
    cuv_format[max] = '\0';
    printf("%s\n", cuv_format);
    return;
  }

  for(int i = 0; i<strlen(alfabetul_multime); i++)
  {
    if(poz == 0)
    {
      cuv_format[poz] = alfabetul_multime[i];
      generare_ordine_2_vocale(cuv_format, alfabetul_multime,poz+1, max);
    }else
    {
      if(isVocala(alfabetul_multime[i]) == 1 && isVocala(cuv_format[poz-1] ) == 1)
      {
        return;
      }
      else
      {
        cuv_format[poz] = alfabetul_multime[i];
        generare_ordine_2_vocale(cuv_format, alfabetul_multime,poz+1, max);
      }
    }
  }
}

int main()
{
  char alph[]="abcde";
  char cuv[10];
  //generare(cuv, alph,2);
  //printf("\n");
  //generare_ordine(cuv, alph,0,2);

  //printf("%d", isVocala('a'));

  generare_ordine_2_vocale(cuv, alph,0,4);

  

  getc(stdin);
  return 0;
}

