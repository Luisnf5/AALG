/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include <stdlib.h>

/***************************************************/
/* Function: random_num Date:                      */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  return rand() % (sup + 1 - inf) + inf;
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int *perm;

  int i;
  int cambio;
  int ind;

  perm = malloc(N * sizeof(int));

  for (i=0; i<N; i++){
    perm[i] = i;
  }

  for (i=0; i<N; i++){
    cambio = perm[i];
    ind = random_num(i, N);
    perm[i] = perm[ind];
    perm[ind] = cambio;
  }

  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N) {
    int **permutations = malloc(n_perms * sizeof(int*));
    if (permutations == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n_perms; i++) {
        permutations[i] = generate_perm(N);  // Generar cada permutación
    }

    return permutations;
}

void free_permutations(int **permutations, int n_perms) {
    for (int i = 0; i < n_perms; i++) {
        free(permutations[i]);  // Liberar cada permutación
    }
    free(permutations);  // Liberar el arreglo de punteros
}