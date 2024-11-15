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
#include <stdio.h>

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
	printf("its me\n");
	return inf + rand() % (sup - inf + 1);
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
		perm[i] = i + 1;
	}

	for (i = 0; i < N; i++)
	{
		aux = random_num(i, N - 1);
		Swap(perm, i, aux);
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
			printf("Error en generate_perm\n");
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

int Swap(int *tabla, int i, int j)
{
	int temp;

	printf("tablastart: i: %d, j: %d\n", tabla[i], tabla[j]);

	temp = tabla[i];
	tabla[i] = tabla[j];
	tabla[j] = temp;

	printf("tablaend: i: %d, j: %d\n", tabla[i], tabla[j]);

	return 1;
}