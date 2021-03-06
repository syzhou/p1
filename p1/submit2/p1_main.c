#include "Ordered_container.h"
#include "Person.h"
#include "Meeting.h"
#include "Room.h"
#include "Utility.h"

#include <stdlib.h>
#include <stdio.h>

void printErrUnrecCmd();

int main() {
	while (1) {
		char cmd1;
		char cmd2;
		struct Ordered_container* people;
		people = OC_create_container((OC_comp_fp_t)comparePeople);
		printf("\nEnter command: ");
		scanf(" %c", &cmd1);
		scanf("%c", &cmd2);
		switch (cmd1) {
		case 'p':
			break;
		case 'a':
			switch (cmd2) {
			case 'i':
			{
				addIndividual(people);
			}
				break;

			default:
				printErrUnrecCmd();
				break;
			}
			break;
		case 'r':
			break;
		case 'd':
			break;
		case 's':
			break;
		case 'l':
			break;
		case 'q':
			switch (cmd2) {
			case 'q' :
				return 0;
				break;
			default:
				printErrUnrecCmd();
				break;
			}
			break;
		default:
			printErrUnrecCmd();
			break;
		}
	}
	return 0;
}
void printErrUnrecCmd() {
	printf("Unrecognized command!\n");
}
void addIndividual(struct Ordered_container* people) {
	struct Person* newPerson = load_Person(stdin);
	if (newPerson && (addPersonIfNotExist(newPerson, people))) {
			printf("There is already a person with this last name!\n");
	}
}
