#include <stdio.h>
#include <stdlib.h>

/*
    char x;
    1 111 1111

    unsigne char x;
    1111 1111

    short(2)
    int (4)
    long (8)
*/
// https://ocw.cs.pub.ro/courses/programare/laboratoare/lab02

struct nod
{
    int x;
    struct nod * next;
};

//recapitulare + uite-te pe codul din acest exemplu

void adaugare_inceput(struct nod ** prim, int val)
{
    struct nod * p = (struct nod *) malloc(sizeof(struct nod));
    p->next = NULL;
    p->x = val;

    if((*prim) == NULL)
    {
        *prim = p;
    }
    else 
    {
        p->next = (*prim);
        *prim = p;
    }
}

void adaugare_sfarsit(struct nod ** prim, int val)
{
    struct nod * p = (struct nod *) malloc(sizeof(struct nod));
    p->next = NULL;
    p->x = val;

    if((*prim) == NULL)
    {
        *prim = p;
    }
    else 
    {
        struct nod * iter = (*prim);
        while(iter -> next != NULL)
            iter = iter -> next;
        iter -> next = p;
    }
}

void parcurgere_inainte(struct nod * prim)
{
    while(prim != NULL)
    {
        printf("%d ", prim->x);
        prim = prim -> next;
    }
}

void parcurgere_inapoi(struct nod * prim)
{
    if(prim == NULL)
        return;

    parcurgere_inapoi(prim->next);
    printf("%d ", prim->x); 
}

void delete_intecput(struct nod ** prim)
{
    if(*prim == NULL)
        return;
    
    struct nod * iter = (*prim);
    (*prim) = (*prim) -> next;

    free(iter);  
    iter = NULL;  
}

void delete_final(struct nod ** prim)
{
    if(*prim == NULL)
        return;

    struct nod * iter = (*prim);
    while( iter -> next != NULL )
    {
        if(iter ->next ->next == NULL)
        {
            free(iter -> next);
            iter -> next = NULL;
            return;
        }
        iter = iter -> next;
    }
}

void delete_valoare(struct nod ** prim, int val)
{
    if(*prim == NULL)
        return;
    struct nod * iter = (*prim);

    //if(iter->)
    
}

//void adaugare_dupa_un_nod(struct nod ** prim, int val, int val_dupa_care_vrei_sa_adaugi)

int main()
{
    struct nod * list = NULL;

    adaugare_inceput(&list, 3);
    adaugare_inceput(&list, 2);
    adaugare_inceput(&list, 1);
    
    adaugare_sfarsit(&list, 4);
    adaugare_sfarsit(&list, 5);
    adaugare_sfarsit(&list, 6);

    parcurgere_inainte(list);
    printf("\n");
    parcurgere_inapoi(list);
    printf("\n");


    delete_intecput(&list);
    delete_final(&list);
    parcurgere_inainte(list);
    printf("\n");


    int x; scanf("%d", &x);
    return 0;
}