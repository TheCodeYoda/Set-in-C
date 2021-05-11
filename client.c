#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bst.h"

/* SET INTERFACE : */

/* Set *init_set(int (*predicate)(), int size_of_type); ----------> Initialises the set */
/* void disp(Iterator* begin, Iterator* end, void (*printer)());------------------------> displays
 * the set */
/* void insert(Set *tree, void *data);--------------------------> Inserts data into set */
/* void erase(Set *tree, void *data);--------------> erases single element in the set */
/* void clear(Set *tree); ---------------------------------> clears the entire set */
/* int size(Set *tree); ------------------------------> no. of elements in the set */
/* void merge(Set *set1, Set *set2); ------> merges 2 sets based o first set's predicate */

/* ITERATOR INTERFACE: */

/* Iterator_t *find(Set *tree, void *data, int (*comparator)()); ---> member find */
/* Iterator_t *begin(Set *tree);----> returns Iterator to the beginning of the set */
/* Iterator_t *end(Set *tree);---> returns Iterator to location one past the last element */
/* Iterator_t *rbegin(Set *tree);----> returns Iterator to the last element of the set */
/* Iterator_t *rend(Set *tree);---> returns Iterator to location one previous than first element */
/* void *next(Iterator_t *iter);----> moves the iterator to next element(inorder way) */
/* void *prev(Iterator_t *iter);----> moves the iterator to prev element(inorder way) */
/* int is_not_null(Iterator_t *iter);----->checks whether Iterator is pointing to NULL */
/* Iterator_t *lower_bound(Iterator_t *begin, Iterator_t *end, void *data, int (*comparator)()); */
/* Iterator_t *upper_bound(Iterator_t *begin, Iterator_t *end, void *data, int (*comparator)()); */
/* void *get_data(Iterator_t *it); ---> returns void pointer to data pointed to by Iterator */

typedef struct point {
  int x;
  int y;
} point_t;

int predicate_point(const void *x, const void *y)
{
  point_t a = *(point_t *)x;
  point_t b = *(point_t *)y;
  if ((a.x + a.y) < (b.x + b.y)) {
    return 1;
  }
  else if ((a.x + a.y) > (b.x + b.y)) {
    return 0;
  }
  return -1;
}

int comparator_point(const void *x, const void *y)
{
  point_t a = *(point_t *)x;
  point_t b = *(point_t *)y;
  if ((a.x + a.y) < (b.x + b.y)) {
    return 1;
  }
  else if ((a.x + a.y) > (b.x + b.y)) {
    return 0;
  }
  if (a.x == b.x && a.y == b.y) {
    return -1;
  }
  return 1;
}

void printer_point(const void *data)
{
  point_t p = *(point_t *)data;
  printf("{%d,%d}\n", p.x, p.y);
}

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
  printf("%lf\t", *(double *)x);
}

void printer_int(const void *x)
{
  printf("%d\n", *(int *)x);
}

int comparator_string(const void *x, const void *y)
{
  char *a = (char *)x;
  char *b = (char *)y;
  if (strcmp(a, b) < 0) {
    return 1;
  }
  else if (strcmp(a, b) > 0) {
    return 0;
  }
  return -1;
}

int predicate_string(const void *x, const void *y)
{
  char *a = (char *)x;
  char *b = (char *)y;
  if (strcmp(a, b) < 0) {
    return 1;
  }
  else if (strcmp(a, b) > 0) {
    return 0;
  }
  return -1;
}

void printer_string(const void *x)
{
  printf("%s\n", (char *)x);
}

int main()
{

  {
    Set *set0 = init_set(predicate_point, sizeof(point_t));
    point_t a[6] = {{1, 4}, {1, 2}, {9, 5}, {11, 12}, {1, 9}, {0, 1}};
    for (int i = 0; i < 6; i++) {
      insert(set0, &a[i]);
    }

    printf("Reverse Iterating:\n");
    Iterator_t *it = rbegin(set0);
    while (is_not_null(it)) {
      printer_point(get_data(it));
      prev(it);
    }

    printf("\n\n");

    printf("Forward Iterating:\n");
    Iterator_t *it1 = begin(set0);
    while (is_not_null(it1)) {
      printer_point(get_data(it1));
      next(it1);
    }

    printf("\n\n");

    point_t key1 = {9, 5};
    Iterator_t *it2 = find(set0, &key1, comparator_point);
    if (is_not_null(it2)) {
      printf("found!! elem...");
      printer_point(get_data(it2));
    }
    else {
      printf("{%d,%d} not found....\n", key1.x, key1.y);
    }

    printf("\n\n");

    point_t key2 = {11, 13};
    it2 = find(set0, &key2, comparator_point);
    if (is_not_null(it2)) {
      printf("found!! elem...");
      printer_point(get_data(it2));
    }
    else {
      printf("{%d,%d} not found....\n", key2.x, key2.y);
    }

    printf("\n\n");

    printf("Lower bound of {%d,%d} : ", key1.x, key1.y);
    if (is_not_null(lower_bound(begin(set0), end(set0), &key1, comparator_point))) {
      printer_point(get_data(lower_bound(begin(set0), end(set0), &key1, comparator_point)));
    }
    else {
      printf("No lower bound....");
    }
    printf("\n");

    printf("Upper bound of {%d,%d} : ", key2.x, key2.y);
    if (is_not_null(upper_bound(begin(set0), end(set0), &key2, comparator_point))) {
      printer_point(get_data(upper_bound(begin(set0), end(set0), &key2, comparator_point)));
    }
    else {
      printf("No upper bound....");
    }
    printf("\n");

    printf("\n\n");

    point_t key3 = {0, 1};
    printf("erasing element {%d,%d}....\n", key3.x, key3.y);
    erase(set0, &key3);
    disp(begin(set0), end(set0), printer_point);

    printf("\n\n");

    printf("clearing set...\n");
    clear(set0);
    disp(begin(set0), end(set0), printer_point);
    printf("size %d\n", size(set0));

    printf("\n\n");

    printf("Merge operation...\n");
    /* inserting into set 1 */
    Set *set1 = init_set(predicate_point, sizeof(point_t));
    point_t b[3] = {{1, 1}, {2, 2}, {3, 3}};
    for (int i = 0; i < 3; i++) {
      insert(set1, &b[i]);
    }
    /* inserting into set 0 after clearing in prev statements */
    point_t c[6] = {{2, 2}, {4, 4}};
    for (int i = 0; i < 2; i++) {
      insert(set0, &c[i]);
    }
    printf("\nBefore merging..\n\nSet 0 .... \n");
    disp(begin(set0), end(set0), printer_point);
    printf("\n");
    printf("Set 1 .... \n");
    disp(begin(set1), end(set1), printer_point);
    merge(set0, set1);
    printf("\n\nAfter merging..\n\nSet 0 .... \n");
    disp(begin(set0), end(set0), printer_point);
    printf("\n");
    printf("Set 1 .... \n");
    disp(begin(set1), end(set1), printer_point);
  }

  /* -------float example : Def Predicate---------------------- */
  /* { */
  /*   Set *set0 = init_set(predicate_double, sizeof(double)); */
  /*   double a[6] = {1.0, 1.5, 3.5, 2.7, 1.9, 7.9}; */
  /*   for (int i = 0; i < 6; i++) { */
  /*     insert(set0, &a[i]); */
  /*   } */

  /*   printf("Reverse Iterating:\n"); */
  /*   Iterator_t *it = rbegin(set0); */
  /*   while (is_not_null(it)) { */
  /*     printer_double(get_data(it)); */
  /*     prev(it); */
  /*   } */

  /*   printf("\n\n"); */

  /*   printf("Forward Iterating:\n"); */
  /*   Iterator_t *it1 = begin(set0); */
  /*   while (is_not_null(it1)) { */
  /*     printer_double(get_data(it1)); */
  /*     next(it1); */
  /*   } */

  /*   printf("\n\n"); */

  /*   double key1 = 3.5; */
  /*   Iterator_t *it2 = find(set0, &key1, comparator_double); */
  /*   if (is_not_null(it2)) { */
  /*     printf("found!! elem..."); */
  /*     printer_double(get_data(it2)); */
  /*   } */
  /*   else { */
  /*     printf("%f not found....\n", key1); */
  /*   } */

  /*   printf("\n\n"); */

  /*   double key2 = 3.9; */
  /*   it2 = find(set0, &key2, comparator_double); */
  /*   if (is_not_null(it2)) { */
  /*     printf("found!! elem..."); */
  /*     printer_double(get_data(it2)); */
  /*   } */
  /*   else { */
  /*     printf("%f not found....\n", key2); */
  /*   } */

  /*   printf("\n\n"); */

  /*   printf("Lower bound of %lf : ", key1); */
  /*   printer_double(get_data(lower_bound(begin(set0), end(set0), &key1, comparator_double))); */
  /*   printf("\n"); */

  /*   printf("Upper bound of %lf : ", key2); */
  /*   printer_double(get_data(upper_bound(begin(set0), end(set0), &key2, comparator_double))); */
  /*   printf("\n"); */

  /*   printf("\n\n"); */

  /*   double key3 = 3.5; */
  /*   printf("erasing element %lf....\n", key3); */
  /*   erase(set0, &key3); */
  /*   disp(begin(set0), end(set0), printer_double); */

  /*   printf("\n\n"); */

  /*   printf("clearing set...\n"); */
  /*   clear(set0); */
  /*   disp(begin(set0), end(set0), printer_double); */
  /*   printf("size %d\n", size(set0)); */

  /*   printf("\n\n"); */

  /*   printf("Merge operation...\n"); */
  /*   /\* inserting into set 1 *\/ */
  /*   Set *set1 = init_set(predicate_double, sizeof(double)); */
  /*   double b[6] = {1.0, 9.9, 3.5, 2, 7, 6.6}; */
  /*   for (int i = 0; i < 6; i++) { */
  /*     insert(set1, &b[i]); */
  /*   } */
  /*   /\* inserting into set 0 after clearing in prev statements *\/ */
  /*   double c[6] = {1.0, 1.5, 3.5, 2.7, 1.9, 7.9}; */
  /*   for (int i = 0; i < 6; i++) { */
  /*     insert(set0, &c[i]); */
  /*   } */
  /*   printf("\nBefore merging..\n\nSet 0 .... \n"); */
  /*   disp(begin(set0), end(set0), printer_double); */
  /*   printf("\n"); */
  /*   printf("Set 1 .... \n"); */
  /*   disp(begin(set1), end(set1), printer_double); */
  /*   merge(set0, set1); */
  /*   printf("\n\nAfter merging..\n\nSet 0 .... \n"); */
  /*   disp(begin(set0), end(set0), printer_double); */
  /*   printf("\n"); */
  /*   printf("Set 1 .... \n"); */
  /*   disp(begin(set1), end(set1), printer_double); */
  /* } */

  /* ---------------------------Integer : Custom predicate ------------  */

  /* { */
  /*   Set *set0 = init_set(my_predicate, sizeof(int)); */
  /*   int a[6] = {1, 7, 2, 3, 5, 4}; */
  /*   for (int i = 0; i < 6; i++) { */
  /*     insert(set0, &a[i]); */
  /*   } */

  /*   printf("Reverse Iterating:\n"); */
  /*   Iterator_t *it = rbegin(set0); */
  /*   while (is_not_null(it)) { */
  /*     printer_int(get_data(it)); */
  /*     prev(it); */
  /*   } */

  /*   printf("\n\n"); */

  /*   printf("Forward Iterating:\n"); */
  /*   Iterator_t *it1 = begin(set0); */
  /*   while (is_not_null(it1)) { */
  /*     printer_int(get_data(it1)); */
  /*     next(it1); */
  /*   } */

  /*   printf("\n\n"); */

  /*   int key1 = 3; */
  /*   Iterator_t *it2 = find(set0, &key1, comparator_int); */
  /*   if (is_not_null(it2)) { */
  /*     printf("found!! elem..."); */
  /*     printer_int(get_data(it2)); */
  /*   } */
  /*   else { */
  /*     printf("Not found....\n"); */
  /*   } */

  /*   printf("\n\n"); */

  /*   int key2 = 11; */
  /*   it2 = find(set0, &key2, comparator_int); */
  /*   if (is_not_null(it2)) { */
  /*     printf("found!! elem..."); */
  /*     printer_int(get_data(it2)); */
  /*   } */
  /*   else { */
  /*     printf("Not found....\n"); */
  /*   } */

  /*   printf("\n\n"); */

  /*   int key3 = 3; */
  /*   printf("erasing element %d....\n", key3); */
  /*   erase(set0, &key3); */
  /*   disp(begin(set0), end(set0), printer_int); */

  /*   printf("\n\n"); */

  /*   printf("clearing set...\n"); */
  /*   clear(set0); */
  /*   disp(begin(set0), end(set0), printer_int); */
  /*   printf("size %d\n", size(set0)); */

  /*   printf("\n\n"); */

  /*   printf("Merge operation...\n"); */
  /*   /\* inserting into set 1 *\/ */
  /*   Set *set1 = init_set(my_predicate, sizeof(int)); */
  /*   int b[6] = {1, 7, 11, 3, 2, 6}; */
  /*   for (int i = 0; i < 6; i++) { */
  /*     insert(set1, &b[i]); */
  /*   } */
  /*   /\* inserting into set 0 after clearing in prev statements *\/ */
  /*   int c[6] = {12, 15, 23, 11, 7, 3}; */
  /*   for (int i = 0; i < 6; i++) { */
  /*     insert(set0, &c[i]); */
  /*   } */
  /*   printf("\nBefore merging..\n\nSet 0 .... \n"); */
  /*   disp(begin(set0), end(set0), printer_int); */
  /*   printf("\n"); */
  /*   printf("Set 1 .... \n"); */
  /*   disp(begin(set1), end(set1), printer_int); */
  /*   merge(set0, set1); */
  /*   printf("\n\nAfter merging..\n\nSet 0 .... \n"); */
  /*   disp(begin(set0), end(set0), printer_int); */
  /*   printf("\n"); */
  /*   printf("Set 1 .... \n"); */
  /*   disp(begin(set1), end(set1), printer_int); */
  /* } */

  /* ------------Integer : def. predicate ----------------  */

  /* { */
  /*   Set *set0 = init_set(predicate_int, sizeof(int)); */
  /*   int a[6] = {1, 7, 2, 3, 5, 4}; */
  /*   for (int i = 0; i < 6; i++) { */
  /*     insert(set0, &a[i]); */
  /*   } */

  /*   printf("Reverse Iterating:\n"); */
  /*   Iterator_t *it = rbegin(set0); */
  /*   while (is_not_null(it)) { */
  /*     printer_int(get_data(it)); */
  /*     prev(it); */
  /*   } */

  /*   printf("\n\n"); */

  /*   printf("Forward Iterating:\n"); */
  /*   Iterator_t *it1 = begin(set0); */
  /*   while (is_not_null(it1)) { */
  /*     printer_int(get_data(it1)); */
  /*     next(it1); */
  /*   } */

  /*   printf("\n\n"); */

  /*   int key1 = 3; */
  /*   Iterator_t *it2 = find(set0, &key1, comparator_int); */
  /*   if (is_not_null(it2)) { */
  /*     printf("found!! elem..."); */
  /*     printer_int(get_data(it2)); */
  /*   } */
  /*   else { */
  /*     printf("Not found....\n"); */
  /*   } */

  /*   printf("\n\n"); */

  /*   int key2 = 11; */
  /*   it2 = find(set0, &key2, comparator_int); */
  /*   if (is_not_null(it2)) { */
  /*     printf("found!! elem..."); */
  /*     printer_int(get_data(it2)); */
  /*   } */
  /*   else { */
  /*     printf("Not found....\n"); */
  /*   } */

  /*   printf("\n\n"); */

  /*   int key3 = 3; */
  /*   printf("erasing element %d....\n", key3); */
  /*   erase(set0, &key3); */
  /*   disp(begin(set0), end(set0), printer_int); */

  /*   printf("\n\n"); */

  /*   printf("clearing set...\n"); */
  /*   clear(set0); */
  /*   disp(begin(set0), end(set0), printer_int); */
  /*   printf("size %d\n", size(set0)); */

  /*   printf("\n\n"); */

  /*   printf("Merge operation...\n"); */
  /*   /\* inserting into set 1 *\/ */
  /*   Set *set1 = init_set(predicate_int, sizeof(int)); */
  /*   int b[6] = {1, 7, 11, 3, 2, 6}; */
  /*   for (int i = 0; i < 6; i++) { */
  /*     insert(set1, &b[i]); */
  /*   } */
  /*   /\* inserting into set 0 after clearing in prev statements *\/ */
  /*   int c[6] = {12, 15, 23, 11, 7, 3}; */
  /*   for (int i = 0; i < 6; i++) { */
  /*     insert(set0, &c[i]); */
  /*   } */
  /*   printf("\nBefore merging..\n\nSet 0 .... \n"); */
  /*   disp(begin(set0), end(set0), printer_int); */
  /*   printf("\n"); */
  /*   printf("Set 1 .... \n"); */
  /*   disp(begin(set1), end(set1), printer_int); */
  /*   merge(set0, set1); */
  /*   printf("\n\nAfter merging..\n\nSet 0 .... \n"); */
  /*   disp(begin(set0), end(set0), printer_int); */
  /*   printf("\n"); */
  /*   printf("Set 1 .... \n"); */
  /*   disp(begin(set1), end(set1), printer_int); */
  /* } */

  /*----------- String  : def.predicate ----------- */

  /* { */
  /*   char a[][100] = {"Jack", "John", "codeyoda", "aditya", "shashank"}; */
  /*   Set *set0 = init_set(predicate_string, 100); */
  /*   for (char i = 0; i < 5; i++) { */
  /*     insert(set0, a[i]); */
  /*   } */

  /*   printf("Reverse Iterating:\n"); */
  /*   Iterator_t *it = rbegin(set0); */
  /*   while (is_not_null(it)) { */
  /*     printer_string(get_data(it)); */
  /*     prev(it); */
  /*   } */

  /*   printf("\n\n"); */

  /*   printf("Forward Iterating:\n"); */
  /*   Iterator_t *it1 = begin(set0); */
  /*   while (is_not_null(it1)) { */
  /*     printer_string(get_data(it1)); */
  /*     next(it1); */
  /*   } */

  /*   printf("\n\n"); */

  /*   char key1[5] = "Jack"; */
  /*   Iterator_t *it2 = find(set0, &key1, comparator_string); */
  /*   if (is_not_null(it2)) { */
  /*     printf("found!! elem..."); */
  /*     printer_string(get_data(it2)); */
  /*   } */
  /*   else { */
  /*     printf("Not found....\n"); */
  /*   } */

  /*   printf("\n\n"); */

  /*   char key2[4] = "asd"; */
  /*   it2 = find(set0, &key2, comparator_string); */
  /*   if (is_not_null(it2)) { */
  /*     printf("found!! elem..."); */
  /*     printer_string(get_data(it2)); */
  /*   } */
  /*   else { */
  /*     printf("Not found....\n"); */
  /*   } */

  /*   printf("\n\n"); */

  /*   char key3[5] = "Jack"; */
  /*   printf("erasing element %s....\n", key3); */
  /*   erase(set0, key3); */
  /*   disp(begin(set0), end(set0), printer_string); */

  /*   printf("\n\n"); */

  /*   printf("clearing set...\n"); */
  /*   clear(set0); */
  /*   disp(begin(set0), end(set0), printer_string); */
  /*   printf("size %d\n", size(set0)); */

  /*   printf("\n\n"); */

  /*   printf("Merge operation...\n"); */
  /*   /\* inserting into set 1 *\/ */
  /*   Set *set1 = init_set(predicate_string, 100); */
  /*   char b[][100] = {"HP", "Apple", "Dell", "Asus", "Samsung"}; */
  /*   for (char i = 0; i < 5; i++) { */
  /*     insert(set1, b[i]); */
  /*   } */
  /*   /\* inserting into set 0 after clearing in prev statements *\/ */
  /*   char c[][100] = {"alienware", "HP", "Benq"}; */
  /*   for (char i = 0; i < 3; i++) { */
  /*     insert(set0, c[i]); */
  /*   } */
  /*   printf("\nBefore merging..\n\nSet 0 .... \n"); */
  /*   disp(begin(set0), end(set0), printer_string); */
  /*   printf("\n"); */
  /*   printf("Set 1 .... \n"); */
  /*   disp(begin(set1), end(set1), printer_string); */
  /*   merge(set0, set1); */
  /*   printf("\n\nAfter merging..\n\nSet 0 .... \n"); */
  /*   disp(begin(set0), end(set0), printer_string); */
  /*   printf("\n"); */
  /*   printf("Set 1 .... \n"); */
  /*   disp(begin(set1), end(set1), printer_string); */
  /* } */
}
