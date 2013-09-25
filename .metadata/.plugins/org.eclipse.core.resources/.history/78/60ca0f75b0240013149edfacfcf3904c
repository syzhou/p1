#include "Ordered_container_list.c"
#include "p1_globals.h"

#include <stdlib.h>


/* struct LL_Node structure declaration. This declaration is local to this file. 
This is a two-way or doubly-linked list. Each node has a pointer to the previous 
node and another pointer to the next node in the list. This means insertions or
removals of a node can be made in constant time, once the location has been
determined. */
struct LL_Node { 
    struct LL_Node* prev;      /* pointer to the previous node */
	struct LL_Node* next;		/* pointer to the next node */
	void* data_ptr; 			/* uncommitted pointer to the data item */
};

/* Declaration for Ordered_container. This declaration is local to this file.  
A pointer is maintained to the last node in the list as well as the first, meaning that additions to the end of the list can be made in constant time. 
The number of nodes in the list is kept up-to-date in the size member
variable, so that the size of the list can be accessed in constant time. */
struct Ordered_container {
	OC_comp_fp_t comp_func;
	struct LL_Node* first;
	struct LL_Node* last;
	int size;
};
/* Create an empty container using the supplied comparison function, and return the pointer to it. */
struct Ordered_container* OC_create_container(OC_comp_fp_t comp_func) {
	struct Ordered_container* newContainer = malloc(sizeof(Ordered_container));
	newContainer -> comp_func = comp_func;
	newContainer -> first = NULL;
	newContainer -> last = NULL;
	newContainer -> size = 0;
	g_Container_items_allocated++;
	return newContainer;
}

/* Destroy the container and its items; caller is responsible for 
deleting all pointed-to data before calling this function. 
After this call, the container pointer value must not be used again. */
void OC_destroy_container(struct Ordered_container* c_ptr) {
	OCDeleteAllItems(c_ptr);
	free(c_ptr);
}

/* Delete all the items in the container and initialize it. 
Caller is responsible for deleting any pointed-to data first. */
void OC_clear(struct Ordered_container* c_ptr);

/* Return the number of items currently stored in the container */
int OC_get_size(const struct Ordered_container* c_ptr);

/* Return non-zero (true) if the container is empty, zero (false) if the container is non-empty */
int OC_empty(const struct Ordered_container* c_ptr);

/*
Functions for working with individual items in the container.
*/

/* Get the data object pointer from an item. */
void* OC_get_data_ptr(const void* item_ptr);

/* Delete the specified item.
Caller is responsible for any deletion of the data pointed to by the item. */
void OC_delete_item(struct Ordered_container* c_ptr, void* item_ptr);

/*
Functions that search and insert into the container using the supplied comparison function.
*/

/* Create a new item for the specified data pointer and put it in the container in order.
If there is already an item in the container that compares equal to new item according to
the comparison function, the order of the new item relative to the existing item is not specified. */
void OC_insert(struct Ordered_container* c_ptr, void* data_ptr);

/* Return a pointer to an item that points to data equal to the data object pointed to by data_ptr,
using the ordering function to do the comparison with data_ptr as the first argument.
The data_ptr object is assumed to be of the same type as the data objects pointed to by container items.
NULL is returned if no matching item is found. If more than one matching item is present, it is 
unspecified which one is returned. */
void* OC_find_item(const struct Ordered_container* c_ptr, const void* data_ptr);

/* typedef for a function used by OC_find_item_arg. The function returns negative, 0, or positive, 
if the data pointed to by arg_ptr corresponds to a data object that should come before, is equal to, or comes after, 
the data object pointed to by data_ptr. For example, arg_ptr could point to a datum with the same value
as a member of the sought-for data object. */
typedef int (*OC_find_item_arg_fp_t) (const void* arg_ptr, const void* data_ptr);

/* Return a pointer to the item that points to data that matches the supplied argument given by arg_ptr
according to the supplied function, which compares arg_ptr as the first argument with the data pointer
in each item. This function does not require that arg_ptr be of the same type as the data objects, and
so allows the container to be searched without creating a complete data object first.
NULL is returned if no matching item is found. If more than one matching item is present, it is 
unspecified which one is returned. The comparison function must implement an ordering consistent 
with the ordering produced by the comparison function specified when the container was created; 
if not, the result is undefined. */
void* OC_find_item_arg(const struct Ordered_container* c_ptr, const void* arg_ptr, OC_find_item_arg_fp_t fafp);

/* Functions that traverse the items in the container, processing each item in order. */

/* Type of a function used by OC_apply.
An apply function takes a data pointer as an argument, and returns void. It is allowed to modify the data item,
but if the ordering information is changed, attempts to search the container afterwards with OC_find are undefined. */
typedef void (*OC_apply_fp_t) (void* data_ptr);

/* Apply the supplied function to the data pointer in each item of the container. 
The contents of the container cannot be modified. */
void OC_apply(const struct Ordered_container* c_ptr, OC_apply_fp_t afp);

/* Type of a function used by OC_apply_if.
An apply_if function takes a data pointer as an argument, and returns zero or non-zero. 
It is allowed to modify the data item, but if the ordering information is changed,
attempts to search the container afterwards with OC_find are undefined. */
typedef int (*OC_apply_if_fp_t) (void* data_ptr);

/* Apply the supplied function to the data pointer in each item in the container. 
If the function returns non-zero, the iteration is terminated, and that value
returned. Otherwise, zero is returned. The contents of the container cannot be modified. */
int OC_apply_if(const struct Ordered_container* c_ptr, OC_apply_if_fp_t afp);

/* Type of a function used by OC_apply_arg.
An OC_apply_arg function takes a data pointer as the first argument, 
a supplied argument pointer as a second argument, and returns void. */
typedef void (*OC_apply_arg_fp_t) (void* data_ptr, void* arg_ptr);

/* Apply the supplied function to the data pointer in each item in the container;
the function takes a second argument, which is the supplied void pointer. 
The contents of the container cannot be modified. */
void OC_apply_arg(const struct Ordered_container* c_ptr, OC_apply_arg_fp_t afp, void* arg_ptr);

/* Type of a function used by OC_apply_if_arg.
An OC_apply_arg function takes a data pointer as an argument, 
a supplied argument pointer as a second argument, and returns an zero or non-zero. */
typedef int (*OC_apply_if_arg_fp_t) (void* data_ptr, void* arg_ptr);

/* Apply the supplied function to the data pointer in each item in the container;
the function takes a second argument, which is the supplied void pointer. 
If the function returns non-zero, the iteration is terminated, and that value
returned. Otherwise, zero is returned. The contents of the container cannot be modified */
int OC_apply_if_arg(const struct Ordered_container* c_ptr, OC_apply_if_arg_fp_t afp, void* arg_ptr);

/* Delete all the items in the container, but does not delete the container itself;
 * the function takes a pointer to the container as the parameter. */
void OCDeleteAllItems(struct Ordered_container* cPtr) {
	int i = 0, size = cPtr -> size;
	LL_Node* ptrToDelete = cPtr -> first;
	for (; i < size; i++) {
		LL_Node* nextPtr = ptrToDelete -> next;
		free(ptrToDelete);
		ptrToDelete = nextPtr;
	}
	cPtr -> size = 0;
	cPtr -> first = NULL;
	cPtr -> last = NULL;
}

