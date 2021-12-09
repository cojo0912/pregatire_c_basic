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

node_t *addWord(node_t *concordance, char word[])
{
    if(find_word(concordance,word)!=NULL)
    {
        printf("URL %s is already exists\n", word);
        return concordance;
    }

    node_t * new = (struct page *)malloc(sizeof(node_t));
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
        printf("%20s:", concordance->word);
        concordance = concordance ->nextWord;
        printf("\n");
    }
    if(nr_of_printed_words==0)
        printf("pThe concordance is empty.\n");
}

int main()
{

    char command;
    bool ask = true;
    char argument[255];
    node_t * concordance = NULL;

    while (1)
    {

        if (ask)
            printf("Command? ");
        scanf("%c", &command);

        ask = true;

        switch (command)
        {
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
