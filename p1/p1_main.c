#include "Ordered_container.h"
#include "Person.h"
#include "Meeting.h"
#include "Room.h"
#include "Utility.h"
#include "p1_globals.h"

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
void printMemory(struct Ordered_container* rooms, struct Ordered_container* people);
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
int findPersonRoom(struct Room* room, struct Person* person);
void deleteRoom(struct Ordered_container* rooms);
void deleteMeeting(struct Ordered_container* rooms);
void deleteParticipant(struct Ordered_container* rooms, struct Ordered_container* people);
void deleteSchedule(struct Ordered_container* rooms);
void deleteGroup(struct Ordered_container* rooms, struct Ordered_container* people);
int roomHasMeeting(struct Room* room);
void deleteAll(struct Ordered_container* rooms, struct Ordered_container* people);
void saveData(struct Ordered_container* rooms, struct Ordered_container* people);
void printErrOpenFile(void);
void loadData(struct Ordered_container* rooms, struct Ordered_container* people);
void deleteAllSilent(struct Ordered_container* rooms, struct Ordered_container* people);
void printErrInvalidFile(struct Ordered_container* rooms, struct Ordered_container* people, FILE* file);


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
		scanf(" %c", &cmd2);
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
			case 'a':
				printMemory(rooms, people);
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
			switch (cmd2) {
			case 'd' :
				saveData(rooms, people);
				break;
			default:
				printErrUnrecCmd();
				break;
			}
			break;
		case 'l':
			switch (cmd2) {
			case 'd' :
				loadData(rooms, people);
				break;
			default:
				printErrUnrecCmd();
				break;
			}
			break;
		case 'q':
			switch (cmd2) {
			case 'q' :
				deleteAll(rooms, people);
				OC_destroy_container(rooms);
				OC_destroy_container(people);
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
/* Consume the rest of the line in stdin buffer and prints error
 * message for no such people in the people list.
 */
void printErrNoPerson() {
	readRestOfLine();
	printf("No person with that name!\n");
}

/* Consume the rest of the line in stdin buffer.
 */
void readRestOfLine() {
	char c;
	while ((c = getchar()) != '\n');
}


/* Read a room number from stdin and print out the room's information.
 * Print an error message if that person doesn't exist.
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

/* Read the room number from stdin and return the number
 * print error message and return -1 if unable to read an
 * integer or room number is out of range
 */
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

/* Consume the rest of the line in stdin buffer and prints error
 * message that can't read integer.
 */
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
	if (itemPtr) {
		return OC_get_data_ptr(itemPtr);
	} else {
		return NULL;
	}
}

/* Compares the given room number and a room structure.
 */
int compareNumAndRoom(const int* roomNum, struct Room* room) {
	return (*roomNum - get_Room_number(room));
}

/* Consume the rest of the line in stdin buffer and prints error
 * message that no such room with the room number.
 */
void printErrNoRoom(void) {
	readRestOfLine();
	printf("No room with that number!\n");
}

/* Read a room number and meeting time from stdin and print out the meeting's information.
 * Print an error message if can't read integer value, room number out of range,
 * no such room found, meeting time out of range or meeting does exist.
 */
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

/* Read the meeting time from stdin and return the number
 * print error message and return -1 if unable to read an
 * integer or time out of range
 */
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

/* Helper function that finds a meeting given an OC of meetings and meeting time.
 * Return the pointer to that meeting if found. Return NULL if not found.
 */
struct Meeting* findMeetingByTime(const struct Ordered_container* meetings, int* time) {
	void *itemPtr = OC_find_item_arg(meetings, time,
			(OC_find_item_arg_fp_t)compareTimeAndMeeting);
	if (itemPtr) {
		return OC_get_data_ptr(itemPtr);
	} else {
		return NULL;
	}
}

/* Compare function that compares meetings given a meeting time and a meeting pointer.
 */
int compareTimeAndMeeting(const int* meetingTime1Ptr, struct Meeting* meeting) {
	int meetingTime2 = get_Meeting_time(meeting);
	return compareTime(*meetingTime1Ptr, meetingTime2);
}

/* Consume the rest of the line in stdin buffer and prints error
 * message that no such meeting found.
 */
void printErrNoMeeting(void) {
	readRestOfLine();
	printf("No meeting at that time!\n");
}

/* Print the whole schecule with all meetings in all rooms.
 */
void printSchedule(struct Ordered_container* rooms) {
	int roomCnt;
	if ((roomCnt = OC_get_size(rooms))) {
		printf("Information for %d rooms:\n", roomCnt);
		OC_apply(rooms, (OC_apply_fp_t)print_Room);
	} else {
		printf("List of rooms is empty\n");
	}
}

/* Print every person's information.
 */
void printGroup(struct Ordered_container* people) {
	int peopleCnt;
	if ((peopleCnt = OC_get_size(people))) {
		printf("Information for %d people:\n", peopleCnt);
		OC_apply(people, (OC_apply_fp_t)print_Person);
	} else {
		printf("List of people is empty\n");
	}
}

/* Print memory allocation status.
 */
void printMemory(struct Ordered_container* rooms, struct Ordered_container* people) {
	printf("Memory allocations:\n");
	printf("C-strings: %d bytes total\n", g_string_memory);
	printf("Person structs: %d\n", OC_get_size(people));
	printf("Meeting structs: %d\n", g_Meeting_memory);
	printf("Room structs: %d\n", OC_get_size(rooms));
	printf("Containers: %d\n", g_Container_count);
	printf("Container items in use: %d\n", g_Container_items_in_use);
	printf("Container items allocated: %d\n", g_Container_items_allocated);

}
/* Consume the rest of the line in stdin and
 * print out error when command is not recognized.
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
		destroy_Person(newPerson);
		printErrPersonExist();
		return;
	}
	printf("Person %s added\n", get_Person_lastname(newPerson));
}

/* Consume the rest of the line in stdin buffer and prints error
 * message that the last name already exists.
 */
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

/* Consume the rest of the line in stdin buffer and prints error
 * message that the room number already exists.
 */
void printErrRoomExist(void) {
	readRestOfLine();
	printf("There is already a room with this number!\n");
}

/* Read room number, meeting time and meeting topic from stdin
 * and add the meeting to the meeting list.
 * Print an error message if can't read integer value, room number
 * out of range, room not found, time out of range, meeting already exist.
 */
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

/* Consume the rest of the line in stdin buffer and prints error
 * message that the meeting with room number and time already exists.
 */
void printErrMeetingExist(void) {
	readRestOfLine();
	printf("There is already a meeting at that time!\n");
}

/* Read room number, meeting time and participant lastname from stdin
 * and add the participant to the meeting.
 * Print an error message if can't read integer value, room number
 * out of range, room not found, time out of range, meeting not found,
 * person not found, person already a participant.
 */
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
	} else if (add_Meeting_participant(meeting, person)) {
		printErrParticipantExist();
	} else {
		printf("Participant %s added\n", lastnameBuffer);
	}
}

/* Consume the rest of the line in stdin buffer and prints error
 * message that person is already a participant.
 */
void printErrParticipantExist(void) {
	readRestOfLine();
	printf("This person is already a participant!\n");
}

/* Read old room number, old meeting time new room number and new meeting time,
 * reschedule the meeting to new room and new time.
 * Print an error message if can't read integer value, room number
 * out of range, room not found, time out of range, meeting not found
 * or new meeting time and room already taken.
 */
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
	printf("Meeting rescheduled to room %d at %d\n", newRoomNum, newTime);
}

/* Read lastname from stdin and delete the person from the people list.
 * Print an error message if that person doesn't exist
 * or an participant of a meeting.
 */
void deleteIndividual(struct Ordered_container* people, struct Ordered_container* rooms) {
	char lastnameBuffer[MAX_STRING_LENGTH];
	struct Person* person;
	SAFESCANF(lastnameBuffer);
	if (!(person = findPersonByLastname(people, lastnameBuffer))) {
		printErrNoPerson();
		return;
	}
	/* Check if the person is a participant of a meeting.
	 * The check will call findPersonRoom in each room
	 * then in each room find the person in each meeting.
	 */
	if (OC_apply_if_arg(rooms,
			(OC_apply_if_arg_fp_t)findPersonRoom, person)) {
		readRestOfLine();
		printf("This person is a participant in a meeting!\n");
	} else {
		OC_delete_item(people, OC_find_item(people, person));
		destroy_Person(person);
		printf("Person %s deleted\n", lastnameBuffer);
	}
}
/* Check whether a person is a participant of any meetings in the room.
 */
int findPersonRoom(struct Room* room, struct Person* person) {
	return OC_apply_if_arg(get_Room_Meetings(room),
				(OC_apply_if_arg_fp_t)is_Meeting_participant_present, person);
}

/* Read room number from stdin and delete the room from the people list.
 * All meetings in that room will also be canceled.
 * Print an error message if can't read integer, integer out of range
 * or that room doesn't exist
 */
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
	OC_delete_item(rooms, OC_find_item(rooms, room));
	clear_Room(room);
	destroy_Room(room);
	printf("Room %d deleted\n", roomNum);
}

/* Read a room number and meeting time from stdin and delete the room's information.
 * Print an error message if can't read integer value, room number out of range,
 * no such room found, meeting time out of range or meeting does exist.
 */
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
	remove_Room_Meeting(room, meeting);
	destroy_Meeting(meeting);
	printf("Meeting at %d deleted\n", time);
}

/* Read a room number, meeting time and lastname from stdin
 * and remove the participant.
 * Print an error message if can't read integer value, room number out of range,
 * no such room found, meeting time out of range, meeting does exist
 * or participant not exist.
 */
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
	} else if (remove_Meeting_participant(meeting, person)) {
		readRestOfLine();
		printf("This person is not a participant in the meeting!\n");
	} else {
		printf("Participant %s deleted\n", lastnameBuffer);
	}
}

/* Delete all meetings in all rooms
 */
void deleteSchedule(struct Ordered_container* rooms) {
	OC_apply(rooms, (OC_apply_fp_t)clear_Room);
	printf("All meetings deleted\n");
}

/* Delete all people information.
 * Print an error if there're meetings exist.
 */
void deleteGroup(struct Ordered_container* rooms, struct Ordered_container* people) {
	if (OC_apply_if(rooms, (OC_apply_if_fp_t)roomHasMeeting)) {
		readRestOfLine();
		printf("Cannot clear people list unless there are no meetings!\n");
	} else {
		OC_apply(people, (OC_apply_fp_t)destroy_Person);
		OC_clear(people);
		printf("All persons deleted\n");
	}
}

/* Check whether a room has any meetings.
 * Returns zero if no meeting found, non-zero otherwise.
 */
int roomHasMeeting(struct Room* room) {
	return (!OC_empty(get_Room_Meetings(room)));
}

/* Delete all data including meetings, rooms and people
 */
void deleteAll(struct Ordered_container* rooms, struct Ordered_container* people) {
	deleteSchedule(rooms);
	OC_apply(rooms, (OC_apply_fp_t)destroy_Room);
	OC_clear(rooms);
	printf("All rooms deleted\n");
	deleteGroup(rooms, people);
}

/* Read file name from stdin and save the current state to the file
 * Print an error if file can't be open to write.
 */
void saveData(struct Ordered_container* rooms, struct Ordered_container* people) {
	char fileNameBuffer[MAX_STRING_LENGTH];
	FILE *file;
	SAFESCANF(fileNameBuffer);
	if (!(file = fopen(fileNameBuffer, "w"))) {
		printErrOpenFile();
		return;
	}
	fprintf(file, "%d\n", OC_get_size(people));
	OC_apply_arg(people, (OC_apply_arg_fp_t)save_Person, file);
	fprintf(file, "%d\n", OC_get_size(rooms));
	OC_apply_arg(rooms, (OC_apply_arg_fp_t)save_Room, file);



	fclose(file);
	printf("Data saved\n");
}

/* Consume the rest of the line from stdin and print error file can't open.
 */
void printErrOpenFile(void) {
	readRestOfLine();
	printf("Could not open file!\n");
}

/* Read file name from stdin and load the file to current state.
 * Print an error if file can't be open to read or invalid file.
 */
void loadData(struct Ordered_container* rooms, struct Ordered_container* people) {
	char fileNameBuffer[MAX_STRING_LENGTH];
	int peopleCnt;
	int roomCnt;
	int i;
	FILE *file;
	SAFESCANF(fileNameBuffer);
	if (!(file = fopen(fileNameBuffer, "r"))) {
		printErrOpenFile();
		return;
	}
	deleteAllSilent(rooms, people);
	if (fscanf(file, "%d", &peopleCnt) != 1) {
		printErrInvalidFile(rooms, people, file);
		return;
	}
	for (i = 0; i < peopleCnt; i++) {
		struct Person* person;
		if (!(person = load_Person(file))) {
			printErrInvalidFile(rooms, people, file);
			return;
		}
		OC_insert(people, person);
	}
	if (fscanf(file, "%d", &roomCnt) != 1) {
		printErrInvalidFile(rooms, people, file);
		return;
	}
	for (i = 0; i < roomCnt; i++) {
		struct Room* room;
		if(!(room = load_Room(file, people))) {
			printErrInvalidFile(rooms, people, file);
			return;
		}
		OC_insert(rooms, room);
	}
	fclose(file);
	printf("Data loaded\n");
}

/* Delete all data in current state without stdout output.
 */
void deleteAllSilent(struct Ordered_container* rooms, struct Ordered_container* people) {
	OC_apply(rooms, (OC_apply_fp_t)clear_Room);
	OC_apply(rooms, (OC_apply_fp_t)destroy_Room);
	OC_clear(rooms);
	OC_apply(people, (OC_apply_fp_t)destroy_Person);
	OC_clear(people);
}

/* Consume the rest of line from stdin and print error invalid file.
 */
void printErrInvalidFile(struct Ordered_container* rooms, struct Ordered_container* people, FILE* file) {
	fclose(file);
	deleteAllSilent(rooms, people);
	readRestOfLine();
	printf("Invalid data found in file!\n");
}
