#include "Utility.h"
#include "Person.h"

#include <string.h>

/* Allocate the memory for the new string and copy the source string
 * to the destination string.
 */
void strAllocCpy(char* destination, const char* source) {
	destination = malloc(strlen(source) + 1);
	strcpy(destination, source);
}

/* Comparison function for people structure.
 */
int comparePeople (const void* data_ptr1, const void* data_ptr2) {
	struct Person* person1 = (struct Person*) data_ptr1;
	struct Person* person2 = (struct Person*) data_ptr2;
	return strcmp(get_Person_lastname(person1), get_Person_lastname(person2));

}

/*Find a person by lastname and returns a pointer to the person structure.
 * Returns NULL if not found.
 * The function takes the pointer to the ordered containter and the lastname
 * as parameters.
 */
struct Person *findPersonByLastname (const struct Ordered_container* people, char* lastname) {
	struct Person* soughtForPerson = create_Person(NULL, lastname, NULL);
	void *itemPtr = OC_find_item(people, (void*) soughtForPerson);
	destroy_Person(soughtForPerson);
	return OC_get_data_ptr(itemPtr);
}
