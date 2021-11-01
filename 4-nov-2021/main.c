#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void read_contents(char *filename, int contents[])
{
    FILE * file;
    file = fopen (filename , "r");
    if (file == NULL)
    {
        printf("Cannot open file %s\n", filename);
        return;
    }
    
    int i = 0;
    int aux = EOF;
    do
    {
        aux = fgetc(file);
        contents[i++]=aux;
    }while(aux!=EOF);

    fclose(file);
}

void cat(int contents[])
{
    int i = 0;
    while(contents[i] != EOF)
    {
        printf("%c", contents[i++]);
    }
    printf("\n");
}

void rev(int contents[])
{
    int i=-1;
    int j=0;

    
    do{
        i++;
        if(contents[i] == '\n' || contents[i] == EOF)
        {
            j = i-1;
            while(j>=0 && contents[j]!='\n')
                printf("%c",contents[j--]);
            printf("\n");
        }       
    }while(contents[i] != EOF);

}

void wc(int contents[])
{
    int lines = 0;
    int words = 0;

    int i=0;
    while(contents[i] != EOF)
    {
        if(contents[i] == '\n')
            lines++;
        if( (contents[i] != ' ' && contents[i] != '\n') && (contents[i+1] == ' ' || contents[i+1] == '\n') )
            words++;
        i++;
    }

    printf("%d lines, %d words, %d characters\n",lines,words,i);
}

void parindrome(char * string)
{   
    for(int i=0; i<strlen(string)/2; i++)
        if(string[i] != string[strlen(string) - i - 1])
        {
            printf("Is not a palindrome.\n");
            return;
        }
    printf("Is a palindrome.\n");
}

void brackets(int contents[])
{
    int lines = 0;
    int character = 0;

    int count = 0;
    int i = 0;

    while(contents[i] != EOF)
    {
        if(contents[i] == '(')
            count++;
        if(contents[i] == ')')
            count--;

        if(count < 0)
        {
            printf("Brackets not matched at line %d character %d.\n", lines, character);
            return;
        }

        character++;
        if(contents[i] == '\n')
        {
            lines++;
            character=0;
        }
        i++;   
    }

    if(count == 0)
        printf("Brackets are matched at end of file.\n");
    else
        printf("Brackets are not matched at end of file.\n");
}

void tac(int contents[])
{
    int lungime = 0;
    
    while(contents[lungime] != EOF)
        lungime++;
    lungime--;
    for(int i = lungime; i >=0; i--)
    {
        if(i==0)
            printf("\n");
        if(contents[i] == '\n' || i==0)
        {
            for(int j=i; j<lungime; j++)
                printf("%c", (char)contents[j]);
            lungime = i;
        }
    }
}

int main()
{
    char comanda;
    bool ask = true;

    int contents[10000];
    contents[0] = EOF;

    while(1)
    {
        if(ask)
            printf("Command? "); 
        scanf("%c", &comanda);

        ask = true;
        char argument[255];

        switch(comanda)
        {
            case 't':
                tac(contents);
                break;

            case 'b':
                brackets(contents);
                break;

            case 'p':
                printf("String? ");
                scanf("%s",argument);
                parindrome(argument);
                break;

            case 'w':
                wc(contents);
                break;

            case 'r':
                rev(contents);
                break;

            case 'c':
                cat(contents);
                break;

            case 'f':
                printf("File name? ");
                scanf("%s",argument);
                read_contents(argument,contents);
                break;

            case '\r':
            case '\n':
                ask = false;
                break;

            default:
                printf("Unknown command '%c'.\n", comanda);
                break;
        }
    }
    return 0;
}