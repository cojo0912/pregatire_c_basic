#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LUNGIME 100

int numberOfWords(char **dict)
{
    if(dict == NULL)
        return 0;
    int counter = 0;
    for(int i=0; i<LUNGIME;i++)
        if(dict[i]!=NULL)
            counter ++;
    return counter;
}

void printWords(char **dict)
{
    printf("Dictionary:\n");
    if(dict == NULL)
    {
        printf("The dictionary is empty.\n");
        return;
    }

    if(numberOfWords(dict)==0)
    {
        printf("The dictionary is empty.\n");
        return;
    }

    for(int i=0; i<LUNGIME;i++)
        if(dict[i]!=NULL)
            printf("- %s\n", dict[i]);    
}

void addWord(char **dict, char *word)
{
    for(int i=0; i<LUNGIME;i++)
        if(dict[i]==NULL)
        {
            dict[i] = malloc(sizeof(char) * (strlen(word)+1));
            strcpy(dict[i], word);
            return;
        }
}

void splitSentenceToWords(char **dict, char *sentence)
{
    if(dict == NULL)
    {
        return;
    }

    char * pch = strtok (sentence," ");
    while (pch != NULL)
    {
        addWord(dict, pch);
        pch = strtok (NULL, " ,.-");
    }
}

void swapWords(char **dict, int i, int j)
{
    char *aux;

    aux = dict[i];
    dict[i] = dict[j];
    dict[j] = aux; 
}

int compare(char *a, char *b)
{
    //return 1 daca trebuie schimbate si 0 daca nu

    if(a == NULL && b != NULL)
        return 0;

    if(a != NULL && b == NULL)
        return 1;

    if(a == NULL && b == NULL)
        return 0;

    if(strlen(a)>strlen(b))
        return 1;
    else
        return 0;
}

void sortWordsOnSize(char **dict)
{
    int este_sortat = 0;
    while(este_sortat == 0)
    {
        este_sortat = 1;
        for(int i=0; i<LUNGIME-1;i++)
            if(compare(dict[i],dict[i+1])>0)
            {
                este_sortat = 0;
                swapWords(dict,i,i+1);
            }
    }
}

int countWord(char **dict, char *word)
{
    int counter = 0;
    for(int i=0; i<LUNGIME;i++)
        if(dict[i]!=NULL)
            if(strcmp(dict[i],word)==0)
                counter++;
    return counter;
}

void removeDuplicates(char **dict)
{
    for(int i=0; i<LUNGIME; i++)
        if(dict[i]!=NULL)
        {
            int nr_aparitii = countWord(dict, dict[i]);
            if(nr_aparitii>1)
            {
                int gasit = 0;
                for(int j=0; j<LUNGIME; j++)
                    if(dict[j]!=NULL)
                        if(strcmp(dict[j],dict[i])==0)
                        {
                            if(gasit == 0)
                            {
                                gasit = 1;
                            }else
                            {
                                free(dict[j]);
                                dict[j] = NULL;
                            }
                        }
            }
        }
}

int main()
{
    //char **dict;
    //dict = (char**)malloc(100*sizeof(char*)); //alocare dinamiac
    char *dict[LUNGIME]; //alocare statica
    for(int i=0; i<LUNGIME;i++)
        dict[i] = NULL;
    
    char aux[1024];
    printf("Enter a sentence: ");
    gets(aux);
    
    splitSentenceToWords(dict, aux);

    printWords(dict);

    swapWords(dict, 0 , 2);

    printWords(dict);

    sortWordsOnSize(dict);

    printWords(dict);

    removeDuplicates(dict);

    printWords(dict);

    getc(stdin);
    return 0;
}