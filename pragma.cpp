#include <fstream>
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>


#include <omp.h>

int main(){
	#pragma omp parallel for
	for(int n = 0; n < 10; ++n)
	{
		printf(" %d", n);
	}
	printf("\n");
	return 0;
}
