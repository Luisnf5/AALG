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

int heapsort(int *tabla, int ip, int iu)
{
    int ob = 0, obaux;

    if (tabla == NULL || ip < 0 || iu < 0 || iu < ip)
    {
        printf("error 20\n");
        return ERR;
    }

    obaux = CrearHeap(tabla, iu - ip + 1);
    if (obaux == ERR)
    {
        printf("error 21\n");
        return ERR;
    }
    else
    {
        ob += obaux;
    }

    obaux = OrdenarHeap(tabla, iu - ip + 1);
    if (obaux == ERR)
    {
        printf("error 22\n");
        return ERR;
    }
    else
    {
        ob += obaux;
    }

    return ob;
}

int Swap(int *tabla, int i, int j, int n)
{
    int temp;

    if (tabla == NULL || i < 0 || j < 0 || i > n || j > n)
    {
        printf("error 23\n");
        printf("i: %d, j: %d, n: %d\n", i, j, n);
        return ERR;
    }

    if (i == j)
    {
        return 0;
    }

    temp = tabla[i];
    tabla[i] = tabla[j];
    tabla[j] = temp;

    return 1;
}

int Heapify(int *tabla, int n, int i)
{
    int ob = 0, obaux;
    if (tabla == NULL || n < 0 || i < 0 || i > n)
    {
        printf("error 24\n");
        return ERR;
    }

    while ((2 * i) + 2 < n)
    {
        if (tabla[i] < tabla[2 * i + 1] && tabla[2 * i + 1] > tabla[2 * i + 2])
        {
            obaux = Swap(tabla, i, 2 * i + 1, n);
            if (obaux == ERR)
            {
                printf("error 25\n");
                return ERR;
            }
            else
            {
                ob += obaux;
            }
            i = 2 * i + 1;
        }
        else if (tabla[i] < tabla[2 * i + 2])
        {
            obaux = Swap(tabla, i, 2 * i + 2, n);
            if (obaux == ERR)
            {
                printf("error 27\n");
                return ERR;
            }
            else
            {
                ob += obaux;
            }
            i = 2 * i + 2;
        }
        else
        {
            break;
        }
    }
    return ob;
}

int OrdenarHeap(int *tabla, int n)
{
    int i, temp, ind, ob = 0, obaux;

    if (tabla == NULL || n < 1)
    {
        printf("error 28\n");
        return ERR;
    }

    for (i = n - 1; i > 0; i--)
    {
        obaux = Swap(tabla, 0, i, n);
        if (obaux == ERR)
        {
            printf("error 29\n");
            return ERR;
        }
        else
        {
            ob += obaux;
        }
        obaux = Heapify(tabla, i, 0);
        if (obaux == ERR)
        {
            printf("error 30\n");
            return ERR;
        }
        else
        {
            ob += obaux;
        }
    }
    return ob;
}

int CrearHeap(int *tabla, int n)
{
    int i, ob = 0, obaux;

    if (tabla == NULL || n < 1)
    {
        printf("error 31\n");
        return ERR;
    }

    for (i = n / 2 - 1; i >= 0; i--)
    {
        obaux = Heapify(tabla, n, i);
        if (obaux == ERR)
        {
            printf("error 32\n");
            return ERR;
        }
        else
        {
            ob += obaux;
        }
    }

    return ob;
}