#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define MAX_CHILDREN 4
struct station{
    char *name; 
    struct station *destinations;
    struct station * next;
    int visited;
};

struct station *findStation(struct station *stations, char* station_name)
{
    while(stations != NULL)
    {
        if(strcmp(stations ->name, station_name) == 0)
            return stations;
        stations = stations -> next;
    }
    return NULL;
}

void addStation(struct station **stations, char *station_name)
{
    if(findStation(*stations, station_name) != NULL)
    {
        printf("%s already exists\n", station_name);
        return;
    }

    struct station * new = (struct station *) malloc (sizeof(struct station));
    new ->destinations = NULL;
    new ->next = NULL;
    new -> name = (char*)malloc(sizeof(char) * (strlen(station_name)+1));
    strcpy(new -> name, station_name);

    new ->next = (*stations);
    *stations = new;
}

void addDestintaion(struct station *station, char *station_name)
{
    struct station * iter = station ->destinations;
    while(iter != NULL)
    {
        if(strcmp(iter->name,station_name) == 0)
        {
            printf("%s already exists\n", station_name);
            return;
        }
        iter = iter ->destinations;
    }

    struct station * new = (struct station *) malloc (sizeof(struct station));
    new ->destinations = NULL;
    new ->next = NULL;
    new -> name = (char*)malloc(sizeof(char) * (strlen(station_name)+1));
    strcpy(new -> name, station_name);

    new ->destinations = station->destinations;
    station->destinations = new;
}

void  removeStation(struct station **stations, char *station_name)
{
    if((*stations) == NULL)
    {
        return;
    }

    struct station *iter = (*stations);
    while(iter!=NULL)
    {
        struct station *iter2 = iter->destinations;
        if(iter2!=NULL)
        {       
            if(strcmp(iter2->name, station_name)==0)
            {
                struct station * toDel = iter2;
                iter2 = iter2 ->destinations;
                free(toDel->name);
                free(toDel);
                iter->destinations = iter2;
            }else
            {         
                while(iter2 -> destinations != NULL)
                {
                    if(strcmp(iter2-> destinations->name, station_name)==0)
                    {
                        struct station * toDel = iter2 -> destinations;
                        iter2 ->destinations = iter2 ->destinations ->destinations;
                        free(toDel->name);
                        free(toDel);
                        break;
                    }
                    iter2 = iter2->destinations;
                }
            }
        }
        iter = iter ->next;
    }

    iter = (*stations);
    if(strcmp(iter->name, station_name)==0)
    {
        struct station * toDel = iter;
        iter = iter ->next;
        free(toDel->name);
        free(toDel);
        (*stations) = iter;
    }else
    {         
        while(iter -> next != NULL)
        {
            if(strcmp(iter-> next->name, station_name)==0)
            {
                struct station * toDel = iter -> next;
                iter ->next = iter ->next ->next;
                free(toDel->name);
                free(toDel);
                break;
            }
            iter = iter ->next;
        }
    }
}

void printStations(struct station *stations)
{
    while(stations != NULL)
    {
        printf("Station: %s\n", stations->name);
        struct station * iter = stations ->destinations;
        while(iter != NULL)
        {
            printf("- %s\n", iter->name);
            iter=iter->destinations;
        }
        stations = stations -> next;
    }
}

int findShortestPath(struct station *stations, struct station*a, struct station *b) //a - pozition actuala b - pozitia dorita
{
    if(a ->visited == 1)
        return 9999;
    if(a == b)
        return 0;

    a -> visited = 1;
    int min = 9999;
    
    struct station * iter = a ->destinations;
    while(iter != NULL)
    {
        struct station * aux = findStation(stations, iter->name);
        int aux2 = findShortestPath(stations, aux, b);
        /////////////
        aux ->visited = 0;
        if(aux2<min)
            min = aux2;
        iter = iter->destinations;
    }
    
    return 1+min;
}

int main()
{
    char comanda;
    bool ask = true;    

    struct station * list = NULL;

    while(1)
    {
        if(ask)
            printf("Command? "); 
        scanf("%c", &comanda);

        ask = true;
        char argument1[255];
        char argument2[255];

        

        switch(comanda)
        {
            case 'f':
                printf("Station 1 name? ");scanf("%s", argument1);
                struct station * s1 = findStation(list, argument1);

                printf("Station 2 name? ");scanf("%s", argument2);
                struct station * s2 = findStation(list, argument2);

                if(s1 == NULL || s2 == NULL)
                {
                    printf("One of the stations is missing");
                    break;
                }else
                {
                    struct station * iter = list;
                    while(iter!=NULL)
                    {
                        iter ->visited = 0;
                        iter = iter ->next;
                    }
                    printf("Shortest path: %d\n", findShortestPath(list,s1,s2));
                    break;
                }

            case 's':
                printf("Station name? ");scanf("%s", argument1);
                addStation(&list, argument1);
                break;
            
            case 'd':
                printf("Station name? ");scanf("%s", argument1);
                struct station * s = findStation(list, argument1);
                if(s == NULL)
                {
                    printf("%s doesn't exist", argument1);
                    break;
                }
                printf("Destination name? ");scanf("%s", argument1);
                addDestintaion(s, argument1);
                break;

            case 'p':
                printStations(list);
                break;

            case 'r':
                printf("Station name? ");scanf("%s", argument1);
                removeStation(&list, argument1);
                break;

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