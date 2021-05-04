#include <stdio.h>

#include "bst.h"

int predicate_int(const void *x, const void *y)
{

  int a = *(int *)x;
  int b = *(int *)y;
  if (a < b) {
    return 1;
  }
  else if (a > b) {
    return 0;
  }
  return -1;
}

int predicate_double(const void *x, const void *y)
{

  double a = *(double *)x;
  double b = *(double *)y;
  if (a - b < 0) {
    return 1;
  }
  else if (a - b > 0) {
    return 0;
  }
  return -1;
}

int my_predicate(const void *x, const void *y)
{
  int a = *(int *)x;
  int b = *(int *)y;

  if ((a % 3) < (b % 3)) {
    return 1;
  }
  else if ((a % 3) > (b % 3)) {
    return 0;
  }
  return -1;
}

int comparator_int(const void *x, const void *y)
{
  int a = *(int *)x;
  int b = *(int *)y;
  if (a < b) {
    return 1;
  }
  else if (a > b) {
    return 0;
  }
  return -1;
}

int comparator_double(const void *x, const void *y)
{
  double a = *(double *)x;
  double b = *(double *)y;
  if (a - b < 0) {
    return 1;
  }
  else if (a - b > 0) {
    return 0;
  }
  return -1;
}

void printer_double(const void *x)
{
  printf("%lf\n", *(double *)x);
}

void printer_int(const void *x)
{
  printf("%d\n", *(int *)x);
}

int main()
{
  Tree_t *tree = init_set(predicate_double, sizeof(double));
  double a[6] = {1.0, 1.5, 3.5, 2.7, 1.9, 7.9};
  for (int i = 1; i < 6; i++) {
    insert(tree, &a[i]);
  }
  disp(tree, printer_double);
  double key = 2.7;
  Iterator_t *it = find(tree, &key, comparator_double);
  if (has_next(it)) {
    printf("\nfound!! elem ");
    printer_double(get_data(it));
  }
  else {
    printf("Not found....\n");
  }
  printf("Size : %d\n", size(tree));
  erase(tree, &key);
  clear(tree);
  printf("Size : %d\n", size(tree));
  it = begin(tree);
  while (has_next(it)) {
    printf("Next : ");
    printer_double(get_data(it));
    next(it);
  }

  Tree_t *set1 = init_set(predicate_int, sizeof(int));
  int b[6] = {2, 2, 5, 6, 11, 13};
  for (int i = 0; i < 6; i++) {
    insert(set1, &b[i]);
  }
  disp(set1, printer_int);
  int key1 = 6;
  it = find(set1, &key1, comparator_int);
  if (has_next(it)) {
    printf("\nfound!! elem ");
    printer_int(get_data(it));
  }
  else {
    printf("Not found....\n");
  }
  printf("Size : %d\n", size(set1));
  erase(set1, &key);
  clear(set1);
  printf("Size : %d\n", size(set1));
  it = begin(set1);
  while (has_next(it)) {
    printf("Next : ");
    printer_int(get_data(it));
    next(it);
  }

  Tree_t *set2 = init_set(my_predicate, sizeof(int));
  int c[9] = {9, 3, 15, 13, 16, 19, 5, 8, 11};
  for (int i = 0; i < 9; i++) {
    insert(set2, &c[i]);
  }
  disp(set2, printer_int);
  int key2 = 6;
  it = find(set2, &key1, comparator_int);
  if (has_next(it)) {
    printf("\nfound!! elem ");
    printer_int(get_data(it));
  }
  else {
    printf("Not found....\n");
  }

  int key3 = 3;
  it = find(set2, &key1, comparator_int);
  if (has_next(it)) {
    printf("\nfound!! elem ");
    printer_int(get_data(it));
  }
  else {
    printf("Not found....\n");
  }

  printf("Size : %d\n", size(set2));
  erase(set2, &key);
  clear(set2);
  printf("Size : %d\n", size(set2));
  it = begin(set2);
  while (has_next(it)) {
    printf("Next : ");
    printer_int(get_data(it));
    next(it);
  }

  /* Iterator_t *it1 = upper_bound(begin(tree), end(tree), 5); */
  /* printf("\nUpper bound of 5 : %d\n", get_data(it1)); */
  /* Iterator_t *it2 = lower_bound(begin(tree), end(tree), 5); */
  /* printf("\nLower bound of 5 : %d\n", get_data(it2)); */

  /* erase(tree, 2); */
  /* erase(tree, 4); */
  /* erase(tree, 7); */

  /* printf("Size : %d\n", size(tree)); */

  /* insert(tree, 2); */
  /* insert(tree, 2); */
  /* insert(tree, 4); */

  /* printf("Size : %d\n", size(tree)); */

  /* disp(tree); */

  /* Iterator_t *it_start; */
  /* it_start = begin(tree); */
  /* printf("iter_start : %d\n", get_data(it_start)); */

  /* Iterator_t *it_end; */
  /* it_end = end(tree); */
  /* printf("iter_start : %d\n", get_data(it_end)); */

  /* Iterator_t *res = find(tree, 7); */
  /* if (res->ptr == NULL) { */
  /*   printf("\n not found!!\n"); */
  /* } */
  /* else { */
  /*   printf("res : %d\n", get_data(res)); */
  /* } */

  /* printf("Clearing set...\n"); */
  /* clear(tree); */
  /* insert(tree, 7); */
  /* disp(tree); */

  /* Tree_t *set1 = init_set(my_predicate, "int"); */
  /* insert(set1, 3); */
  /* insert(set1, 5); */
  /* insert(set1, 9); */
  /* insert(set1, 12); */
  /* insert(set1, 13); */
  /* insert(set1, 15); */
  /* disp(set1); */

  /* it = begin(set1); */
  /* while (has_next(it)) { */
  /*   printf("Next : %d\n", get_data(it)); */
  /*   next(it); */
  /* } */

  /* Iterator_t *res = find(set1, 7); */
  /* if (res->ptr == NULL) { */
  /*   printf("\n not found!!\n"); */
  /* } */
  /* else { */
  /*   printf("res : %d\n", get_data(res)); */
  /* } */
}
