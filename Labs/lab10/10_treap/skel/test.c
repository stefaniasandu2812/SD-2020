#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
	int an;
	char *profil;
};

struct student* init(struct student *s){
	s = malloc(sizeof(struct student));
	s->profil = malloc(30*sizeof(char));
	return s;
}

int main()
{
	
	// char *s;
	// s = malloc(20*sizeof(char));
	// char *b;
	// b = malloc(20*sizeof(char));
	// memcpy(b, "Ana are mere\0", (strlen("Ana are mere\0") + 1) * sizeof(char));

	// // b = "Ana are mere\0";
	// memcpy(s, b, (strlen(b) + 1) * sizeof(char));
	// printf("%s\n", s);
	// printf("%s\n", b);

	// free(s);
	// free(b);

	struct student *dani, *stefi;

	dani = init(dani);
	stefi = malloc(sizeof(struct student));

	dani->an = 1;
	memcpy(dani->profil, "mate-info", strlen("mate-info\0") * sizeof(char));

	stefi = dani;

	printf("%d\n%s\n", stefi->an, stefi->profil);

	return 0;
}