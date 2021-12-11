#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXINDEX 10
typedef struct _node_t {
  char *word;
  int indices[MAXINDEX];
  struct _node_t *nextWord;
} node_t;

//char * word <==> char word[]

node_t *find_word(node_t *concordance, char word[])
{
    while(concordance != NULL)
    {
        if(strcmp(concordance -> word, word) == 0)
            return concordance;
        concordance = concordance -> nextWord;
    }
    return NULL;
}

int calculate_max_index(node_t *concordance)
{
    int max_index = -1;
    while(concordance != NULL)
    {
        for(int i=0; i<MAXINDEX; i++)
            if(concordance->indices[i] > max_index)
                max_index = concordance->indices[i];
        concordance = concordance ->nextWord;
    }
    return max_index;
}

node_t *addWord(node_t *concordance, char word[])
{
    if(find_word(concordance,word)!=NULL)
    {
        //printf("word %s is already exists\n", word);
        return concordance;
    }

    node_t * new = (node_t *)malloc(sizeof(node_t));
    new ->nextWord = NULL;
    for(int i = 0; i<MAXINDEX; i++)
        new -> indices[i] = -1;
    new -> word = (char*)malloc(sizeof(char) * (strlen(word)+1));
    strcpy(new -> word, word);

    if(concordance == NULL)
        return new;

    node_t * iter = concordance;
    if(strcmp(iter->word,new->word)>0)
    {
        new->nextWord = concordance;
        return new;
    }

    // strcmp(a,b)  <==>   if(a>b)
    while(iter->nextWord!=NULL)
    {
        if(strcmp(iter->nextWord->word,new->word)>0)
        {
            new->nextWord = iter->nextWord;
            iter ->nextWord = new;
            return concordance;
        }
        iter = iter -> nextWord;
    }

    iter ->nextWord = new;
    return concordance;
}

void printConcordance(node_t *concordance)
{
    int nr_of_printed_words = 0;
    while(concordance != NULL)
    {
        printf("%10s:", concordance->word);
        for(int i=0; i<MAXINDEX; i++)
            if(concordance->indices[i]!=-1)
                printf(" %d", concordance->indices[i]);
        concordance = concordance ->nextWord;
        printf("\n");
        nr_of_printed_words++;
    }
    if(nr_of_printed_words==0)
        printf("The concordance is empty.\n");
}

void addIndex(node_t *concordance, char word[], int index)
{
    node_t *aux = find_word(concordance, word);
    if(aux != NULL)
    {
        int isInserted = 0;
        for(int i=0; i<MAXINDEX; i++)
            if(aux->indices[i]==-1)
            {
                aux->indices[i] = index;
                isInserted = 1;
                break;
            }
        if(isInserted == 0)
            printf("Word's index list is full");
    }else
        printf("Word %s was not found", word);
}

char *findWordAtIndex(node_t *concordance, int index)
{
    while(concordance != NULL)
    {
        for(int i=0; i<MAXINDEX; i++)
            if(concordance->indices[i]==index)
                return concordance->word;
        concordance = concordance->nextWord;
    }
    return NULL;
}

void printOriginalText(node_t *concordance, int index)
{
    for(int i=0; i<=index; i++)
    {
        char * aux = findWordAtIndex(concordance, i);
        if(aux!=NULL)
            printf("%s ", aux);
        else
            printf("? ");
    }
    printf("\n");
}

void removeWord(node_t **concordance, char word[])
{
    if((*concordance) == NULL)
        return;

    node_t * p = find_word(*concordance,word);
    if(p==NULL)
    {
        printf("word %s is not already on the concordance\n", word);
        return;
    }

    if((*concordance) == p)
    {
        (*concordance) = (*concordance) -> nextWord;
    }else
    {
        node_t * iter = (*concordance);
        while(iter->nextWord!=p)
            iter = iter ->nextWord;
        iter->nextWord = iter->nextWord->nextWord;
    }

    free(p->word);
    free(p);
}

void readFile(node_t **concordance, char *filename, int *index)
{
    FILE *fp;
    fp = fopen(filename,"r");

    if(fp==NULL)
        return;

    char aux[255];

    while (fscanf(fp, " %s", aux) != EOF) 
    {
        (*index)++;
        if(find_word(*concordance, aux)!=NULL)
            (*concordance) = addWord(*concordance,aux);
        addIndex(*concordance,aux,*index);
    }
    fclose(fp);
    return;
}

int main()
{

    char command;
    bool ask = true;
    char argument[255];
    int argument2;
    int max_index = -1;
    node_t * concordance = NULL;

    while (1)
    {

        if (ask)
            printf("Command? ");
        scanf("%c", &command);
        char * aux;
        ask = true;

        switch (command)
        {
        case 'r':
            printf("File name? ");
            scanf("%s", argument);
            readFile(&concordance, argument, &max_index);
            break;

        case 'W':
            printf("Word? ");
            scanf("%s", argument);
            removeWord(&concordance, argument);
            max_index = calculate_max_index(concordance);
            break;

        case 'o':
            printOriginalText(concordance, max_index);
            break;

        case 'f':
            printf("Index? ");
            scanf("%d",&argument2);
            aux = findWordAtIndex(concordance, argument2);
            if(aux!=NULL)
                printf("The word at index %d is %s.", argument2, aux);
            else    
                 printf("There is no word at index %s.", argument2);
            break;

        case 'i':
            printf("Word index? ");
            scanf("%s %d", argument, &argument2);
            addIndex(concordance,argument,argument2);
            max_index = calculate_max_index(concordance);
            break;

        case 'w':
            printf("Word? ");
            scanf("%s", argument);
            concordance = addWord(concordance, argument);
            break;

        case 'p':
            printConcordance(concordance);
            break;

        case ' ':
        case '\r':
        case '\n':
            ask = false;
            break;

        default:
            printf("Unknown command '%c'.\n", command);
            break;
        }
    }
}
