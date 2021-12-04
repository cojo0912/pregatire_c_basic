#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define LOCATIE_FISIER "/Users/andrei/Documents/PersonalProjects/pregatire_c_basic/03-dec-2021-didactic/fisier.txt"

void exemplu1()
{
    FILE * pFile;
    int c;
    int n = 0;
    pFile=fopen (LOCATIE_FISIER,"r");
    if (pFile==NULL) 
    {    
        printf("Error opening file\n");
    }
    else
    {
        do 
        {
            c = getc (pFile);
            printf("<%c>",c);
        } 
        while (c != EOF);
        fclose (pFile);
    }
}

void exemplu2()
{
    FILE * pFile;
    char str[50];
    int n = 0;
    pFile=fopen (LOCATIE_FISIER,"r");
    if (pFile==NULL) 
    {    
        printf("Error opening file\n");
    }
    else
    {
        while(fgets (str,50,pFile) != NULL)
        {
            printf("<%s>",str);
        }
        fclose (pFile);
    }
}

void exemplu3()
{
    char str[255];
    while(gets(str)!=NULL)
    {
        if(strstr(str,"exit")!=NULL)
        {
            return;
        }else
        {
            printf("<%s>",str);
        }
    }
}

void exemplu4()
{
    FILE * pFile;
    char c;

    pFile=fopen(LOCATIE_FISIER,"w");

    if (pFile==NULL) 
    {    
        printf("Error opening file\n");
    }
    else
    {
        for (c = 'A' ; c <= 'Z' ; c++) 
        {
            putc (c , pFile);
        }
        fclose (pFile);
    }
}

void exemplu5()
{
    FILE * pFile;
    char c;

    pFile=fopen(LOCATIE_FISIER,"a+");

    if (pFile==NULL) 
    {    
        printf("Error opening file\n");
    }
    else
    {
        for (c = 'A' ; c <= 'Z' ; c++) 
        {
            putc (c , pFile);
        }
        fclose (pFile);
    }
}

void exemplu6()
{
    FILE * pFile;
    char str[]="ana are mere\nmihai are pere\n";

    pFile=fopen(LOCATIE_FISIER,"a+");

    if (pFile==NULL) 
    {    
        printf("Error opening file\n");
    }
    else
    {

        fputs(str , pFile);
        puts(str);
        fclose (pFile);
    }
}

void exemplu7()
{
    printf("\n\nEXEMPLU 7\n\n");

    char str1[255];
    strcpy(str1, "Ana are,mere\nMihai are.pere\nAlina are;caise\n");
    char str2[255];
    strcpy(str2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    printf("S1: %s\nS2: %s\n\n", str1, str2); 
    printf("Press to continue....\n"); getc(stdin);

    printf("Lugime string %d\n", strlen(str1));
    printf("Press to continue....\n"); getc(stdin);

    strcat(str1, str2);
    printf("%s\n",str1);
    printf("Press to continue....\n"); getc(stdin);

    printf("%d %d %d", strcmp(str1, str2), strcmp(str2, str1), strcmp(str1,str1));
    printf("Press to continue....\n"); getc(stdin);

    char * pch;
    pch=strchr(str1,'a');
    while (pch!=NULL)
    {
        printf ("found at %d\n",pch-str1+1);
        pch=strchr(pch+1,'s');
    }
    printf("Press to continue....\n"); getc(stdin);

    char * rez;
    rez = strstr(str1, "are");
    if(rez!=NULL)
        printf("strstr: %s\n", rez);
    else
        printf("strstr: NULL\n");

    rez = str1;
    do
    {
        rez = strstr(rez, "are");
        if(rez!=NULL)
        {
            printf("strstr: %s\n", rez);
            rez = rez + 1;
        }
        else
            printf("strstr: NULL\n");
    }while(rez!=NULL);
    printf("Press to continue....\n"); getc(stdin);

    pch = strtok (str1," ,.;");
    while (pch != NULL)
    {
        printf ("<%s>",pch);
        pch = strtok (NULL, " ,.;");
    }
    printf("Press to continue....\n"); getc(stdin);

    for(int i=0; i<strlen(str1); i++)
    {
        if (isalpha(str1[i]))
            str1[i] = tolower(str1[i]); // exista si toupper
    }
    printf("%s\n",str1);
    //Preentare alte functii ctype https://www.geeksforgeeks.org/ctype-hcctype-library-in-c-c-with-examples/
    printf("Press to continue....\n"); getc(stdin);

}

int main()
{
    //citire
    //exemplu1();
    //exemplu2();
    //exemplu3();

    //scriere
    //exemplu4(); -- sterge fisierul
    //exemplu5();
    //exemplu6();
    exemplu7();  
    return 0; 
}