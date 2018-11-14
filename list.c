// Joshua Guinness, November 10-13, 2018

#include "assignment3.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Personal functions created to use on assignment
static HBnodePtr HBAddToFront(HBnodePtr L, int value);
static SLnodePtr SLAddToFront(SLnodePtr L, int value);
static void clearArray(int *a, int m);
static SLnodePtr merge(SLnodePtr L, HBnodePtr Lnext);
static SLnodePtr SLAddToBack(SLnodePtr L, int value);
static SLnodePtr SLInsert(SLnodePtr L, int value, int counter);
static SLnodePtr SLReverse(SLnodePtr L);

// qSort function
int cmpfunc(const void *a, const void *b) { return (*(int *)b - *(int *)a); }

// Defined functions via assignment

HBnodePtr createHBlist(int n, int m) {

  srand(time(NULL));
  int arrayN[n];
  int arrayM[m];
  for (int i = 0; i < n; i++) {
    arrayN[i] = rand() % 50;
  }
  for (int i = 0; i < m; i++) {
    arrayM[i] = 0;
  }
  qsort(arrayN, n, sizeof(int), cmpfunc);

  HBnodePtr L = NULL;

  for (int j = 0; j < n; j++) {

    L = HBAddToFront(L, arrayN[j]);
    int numberOfBottomNodes = rand() % m;

    for (int k = 0; k < numberOfBottomNodes; k++) {
      arrayM[k] = rand() % 50 + arrayN[j];
    }
    qsort(arrayM, m, sizeof(int), cmpfunc);

    SLnodePtr firstSL = NULL;

    for (int l = 0; l < numberOfBottomNodes; l++) {
      firstSL = SLAddToFront(firstSL, arrayM[l]);
    }

    L->bottom = firstSL;
    clearArray(arrayM, numberOfBottomNodes);
  }

  return L;
}

void printHBlist(const HBnodePtr L) {

  HBnodePtr p;

  for (p = L; p != NULL; p = p->next) {
    printf("\n%d -> ", p->key);
    printSLlist(p->bottom);
  }
  printf("\n");
  free(p);
}

SLnodePtr flattenList(const HBnodePtr L) {

  HBnodePtr p;
  SLnodePtr q;
  SLnodePtr SLlist = NULL;
  SLlist = SLAddToFront(SLlist, L->key);
  for (q = L->bottom; q != NULL; q = q->next) {
    SLlist = SLAddToFront(SLlist, q->key);
  }

  for (p = L->next; p != NULL; p = p->next) {
    SLlist = merge(SLlist, p);
  }

  SLlist = SLReverse(SLlist);
  return SLlist;
}

void printSLlist(const SLnodePtr L) {

  SLnodePtr p;

  for (p = L; p != NULL; p = p->next) {
    printf("%d ", p->key);
  }
  free(p);
}

void freeSLlist(SLnodePtr L) {

  if (L->next != NULL) {
    freeSLlist(L->next);
  }

  free(L);
}

void freeHBlist(HBnodePtr L) {

  if (L->next != NULL) {
    freeHBlist(L->next);
  }

  free(L->bottom);
  free(L);
}

// Personal functions created to use on assignment

// Merges two SL linked lists together into one
static SLnodePtr merge(SLnodePtr L, HBnodePtr Lnext) {

  SLnodePtr r;
  int value = Lnext->key;
  int counter = 1;

  for (r = L; r != NULL; r = r->next) {

    if (value > r->key && counter == 1) {
      L = SLAddToFront(L, value);
      break;
    } else if (r->next == NULL) {
      L = SLAddToBack(L, value);
      break;
    } else if (r->next != NULL) {
      if (value <= r->key && value >= r->next->key) {
        L = SLInsert(L, value, counter);
        break;
      }
    }

    counter++;
  }

  SLnodePtr p;

  for (p = Lnext->bottom; p != NULL; p = p->next) {
    int value = p->key;
    int counter2 = 1;
    SLnodePtr q;

    for (q = L; q != NULL; q = q->next) {
      if (value > q->key && counter2 == 1) {
        L = SLAddToFront(L, value);
        break;
      } else if (q->next == NULL) {
        L = SLAddToBack(L, value);
        break;
      } else if (q->next != NULL) {
        if (value <= q->key && value >= q->next->key) {
          L = SLInsert(L, value, counter2);
          break;
        }
      }

      counter2++;
    }
  }

  return L;
}

// Adds a node to the front of a SL list
static SLnodePtr SLAddToFront(SLnodePtr L, int value) {

  SLnodePtr newNode;
  newNode = malloc(sizeof(struct SLnode));
  if (newNode == NULL) {
    printf("Error: malloc failed in SLAddToFront");
    exit(EXIT_FAILURE);
  }
  newNode->key = value;
  newNode->next = L;
  return newNode;
}

// Clears an array and fills it with all 0's
static void clearArray(int *a, int m) {
  for (int i = 0; i < m; i++) {
    *(a + i) = 0;
  }
}

// Adds ta node to the front of a SL list
static HBnodePtr HBAddToFront(HBnodePtr L, int value) {

  HBnodePtr newNode;
  newNode = malloc(sizeof(struct HBnode));
  if (newNode == NULL) {
    printf("Error: malloc failed in HBAddToFront");
    exit(EXIT_FAILURE);
  }
  newNode->key = value;
  newNode->next = L;
  newNode->bottom = NULL;
  return newNode;
}

// Adds a node to the back of a SL list
static SLnodePtr SLAddToBack(SLnodePtr L, int value) {

  SLnodePtr newNode, p;
  newNode = malloc(sizeof(struct SLnode));
  if (newNode == NULL) {
    printf("Error: malloc failed in SLAddToBack");
    exit(EXIT_FAILURE);
  }

  newNode->key = value;
  newNode->next = NULL;

  for (p = L; p != NULL; p = p->next) {
    if (p->next == NULL) {
      p->next = newNode;
      break;
    }
  }
  return L;
}

// Function which inserts a nodee into a SL list a counter number of nodes
// starting from the first one
static SLnodePtr SLInsert(SLnodePtr L, int value, int counter) {

  SLnodePtr newNode, p;
  newNode = malloc(sizeof(struct SLnode));
  if (newNode == NULL) {
    printf("Error: malloc failed in SLAddToBack");
    exit(EXIT_FAILURE);
  }
  int i = 1;
  for (p = L; i <= counter; p = p->next) {
    if (i == counter) {
      SLnodePtr temp = p->next;
      p->next = newNode;
      newNode->key = value;
      newNode->next = temp;
    }
    i++;
  }

  return L;
}

// Function to reverse a SL list
static SLnodePtr SLReverse(SLnodePtr L) {

  if (!L) {
    return NULL;
  }

  SLnodePtr head = L;
  SLnodePtr tail = head->next;

  if (!tail) {
    return head;
  }

  SLnodePtr rev = SLReverse(tail);
  SLnodePtr last = rev;

  while (last->next) {
    last = last->next;
  }
  last->next = head;
  head->next = NULL;

  return rev;
}
