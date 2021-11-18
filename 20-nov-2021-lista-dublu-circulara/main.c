#include <stdio.h>
#include <stdlib.h>

struct nod
{
    int val;
    struct nod * next;
    struct nod * prev;
};


void adaugare_inceput(struct nod ** prim, int val)
{
    struct nod * p = (struct nod *) malloc(sizeof(struct nod));
    p->next = NULL;
    p->prev = NULL;
    p->val = val;

    if((*prim) == NULL)
    {
        p->next = p;
        p->prev = p;
        *prim = p;
    }
    else 
    {
        p->next = (*prim);
        p->prev = (*prim) ->prev;
        (*prim) ->prev->next = p;
        (*prim)->prev = p; 
        *prim = p;
    }
}

void parcurgere_inainte(struct nod * prim)
{
    if(prim == NULL)
        return;

    struct nod * iter = prim;
    do
    {
        printf("%d ", iter->val);
        iter = iter -> next;
    }while(iter != prim);
}

void parcurgere_inapoi(struct nod * prim)
{
    if(prim == NULL)
        return;
        
    struct nod * iter = prim;
    do
    {
        iter = iter -> prev;
        printf("%d ", iter->val);
    }while(iter != prim);
}

void parcurgere_inapoi_rec(struct nod * prim, struct nod * iter)
{
    if(prim == NULL)
        return;

    if(iter->next != prim)
        parcurgere_inapoi_rec(prim, iter->next);
    printf("%d ", iter->val); 
}

void delete_inceput(struct nod ** prim)
{
    if(*prim == NULL)
        return;
    
    struct nod * to_del = (*prim);
    (*prim) = (*prim) -> next;
    
    (*prim) -> prev = to_del ->prev;
    to_del ->prev ->next = (*prim);

    if((*prim) == to_del)
        (*prim) = NULL;

    free(to_del);
}

struct nod * exista(struct nod * prim, int val)
{
    if(prim == NULL)
        return NULL;

    struct nod * iter = prim;
    do
    {
        if(iter->val == val)
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

    if(to_del == (*prim))
        (*prim) = (*prim) -> next;
    
    to_del -> next -> prev = to_del ->prev;
    to_del ->prev ->next = to_del -> next;

    if((*prim) == to_del)
        (*prim) = NULL;

    free(to_del);
}

void adaugare_dupa_un_nod(struct nod ** prim, int val, int val_dupa_care_vrei_sa_adaugi)
{
    if((*prim) == NULL)
        return;

    struct nod * de_dupa = exista((*prim), val_dupa_care_vrei_sa_adaugi);
    if(de_dupa == NULL)
        return;

    struct nod * p = (struct nod *) malloc(sizeof(struct nod));
    p->next = NULL;
    p->val = val;

    p ->prev = de_dupa;
    p -> next = de_dupa -> next;
    de_dupa ->next ->prev = p;
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
    parcurgere_inapoi(list); printf("\n");
    parcurgere_inapoi_rec(list, list); printf("\n");

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

    delete_valoare(&list, 100);
    parcurgere_inainte(list); printf("\n");
    parcurgere_inapoi(list); printf("\n");


    int x; scanf("%d", &x);
    return 0;
}