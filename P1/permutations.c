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
int random_num(int inf, int sup) /*CAMBIAR FUNCION*/
{
  if (inf > sup || inf < 0 || sup < 1)
  {
    return -1;
  }

  return rand() % (sup - inf) + inf;
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
int *generate_perm(int N)
{
  int *perm;

  int i;
  int cambio;
  int ind;
  int aux;

  perm = (int *)malloc(N * sizeof(int));
  if (perm == NULL)
  {
    return NULL;
  }

  for (i = 0; i < N; i++)
  {
    perm[i] = i;
  }

  for (i = 0; i < N; i++)
  {
    cambio = perm[i];
    aux = random_num(i, N);
    if (aux == -1)
    {
      free(perm);
      return NULL;
    }
    ind = aux;
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
int **generate_permutations(int n_perms, int N)
{
  int i, j;
  int *aux;

  int **permutations = malloc(n_perms * sizeof(int *));
  if (permutations == NULL)
  {
    return NULL;
  }

  for (i = 0; i < n_perms; i++)
  {
    aux = generate_perm(N);
    if (aux == NULL)
    {
      for (j = 0; j < i; j++)
      {
        free(permutations[j]);
      }
      free(permutations);
      return NULL;
    }
    permutations[i] = aux;
  }

  return permutations;
}

void free_permutations(int **permutations, int n_perms)
{
  int i;

  if (permutations == NULL)
  {
    return;
  }

  for (i = 0; i < n_perms; i++)
  {
    free(permutations[i]);
  }
  free(permutations);
}