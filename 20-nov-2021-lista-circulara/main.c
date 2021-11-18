#include <stdio.h>
#include <stdlib.h>



struct nod
{
    int x;
    struct nod * next;
};


void adaugare_inceput(struct nod ** prim, int val)
{
    struct nod * p = (struct nod *) malloc(sizeof(struct nod));
    p->next = NULL;
    p->x = val;

    if( (*prim) == NULL )
    {
        p->next = p;
        *prim = p;
    }
    else 
    {
        struct nod * iter = (*prim);
        while(iter->next != (*prim))
            iter = iter -> next;

        iter -> next = p;
        p->next = (*prim);
        *prim = p;
    }
}

void parcurgere_inainte(struct nod * prim)
{
    struct nod * iter = prim;
    do
    {
        printf("%d ", iter->x);
        iter = iter -> next;
    }while(iter != prim);
}

void parcurgere_inapoi(struct nod * prim, struct nod * iter)
{
    if(iter->next != prim)
        parcurgere_inapoi(prim, iter->next);
    printf("%d ", iter->x); 
}

void delete_inceput(struct nod ** prim)
{
    if(*prim == NULL)
        return;

    struct nod * iter = (*prim);
    while(iter->next != (*prim))
        iter = iter -> next;
    
    struct nod * toDel = (*prim);
    (*prim) = (*prim) -> next;

    iter ->next = (*prim);

    if((*prim) == toDel)
        (*prim) = NULL;

    free(toDel);  
    iter = NULL;  
}

struct nod * exista(struct nod * prim, int val)
{
    struct nod * iter = prim;
    do
    {
        if(iter->x == val)
            return iter;
        iter = iter -> next;
    }while(iter != prim);
    return NULL;
}

void delete_valoare(struct nod ** prim, int val)
{
    if(*prim == NULL)
        return;

    struct nod * to_del = exista((*prim), val);
    if(to_del == NULL)
        return;

    struct nod * iter = (*prim);
    while(iter->next != to_del)
        iter = iter -> next;

    if((*prim) == to_del)
        (*prim) = (*prim) ->next;
    
    iter ->next = iter->next->next;

    if((*prim) == to_del)
        (*prim) = NULL;

    free(to_del);
}

void adaugare_dupa_un_nod(struct nod ** prim, int val, int val_dupa_care_vrei_sa_adaugi)
{
    struct nod * de_dupa = exista((*prim), val_dupa_care_vrei_sa_adaugi);
    if(de_dupa == NULL)
        return;

    struct nod * p = (struct nod *) malloc(sizeof(struct nod));
    p->next = NULL;
    p->x = val;

    p -> next = de_dupa -> next;
    de_dupa ->next = p;
}

int main()
{
    struct nod * list = NULL;

    adaugare_inceput(&list, 11);
    delete_inceput(&list);
    adaugare_inceput(&list, 10);
    delete_valoare(&list, 10);
    
    adaugare_inceput(&list, 9);
    adaugare_inceput(&list, 8);
    adaugare_inceput(&list, 7);
    adaugare_inceput(&list, 6);
    adaugare_inceput(&list, 5);
    adaugare_inceput(&list, 4);
    adaugare_inceput(&list, 3);
    adaugare_inceput(&list, 2);
    adaugare_inceput(&list, 1);
    
    parcurgere_inainte(list); printf("\n");
    parcurgere_inapoi(list, list); printf("\n");

    delete_inceput(&list);
    parcurgere_inainte(list); printf("\n");

    delete_valoare(&list, 2);
    parcurgere_inainte(list); printf("\n");

    adaugare_dupa_un_nod(&list, 100, 5);
    parcurgere_inainte(list); printf("\n");

    adaugare_dupa_un_nod(&list, 101, 9);
    parcurgere_inainte(list); printf("\n");

    delete_valoare(&list, 101);
    parcurgere_inainte(list); printf("\n");

    delete_valoare(&list, 3);
    parcurgere_inainte(list); printf("\n");

    adaugare_inceput(&list, 3);
    parcurgere_inainte(list); printf("\n");

    int x; scanf("%d", &x);
    return 0;
}