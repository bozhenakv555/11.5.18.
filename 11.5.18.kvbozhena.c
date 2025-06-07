#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct TWN{
float data;
struct TWN *prev;
struct TWN *next;
}TWN;

typedef struct{
TWN *cur;
}CTWL;

CTWL *ctwl_create_empty(void){
	CTWL *new_list = (CTWL*)malloc(sizeof(CTWL));
	if (new_list == NULL){
		printf("Nepodarilo sa alokovat pamat pre novy zoznam\n");
		return NULL;
	}
	new_list->cur = NULL;
	return new_list;
}