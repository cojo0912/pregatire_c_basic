#include <stdio.h>
#include <stdlib.h>

int main()
{
    char comanda;

    while(1)
    {
        printf("Command? "); 
        scanf("%c", &comanda);
        switch(comanda)
        {
            case 'q':
                printf("Bye");
                return 0;

            case '\r':
            case '\n':
                break;

            default:
                printf("Unknown command '%c'", comanda);
                break;
        }
    } 

    return 0;
}