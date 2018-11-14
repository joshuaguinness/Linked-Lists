// Joshua Guinness, November 10-13, 2018

#include <stdio.h>
#include "assignment3.h"

int main() {

	int n = 5, m = 5;
	HBnodePtr L = createHBlist(n, m);
	printf("HB list:\n");
	printHBlist(L);
	printf("\n");

	printf("SL list\n");
	SLnodePtr P = flattenList(L);
	printSLlist(P);
	printf("\n");

	freeSLlist(P);
	freeHBlist(L);
	return 0;
}