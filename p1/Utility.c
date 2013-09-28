#include "Utility.h"
#include "Person.h"
#include "Ordered_container.h"
#include "p1_globals.h"

#include <stdlib.h>
#include <string.h>

#define TIME_BOUND 5


int compareLastnameAndPerson(char* lastname, void* data_ptr);



/* The following two functions manipulate string allocation
 * and deallocation to make string memory counting at one place.
 */

/* Allocate the memory for the new string and copy the source string
 * to the destination string.
 */
char* strAllocCpy(const char* source) {
	int stringSize;
	char* destination;
	if (!(destination = malloc((stringSize = (strlen(source) + 1))))) {
		printErrBadMallocExit();
	}
	strcpy(destination, source);
	g_string_memory += stringSize;
	return destination;
}
/* Deallocate the string pointed by s.
 */
void freeString(char* s) {
	g_string_memory -= strlen(s);
	g_string_memory --;
	free(s);
}
/* Comparison function for people structure. Compares two people by lastname.
 */
int comparePeople (const struct Person* person1, const struct Person* person2) {
	return strcmp(get_Person_lastname(person1), get_Person_lastname(person2));

}

/*Find a person by lastname and returns a pointer to the person structure.
 * Returns NULL if not found.
 * The function takes the pointer to the ordered containter and the lastname
 * as parameters.
 */
struct Person *findPersonByLastname (const struct Ordered_container* people, char* lastname) {
	void *itemPtr = OC_find_item_arg(people, lastname, (OC_find_item_arg_fp_t)compareLastnameAndPerson);
	if (itemPtr) {
		return OC_get_data_ptr(itemPtr);
	} else {
		return NULL;
	}
}

/*Add a person to an ordered container. Return 0 if successful.
 * Don't add to the container and return 1 if that person already exist.
 */
int addPersonIfNotExist(const struct Person* person_ptr, struct Ordered_container* people) {
	if (OC_find_item(people, (void*)person_ptr)) {
		return 1;
	}
	OC_insert(people, (void*)person_ptr);
	return 0;
}

/*Remove a person from an ordered container.
 * Return 0 if sucessful.
 * Don't remove and returns non-zero if that person is not present.
 */
int removePersonIfExist(const struct Person* person_ptr, struct Ordered_container* people) {
	void *itemPtr = OC_find_item(people, (void*)person_ptr);
	if (itemPtr) {
		OC_delete_item(people, itemPtr);
		return 0;
	} else {
		return 1;
	}
}
/* Compares the given last name and a person structure.
 * Used as function pointer in OC_find_item_arg function.
 */
int compareLastnameAndPerson(char* lastname, void* data_ptr) {
	return strcmp(lastname, get_Person_lastname((struct Person*)data_ptr));
}

/* Compare two meeting time given two integer values.
 * Return negative, zero or positive if the first is lesst,
 * equal or greater the the second.
 */
int compareTime(int meetingTime1, int meetingTime2) {
	/* Check which time period (9-12 or 1-5) the two meetings are in. */
	if ((meetingTime1 > TIME_BOUND && meetingTime2 > TIME_BOUND)
		|| (meetingTime1 <= TIME_BOUND && meetingTime2 <= TIME_BOUND)) {
		return meetingTime1 - meetingTime2;
	} else if (meetingTime1 > TIME_BOUND && meetingTime2 <= TIME_BOUND) {
		return -1;
	} else {
		return 1;
	}
}

/* Print an error message that unable to allocate memory and exit with code 1.
 */
void printErrBadMallocExit() {
	printf("Unable to allocate memory\n");
	exit(1);
}
