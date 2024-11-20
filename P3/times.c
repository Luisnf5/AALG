/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include "permutations.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void printArray(int *array, int size)
{
	int i;
	if (!array || size <= 0)
		return;

	for (i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms, int N, PTIME_AA ptime)
{
	int i, min = __INT_MAX__, max = 0, sumOB = 0, err_aux;
	float sumT = 0;
	int **perms = NULL, *obPerms;
	clock_t start, end;
	double final = 0;

	if (metodo == NULL || n_perms < 1 || N < 1 || ptime == NULL)
	{
		printf("error 10\n");
		return ERR;
	}

	obPerms = (int *)malloc(n_perms * sizeof(int));
	if (obPerms == NULL)
	{
		printf("Error al asignar memoria para las permutaciones");
		return 1;
	}

	ptime->N = N;

	ptime->n_elems = n_perms;

	perms = generate_permutations(n_perms, N);
	if (perms == NULL)
	{
		printf("ERROR en generate_permutations\n");
		return ERR;
	}

	for (i = 0; i < n_perms; i++)
	{
		start = clock();

		/*printf("unsorted array: ");
		printArray(perms[i], N);
		printf("\n");*/
		err_aux = metodo(perms[i], 0, N - 1);
		/*printf("sorted array: ");
		printArray(perms[i], N);
		printf("\n");*/
		if (err_aux == ERR)
		{
			printf("ERROR en metodo\n");
			return ERR;
		}
		obPerms[i] = err_aux;

		end = clock();

		final = ((double)(end - start)) / CLOCKS_PER_SEC;
		sumT += final;
		sumOB += obPerms[i];

		if (obPerms[i] < min)
		{
			min = obPerms[i];
		}
		if (obPerms[i] > max)
		{
			max = obPerms[i];
		}
	}

	ptime->min_ob = min;

	ptime->max_ob = max;

	ptime->time = sumT / n_perms;

	ptime->average_ob = sumOB / n_perms;

	for (i = 0; i < n_perms; i++)
	{
		free(perms[i]);
	}
	free(perms);
	free(obPerms);

	return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char *file, int num_min, int num_max, int incr, int n_perms)
{
	TIME_AA *pt = NULL;
	int i, arr_tam, cont = 0;

	if (method == NULL || file == NULL || num_min < 1 || num_max < 1 || num_min > num_max || incr < 1 || n_perms < 1)
	{
		printf("error 1\n");
		return ERR;
	}
	cont = num_min;

	arr_tam = ((num_max - num_min) / incr) + 1;

	pt = (TIME_AA *)malloc(arr_tam * sizeof(TIME_AA));
	if (pt == NULL)
	{
		printf("error 2\n");
		return ERR;
	}

	for (i = 0; i < arr_tam; i++)
	{
		if (average_sorting_time(method, n_perms, cont, &pt[i]) == ERR)
		{
			free(pt);
			printf("error 3\n");
			return ERR;
		}
		cont += incr;
		system("clear");
		printf("Completado: %f %\n", i * (float)100 / arr_tam);
	}

	if (save_time_table(file, pt, arr_tam) == ERR)
	{
		free(pt);
		printf("error 4\n");
		return ERR;
	}

	free(pt);
	return OK;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char *file, PTIME_AA ptime, int n_times)
{
	int i;
	FILE *f = NULL;

	if (file == NULL || !ptime || n_times < 1)
	{
		return ERR;
	}

	f = fopen(file, "w");
	if (f == NULL)
	{
		return ERR;
	}

	for (i = 0; i < n_times; i++)
	{
		if (fprintf(f, "%d %f %f %d %d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob) < 0)
		{
			fclose(f);
			return ERR;
		}
	}

	fclose(f);
	return OK;
}

/***********************PRACTICA 3****************************/

short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order, char *file, int num_min, int num_max, int incr, int n_times)
{
	TIME_AA *pt = NULL;
	int i, arr_tam, cont = 0;

	if (method == NULL || generator == NULL || file == NULL || num_min < 1 || num_max < 1 || num_min > num_max || incr < 1 || n_times < 1)
	{
		return ERR;
	}

	cont = num_min;

	arr_tam = ((num_max - num_min) / incr) + 1;

	pt = (TIME_AA *)malloc(arr_tam * sizeof(TIME_AA));
	if (pt == NULL)
	{
		return ERR;
	}

	for (i = 0; i < arr_tam; i++)
	{
		if (average_search_time(method, generator, order, cont, n_times, &pt[i]) == ERR)
		{
			free(pt);
			return ERR;
		}
		cont += incr;
		system("clear");
		printf("Completado: %.2f %\n", i * (float)100 / arr_tam);
	}

	if (save_time_table(file, pt, arr_tam) == ERR)
	{
		free(pt);
		return ERR;
	}

	free(pt);
	return OK;
}

short average_search_time(pfunc_search metodo, pfunc_key_generator generator, int order, int N, int n_times, PTIME_AA ptime)
{
	PDICT dict = NULL;
	int *perm, err, **ntimes_N, i, j, pos, tot_ob = 0, it_ob = 0;
	double tot_time = 0;
	clock_t start, end;

	if (metodo == NULL || generator == NULL || N < 1 || n_times < 1 || ptime == NULL)
	{
		return ERR;
	}

	dict = init_dictionary(N, order);
	if (dict == NULL)
	{
		return ERR;
	}

	perm = generate_perm(N);

	err = massive_insertion_dictionary(dict, perm, N);
	if (err == ERR)
	{
		free_dictionary(dict);
		return ERR;
	}

	ntimes_N = (int **)malloc(n_times * sizeof(int *));
	if (ntimes_N == NULL)
	{
		free_dictionary(dict);
		return ERR;
	}

	for (i = 0; i < n_times; i++)
	{
		ntimes_N[i] = (int *)malloc(N * sizeof(int));
		if (ntimes_N[i] == NULL)
		{
			for (j = 0; j < i; j++)
			{
				free(ntimes_N[j]);
			}
			free(ntimes_N);
			free_dictionary(dict);
			return ERR;
		}
	}

	for (i = 0; i < n_times; i++)
	{
		generator(ntimes_N[i], N, N);
	}

	ptime->N = N;
	ptime->n_elems = n_times;
	ptime->min_ob = __INT_MAX__;
	ptime->max_ob = 0;
	ptime->time = 0;

	for (i = 0; i < n_times; i++)
	{
		for (j = 0; j < N; j++)
		{
			it_ob = 0;
			start = clock();
			err = search_dictionary(dict, ntimes_N[i][j], &pos, metodo);
			end = clock();
			tot_time += ((double)(end - start)) / CLOCKS_PER_SEC;
			if (err == ERR)
			{
				for (j = 0; j < i; j++)
				{
					free(ntimes_N[j]);
				}
				free(ntimes_N);
				free_dictionary(dict);
				return ERR;
			}
			else
			{
				it_ob += err;
			}
			if (pos == NOT_FOUND)
			{
				printf("KEY NOT FOUND IN IT i(n_time):%d j(N):%d\n", i, j);
			}
			if (it_ob > ptime->max_ob)
			{
				ptime->max_ob = it_ob;
			}
			if (it_ob < ptime->min_ob)
			{
				ptime->min_ob = it_ob;
			}
			tot_ob += it_ob;
		}
	}

	ptime->average_ob = (double)tot_ob / n_times;
	ptime->time = (double)tot_time / n_times;

	for (i = 0; i < n_times; i++)
	{
		free(ntimes_N[i]);
	}
	free(ntimes_N);
	free(perm);
	free_dictionary(dict);

	return OK;
}