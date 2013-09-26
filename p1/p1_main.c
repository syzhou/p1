#include "Ordered_container.h"
#include "Person.h"
#include "Meeting.h"
#include "Room.h"
#include "Utility.h"

#include <stdlib.h>
#include <stdio.h>

int compareRooms(struct Room* rm1, struct Room* rm2);
void printIndividual(struct Ordered_container* people);
void printErrNoPerson(void);
void readRestOfLine(void);
void printRoom(struct Ordered_container* rooms);
int scanRoomNum(void);
void printErrInteger(void);
struct Room* findRoomByNum(struct Ordered_container* rooms, int* roomNum);
int compareNumAndRoom(const int* roomNum, struct Room* room);
void printErrNoRoom(void);
void printMeeting(struct Ordered_container* rooms);
int scanMeetingTime(void);
struct Meeting* findMeetingByTime(const struct Ordered_container* meetings, int* time);
int compareTimeAndMeeting(const int* time, struct Meeting* meeting);
void printErrNoMeeting(void);
void printSchedule(struct Ordered_container* rooms);
void printGroup(struct Ordered_container* people);
void printErrUnrecCmd(void);
void addIndividual(struct Ordered_container* people);
void printErrPersonExist(void);
void addRoom(struct Ordered_container* rooms);
void printErrRoomExist(void);
void addMeeting(struct Ordered_container* rooms);
void printErrMeetingExist(void);
void addParticipant(struct Ordered_container* rooms, struct Ordered_container* people);
void printErrParticipantExist(void);
void rescheduleMeeting(struct Ordered_container* rooms);
void deleteIndividual(struct Ordered_container* people, struct Ordered_container* rooms);
int findPersonRoomMeeting(struct Room* room, struct Person* person);
void deleteRoom(struct Ordered_container* rooms);
void destroyRoomMeeting(struct Room* room);
void deleteMeeting(struct Ordered_container* rooms);
void deleteParticipant(struct Ordered_container* rooms, struct Ordered_container* people);
void deleteSchedule(struct Ordered_container* rooms);
void deleteGroup(struct Ordered_container* rooms, struct Ordered_container* people);
int roomHasMeeting(struct Room* room);
void deleteAll(struct Ordered_container* rooms, struct Ordered_container* people);
int main() {
	struct Ordered_container* people;
	struct Ordered_container* rooms;
	people = OC_create_container((OC_comp_fp_t)comparePeople);
	rooms = OC_create_container((OC_comp_fp_t)compareRooms);
	while (1) {
		char cmd1;
		char cmd2;
		printf("\nEnter command: ");
		scanf(" %c", &cmd1);
		scanf("%c", &cmd2);
		switch (cmd1) {
		case 'p':
			switch (cmd2) {
			case 'i':
				printIndividual(people);
				break;
			case 'r':
				printRoom(rooms);
				break;
			case 'm':
				printMeeting(rooms);
				break;
			case 's':
				printSchedule(rooms);
				break;
			case 'g':
				printGroup(people);
				break;
			default:
				printErrUnrecCmd();
				break;
			}
			break;
		case 'a':
			switch (cmd2) {
			case 'i':
				addIndividual(people);
				break;
			case 'r':
				addRoom(rooms);
				break;
			case 'm':
				addMeeting(rooms);
				break;
			case 'p':
				addParticipant(rooms, people);
				break;
			default:
				printErrUnrecCmd();
				break;
			}
			break;
		case 'r':
			switch (cmd2) {
			case 'm':
				rescheduleMeeting(rooms);
				break;
			default:
				printErrUnrecCmd();
				break;
			}
			break;
		case 'd':
			switch (cmd2) {
			case 'i':
				deleteIndividual(people, rooms);
				break;
			case 'r':
				deleteRoom(rooms);
				break;
			case 'm':
				deleteMeeting(rooms);
				break;
			case 'p':
				deleteParticipant(rooms, people);
				break;
			case 's':
				deleteSchedule(rooms);
				break;
			case 'g':
				deleteGroup(rooms, people);
				break;
			case 'a':
				deleteAll(rooms, people);
				break;
			default:
				printErrUnrecCmd();
				break;
			}
			break;
		case 's':
			break;
		case 'l':
			break;
		case 'q':
			switch (cmd2) {
			case 'q' :
				printf("All meetings deleted\n");
				printf("All rooms deleted\n");
				printf("All persons deleted\n");
				printf("Done\n");
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

/* Compare two rooms and returns negative, 0 or positive if the
 * first room compares lesser, equal or larger than the second one.
 */
int compareRooms(struct Room* rm1, struct Room* rm2) {
	return (get_Room_number(rm1) - get_Room_number(rm2));
}

/* Read a lastname from stdin and print out the person's information.
 * Print an error message if that person desn't exist.
 */
void printIndividual(struct Ordered_container* people) {
	char lastnameBuffer[MAX_STRING_LENGTH];
	struct Person* person;
	SAFESCANF(lastnameBuffer);
	if ((person = findPersonByLastname(people, lastnameBuffer))) {
		print_Person(person);
	} else {
		printErrNoPerson();
	}
}

void printErrNoPerson() {
	readRestOfLine();
	printf("No person with that name!\n");
}

void readRestOfLine() {
	char c;
	while ((c = getchar()) != '\n');
}


/* Read a room number from stdin and print out the room's information.
 * Print an error message if that person desn't exist.
 */
void printRoom(struct Ordered_container* rooms) {
	struct Room* room;
	int roomNum;
	if ((roomNum = scanRoomNum()) != -1) {
		if ((room = findRoomByNum(rooms, &roomNum))) {
			print_Room(room);
		} else {
			printErrNoRoom();
		}
	}
}


int scanRoomNum(void) {
	int roomNum;
	if (scanf("%d", &roomNum) != 1) {
		printErrInteger();
		return -1;
	} else if (roomNum <= 0) {
		readRestOfLine();
		printf("Room number is not in range!\n");
		return -1;
	}
	return roomNum;
}

void printErrInteger(void) {
	readRestOfLine();
	printf("Could not read an integer value!\n");
}

/*Find a room by room number and returns a pointer to the room structure.
 * Returns NULL if not found.
 * The function takes the pointer to the ordered containter and the room number
 * as parameters.
 */
struct Room* findRoomByNum(struct Ordered_container* rooms, int* roomNum) {
	void *itemPtr = OC_find_item_arg(rooms, roomNum,
			(OC_find_item_arg_fp_t)compareNumAndRoom);
	return OC_get_data_ptr(itemPtr);
}

/* Compares the given room number and a room structure.
 * Used as function pointer in OC_find_item_arg function.
 */
int compareNumAndRoom(const int* roomNum, struct Room* room) {
	return (*roomNum - get_Room_number(room));
}


void printErrNoRoom(void) {
	readRestOfLine();
	printf("No room with that number!\n");
}

void printMeeting(struct Ordered_container* rooms) {
	int roomNum;
	int time;
	struct Room* room;
	struct Meeting* meeting;
	if ((roomNum = scanRoomNum()) == -1) {
		return;
	}
	if (!(room = findRoomByNum(rooms, &roomNum))) {
		printErrNoRoom();
		return;
	}
	if ((time = scanMeetingTime()) == -1) {
		return;
	}
	if (!(meeting = findMeetingByTime(get_Room_Meetings(room), &time))) {
		printErrNoMeeting();
		return;
	}
	print_Meeting(meeting);
}

int scanMeetingTime(void) {
	int time;
	if (scanf("%d", &time) != 1) {
		printErrInteger();
		return -1;
	} else if (!((time >=9 && time <=12) || (time >=1 && time <= 5))) {
		readRestOfLine();
		printf("Time is not in range!\n");
		return -1;
	}
	return time;
}

struct Meeting* findMeetingByTime(const struct Ordered_container* meetings, int* time) {
	void *itemPtr = OC_find_item_arg(meetings, time,
			(OC_find_item_arg_fp_t)compareTimeAndMeeting);
	return OC_get_data_ptr(itemPtr);
}
int compareTimeAndMeeting(const int* time, struct Meeting* meeting) {
	return (*time - get_Meeting_time(meeting));
}
void printErrNoMeeting(void) {
	readRestOfLine();
	printf("No meeting at that time!\n");
}
void printSchedule(struct Ordered_container* rooms) {
	OC_apply(rooms, (OC_apply_fp_t)print_Room);
}

void printGroup(struct Ordered_container* people) {
	OC_apply(people, (OC_apply_fp_t)print_Person);
}
/*Print out error when command is not recognized.
 *
 */
void printErrUnrecCmd() {
	readRestOfLine();
	printf("Unrecognized command!\n");
}



/* Read firstname, lastname and phone number from stdin
 * and add the person to the people list.
 * Print an error message if that person already exist.
 */
void addIndividual(struct Ordered_container* people) {
	struct Person* newPerson = load_Person(stdin);
	if (newPerson && (addPersonIfNotExist(newPerson, people))) {
		printErrPersonExist();
		return;
	}
	printf("Person %s added\n", get_Person_lastname(newPerson));
}

void printErrPersonExist(void) {
	readRestOfLine();
	printf("There is already a person with this last name!\n");
}


/* Read room number from stdin and add the room to the room list.
 * Print an error message if that person already exist.
 */
void addRoom(struct Ordered_container* rooms) {
	int roomNum;
	struct Room* room;
	if ((roomNum = scanRoomNum()) != -1) {
		if (findRoomByNum(rooms, &roomNum)) {
			printErrRoomExist();
			return;
		} else {
			room = create_Room(roomNum);
			OC_insert(rooms, room);
			printf("Room %d added\n", roomNum);
		}
	}
}

void printErrRoomExist(void) {
	readRestOfLine();
	printf("There is already a room with this number!\n");
}
void addMeeting(struct Ordered_container* rooms) {
	int roomNum;
	int time;
	struct Room* room;
	struct Meeting* meeting;
	char topicBuffer[MAX_STRING_LENGTH];
	if ((roomNum = scanRoomNum()) == -1) {
		return;
	}
	if (!(room = findRoomByNum(rooms, &roomNum))) {
		printErrNoRoom();
		return;
	}
	if ((time = scanMeetingTime()) == -1) {
		return;
	}
	if (findMeetingByTime(get_Room_Meetings(room), &time)) {
		printErrMeetingExist();
		return;
	}
	SAFESCANF(topicBuffer);
	meeting = create_Meeting(time, topicBuffer);
	add_Room_Meeting(room, meeting);
	printf("Meeting added at %d\n", time);

}
void printErrMeetingExist(void) {
	readRestOfLine();
	printf("There is already a meeting at that time!\n");
}

void addParticipant(struct Ordered_container* rooms, struct Ordered_container* people) {
	int roomNum;
	int time;
	char lastnameBuffer[MAX_STRING_LENGTH];
	struct Room* room;
	struct Meeting* meeting;
	struct Person* person;
	if ((roomNum = scanRoomNum()) == -1) {
		return;
	}
	if (!(room = findRoomByNum(rooms, &roomNum))) {
		printErrNoRoom();
		return;
	}
	if ((time = scanMeetingTime()) == -1) {
		return;
	}
	if (!(meeting = findMeetingByTime(get_Room_Meetings(room), &time))) {
		printErrNoMeeting();
		return;
	}
	SAFESCANF(lastnameBuffer);
	if (!(person = findPersonByLastname(people, lastnameBuffer))) {
		printErrNoPerson();
	}
	if (add_Meeting_participant(meeting, person)) {
		printErrParticipantExist();
	} else {
		printf("Participant %s added\n", lastnameBuffer);
	}
}

void printErrParticipantExist(void) {
	readRestOfLine();
	printf("This person is already a participant!\n");
}

void rescheduleMeeting(struct Ordered_container* rooms) {
	int oldRoomNum;
	int oldTime;
	struct Room* oldRoom;
	struct Meeting* meeting;
	int newRoomNum;
	int newTime;
	struct Room* newRoom;
	if ((oldRoomNum = scanRoomNum()) == -1) {
		return;
	}
	if (!(oldRoom = findRoomByNum(rooms, &oldRoomNum))) {
		printErrNoRoom();
		return;
	}
	if ((oldTime = scanMeetingTime()) == -1) {
		return;
	}
	if (!(meeting = findMeetingByTime(get_Room_Meetings(oldRoom), &oldTime))) {
		printErrMeetingExist();
		return;
	}
	if ((newRoomNum = scanRoomNum()) == -1) {
		return;
	}
	if (!(newRoom = findRoomByNum(rooms, &newRoomNum))) {
		printErrNoRoom();
		return;
	}
	if ((newTime = scanMeetingTime()) == -1) {
		return;
	}
	if (findMeetingByTime(get_Room_Meetings(newRoom), &newTime)) {
		printErrMeetingExist();
		return;
	}
	remove_Room_Meeting(oldRoom, meeting);
	set_Meeting_time(meeting, newTime);
	add_Room_Meeting(newRoom, meeting);
}
void deleteIndividual(struct Ordered_container* people, struct Ordered_container* rooms) {
	char lastnameBuffer[MAX_STRING_LENGTH];
	struct Person* person;
	SAFESCANF(lastnameBuffer);
	if (!(person = findPersonByLastname(people, lastnameBuffer))) {
		printErrNoPerson();
		return;
	}
	if (OC_apply_if_arg(rooms,
			(OC_apply_if_arg_fp_t)findPersonRoomMeeting, person)) {
		readRestOfLine();
		printf("This person is a participant in a meeting!\n");
	} else {
		OC_delete_item(people, findPersonByLastname(people, lastnameBuffer));
		destroy_Person(person);
		printf("Person %s deleted\n", lastnameBuffer);
	}
}

int findPersonRoomMeeting(struct Room* room, struct Person* person) {
	return (int)OC_find_item(get_Room_Meetings(room), person);
}
void deleteRoom(struct Ordered_container* rooms) {
	struct Room* room;
	int roomNum;
	if ((roomNum = scanRoomNum()) == -1) {
		return;
	}
	if (!(room = findRoomByNum(rooms, &roomNum))) {
		printErrNoRoom();
		return;
	}
	destroyRoomMeeting(room);
	printf("Room %d deleted\n", roomNum);
}
void destroyRoomMeeting(struct Room* room) {
	clear_Room(room);
	destroy_Room(room);
}

void deleteMeeting(struct Ordered_container* rooms) {
	int roomNum;
	int time;
	struct Room* room;
	struct Meeting* meeting;
	if ((roomNum = scanRoomNum()) == -1) {
		return;
	}
	if (!(room = findRoomByNum(rooms, &roomNum))) {
		printErrNoRoom();
		return;
	}
	if ((time = scanMeetingTime()) == -1) {
		return;
	}
	if (!(meeting = findMeetingByTime(get_Room_Meetings(room), &time))) {
		printErrNoMeeting();
		return;
	}
	destroy_Meeting(meeting);
	printf("Meeting at %d deleted\n", time);
}
void deleteParticipant(struct Ordered_container* rooms, struct Ordered_container* people) {
	int roomNum;
	int time;
	char lastnameBuffer[MAX_STRING_LENGTH];
	struct Room* room;
	struct Meeting* meeting;
	struct Person* person;
	if ((roomNum = scanRoomNum()) == -1) {
		return;
	}
	if (!(room = findRoomByNum(rooms, &roomNum))) {
		printErrNoRoom();
		return;
	}
	if ((time = scanMeetingTime()) == -1) {
		return;
	}
	if (!(meeting = findMeetingByTime(get_Room_Meetings(room), &time))) {
		printErrNoMeeting();
		return;
	}
	SAFESCANF(lastnameBuffer);
	if (!(person = findPersonByLastname(people, lastnameBuffer))) {
		printErrNoPerson();
	}
	if (remove_Meeting_participant(meeting, person)) {
		readRestOfLine();
		printf("This person is not a participant in the meeting!\n");
	} else {
		printf("Participant %s deleted\n", lastnameBuffer);
	}
}
void deleteSchedule(struct Ordered_container* rooms) {
	OC_apply(rooms, (OC_apply_fp_t)destroyRoomMeeting);
}

void deleteGroup(struct Ordered_container* rooms, struct Ordered_container* people) {
	if (OC_apply_if(rooms, (OC_apply_if_fp_t)roomHasMeeting)) {
		readRestOfLine();
		printf("Cannot clear people list unless there are no meetings!\n");
	} else {
		OC_apply(people, (OC_apply_fp_t)destroy_Person);
	}
}
int roomHasMeeting(struct Room* room) {
	return (!OC_empty(get_Room_Meetings(room)));
}
void deleteAll(struct Ordered_container* rooms, struct Ordered_container* people) {
	deleteSchedule(rooms);
	deleteGroup(rooms, people);
}
