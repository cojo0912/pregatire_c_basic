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

node_t *addWord(node_t *concordance, char word[])
{
    
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
