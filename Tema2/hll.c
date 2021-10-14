// Copyright 2020 <Sandu Stefania-Cristina>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INT_SIZE 32

unsigned int hash_function_int(void *a) {
    /*
     * Credits: https://stackoverflow.com/a/12996028/7883884
     */
    unsigned int uint_a = *((unsigned int *)a);

    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
    uint_a = (uint_a >> 16u) ^ uint_a;
    return uint_a;
}
int count_zeros(int number){
	int cnt = 0;
	int aux = number << 11;
	if (number == 0){
		cnt = INT_SIZE;
	} else{
	while (!(aux & (1 << (INT_SIZE - 1)))){
        cnt++;
        aux <<= 1;
    }
    }
    return cnt;
}
int max_function(int a, int b){
	if (a > b){
		return a;
	} else{
		return b;
	}
}
int main(int argc, char *argv[]){
	if (argc > 2){
		printf("Error input\n");
		return -1;
	}
	FILE *fin = fopen(argv[1], "rt");
	if (fin == NULL){
		printf("Error opening file\n");
		return -1;
	}
	int n;
	int m = 1 << 11;  // m = 2^11
	int j;
	int *M = calloc(m+1, sizeof(int));
	if (M == NULL) {
        perror("Not enough memory!");
        return -1;
    }
	while (fscanf(fin, "%d", &n) == 1){
		j = ((hash_function_int(&n)) >> (INT_SIZE - 11));
		int x = count_zeros(hash_function_int(&n)) + 1;
		M[j] = max_function(M[j], x);
	}
	float s = 0;
	for (j = 1; j < m+1; ++j){
		float p = 1 << M[j];
    	s += (float)(1/p);
    }
	float Z = (float)(1/s);
	float alpha = (float)(0.7213/(1+(float)(1.079/m)));
	int E = alpha*m*m*Z;
	printf("%d\n", E);
	free(M);
	fclose(fin);
	return 0;
}
