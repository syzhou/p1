#include "Ordered_container.h"
#include "p1_globals.h"
#include "Utility.h"


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



void OCInit(struct Ordered_container * cPtr);
void OCDeleteAllItems(struct Ordered_container* cPtr);
struct LL_Node* OCFindItemLesserThan(const struct Ordered_container* cPtr, const void* dataPtr);

/* Create an empty container using the supplied comparison function, and return the pointer to it. */
struct Ordered_container* OC_create_container(OC_comp_fp_t comp_func) {
	struct Ordered_container* newContainer;
	if (!(newContainer = malloc(sizeof(struct Ordered_container)))) {
		printErrBadMallocExit();
	}
	newContainer->comp_func = comp_func;
	OCInit(newContainer);
	g_Container_count++;
	return newContainer;
}

/* Initialize an ordered container.
 * takes a pointer to the container as parameter.
 */
void OCInit(struct Ordered_container * cPtr) {
	cPtr -> size = 0;
	cPtr -> first = NULL;
	cPtr -> last = NULL;
}

/* Destroy the container and its items; caller is responsible for 
deleting all pointed-to data before calling this function. 
After this call, the container pointer value must not be used again. */
void OC_destroy_container(struct Ordered_container* c_ptr) {
	OCDeleteAllItems(c_ptr);
	free(c_ptr);
	g_Container_count--;
}

/* Delete all the items in the container, but does not delete the container itself;
 * the function takes a pointer to the container as the parameter.
 */
void OCDeleteAllItems(struct Ordered_container* cPtr) {
	int i = 0, size = cPtr->size;
	struct LL_Node* ptrToDelete = cPtr->first;
	for (; i < size; i++) {
		struct LL_Node* nextPtr = ptrToDelete->next;
		free(ptrToDelete);
		ptrToDelete = nextPtr;
		g_Container_items_allocated--;
		g_Container_items_in_use--;
	}
}

/* Delete all the items in the container and initialize it. 
Caller is responsible for deleting any pointed-to data first. */
void OC_clear(struct Ordered_container* c_ptr) {
	OCDeleteAllItems(c_ptr);
	OCInit(c_ptr);
}

/* Return the number of items currently stored in the container */
int OC_get_size(const struct Ordered_container* c_ptr) {
	return c_ptr->size;
}

/* Return non-zero (true) if the container is empty, zero (false) if the container is non-empty */
int OC_empty(const struct Ordered_container* c_ptr) {
	return (c_ptr->size == 0);
}

/*
Functions for working with individual items in the container.
*/

/* Get the data object pointer from an item. */
void* OC_get_data_ptr(const void* item_ptr) {
	if (item_ptr) {
		return ((struct LL_Node*)item_ptr)->data_ptr;
	} else {
		return NULL;
	}
}

/* Delete the specified item.
Caller is responsible for any deletion of the data pointed to by the item. */
void OC_delete_item(struct Ordered_container* c_ptr, void* item_ptr) {
	struct LL_Node* item = (struct LL_Node*)item_ptr;
	/* If the item isn't the last one, assign the next one's prev to the prev.
	 * Otherwise, if the item is the last one, we need to change last pointer
	 * in Container to be the one before the deleted one.
	 */
	if (item->next) {
		item->next->prev = item->prev;
	} else {
		c_ptr->last = item->prev;
	}
	if (item->prev) {
		item->prev->next = item->next;
	} else {
		c_ptr->first = item->next;
	}
	free(item);
	c_ptr->size--;
	g_Container_items_allocated--;
	g_Container_items_in_use--;
}

/*
Functions that search and insert into the container using the supplied comparison function.
*/

/* Create a new item for the specified data pointer and put it in the container in order.
If there is already an item in the container that compares equal to new item according to
the comparison function, the order of the new item relative to the existing item is not specified. */
void OC_insert(struct Ordered_container* c_ptr, void* data_ptr) {
	struct LL_Node* newNode;
	struct LL_Node* prevNode;
	if (!(newNode = malloc(sizeof(struct LL_Node)))) {
		printErrBadMallocExit();
	}
	prevNode = OCFindItemLesserThan(c_ptr, data_ptr);
	newNode->data_ptr = data_ptr;
	newNode->prev = prevNode;
	/* If list was empty, assign the first and last pointer to the inserted one
	 * Otherwise, if there are items before the inserted one, assign its next pointer.
	 * Or, if there aren't any items before the inserted one, meaning there must be
	 * items after the inserted one, deal with the first pointer and the new item.
	 */
	if (OC_empty(c_ptr)) {
		newNode->next = NULL;
		c_ptr->first = newNode;
		c_ptr->last = newNode;
	} else if (prevNode){
		newNode->next = prevNode->next;
		if (prevNode->next) {
			prevNode->next->prev = newNode;
		} else {
			c_ptr->last = newNode;
		}
		prevNode->next = newNode;
	} else {
		struct LL_Node* originalFirstNode = c_ptr->first;
		originalFirstNode->prev = newNode;
		newNode->next = originalFirstNode;
		c_ptr->first = newNode;
	}
	c_ptr->size++;
	g_Container_items_allocated++;
	g_Container_items_in_use++;
}

/* Find the item that compares equal to the given item;
 * takes the item pointer and the ordered container pointer as parameters;
 * returns the pointer to the item that is lesser or equal to the pointer,
 * returns NULL if the size is zero or if all the items in the container
 * lesser than the given item
 */
struct LL_Node* OCFindItemLesserThan(const struct Ordered_container* cPtr, const void* dataPtr) {
	struct LL_Node* itemPtrItr;
	if (OC_empty(cPtr)) {
		return NULL;
	}
	itemPtrItr = cPtr->first;
	/* From the first item, compare every data in the list with the sought-for.*/
	while(itemPtrItr) {
		if (cPtr->comp_func(dataPtr, OC_get_data_ptr(itemPtrItr)) >= 0) {
			itemPtrItr = itemPtrItr->next;
		} else {
			/* Stop if the data in the list is already larger than the
			 * sought-for item.
			 */
			break;
		}
	}
	if (itemPtrItr) {
		return itemPtrItr->prev;
	} else {
		return cPtr->last;
	}
}

/* Return a pointer to an item that points to data equal to the data object pointed to by data_ptr,
using the ordering function to do the comparison with data_ptr as the first argument.
The data_ptr object is assumed to be of the same type as the data objects pointed to by container items.
NULL is returned if no matching item is found. If more than one matching item is present, it is
unspecified which one is returned. */
void* OC_find_item(const struct Ordered_container* c_ptr, const void* data_ptr) {
	struct LL_Node* foundItemPtr = OCFindItemLesserThan(c_ptr, data_ptr);
	if (foundItemPtr && !c_ptr->comp_func(OC_get_data_ptr(foundItemPtr), data_ptr)) {
		return foundItemPtr;
	} else {
		return NULL;
	}
}

/* Return a pointer to the item that points to data that matches the supplied argument given by arg_ptr
according to the supplied function, which compares arg_ptr as the first argument with the data pointer
in each item. This function does not require that arg_ptr be of the same type as the data objects, and
so allows the container to be searched without creating a complete data object first.
NULL is returned if no matching item is found. If more than one matching item is present, it is 
unspecified which one is returned. The comparison function must implement an ordering consistent 
with the ordering produced by the comparison function specified when the container was created; 
if not, the result is undefined. */
void* OC_find_item_arg(const struct Ordered_container* c_ptr, const void* arg_ptr, OC_find_item_arg_fp_t fafp) {
	struct LL_Node* itemPtrItr;
	if (OC_empty(c_ptr)) {
		return NULL;
	}
	itemPtrItr = c_ptr->first;
	/* From the first item, compare every data in the list with the sought-for.
	 * If compares equal return. If the data in the list is larger than sought-for
	 * item, break and return NULL;
	 */
	while(itemPtrItr) {
		if (fafp(arg_ptr, OC_get_data_ptr(itemPtrItr)) == 0) {
			return itemPtrItr;
		} else if (fafp(arg_ptr, OC_get_data_ptr(itemPtrItr)) < 0) {
			break;
		}
		itemPtrItr = itemPtrItr->next;
	}
	return NULL;

}

/* Functions that traverse the items in the container, processing each item in order. */

/* Apply the supplied function to the data pointer in each item of the container. 
The contents of the container cannot be modified. */
void OC_apply(const struct Ordered_container* c_ptr, OC_apply_fp_t afp) {
	struct LL_Node* itemPtrItr = c_ptr->first;
	while(itemPtrItr) {
		afp(OC_get_data_ptr(itemPtrItr));
		itemPtrItr = itemPtrItr->next;
	}
}

/* Apply the supplied function to the data pointer in each item in the container. 
If the function returns non-zero, the iteration is terminated, and that value
returned. Otherwise, zero is returned. The contents of the container cannot be modified. */
int OC_apply_if(const struct Ordered_container* c_ptr, OC_apply_if_fp_t afp) {
	struct LL_Node* itemPtrItr = c_ptr->first;
	int returnValue = 0;
	while(itemPtrItr && !(returnValue = afp(OC_get_data_ptr(itemPtrItr)))) {
		itemPtrItr = itemPtrItr->next;
	}
	return returnValue;
}

/* Apply the supplied function to the data pointer in each item in the container;
the function takes a second argument, which is the supplied void pointer. 
The contents of the container cannot be modified. */
void OC_apply_arg(const struct Ordered_container* c_ptr, OC_apply_arg_fp_t afp, void* arg_ptr) {
	struct LL_Node* itemPtrItr = c_ptr->first;
		while(itemPtrItr) {
			afp(OC_get_data_ptr(itemPtrItr), arg_ptr);
			itemPtrItr = itemPtrItr->next;
		}
}

/* Apply the supplied function to the data pointer in each item in the container;
the function takes a second argument, which is the supplied void pointer. 
If the function returns non-zero, the iteration is terminated, and that value
returned. Otherwise, zero is returned. The contents of the container cannot be modified */
int OC_apply_if_arg(const struct Ordered_container* c_ptr, OC_apply_if_arg_fp_t afp, void* arg_ptr) {
	struct LL_Node* itemPtrItr = c_ptr->first;
		int returnValue = 0;
		while(itemPtrItr && !(returnValue = afp(OC_get_data_ptr(itemPtrItr), arg_ptr))) {
			itemPtrItr = itemPtrItr->next;
		}
		return returnValue;
}
