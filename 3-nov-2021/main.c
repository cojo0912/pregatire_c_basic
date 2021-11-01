#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct person{
    char * name;
    struct person * contacts;
    struct person * next;
};

void print_contacts(struct person * contacts)
{
    while(contacts != NULL)
    {
         printf("- %s\n", contacts->name);
         contacts = contacts -> contacts;
    }
}

void print_persons(struct person * persons)
{
    while(persons!=NULL)
    {
        printf("Person: %s\n", persons->name);
        print_contacts(persons->contacts);
        persons = persons->next;
    }
}


void add_person(struct person ** persons, char*name)
{
    struct person * p = (struct person *)malloc(sizeof(struct person));
    p->next = NULL;
    p->contacts = NULL;
    p->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    strcpy(p->name, name);

    p->next = (*persons);
    (*persons) = p;
}

struct person * find_person(struct person * persons, char *name)
{
    while(persons!=NULL)
    {
        if(strcmp(persons->name, name) == 0)
            return persons;
        persons = persons -> next;
    }
    return NULL;
} 

void add_contact(struct person * persons, char*name)
{
    if(persons == NULL)
        return;

    struct person * p = (struct person *)malloc(sizeof(struct person));
    p->next = NULL;
    p->contacts = NULL;
    p->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    strcpy(p->name, name);

    if(persons -> contacts == NULL) 
    {
        persons -> contacts = p;
        return;
    }

    struct person * iter = persons -> contacts;
    while(iter->contacts != NULL)
    {
        iter = iter->contacts;
    }
    iter->contacts = p;
}

void free_node(struct person * nod)
{
    if(nod == NULL)
        return;

    free( nod->name );
    free( nod );
}

void remove_contanct(struct person * persons, char*name)
{
    if(persons->contacts == NULL)
        return;

    if(strcmp(persons->contacts->name,name)==0)
    {
        struct person * iter = persons -> contacts;
        persons -> contacts = persons -> contacts -> contacts;
        free_node(iter);
        return;
    }

    struct person * iter = persons -> contacts;
    while(iter->contacts != NULL)
    {
        if(strcmp(iter->contacts->name,name)==0)
        {
            struct person * iter2 = iter->contacts;
            iter->contacts = iter->contacts ->contacts;
            free_node(iter2);
            return;
        }
        iter = iter->contacts;
    }
}

struct person * remove_person(struct person * persons, char*name)
{
    struct person *iter = persons;
    while(iter!=NULL)
    {
        remove_contanct(iter,name);
        iter = iter ->next;
    }


    if( strcmp(persons->name, name) == 0 )
    {
        while(persons->contacts != NULL)
        {
            struct person * iter = persons->contacts;
            persons->contacts = persons->contacts->contacts;
            free_node(iter);
        }
    }

    iter = persons;
    while(iter->next != NULL)
    {
        if(strcmp(iter->next->name,name) == 0)
        {
            struct person * iter2 = iter->next;
            iter->next = iter->next->next;
            free_node(iter2);
            return persons;
        }
    }   
}

int main()
{
    char comanda;
    bool ask = true;

    struct person *list = NULL;

    while(1)
    {
        if(ask)
            printf("Command? "); 
        scanf("%c", &comanda);

        ask = true;
        char argument[255];
        char argument2[255];

        switch(comanda)
        {
            case 'R':
                printf("Person? ");
                scanf("%s",argument);
                list = remove_person(list,argument);
                break;

            case 'r':
                printf("Person A? ");
                scanf("%s",argument);
                printf("Person B? ");
                scanf("%s",argument2);
                remove_contanct(find_person(list,argument),argument2);
                break;

            case 'c':
                printf("Person A? ");
                scanf("%s",argument);
                printf("Person B? ");
                scanf("%s",argument2);
                add_contact(find_person(list,argument),argument2);
                break;

            case 'p':
                print_persons(list);
                break;

            case 'a':
                printf("Person? ");
                scanf("%s",argument);
                add_person(&list, argument);
                break;

            case 'q':
                printf("Bye!\n");
                return 0;

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