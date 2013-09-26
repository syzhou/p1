#include "Ordered_container.h"

#include <stdlib.h>
/* A complete type declaration for Ordered_container implemented as an array */
struct Ordered_container {
	OC_comp_fp_t comp_fun;	/* pointer to comparison function  */
	void** array;			/* pointer to array of pointers to void */
	int allocation;			/* current size of array */
	int size;				/* number of items currently in the array */
};

struct Ordered_container* OC_create_container(OC_comp_fp_t comp_func) {return NULL;}

/* Destroy the container and its items; caller is responsible for
deleting all pointed-to data before calling this function.
After this call, the container pointer value must not be used again. */
void OC_destroy_container(struct Ordered_container* c_ptr) {}

/* Delete all the items in the container and initialize it.
Caller is responsible for deleting any pointed-to data first. */
void OC_clear(struct Ordered_container* c_ptr){}

/* Return the number of items currently stored in the container */
int OC_get_size(const struct Ordered_container* c_ptr){return 0;}

/* Return non-zero (true) if the container is empty, zero (false) if the container is non-empty */
int OC_empty(const struct Ordered_container* c_ptr){return 0;}

/*
Functions for working with individual items in the container.
*/

/* Get the data object pointer from an item. */
void* OC_get_data_ptr(const void* item_ptr){return NULL;}

/* Delete the specified item.
Caller is responsible for any deletion of the data pointed to by the item. */
void OC_delete_item(struct Ordered_container* c_ptr, void* item_ptr){}

/*
Functions that search and insert into the container using the supplied comparison function.
*/

/* Create a new item for the specified data pointer and put it in the container in order.
If there is already an item in the container that compares equal to new item according to
the comparison function, the order of the new item relative to the existing item is not specified. */
void OC_insert(struct Ordered_container* c_ptr, void* data_ptr){}

/* Return a pointer to an item that points to data equal to the data object pointed to by data_ptr,
using the ordering function to do the comparison with data_ptr as the first argument.
The data_ptr object is assumed to be of the same type as the data objects pointed to by container items.
NULL is returned if no matching item is found. If more than one matching item is present, it is
unspecified which one is returned. */
void* OC_find_item(const struct Ordered_container* c_ptr, const void* data_ptr){return NULL;}


/* Return a pointer to the item that points to data that matches the supplied argument given by arg_ptr
according to the supplied function, which compares arg_ptr as the first argument with the data pointer
in each item. This function does not require that arg_ptr be of the same type as the data objects, and
so allows the container to be searched without creating a complete data object first.
NULL is returned if no matching item is found. If more than one matching item is present, it is
unspecified which one is returned. The comparison function must implement an ordering consistent
with the ordering produced by the comparison function specified when the container was created;
if not, the result is undefined. */
void* OC_find_item_arg(const struct Ordered_container* c_ptr, const void* arg_ptr, OC_find_item_arg_fp_t fafp){return NULL;}

/* Functions that traverse the items in the container, processing each item in order. */


/* Apply the supplied function to the data pointer in each item of the container.
The contents of the container cannot be modified. */
void OC_apply(const struct Ordered_container* c_ptr, OC_apply_fp_t afp){}

/* Apply the supplied function to the data pointer in each item in the container.
If the function returns non-zero, the iteration is terminated, and that value
returned. Otherwise, zero is returned. The contents of the container cannot be modified. */
int OC_apply_if(const struct Ordered_container* c_ptr, OC_apply_if_fp_t afp){return 0;}

/* Apply the supplied function to the data pointer in each item in the container;
the function takes a second argument, which is the supplied void pointer.
The contents of the container cannot be modified. */
void OC_apply_arg(const struct Ordered_container* c_ptr, OC_apply_arg_fp_t afp, void* arg_ptr){}

/* Apply the supplied function to the data pointer in each item in the container;
the function takes a second argument, which is the supplied void pointer.
If the function returns non-zero, the iteration is terminated, and that value
returned. Otherwise, zero is returned. The contents of the container cannot be modified */
int OC_apply_if_arg(const struct Ordered_container* c_ptr, OC_apply_if_arg_fp_t afp, void* arg_ptr){return 0;}
