#include "Ordered_container.h"

#include <stdio.h>
#include <stdlib.h>

#define PRINT(i) printf("%d\n", i)
struct Ordered_container* numbers;
int compare(int *a, int* b);
int find(int a);
int findArg(int a);
void addOneAll(int* a);
void addSomeAll(int* a, int* b);
void printAll(int* a);
int stopAt5(int* a);
int stopAtSome(int* a, int* b);

int compare(int *a, int* b) {
	return (*a - *b);
}
int find(int a) {
	printf("finding %d    ", a);
	void* itemPtr = OC_find_item(numbers, &a);
	if (itemPtr) {
		printf("found %d\n", *((int*)(OC_get_data_ptr(itemPtr))));
	} else {
		printf("not found\n");
	}
	return 0;
}
int findArg(int a) {
	void* itemPtr = OC_find_item_arg(numbers, &a, (OC_find_item_arg_fp_t)compare);
	if (itemPtr) {
		return *((int*)(OC_get_data_ptr(itemPtr)));
	} else {
		return 0;
	}
}
void addOneAll(int* a) {
	*a = *a + 1;
}
void addSomeAll(int* a, int* b) {
	*a = *a + *b;
}
void printAll(int* a) {
	printf("printing ALL  ");
	PRINT(*a);
}
int stopAt5(int* a) {
	if (*a == 5) {
		printf("find 5");
		PRINT(5);
		return 5;
	}
	return 0;
}
int stopAtSome(int* a, int* b) {
	if (*a == *b) {
		printf("find %d", *b);
		return *b;
	}
	return 0;
}

int main() {
	numbers = OC_create_container((OC_comp_fp_t)compare);
	int one = 1;
	int minus1  = -1;
	int a1= 1;
	int a2 = 2;
	int a3 = 3;
	int a4 = 4;
	int a5 = 5;
	int a6 = 6;
	int a7 = 7;
	int a8 = 8;
	OC_clear(numbers);
	PRINT(OC_get_size(numbers));
	PRINT(OC_empty(numbers));
	PRINT(find(1));
	OC_apply(numbers, (OC_apply_fp_t)addOneAll);
	OC_apply_arg(numbers, (OC_apply_arg_fp_t)addSomeAll, &minus1);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	PRINT(OC_apply_if(numbers, (OC_apply_if_fp_t)stopAt5));
	PRINT(OC_apply_if_arg(numbers, (OC_apply_if_arg_fp_t)stopAtSome, &a5));
	OC_apply(numbers, (OC_apply_fp_t)printAll);

	printf("\n\ninsert one\n");

	OC_insert(numbers, &a1);
	printf("size = ");
	PRINT(OC_get_size(numbers));
	printf("empty? ");
	PRINT(OC_empty(numbers));
	printf("finding 1  ");
	PRINT(find(1));
	printf("add one to ALL\n");
	OC_apply(numbers, (OC_apply_fp_t)addOneAll);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("minus one to all\n");
	OC_apply_arg(numbers, (OC_apply_arg_fp_t)addSomeAll, &minus1);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("stop 5  ");
	PRINT(OC_apply_if(numbers, (OC_apply_if_fp_t)stopAt5));
	printf("stop 5   ");
	PRINT(OC_apply_if_arg(numbers, (OC_apply_if_arg_fp_t)stopAtSome, &a5));
	OC_apply(numbers, (OC_apply_fp_t)printAll);

	printf("\n\ninsert one\n");

	OC_insert(numbers, &a1);
	printf("size = ");
	PRINT(OC_get_size(numbers));
	printf("empty? ");
	PRINT(OC_empty(numbers));
	printf("finding 1  ");
	PRINT(find(1));
	printf("add one to ALL\n");
	OC_apply(numbers, (OC_apply_fp_t)addOneAll);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("minus one to all\n");
	OC_apply_arg(numbers, (OC_apply_arg_fp_t)addSomeAll, &minus1);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("stop 5  ");
	PRINT(OC_apply_if(numbers, (OC_apply_if_fp_t)stopAt5));
	printf("stop 5   ");
	PRINT(OC_apply_if_arg(numbers, (OC_apply_if_arg_fp_t)stopAtSome, &a5));
	OC_apply(numbers, (OC_apply_fp_t)printAll);

	printf("\n\ninsert one\n");

	OC_insert(numbers, &a1);
	printf("size = ");
	PRINT(OC_get_size(numbers));
	printf("empty? ");
	PRINT(OC_empty(numbers));
	printf("finding 1  ");
	PRINT(find(1));
	printf("add one to ALL\n");
	OC_apply(numbers, (OC_apply_fp_t)addOneAll);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("minus one to all\n");
	OC_apply_arg(numbers, (OC_apply_arg_fp_t)addSomeAll, &minus1);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("stop 5  ");
	PRINT(OC_apply_if(numbers, (OC_apply_if_fp_t)stopAt5));
	printf("stop 5   ");
	PRINT(OC_apply_if_arg(numbers, (OC_apply_if_arg_fp_t)stopAtSome, &a5));
	OC_apply(numbers, (OC_apply_fp_t)printAll);


	OC_clear(numbers);
	printf("\n\nclear\n");
	printf("size = ");
	PRINT(OC_get_size(numbers));
	printf("empty? ");
	PRINT(OC_empty(numbers));
	printf("finding 1  ");
	PRINT(find(1));
	printf("add one to ALL\n");
	OC_apply(numbers, (OC_apply_fp_t)addOneAll);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("minus one to all\n");
	OC_apply_arg(numbers, (OC_apply_arg_fp_t)addSomeAll, &minus1);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("stop 5  ");
	PRINT(OC_apply_if(numbers, (OC_apply_if_fp_t)stopAt5));
	printf("stop 5   ");
	PRINT(OC_apply_if_arg(numbers, (OC_apply_if_arg_fp_t)stopAtSome, &a5));
	OC_apply(numbers, (OC_apply_fp_t)printAll);


	printf("\n\ninsert four\n");

	OC_insert(numbers, &a4);
	printf("size = ");
	PRINT(OC_get_size(numbers));
	printf("empty? ");
	PRINT(OC_empty(numbers));
	printf("finding 1  ");
	PRINT(find(1));
	printf("add one to ALL\n");
	OC_apply(numbers, (OC_apply_fp_t)addOneAll);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("minus one to all\n");
	OC_apply_arg(numbers, (OC_apply_arg_fp_t)addSomeAll, &minus1);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("stop 5  ");
	PRINT(OC_apply_if(numbers, (OC_apply_if_fp_t)stopAt5));
	printf("stop 5   ");
	PRINT(OC_apply_if_arg(numbers, (OC_apply_if_arg_fp_t)stopAtSome, &a5));
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("\n\ninsert five\n");

	OC_insert(numbers, &a5);
	printf("size = ");
	PRINT(OC_get_size(numbers));
	printf("empty? ");
	PRINT(OC_empty(numbers));
	printf("finding 1  ");
	PRINT(find(1));
	printf("add one to ALL\n");
	OC_apply(numbers, (OC_apply_fp_t)addOneAll);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("minus one to all\n");
	OC_apply_arg(numbers, (OC_apply_arg_fp_t)addSomeAll, &minus1);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("stop 5  ");
	PRINT(OC_apply_if(numbers, (OC_apply_if_fp_t)stopAt5));
	printf("stop 5   ");
	PRINT(OC_apply_if_arg(numbers, (OC_apply_if_arg_fp_t)stopAtSome, &a5));
	OC_apply(numbers, (OC_apply_fp_t)printAll);


	printf("\n\n\ndelete 5\n");
	OC_delete_item(numbers, OC_find_item(numbers, &a5));
	PRINT(OC_get_size(numbers));
	printf("empty? ");
	PRINT(OC_empty(numbers));
	printf("finding 1  ");
	PRINT(find(1));
	printf("add one to ALL\n");
	OC_apply(numbers, (OC_apply_fp_t)addOneAll);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("minus one to all\n");
	OC_apply_arg(numbers, (OC_apply_arg_fp_t)addSomeAll, &minus1);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("stop 5  ");
	PRINT(OC_apply_if(numbers, (OC_apply_if_fp_t)stopAt5));
	printf("stop 5   ");
	PRINT(OC_apply_if_arg(numbers, (OC_apply_if_arg_fp_t)stopAtSome, &a5));
	OC_apply(numbers, (OC_apply_fp_t)printAll);


	OC_insert(numbers, &a3);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	OC_delete_item(numbers, OC_find_item(numbers, &a3));
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	OC_insert(numbers, &a3);
	OC_insert(numbers, &a6);
	OC_insert(numbers, &a2);
	OC_insert(numbers, &a5);
	find(5);
	find(3);
	find(6);
	find(2);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("\n\n");
	OC_delete_item(numbers, OC_find_item(numbers, &a2));
	OC_delete_item(numbers, OC_find_item(numbers, &a6));
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	printf("\n\n");
	OC_clear(numbers);
	OC_apply(numbers, (OC_apply_fp_t)printAll);
	OC_destroy_container(numbers);












	return 0;


}
