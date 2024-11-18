/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"
#include "permutations.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int *array, int ip, int iu)
{
	int i, j, temp;
	int count = 0; /**Contador de intercambios */

	/* Validar los parámetros de entrada */
	if (!array || ip < 0 || iu < 0 || ip > iu)
		return ERR;

	/* Algoritmo de ordenación burbuja */
	for (i = ip; i < iu; i++)
	{
		for (j = iu; j > i; j--)
		{
			if (array[j] < array[j - 1])
			{
				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
				count++;
			}
		}
	}

	return count;
}

int BubbleSortFlag(int *array, int ip, int iu)
{
	int i, j, temp, flag;
	int count = 0; /**Contador de intercambios */

	/* Validar los parámetros de entrada */
	if (!array || ip < 0 || iu < 0 || ip > iu)
		return ERR;

	/* Algoritmo de ordenación burbuja */
	for (i = ip; i < iu; i++)
	{
		flag = 0;
		for (j = iu; j > i; j--)
		{
			if (array[j] < array[j - 1])
			{
				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
				count++;
				flag = 1;
			}
		}

		if (flag == 0)
		{
			break;
		}
	}

	return count;
}
int mergesort(int *tabla, int ip, int iu)
{
	int imedio;
	int ob = 0;

	if (iu < ip || tabla == NULL || ip < 0 || iu < 0)
	{
		return ERR;
	}
	else if (iu == ip)
	{
		return 0;
	}

	imedio = (ip + iu) / 2;

	ob += mergesort(tabla, ip, imedio);
	ob += mergesort(tabla, imedio + 1, iu);
	ob += merge(tabla, ip, iu, imedio);

	return ob;
}

int merge(int *tabla, int ip, int iu, int imedio)
{
	int *tAux, i, j, k, ob = 0;

	if (iu < ip || tabla == NULL || ip < 0 || iu < 0 || imedio > iu || imedio < ip || imedio < 0)
	{
		return ERR;
	}

	tAux = (int *)malloc(((iu - ip) + 1) * sizeof(int));

	if (tAux == NULL)
	{
		return ERR;
	}

	for (i = ip; i <= iu; i++)
	{
		tAux[i - ip] = tabla[i];
		ob++;
	}

	i = 0;
	j = imedio - ip + 1;
	k = ip;

	while (i <= imedio - ip && j <= iu - ip)
	{
		ob++;
		if (tAux[i] < tAux[j])
		{
			tabla[k] = tAux[i];
			i++;
		}
		else
		{
			tabla[k] = tAux[j];
			j++;
		}
		k++;
		ob++;
	}

	if (i > imedio - ip)
	{
		while (j <= iu - ip)
		{
			tabla[k] = tAux[j];
			j++;
			k++;
			ob++;
		}
	}
	else if (j > iu - ip)
	{
		while (i <= imedio - ip)
		{
			tabla[k] = tAux[i];
			i++;
			k++;
			ob++;
		}
	}

	free(tAux);
	return ob;
}

int max(int *tabla, int n, int i, int j, int k, int *result)
{

	printf("i: %d, j: %d, k: %d\n", tabla[i], tabla[j], tabla[k]);
	int ob = 0;
	if (result == NULL || tabla == NULL || i > n || j > n || k > n)
	{
		printf("error\n");
		return ERR;
	}
	if (tabla[i] > tabla[j])
	{
		ob++;
		if (tabla[i] > tabla[k])
		{
			ob++;
			*result = i;
			return ob;
		}
		else
		{
			ob++;
			*result = k;
			return ob;
		}
	}
	else
	{
		ob++;
		if (tabla[j] > tabla[k])
		{
			ob++;
			*result = j;
			return ob;
		}
		else
		{
			ob++;
			*result = k;
			return ob;
		}
	}
}

int heapsort(int *tabla, int ip, int iu)
{
    int n = iu - ip + 1;

    if (!tabla || ip < 0 || iu < 0 || ip > iu)
        return ERR;

    CrearHeap(tabla, n, ip);
    OrdenarHeap(tabla, n, ip);

    return 0;
}


int Heapify(int *tabla, int n, int i, int ip)
{
    int izq = 2 * (i - ip) + 1 + ip;
    int der = 2 * (i - ip) + 2 + ip; 
    int max = i;

    if (izq < n && tabla[izq] > tabla[max])
        max = izq;

    if (der < n && tabla[der] > tabla[max])
        max = der;

    if (max != i)
    {
        Swap(tabla, i, max);
        Heapify(tabla, n, max, ip);
    }

    return 0;
}


int CrearHeap(int *tabla, int n, int ip)
{
    int i;

    for (i = (n / 2) - 1 + ip; i >= ip; i--) 
        Heapify(tabla, n + ip, i, ip);

    return 0;
}

int OrdenarHeap(int *tabla, int n, int ip)
{
    int i;

    for (i = n - 1 + ip; i > ip; i--)
    {
        Swap(tabla, ip, i);
        Heapify(tabla, i, ip, ip);
    }

    return 0;
}



