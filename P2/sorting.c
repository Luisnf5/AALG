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

    if (iu < ip || tabla == NULL || ip < 0 || iu < 0)
    {
        return ERR;
    }
    else if (iu == ip)
    {
        return 0;
    }

    imedio = (ip + iu) / 2;

    mergesort(tabla, ip, imedio);

    mergesort(tabla, imedio + 1, iu);

    return merge(tabla, ip, iu, imedio);
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
    }

    i = 0;
    j = imedio - ip + 1;
    k = ip;

    while (i <= imedio - ip && j <= iu - ip)
    {
        if (tAux[i] < tAux[j])
        {
            tabla[k] = tAux[i];
            i++;
            ob++;
        }
        else
        {
            tabla[k] = tAux[j];
            j++;
        }
        k++;
    }

    if (i > imedio - ip)
    {
        while (j <= iu - ip)
        {
            tabla[k] = tAux[j];
            j++;
            k++;
        }
    }
    else if (j > iu - ip)
    {
        while (i <= imedio - ip)
        {
            tabla[k] = tAux[i];
            i++;
            k++;
        }
    }

    free(tAux);
    return ob;
}
