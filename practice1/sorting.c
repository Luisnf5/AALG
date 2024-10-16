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

/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{
    int i, j, temp;
    int count = 0;  // Contador de intercambios

    // Validar los parámetros de entrada
    if (!array || ip < 0 || iu < 0 || ip > iu) return ERR;

    // Algoritmo de ordenación burbuja
    for (i = ip; i < iu; i++) {
        for (j = iu; j > i; j--) {
            if (array[j] < array[j - 1]) {
                // Intercambiar los elementos
                temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
                count++;  // Incrementar el contador de intercambios
            }
        }
    }

    return count;  // Devolver el número de intercambios
}

int BubbleSortFlag(int* array, int ip, int iu)
{
  /* your code */
}



