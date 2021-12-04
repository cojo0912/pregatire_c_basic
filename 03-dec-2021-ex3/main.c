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

struct person *insert(struct person *registry, char *name, float height){
    
    if (findperson(registry, name)!=NULL){
    
        printf ("This person already exists.\n");
        return registry;
    }
    
    
    struct person *p=(struct person *)malloc(sizeof (struct person));
    p->name=(char *)malloc(sizeof(char)*(strlen(name)+1));
    strcpy(p->name, name);
    p->next=NULL;    
    p->height=height;
    
    if (registry==NULL) 
       return p;
    
    struct person *iter=registry;
    
    if (p->height<registry->height)
    { 
        p->next=registry;
        return p;     
    }
    
    while (iter->next!=NULL){
    
        if (p->height<iter->next->height)
        {
            p->next=iter->next;
            iter->next=p;
            return registry;
        }
        
        if (p->height==iter->next->height)
        {
            if (strcmp(iter->next->name, p->name)>0)
            {
                p->next=iter->next;
                iter->next=p;
                return registry;
            }
        } 
     iter=iter->next;
    }
    
    iter->next=p;
    return registry;
}

void print(struct person *registry)
{

    if (registry == NULL)
        return;

    while (registry != NULL)
    {
        printf("%s is %.2f cm tall.\n", registry->name, registry->height);
        registry = registry->next;
    }
}

void correct_case(struct person *registry)
{
    struct person *iter = registry;

    while (iter != NULL)
    {

        int len = strlen(iter->name) + 1;
        for (int i = 0; i < len; i++)
        {
            iter->name[i] = tolower((unsigned char)iter->name[i]);
        }
        iter->name[0] = toupper((unsigned char)iter->name[0]);
        iter = iter->next;
    }
}

void free_space (struct person *registry)
{  
    if (registry==NULL) return;

    free(registry->name);
    free(registry);
}

struct person *delete_height (struct person *registry, float height){

    struct person *iter = NULL;

    while(NULL != registry)
    {
        if(registry -> height < height)
        {
            iter = registry;
            registry = registry -> next;
            free_space(iter);
        }else
            return registry;
    }  
    return registry;
}

void print_registry_reverse(struct person *registry){
    
    if (registry==NULL) 
        return;
    print_registry_reverse(registry->next);
    
    printf("%s is %f cm tall.", registry->name, registry->height);
    printf("\n");

    
}
 
int main()
{

    char command;
    struct person *registry = NULL;
    char name[1000];
    float height;
    bool ask = true;

    /* scanf ("%s", name);
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
        
        case 'r':
            print_registry_reverse(registry);
            break;
        
        case 'd':
            printf("minimum height ? ");
            scanf ("%f", &height);
            registry=delete_height(registry, height);
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
