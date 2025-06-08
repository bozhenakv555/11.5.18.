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

TWN *ctwl_insert_right(CTWL* list, float val){
	if (list == NULL){
		return NULL;
	}
	TWN *new_node = (TWN*)malloc(sizeof(TWN));
	if (new_node == NULL){
		return NULL;
	}
	new_node->data = val;
	if(list->cur == NULL){
		list->cur = new_node;
		new_node->next = new_node;
		new_node->prev = new_node;
		return new_node;
	}
	TWN *cur = list->cur;
	TWN *right = cur->next;
	
	new_node->prev = cur;
    new_node->next = right;
    cur->next = new_node;
    right->prev = new_node;
	
	return new_node;
}

TWN *ctwl_insert_left(CTWL* list, float val){
	if (list == NULL){
		return NULL;
	}
	TWN *new_node = (TWN*)malloc(sizeof(TWN));
	if (new_node == NULL){
		return NULL;
	}
	new_node->data = val;
	if(list->cur == NULL){
		list->cur = new_node;
		new_node->next = new_node;
		new_node->prev = new_node;
		return new_node;
	}
	TWN *cur = list->cur;
	TWN *left = cur->prev;
	
	new_node->prev = left;
    new_node->next = cur;
    left->next = new_node;
    cur->prev = new_node;
	
	return new_node;
}


CTWL *ctwl_create_random(unsigned int size){
	CTWL *list = ctwl_create_empty();
	for (unsigned int i = 0; i < size; i++){
		float val = (float)(rand()%100);
		ctwl_insert_right(list, val);
    }
    return list;    
}

void ctwl_print(CTWL *list){
    if (list == NULL || list->cur == NULL){
        printf("Zoznam je prazdny\n");
        return;
    }	
    TWN *temp_cur = list->cur;
    do{
    	printf("%.1f ", temp_cur->data);
    	temp_cur = temp_cur->next;
	}while (temp_cur != list->cur);
}

void ctwl_destroy(CTWL* list){
	if (list == NULL || list->cur == NULL){
		return;
	}
	TWN *cur = list->cur;
	TWN *temp_cur = cur->next;
	
	while (temp_cur != cur){
	    TWN *to_free = temp_cur;
		temp_cur = temp_cur->next;	
		free(to_free);
	}
	
	free(cur);
	free(list);
}

