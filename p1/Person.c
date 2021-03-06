#include "Person.h"
#include "Utility.h"
#include "p1_globals.h"

#include <stdlib.h>
#include <string.h>

/* a Person consist of pointers to C-strings for names and phone number */
struct Person {
	char* firstname;
	char* lastname;
	char* phoneno;
};

/* Create a Person object.
This is the only function that allocates dynamic memory for a Person
and the contained data. */
struct Person* create_Person(const char* firstname, const char* lastname, const char* phoneno) {
	struct Person* newPerson;
	if (!(newPerson = malloc(sizeof(struct Person)))) {
		printErrBadMallocExit();
	}
	newPerson->firstname = strAllocCpy(firstname);
	newPerson->lastname = strAllocCpy(lastname);
	newPerson->phoneno = strAllocCpy(phoneno);
	return newPerson;
}

/* Destroy a Person object
This is the only function that frees the memory for a Person
and the contained data. */
void destroy_Person(struct Person* person_ptr) {
	freeString(person_ptr->firstname);
	freeString(person_ptr->lastname);
	freeString(person_ptr->phoneno);
	free(person_ptr);
}

/* Return the lastname pointer as a pointer to unmodifiable characters. */
const char* get_Person_lastname(const struct Person* person_ptr) {
	return person_ptr->lastname;
}

/* Print a Person data item to standard output with a final \n character. */
void print_Person(const struct Person* person_ptr) {
	printf("%s %s %s\n", person_ptr->firstname,
						 person_ptr->lastname,
						 person_ptr->phoneno);
}

/* Write a Person to a file stream, as a line containing
firstname, lastname, phoneno,  whitespace-separated with a final \n character. */
void save_Person(const struct Person* person_ptr, FILE* outfile) {
	fprintf(outfile, "%s %s %s\n", person_ptr->firstname,
								   person_ptr->lastname,
								   person_ptr->phoneno);
}

/* Read a Person's data from a file stream, create the data object and
return a pointer to it, NULL if invalid data discovered in file.
No check made for whether the Person already exists or not. */
struct Person* load_Person(FILE* infile) {
	char firstnameBuf[BUFFER_SIZE];
	char lastnameBuf[BUFFER_SIZE];
	char phonenoBuf[BUFFER_SIZE];
	/* Read the strings and check read status*/
	if (SAFEFSCANF(infile, firstnameBuf) == EOF) {
		return NULL;
	}
	if (SAFEFSCANF(infile, lastnameBuf) == EOF) {
		return NULL;
	}
	if (SAFEFSCANF(infile, phonenoBuf) == EOF) {
		return NULL;
	}
	return create_Person(firstnameBuf, lastnameBuf, phonenoBuf);
}


