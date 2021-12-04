#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

struct person
{
    char *name;
    float height;
    struct person *next;
};

struct person *findperson(struct person *registry, char *name)
{

    while (registry != NULL)
    {
        if (strcmp(registry->name, name) == 0)
        {
            return registry;
        }
        registry = registry->next;
    }

    return NULL;
}

struct person *insert(struct person *registry, char *name, float height)
{

    if (findperson(registry, name) != NULL)
    {

        printf("This person already exists.\n");
    }

    struct person *p = (struct person *)malloc(sizeof(struct person));
    p->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    p->next = NULL;
    strcpy(p->name, name);
    p->height = height;

    if (registry == NULL)
        return p;

    struct person *iter = registry;

    if (p->height < iter->height)
    {
        p->next = registry;
        return p;
    }

    while (iter->next != NULL)
    {

        if (p->height < iter->next->height)
        {
            p->next = iter->next;
            iter->next = p;
            return registry;
        }

        if (p->height == iter->next->height)
        {
            if (strcmp(iter->next->name, p->name) > 0)
            {
                p->next = iter->next;
                iter->next = p;
                return registry;
            }        
        }
        iter = iter->next;
    }
}

void print(struct person *registry)
{

    if (registry == NULL)
        return;

    while (registry != NULL)
    {
        printf("%s is %f cm tall.", registry->name, registry->height);
        printf("\n");

        registry = registry->next;
    }
}

void lower_case(struct person *registry)
{

    struct person *iter = registry;

    while (iter != NULL)
    {

        int len = strlen(iter->name);
        
        for (int i = 0; i < len; i++)
        {
            iter->name[i] = tolower(iter->name[i]);
        }

        iter->name[0] = toupper(iter->name[0]);
        iter = iter->next;
    }
}

void correct_case(struct person *registry)
{

    lower_case(registry);

    struct person *iter = registry;

    while (iter != NULL)
    {

        int len = strlen(iter->name) + 1;
        char name2[len];
        strcpy(name2, iter->name);

        for (int i = 0; i < len; i++)
        {
            name2[0] = toupper((unsigned char)name2[0]);
            break;
        }

        strcpy(iter->name, name2);

        iter = iter->next;
    }
}

struct person *delete_height(struct person *registry, float height)
{
}

int main()
{

    char command;
    struct person *registry;
    char name[1000];
    float height;
    bool ask = true;

    /*  scanf ("%s", name);
    scanf ("%f", &height);
    registry=insert(registry,name,height);
    
    scanf ("%s", name);
    scanf ("%f", &height);
    registry=insert(registry,name,height);
    
    scanf ("%s", name);
    scanf ("%f", &height);
    registry=insert(registry,name,height);
    
    lower_case (registry);
    print (registry); */

    while (1)
    {

        if (ask)
            printf("Command? ");
        scanf("%c", &command);

        ask = true;

        switch (command)
        {

        case 'q':
            printf("Bye!\n");
            break;

        case 'i':
            printf("Name? ");
            scanf("%s", name);
            printf("Height? ");
            scanf("%f", &height);
            registry = insert(registry, name, height);
            break;

        case 'p':
            print(registry);
            break;

        case 'c':
            correct_case(registry);
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
