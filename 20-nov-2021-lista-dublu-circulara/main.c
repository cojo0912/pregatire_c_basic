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
    do
    {
        printf("%d ", prim->val);
        prim = prim -> next;
    }
    printf("\n ");
}

void parcurgere_inapoi(struct nod * prim)
{
    if(prim == NULL)
        return;
    while(prim -> next != NULL)
    {
        prim = prim -> next;
    }
    while(prim != NULL)
    {
        printf("%d ", prim->val);
        prim = prim -> prev;
    }
}

void parcurgere_inapoi_rec(struct nod * prim)
{
    if(prim == NULL)
        return;

    parcurgere_inapoi_rec(prim->next);
    printf("%d ", prim->val); 
}

void delete_intecput(struct nod ** prim)
{
    if(*prim == NULL)
        return;
    
    struct nod * iter = (*prim);
    (*prim) = (*prim) -> next;
    if((*prim) != NULL)
        (*prim) -> prev = NULL;

    free(iter);  
    iter = NULL;  
}

void delete_valoare(struct nod ** prim, int val)
{
    if(*prim == NULL)
        return;
    struct nod * iter = (*prim);

    while(iter != NULL)
    {
        if(iter->val == val)
        {
            if(iter->prev != NULL)
                iter -> prev -> next = iter ->next;

            if(iter->next!=NULL)
                iter->next->prev = iter->prev;

            if(iter == (*prim))
                (*prim) = iter->next;

            free(iter);
            return;
        }
        iter = iter->next;
    }
}

void adaugare_dupa_un_nod(struct nod ** prim, int val, int val_dupa_care_vrei_sa_adaugi)
{
    struct nod * p = (struct nod *) malloc(sizeof(struct nod));
    p->next = NULL;
    p->prev = NULL;
    p->val = val;

    struct nod * iter = (*prim);
    while(iter!=NULL)
    {
        if(iter->val == val_dupa_care_vrei_sa_adaugi)
        {
            p->next = iter->next;
            p->prev = iter;
            iter->next = p;
            if(p->next != NULL)
                p->next->prev = p;
            return;
        }
        iter = iter->next;
    }    
}

int main()
{
    struct nod * list = NULL;
    adaugare_inceput(&list, 8);
    adaugare_inceput(&list, 7);
    adaugare_inceput(&list, 6);
    adaugare_inceput(&list, 5);
    adaugare_inceput(&list, 4);
    adaugare_inceput(&list, 3);
    adaugare_inceput(&list, 2);
    adaugare_inceput(&list, 1);


    parcurgere_inainte(list);
    printf("\n");
    parcurgere_inapoi(list);
    printf("\n");
    parcurgere_inapoi_rec(list);
    printf("\n");
    



    int x; scanf("%d", &x);
    return 0;
}