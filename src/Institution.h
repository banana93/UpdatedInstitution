#ifndef Institution_H
#define Institution_H
#include "LinkedList.h"
#include "Stack.h"

typedef enum {Unknown, University, UniversityCollege, College} InstitutionType;

typedef struct Institution_t
{
	char *name;
	char *address;
	unsigned long int postcode;
	unsigned long int telephone;
	InstitutionType type;
	int yearEstablished;
} Institution;

int Institution_reverse(LinkedList *inputList, LinkedList *outputList);
int isUniversityCollege(void *elem1, void *type);
int Institution_select(LinkedList *inputList, LinkedList *outputList, void *criterion, int (*compare)(void *, void *));
int wasEstablishedBefore(void *elem, void *year);

#endif // Institution_H
