#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
	int uvijet = 1;
	printf("***SKLADISTE NBA DRESOVA***\n\n");

	while (uvijet != 99)
		uvijet = izbornik();

	return 0;
}