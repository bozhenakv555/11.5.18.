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

#define CTWL_OK 1
#define CTWL_FAIL 0

char ctwl_delete(CTWL* list){
	if (list == NULL || list->cur == NULL){
		return CTWL_FAIL;
	}
	TWN *cur = list->cur;
    if (cur == cur->next){
    	free(cur);
    	list->cur = NULL;
    	return CTWL_OK;
	}
	TWN *left = cur->prev;
	TWN *right = cur->next;
	left->next = right;
	right->prev = left;
	list->cur = right;
	free(cur);
	return CTWL_OK;
}

CTWL *ctwl_create_random(unsigned int size){
	if (size == 0){
		return NULL;
	}
	CTWL *list = ctwl_create_empty();
	if (list == NULL){
		return NULL;
    }
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
    	int is_max = 0;
    	float prev_val = temp_cur->prev->data;
        float cur_val = temp_cur->data;
        float next_val = temp_cur->next->data;
        if (cur_val > prev_val && cur_val > next_val){
		is_max = 1;
		}
    	if (temp_cur == list->cur){
    		if(is_max == 1){
    		printf("[*%.1f*] ", temp_cur->data);	
			}else{
    	    printf("[%.1f] ", temp_cur->data);
    	    }
		}else{
			if(is_max == 1){
    		printf("*%.1f* ", temp_cur->data);	
			}else{
    	    printf("%.1f ", temp_cur->data);
    	    }
    }
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

void ctwl_cur_step_right(CTWL *list){
	if (list == NULL || list->cur == NULL){
		return;
	}
	list->cur = list->cur->next;
}

void ctwl_cur_step_left(CTWL *list){
	if (list == NULL || list->cur == NULL){
		return;
	}
	list->cur = list->cur->prev;
}

CTWL *ctwl_create_random_bimodal(unsigned int size){
	if (size < 4){ 
	    return NULL;
	}
    int attempts = 0;
    int max_attempts = 100;
    
    while (attempts < max_attempts){
    	CTWL *list = ctwl_create_random(size);
    	if (list == NULL){
		return NULL;
        }
        TWN *temp_cur = list->cur;
        int max_count = 0;
        do{
        	float prev_val = temp_cur->prev->data;
        	float cur_val = temp_cur->data;
        	float next_val = temp_cur->next->data;
        	if (cur_val > prev_val && cur_val > next_val){
			max_count++;
			}
		    temp_cur = temp_cur->next;
		}while(temp_cur != list->cur);
		if (max_count == 2){
			return list;
		}else{
			ctwl_destroy(list);
			attempts++;
		}
	}
	return NULL;
}

int main(){
	srand(time(NULL));
	unsigned int size = 10;
	
	CTWL *bimodal_list = ctwl_create_random_bimodal(size);
	
	if (bimodal_list == NULL){
		printf("Nepodarilo sa vygenerovat bimodalny zoznam.\n");
		return 1;
	}
	
	printf("Vygenerovany bimodalny zoznam s %u prvkami:\n", size);
	ctwl_print(bimodal_list);
	
    ctwl_destroy(bimodal_list);
	
    return 0;
}

