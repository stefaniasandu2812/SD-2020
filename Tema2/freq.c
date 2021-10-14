// Copyright 2020 <Sandu Stefania-Cristina>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

int main(){
	unsigned int n, *freq_array, MAX, i;
	MAX = 0;
	while (scanf("%d", &n) == 1){
		if (n > MAX){
			MAX = n;
		}
	}
	freq_array = calloc(MAX+1, sizeof(unsigned int));  // aloc memorie
	if (freq_array == NULL) {  // verific daca s-a alocat memoria
        perror("Not enough memory!");
        return -1;
    }
	fseek(stdin, 0, SEEK_SET);
	while (scanf("%d", &n) == 1){
		for (i = 0; i < MAX+1; i++){
			if (i == n){
				freq_array[i]++;
			}
		}
	}
	for (i = 0; i < MAX+1; i++){
		if (freq_array[i] != 0){
			printf("%d %d\n", i, freq_array[i]);
		}
	}
	free(freq_array);
	return 0;
}
