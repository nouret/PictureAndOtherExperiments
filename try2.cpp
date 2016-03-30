#include <fstream>
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <stdlib.h>

using namespace std;

int main(){
	char c;
	while (fread(&c, 1, 1, stdin) > 0){
		printf("%x ", (((int) c) & 255));
	}
	return 0;
}
