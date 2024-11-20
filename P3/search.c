/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be
 *				 allocated externally to the function.
 */

/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
	int i;

	for (i = 0; i < n_keys; i++)
		keys[i] = 1 + (i % max);

	return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
	int i;

	for (i = 0; i < n_keys; i++)
	{
		keys[i] = .5 + max / (1 + max * ((double)rand() / (RAND_MAX)));
	}

	return;
}

PDICT init_dictionary(int size, char order)
{
	PDICT pdict;

	pdict = (PDICT)malloc(sizeof(DICT));

	if (pdict == NULL)
		return NULL;

	pdict->size = size;
	pdict->n_data = 0;
	pdict->order = order;
	pdict->table = (int *)malloc(size * sizeof(int));

	if (pdict->table == NULL)
	{
		free(pdict);
		return NULL;
	}

	return pdict;
}

void free_dictionary(PDICT pdict)
{
	if (pdict != NULL)
	{
		if (pdict->table != NULL)
			free(pdict->table);
		free(pdict);
	}
}

int insert_dictionary(PDICT pdict, int key)
{
	int i, ob = 0;

	if (pdict == NULL)
	{
		return ERR;
	}
	if (pdict->n_data == pdict->size)
		return ERR;
	if (pdict->order == SORTED)
	{
		i = pdict->n_data - 1;
		while (i >= 0 && pdict->table[i] > key)
		{
			pdict->table[i + 1] = pdict->table[i];
			ob++;
			i--;
		}
		pdict->table[i + 1] = key;
		ob++;
		pdict->n_data++;
	}
	else
	{
		pdict->table[pdict->n_data] = key;
		ob++;
		pdict->n_data++;
	}

	return ob;
}

int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys)
{
	int i, j, ob = 0;
	if (pdict == NULL)
	{
		return ERR;
	}
	if (pdict->n_data + n_keys > pdict->size)
	{
		return ERR;
	}

	if (pdict->order == SORTED)
	{
		for (i = 0; i < n_keys; i++)
		{
			j = pdict->n_data - 1;
			while (j >= 0 && pdict->table[j] > keys[i])
			{
				pdict->table[j + 1] = pdict->table[j];
				ob++;
				j--;
			}
			pdict->table[j + 1] = keys[i];
			ob++;
			pdict->n_data++;
		}
	}
	else
	{
		for (i = 0; i < n_keys; i++)
		{
			pdict->table[pdict->n_data] = keys[i];
			ob++;
			pdict->n_data++;
		}
	}

	return 0;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
	int err, ob = 0;

	if (pdict == NULL || method == NULL || ppos == NULL)
	{
		return ERR;
	}

	err = method(pdict->table, 0, pdict->n_data - 1, key, ppos);
	if (err == ERR)
	{
		return ERR;
	}
	else
	{
		ob += err;
	}

	return ob;
}

/* Search functions of the Dictionary ADT */
int bin_search(int *table, int F, int L, int key, int *ppos)
{
	int m, ob = 0;

	if (table == NULL || F > L || ppos == NULL || F < 0 || L < 0)
	{
		return ERR;
	}

	*ppos = NOT_FOUND;

	while (F <= L)
	{
		ob++;
		m = (F + L) / 2;
		if (table[m] == key)
		{
			*ppos = m;
			break;
		}
		if (table[m] < key)
		{
			F = m + 1;
		}
		else
		{
			L = m - 1;
		}
	}

	return ob;
}

int lin_search(int *table, int F, int L, int key, int *ppos)
{
	int i, ob = 0;

	if (table == NULL || F > L || ppos == NULL || F < 0 || L < 0)
	{
		return ERR;
	}

	*ppos = NOT_FOUND;

	for (i = F; i <= L; i++)
	{
		ob++;
		if (table[i] == key)
		{
			*ppos = i;
			break;
		}
	}

	return ob;
}

int lin_auto_search(int *table, int F, int L, int key, int *ppos)
{
	int i, aux, ob = 0;

	if (table == NULL || F > L || ppos == NULL || F < 0 || L < 0)
	{
		return ERR;
	}

	*ppos = NOT_FOUND;

	for (i = F; i <= L; i++)
	{
		ob++;
		if (table[i] == key)
		{
			*ppos = i;
			if (i > F)
			{
				aux = table[i - 1];
				table[i - 1] = table[i];
				table[i] = aux;
			}
			break;
		}
	}

	return ob;
}
