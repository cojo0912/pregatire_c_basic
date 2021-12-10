#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

void printmat(int **a, int nl, int nc) {
  for (int i = 0; i < nl; i++) {
    for (int j = 0; j < nc; j++) {
      printf("%2d", a[i][j]);
    }
 
    printf("\n");
  }
}

int main()
{
  int **a;
  int i, j, nl, nc;
 
  printf("nr. linii = ");
  scanf("%d", &nl);
 
  printf("nr. coloane = ");
  scanf("%d", &nc);
 
  /* 
   * In cele ce urmeaza presupunem ca toate apelurile de alocare de memorie
   * nu vor esua.
   */
  a = malloc(nl * sizeof(int *));   // Alocare pentru vector de pointeri
 
  for (i = 0; i < nl; i++) {
    a[i] = calloc(nc, sizeof(int)); // Alocare pentru o linie si initializare la zero
  }
 
  // Completare diagonala matrice unitate
  for (i = 0; i < nl; i++) 
    a[i][i] = 1;                    // a[i][j]=0 pentru i != j   
 
 
  // Afisare matrice
  printmat(a, nl, nc);
 
  for (i = 0; i < nl; i++)
     free(a[i]);
  free(a);                         // Nu uitam sa eliberam! 
 
  scanf("%d", &i);
  return 0;
}

