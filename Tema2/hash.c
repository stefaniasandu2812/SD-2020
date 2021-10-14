// Copyright 2020 <Sandu Stefania-Cristina>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#define NMAX 100

struct info{
	char *key;
	int freq;
};
struct Hashtable{
	struct info *bucket;
	int size;
	unsigned int (*hash_function)(void*);
};
unsigned int hash_function(void *a) {
    /*
     * Credits: http://www.cse.yorku.ca/~oz/hash.html
     */
    unsigned char *puchar_a = (unsigned char*) a;
    uint64_t hash = 5381;
    int c;

    while ((c = *puchar_a++))
        hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

    return hash;
}

void init_ht(struct Hashtable *ht, int nr){
	ht->bucket = malloc(nr*sizeof(struct info));
	if (ht->bucket == NULL) {  // verific daca s-a alocat memorie
        perror("Not enough memory!");
        return;
    }
	ht->size = nr;  // dimensiunea hashtable-ului va fi nr de string-uri
	for (int i = 0; i < ht->size; ++i){
		ht->bucket[i].key ="\0";  // initializez key
		ht->bucket[i].freq = 0;  // initializez frecventa
	}
	ht->hash_function = hash_function;
}
void put(struct Hashtable *ht, char *key, int key_size_bites){
	int index = ht->hash_function(key)%ht->size;
	if (strcmp(ht->bucket[index].key, "\0") == 0){
		ht->bucket[index].key = malloc(key_size_bites);
		memcpy(ht->bucket[index].key, key, key_size_bites);
		ht->bucket[index].freq = 1;
		return;
	}
	if (strcmp(ht->bucket[index].key, "\0") != 0){
		if (strcmp(ht->bucket[index].key, key) == 0){
			ht->bucket[index].freq++;
			return;
		}
	}
	if (strcmp(ht->bucket[index].key, "\0") != 0){
		if (strcmp(ht->bucket[index].key, key) != 0){
			while(strcmp(ht->bucket[index].key, "\0") != 0){
				index = (index+1)%ht->size;  // caut urmatorul bucket liber
			}
			ht->bucket[index].key = malloc(key_size_bites);
			memcpy(ht->bucket[index].key, key, key_size_bites);
			ht->bucket[index].freq = 1;
		}
	}
}
void free_ht(struct Hashtable *ht) {
    for (int i = 0; i < ht->size; ++i){
		if (strcmp(ht->bucket[i].key, "\0") != 0){
			free(ht->bucket[i].key);
		}
	}
    free(ht->bucket);
    free(ht);
}
int main()
{
	char *s = malloc(NMAX*sizeof(char));
	if (s == NULL) {  // verific daca s-a alocat memorie
        perror("Not enough memory!");
        return -1;
    }
	struct Hashtable *ht;
	ht = malloc(sizeof(struct Hashtable));
	if (ht == NULL) {  // verific daca s-a alocat memorie
        perror("Not enough memory!");
        return -1;
    }
	int nr_inputs = 0;
	while (scanf("%s", s) == 1){
		nr_inputs++;
	}
	fseek(stdin, 0, SEEK_SET);
	init_ht(ht, nr_inputs);
	while (scanf("%s", s) == 1){
		put(ht, s, strlen(s)+1);
	}
	for (int i = 0; i < ht->size; ++i){
		if (strcmp(ht->bucket[i].key, "\0") != 0){
			printf("%s ", ht->bucket[i].key);
			printf("%d\n", ht->bucket[i].freq);
		}
	}
	free_ht(ht);
	free(s);
	return 0;
}
