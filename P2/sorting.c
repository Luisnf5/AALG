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
#include <stdlib.h>

/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{
    int i, j, temp;
    int count = 0;  /**Contador de intercambios */

    /* Validar los parámetros de entrada */
    if (!array || ip < 0 || iu < 0 || ip > iu) return ERR;

    /* Algoritmo de ordenación burbuja */
    for (i = ip; i < iu; i++) {
        for (j = iu; j > i; j--) {
            if (array[j] < array[j - 1]) {
                temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
                count++;  
            }
        }
    }
 
    return count;
}

int BubbleSortFlag(int* array, int ip, int iu)
{
  int i, j, temp, flag;
    int count = 0;  /**Contador de intercambios */

    /* Validar los parámetros de entrada */
    if (!array || ip < 0 || iu < 0 || ip > iu) return ERR;

    /* Algoritmo de ordenación burbuja */
    for (i = ip; i < iu; i++) {
        flag = 0;
        for (j = iu; j > i; j--) {
            if (array[j] < array[j - 1]) {
                temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
                count++;
                flag = 1;
            }
        }

        if (flag == 0){
            break;
        }
    }

    return count;
}

int mergesort(int *tabla, int ip, int iu){
    int imedio;

    if (iu > ip || tabla == NULL || ip < 0 || iu < 0){
        return ERR;
    }else if (iu == ip){
        return 0;
    }

    imedio = (ip + iu)/2;

    mergesort(tabla, ip, imedio);

    mergesort(tabla, imedio+1, iu);

    return merge(tabla, ip, iu, imedio);
}

int merge(int *tabla, int ip, int iu, int imedio){
    int *tAux, i, j, k, ob=0;

    if (iu > ip || tabla == NULL || ip < 0 || iu < 0 || imedio > iu || imedio < ip || imedio < 0){
        return ERR;
    }

    tAux = (int*) malloc(((iu-ip)+1) * sizeof(int));
    if (tAux == NULL){
        return ERR;
    }

    //Copiar tabla de ip a iu
    for (i=ip, j=0; i<=iu; i++, j++){
        tAux[]
    }

    i=ip;
    j=imedio+1;
    k=iu;

    while(i<=imedio && j<= iu){
        if (tabla[i] < tabla[j]){
            tAux[k] = tabla[i];
            i++;
            ob++;
        }else{
            tAux[k] = tabla[j];
            j++;
        }
        k++;
    }

    if (i>imedio){
        while (j<=iu){
            tAux[k] = tabla[j];
            j++;
            k++;
        }
    }else if (j>iu){
        while (i<=imedio){
            tAux[k] = tabla[i];
            i++;
            k++;
        }
    }

    //Copiar tAux en tabla entre ip e iu

    free(tAux);
    return ob;
}



