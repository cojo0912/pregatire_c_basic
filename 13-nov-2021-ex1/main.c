#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAXLINKS 10
struct page {
    char *url; // stores the URL of the page
    int visited; // keep track of whether the page was visited
    struct page *links[MAXLINKS];
    struct page *next;
};

void find_page2(struct page **web, char *url)
{
    while((*web) != NULL)
    {
        if(strcmp((*web) -> url, url) == 0)
            return;
        (*web) = (*web) -> next;
    }
}

struct page *find_page(struct page *web, char *url)
{
    while(web != NULL)
    {
        if(strcmp(web -> url, url) == 0)
            return web;
        web = web -> next;
    }
    return NULL;
}

struct page *add_page (struct page *web, char *url)
{
    if(find_page(web,url)!=NULL)
    {
        printf("URL %s is already on the web\n", url);
        return web;
    }

    struct page * new = (struct page *)malloc(sizeof(struct page));
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

void print_web (struct page *web)
{
    while(web != NULL)
    {
        printf("{URL=\"%s\",visited=%d} -> ", web->url, web->visited);
        for(int i = 0; i<MAXLINKS; i++)
            if(web -> links[i] != NULL)
                printf("\"%s\" ", web -> links[i] -> url);
        printf("\n");        
        web = web -> next;
    }
}

void reset_visited (struct page *web)
{
    while(web != NULL)
    {
        web -> visited = 0;
        web = web -> next;
    }
}

void add_link(struct page *web, char *source_url, char *dest_url)
{
    struct page * source = find_page(web,source_url);
    if(source == NULL)
    {
        printf("Source URL %s is not on the web\n", source_url);
        return;
    }

    struct page * dest = find_page(web,dest_url);
    if(dest == NULL)
    {
        printf("Dest URL %s is not on the web\n", dest_url);
        return;
    }

    if(source == dest)
    {
        printf("Source and destination URL cannot be the same\n");
        return;
    }

    for(int i = 0; i<MAXLINKS; i++)
    {
        if(source -> links[i] == dest)
        {
            printf("%s is already a destination for %s\n", dest_url, source_url);
            return;
        }     
    }

    for(int i = 0; i<MAXLINKS; i++)
    {
        if(source -> links[i] == NULL)
        {
            source -> links[i] = dest;
            return;
        }       
    }

    printf("Maximum number of links reached\n");
}

void remove_page (struct page **web, char *url)
{
    if((*web) == NULL)
        return;

    struct page * p = find_page(*web,url);
    if(p==NULL)
    {
        printf("URL %s is not already on the web\n", url);
        return;
    }

    struct page * iter = (*web);
    while(iter != NULL)
    {
        for(int i = 0; i<MAXLINKS; i++)
            if(iter -> links[i] == p)
            {
                iter -> links[i] = NULL;
                break;
            }
        iter = iter->next;
    }

    if((*web) == p)
    {
        (*web) = (*web) -> next;
    }else
    {
        struct page * iter = (*web);
        while(iter->next!=p)
            iter = iter ->next;
        iter->next = iter->next->next;
    }

    free(p->url);
    free(p);
}

void reachable (struct page *page)
{
    if(page == NULL)
        return;
    
    if(page -> visited > 0)
        return;

    printf("%s\n", page->url);
    page -> visited = 1;
    for(int i = 0; i<MAXLINKS; i++)
        reachable(page->links[i]);
}

int search_page (struct page *page, char *keyword)
{
    char contents[10000];
    FILE * file;
    file = fopen (page ->url , "r");
    if (file == NULL)
    {
        printf("Cannot open file %s\n", page ->url);
        return;
    }
    
    int i = 0;
    int aux = EOF;      
    do
    {
        aux = fgetc(file);
        //if(32 <= aux && aux <= 126) 
            contents[i++]=aux;
    }while(aux!=EOF);

    fclose(file);
    if(strstr(contents, keyword) != NULL)
        return 1;
    else 
        return 0;
}

void search_web (struct page *web, char *keyword)
{
    while(web != NULL)
    {
        if(search_page(web, keyword)>0)
            printf("%s\n",web->url);
        web = web->next;
    }
}

int main()
{
    char comanda;
    bool ask = true;

    struct page *web = NULL; 

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
            case 'S': 
                printf("Search web for? ");
                scanf("%s",argument);
                search_web(web,argument);
                break;

            case 's':          
                printf("Search word in page? ");
                scanf("%s %s",argument2, argument);
                if(find_page(web,argument)!=NULL)
                {
                    if(search_page(find_page(web,argument),argument2)==0)
                    {
                        printf("Page \"%s\" does not contain the word \"%s\"\n", argument, argument2);
                    }else
                    {
                        printf("Page \"%s\" contains the word \"%s\"\n", argument, argument2);
                    }
                }
                else
                    printf("URL %s is not on the web\n", argument);
                break;
            

            case 'r':
                printf("Page URL? ");
                scanf("%s",argument);
                if(find_page(web,argument)!=NULL)
                {
                    reset_visited(web);
                    reachable(find_page(web,argument));
                }
                else
                    printf("URL %s is not on the web\n", argument);
                break;

            case 'P':
                printf("Page URL? ");
                scanf("%s",argument);
                remove_page(&web, argument);
                break; 
                
            case 'l':
                printf("Source & destination URL? ");
                scanf("%s %s",argument, argument2);
                add_link(web, argument, argument2);
                break;                

            case 'v':
                reset_visited(web);
                break;

            case 'f':
                printf("Page URL? ");
                scanf("%s",argument);
                if(find_page(web,argument)!=NULL)
                    printf("URL %s is on the web\n", argument);
                else
                    printf("URL %s is not on the web\n", argument);
                break;

            case 'w':
                print_web(web);
                break;

            case 'p':
                printf("Page URL? ");
                scanf("%s",argument);
                web = add_page(web,argument);
                break;

            case 'q':
                printf("Bye");
                return 0;

            case ' ':
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