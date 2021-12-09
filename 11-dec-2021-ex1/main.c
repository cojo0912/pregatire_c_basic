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
    if(find_page(concordance,word)!=NULL)
    {
        printf("URL %s is already exists\n", word);
        return concordance;
    }

    struct page * new = (struct page *)malloc(sizeof(node_t));
    new ->visited = -1;
    new ->next = NULL;
    for(int i = 0; i<MAXLINKS; i++)
        new -> links[i] = NULL;
    new -> url = (char*)malloc(sizeof(char) * (strlen(url)+1));
    strcpy(new -> url, url);

    if(web == NULL)
        return new;

    struct page * iter = web;
    if(strcmp(iter->url,new->url)>0)
    {
        new->next = web;
        return new;
    }

    // strcmp(a,b)  <==>   if(a>b)
    while(iter->next!=NULL)
    {
        if(strcmp(iter->next->url,new->url)>0)
        {
            new->next = iter->next;
            iter ->next = new;
            return web;
        }
        iter = iter -> next;
    }

    iter ->next = new;
    return web;
}

int main()
{

    char command;
    struct person *registry = NULL;
    char name[1000];
    float height;
    bool ask = true;

    node_t * concordance = NULL;

    while (1)
    {

        if (ask)
            printf("Command? ");
        scanf("%c", &command);

        ask = true;

        switch (command)
        {



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
