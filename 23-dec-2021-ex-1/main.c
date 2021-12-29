#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node_t
{
    float re;
    float im;
    struct node_t *next;
};

// returns a new list
struct node_t *insert_tail(struct node_t *head, float re, float im)
{

    struct node_t *p = (struct node_t *)malloc(sizeof(struct node_t));
    p->re = re;
    p->im = im;
    p->next = NULL;

    if (head == NULL)
        return p;

    struct node_t *copy = head;

    while (copy->next != NULL)
    {
        copy = copy->next;
    }
    copy->next = p;

    return head;
}

void print_list(struct node_t *head)
{
    if (head == NULL)
    {

        printf("[]\n");
        return;
    }

    if (head->next == NULL)
    {
        printf("[%.2f+%.2fi]\n", head->re, head->im);
        return;
    }

    printf("[");

    while (head->next != NULL)
    {

        if (head->im < 0)
            printf("%.2f%.2fi, ", head->re, head->im);

        else

            printf("%.2f+%.2fi,", head->re, head->im);

        head = head->next;
    }

    if (head->im < 0)
        printf("%.2f%.2fi", head->re, head->im);

    else

        printf("%.2f+%.2fi", head->re, head->im);

    printf("]\n");
}

void insert_head(struct node_t **head, float re, float im)
{

    struct node_t *p = (struct node_t *)malloc(sizeof(struct node_t));
    p->re = re;
    p->im = im;
    p->next = NULL;

    p->next = (*head);
    (*head) = p;
}

float distance(float re1, float im1, float re2, float im2)
{

    float distance;

    distance = sqrt(((re1 - re2) * (re1 - re2)) + ((im1 - im2) * (im1 - im2)));

    return distance;
}

struct node_t *find_closest(struct node_t *head, float re, float im)
{

    float min = 10000;
    float dist;
    struct node_t *closest = NULL;

    if (head == NULL)
        return NULL;

    while (head != NULL)
    {

        dist = distance(head->re, head->im, re, im);

        if (dist == min)
        {
            return closest;
        }

        if (dist < min)
        {
            min = dist;
            closest = head;
        }

        head = head->next;
    }

    return closest;
}

void print_closest(struct node_t *head)
{
    if (head->im < 0)
        printf("%.2f%.2fi", head->re, head->im);

    else

        printf("%.2f+%.2fi", head->re, head->im);

    printf("\n");
}

struct node_t *insert_after_closest(struct node_t *head, float re, float im)
{

    struct node_t *p = (struct node_t *)malloc(sizeof(struct node_t));
    p->re = re;
    p->im = im;
    p->next = NULL;

    struct node_t *closest = find_closest(head, re, im);

    if (closest == NULL)
        return p;

    p->next = closest->next;
    closest->next = p;

    return head;
}

void insert_before_closest(struct node_t **head, float re, float im)
{

    struct node_t *p = (struct node_t *)malloc(sizeof(struct node_t));
    p->re = re;
    p->im = im;
    p->next = NULL;

    if ((*head) == NULL)
    {
        (*head) = p;
        return;
    }

    struct node_t *closest = find_closest(*head, re, im);

    struct node_t *copy = *head;

    if (*head == closest)
    {

        p->next = (*head);
        (*head) = p;
        return;
    }

    while (copy->next != closest)
        copy = copy->next;

    p->next = closest;
    copy->next = p;
}

void print_list_reverse(struct node_t *head)
{ 
    if (head == NULL)
        return;

    if (head->next == NULL)
    {

        if (head->im < 0)
            printf("%.2f%.2fi", head->re, head->im);

        else
            printf("%.2f+%.2fi", head->re, head->im);

        return;
    }else
    {
        print_list_reverse(head->next);

        if (head->im < 0)
            printf(",%.2f%.2fi", head->re, head->im);

        else

            printf(",%.2f+%.2fi", head->re, head->im);
    }
}

struct node_t *remove_front(struct node_t *head)
{

    struct node_t *copy = head;

    if (head == NULL)
        return NULL;

    if (head->next == NULL)
    {
        free(copy);
        copy = NULL;
        return NULL;
    }

    head = head->next;
    free(copy);

    copy = NULL;

    return head;
}

void remove_end(struct node_t **head)
{

    struct node_t *copy = *head;

    if (*head == NULL)
        return;
    if ((*head)->next == NULL)
    {

        free(*head);
        (*head) = NULL;
        return;
    }
    while (copy->next->next != NULL)
        copy = copy->next;

    free(copy->next);
    copy->next = NULL;
}

struct node_t *remove_closest(struct node_t *head, float re, float im)
{

    if (head == NULL)
        return NULL;

    struct node_t *closest = find_closest(head, re, im);

    if (head->next == NULL)
    {
        free(head);
        return NULL;
    }

    struct node_t *copy = head;

    while (copy->next != closest)
        copy = copy->next;

    copy->next = closest->next;
    free(closest);

    return head;
}

int main()
{
    char command;

    struct node_t *list = NULL;
    float re;
    float im;

    struct node_t *closest = NULL;

    do
    {
        printf("Command: ");
        scanf(" %c", &command);

        switch (command)
        {

        case 'r':
            printf("re, im? ");

            scanf("%f", &re);
            scanf("%f", &im);
            list = remove_closest(list, re, im);
            break;

        case 'e':
            remove_end(&list);
            break;

        case 'f':
            list = remove_front(list);
            break;

        case 'v':

            printf("[");
            print_list_reverse(list);

            printf("]\n");
            break;

        case 'b':
            printf("re, im? ");

            scanf("%f", &re);
            scanf("%f", &im);

            insert_before_closest(&list, re, im);
            break;

        case 'a':
            printf("re, im? ");

            scanf("%f", &re);
            scanf("%f", &im);

            list = insert_after_closest(list, re, im);
            break;

        case 'c':

            printf("re, im? ");
            scanf("%f", &re);
            scanf("%f", &im);
            closest = find_closest(list, re, im);

            if (closest == NULL)
                printf("No closest node found.\n");
            else
            {
                printf("Closest node is ");
                print_closest(closest);
            }

            break;

        case 'h':
            printf("re, im? ");

            scanf("%f", &re);
            scanf("%f", &im);

            insert_head(&list, re, im);
            break;

        case 'p':

            print_list(list);

            break;

        case 't':
            printf("re, im? ");

            scanf("%f", &re);
            scanf("%f", &im);

            list = insert_tail(list, re, im);

            break;

        case 'q':
            printf("Bye!\n");
            return 0;
            break;

        default:
            printf("Unknown command '%c'.\n", command);
            break;
        }

    } while (command != 'q');
}
