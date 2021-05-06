#include <stdio.h>

#include "bst.h"

/* SET INTERFACE : */

/* Set *init_set(int (*predicate)(), int size_of_type); ----------> Initialises the set*/
/* void disp(Set *tree, void (*printer)());------------------------> displays the set */
/* void insert(Set *tree, void *data);--------------------------> Inserts data into set */
/* void erase(Set *tree, void *data);--------------> erases single element in the set*/
/* void clear(Set *tree); ---------------------------------> clears the entire set */
/* int size(Set *tree); ------------------------------> no. of elements in the set */
/* void merge(Set *set1, Set *set2); ------> merges 2 sets based o first set's predicate */

/* ITERATOR INTERFACE: */

/* void init_iterator(Iterator_t *iter, Set *tree); ---> initialises Iterator pointing to root*/
/* Iterator_t *find(Set *tree, void *data, int (*comparator)()); ---> member find */
/* Iterator_t *begin(Set *tree);----> returns Iterator to the beginning of the set */
/* Iterator_t *end(Set *tree);---> returns Iterator to the end of the set */
/* Iterator_t *next(Iterator_t *iter);----> returns Iterator to next element(inorder way) */
/* int has_next(Iterator_t *iter);----->checks whether Iterator is pointing to NULL */
/* Iterator_t *lower_bound(Iterator_t *begin, Iterator_t *end, void *data, int (*comparator)()); */
/* Iterator_t *upper_bound(Iterator_t *begin, Iterator_t *end, void *data, int (*comparator)()); */
/* void *get_data(Iterator_t *it); ---> returns void pointer to data pointed to by Iterator */

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
  Set *set0 = init_set(predicate_double, sizeof(double));
  double a[6] = {1.0, 1.5, 3.5, 2.7, 1.9, 7.9};
  for (int i = 1; i < 6; i++) {
    insert(set0, &a[i]);
  }
  disp(begin(set0), end(set0), printer_double);
  double key = 3.5;
  Iterator_t *it = find(set0, &key, comparator_double);
  if (has_next(it)) {
    printf("\nfound!! elem ");
    printer_double(get_data(it));
  }
  else {
    printf("Not found....\n");
  }

  key = 2.7;
  Iterator_t *it1 = upper_bound(begin(set0), it, &key, comparator_double);
  if (has_next(it1)) {
    printf("\nupper bound found!! elem ");
    printer_double(get_data(it1));
  }
  else {
    printf("Not found....\n");
  }

  printf("Size : %d\n", size(set0));
  erase(set0, &key);
  disp(begin(set0), end(set0), printer_double);
  printf("Size : %d\n", size(set0));
  it = begin(set0);
  while (has_next(it)) {
    printf("Next : ");
    printer_double(get_data(it));
    next(it);
  }

  Set *set1 = init_set(predicate_int, sizeof(int));
  int b[6] = {2, 2, 5, 6, 11, 13};
  for (int i = 0; i < 6; i++) {
    insert(set1, &b[i]);
  }
  disp(begin(set1), end(set1), printer_int);
  int key1 = 6;
  it = find(set1, &key1, comparator_int);
  if (has_next(it)) {
    printf("\nfound!! elem ");
    printer_int(get_data(it));
  }
  else {
    printf("Not found....\n");
  }
  /* printf("Size : %d\n", size(set1)); */
  /* erase(set1, &key); */
  /* clear(set1); */
  /* printf("Size : %d\n", size(set1)); */
  /* it = begin(set1); */
  /* while (has_next(it)) { */
  /*   printf("Next : "); */
  /*   printer_int(get_data(it)); */
  /*   next(it); */
  /* } */

  Set *set2 = init_set(my_predicate, sizeof(int));
  int c[9] = {9, 3, 15, 13, 16, 19};
  for (int i = 0; i < 9; i++) {
    insert(set2, &c[i]);
  }
  disp(begin(set2), end(set2), printer_int);
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

  /* printf("Size : %d\n", size(set2)); */
  /* erase(set2, &key); */
  /* clear(set2); */
  /* printf("Size : %d\n", size(set2)); */
  /* it = begin(set2); */
  /* while (has_next(it)) { */
  /*   printf("Next : "); */
  /*   printer_int(get_data(it)); */
  /*   next(it); */
  /* } */

  /* printf("before merge: \n\n"); */
  /* disp(set1, printer_int); */
  /* printf("\n"); */
  /* disp(set2, printer_int); */
  /* printf("\n\nafter merge:\n\n"); */
  /* merge(set2, set1); */
  /* disp(set1, printer_int); */
  /* printf("\n"); */
  /* disp(set2, printer_int); */

  /* Iterator_t *it1 = upper_bound(begin(set0), end(set0), 5); */
  /* printf("\nUpper bound of 5 : %d\n", get_data(it1)); */
  /* Iterator_t *it2 = lower_bound(begin(set0), end(set0), 5); */
  /* printf("\nLower bound of 5 : %d\n", get_data(it2)); */

  /* erase(set0, 2); */
  /* erase(set0, 4); */
  /* erase(set0, 7); */

  /* printf("Size : %d\n", size(set0)); */

  /* insert(set0, 2); */
  /* insert(set0, 2); */
  /* insert(set0, 4); */

  /* printf("Size : %d\n", size(set0)); */

  /* disp(set0); */

  /* Iterator_t *it_start; */
  /* it_start = begin(set0); */
  /* printf("iter_start : %d\n", get_data(it_start)); */

  /* Iterator_t *it_end; */
  /* it_end = end(set0); */
  /* printf("iter_start : %d\n", get_data(it_end)); */

  /* Iterator_t *res = find(set0, 7); */
  /* if (res->ptr == NULL) { */
  /*   printf("\n not found!!\n"); */
  /* } */
  /* else { */
  /*   printf("res : %d\n", get_data(res)); */
  /* } */

  /* printf("Clearing set...\n"); */
  /* clear(set0); */
  /* insert(set0, 7); */
  /* disp(set0); */

  /* Set *set1 = init_set(my_predicate, "int"); */
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
