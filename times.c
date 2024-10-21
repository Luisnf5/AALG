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
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms,int N, PTIME_AA ptime)
{
  int i, j, min=0, max=0, sumOB=0;
  float *times, sumT=0;
  int **perms, *obPerms;
  clock_t start, end;
  double final = 0;

  if (metodo == NULL | n_perms < 1 | N < 1 | ptime == NULL){
    return ERR;
  }

  perms = (int**) malloc(n_perms * sizeof(int*));
  if (perms == NULL){
    printf("Error al asignar memoria para las permutaciones");
    return 1;
  }
  obPerms = (int*) malloc(n_perms * sizeof(int));
  if (obPerms == NULL){
    printf("Error al asignar memoria para las permutaciones");
    return 1;
  }
  times = (float*)malloc(n_perms * sizeof(float));
  if (times == NULL){
    printf("Error al asignar memoria para los tiempos");
    return 1;
  }

  ptime->N = N;
  ptime->n_elems = n_perms;

  for (i=0; i<n_perms; i++){
    perms[i] = generate_perm(N);
  }

  for (i=0; i<n_perms; i++){
    start = clock();

    obPerms[i] = BubbleSort(perms[i], perms[i][0], perms[i][sizeof(perms[i]) / sizeof(perms[i][0])]);

    end = clock();

    final = ((double)(end - start)) / CLOCKS_PER_SEC;
    times[i] = final;
    sumT += final;
    sumOB += obPerms[i];

    if (obPerms[i] < min){
      min = obPerms[i];
    }
    if (obPerms[i] > max){
      max = obPerms;
    }
    printf("time: %f , it: %d", final, i);
    printf("obPerms: %d, it: %d", obPerms[i], i);
  }
  ptime->min_ob = min;
  ptime->max_ob = max;
  ptime->time = sumT/n_perms;
  ptime->average_ob = sumOB/n_perms;

  for (i=0; i<n_perms; i++){
    free(perms[i]);
  }
  free(perms);
  free(obPerms);
  free(times);

  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms)
{
  PTIME_AA pt = NULL;
  int i, arr_tam, j;

  if (method == NULL | file == NULL | num_min < 1 | num_max < 1 | num_min > num_max | incr < 1 | n_perms < 1){
    return ERR;
  }

  arr_tam = ((num_max - num_min) / incr) + 1;

  pt = (PTIME_AA*) malloc(arr_tam * sizeof(PTIME_AA));
  if (pt == NULL){
    return ERR;
  }

  for (i=0; i<=arr_tam; i++){
    if (average_sorting_time(method, n_perms, num_min+(incr*i), &pt[i]) == ERR){
      free(pt);
      return ERR;
    }
  }

  if (save_time_table(file, pt, arr_tam) == ERR){
    free(pt);
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
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  int i;
  FILE *f = NULL;

  if (file == NULL | !ptime | n_times < 1){
    return ERR;
  }

  f = fopen(file, "w");
  if (f == NULL){
    return ERR;
  }

  for (i=0; i<n_times; i++){
    if (fprintf(f, "%d %f %f %d %d\n", ptime[i].N, ptime[i].time, ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob) < 0){
      fclose(f);
      return ERR;
    }
  }

  return OK;
}


