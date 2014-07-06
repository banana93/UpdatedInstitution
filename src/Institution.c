#include <stdio.h>
#include <string.h>
#include "Institution.h"
#include "LinkedList.h"
#include "Stack.h"
#include "CException.h"
#include "ErrorCode.h"

/**
 *  Reverse the order of element
 *  Input:
 *		inputList is a list of institutions
 *		outputList is a list of institutions in reversed order
 *	Return:
 *		the number of element reversed
 */
int Institution_reverse(LinkedList *inputList, LinkedList *outputList)
{
	Institution *institute;
	Stack *stack = Stack_create();

	do
	{
		institute = List_removeHead(inputList);
		if(institute != NULL)
		{
			//printf("Name1 : %s \n", institute->name);
			Stack_push(stack, institute);
		}
		else
			printf("Address : %p \n", institute);

		}while(institute != NULL);

	do
	{
		institute = Stack_pop(stack);
		if(institute != NULL)
		{
			//printf("Name : %s \n", institute->name);
			List_addTail(outputList, institute);
		}
		else
			printf("Address : %p \n", institute);

	}while(institute != NULL);		
}

/**
 *	Compare if institutions are of the same type
 *	Input:
 *		elem1 is a pointer to the first institution 
 *		type is a pointer to the type of college that I want
 *	Return:
 *		1 if the institution type is the same
 *		0 if otherwise
 */
int isUniversityCollege(void *elem1, void *type)
{
	if(((Institution *)elem1)->type == *(InstitutionType *)type)
		return 1;
	else
		return 0;
}

/**
 *	Compare if institution was established before the specified year 
 *	Input:
 *		elem is pointer to the first institution
 *		year is a pointer to the year
 *	Return:
 *		1 if the institution type is the same
 *		0 if otherwise
 */ 
int wasEstablishedBefore(void *elem, void *year)
{
	if(((Institution *)elem)->yearEstablished > 2014)
		Throw(ERR_WRONG_YEAR);
		
	if(((Institution *)elem)->yearEstablished < *(int *)year)
		return 1;
	
	return 0;
}

/**
 *	Reverse the order of element
 *	Input:
 *		inputList is a list of institutions
 *		outputList is a list of selected institutions
 *		criterion is a pointer to the criterion for selection
 *	Return:
 *		the number of element selected
 */
int Institution_select(LinkedList *inputList, LinkedList *outputList, void *criterion, int (*compare)(void *, void *))
{
	Institution *institute;
	int result = 0;
	int selectedInstitute = 0;
	
	do
	{
		institute = List_removeHead(inputList);
		if(institute != NULL)
			result = compare(institute, criterion);
			
		if(result == 1 && institute != NULL)
		{
			List_addTail(outputList, institute);
			printf("Name : %s \n", institute->name);
			printf("yearEstablished: %d \n", institute->yearEstablished);
			selectedInstitute++;
		}
		else	
			printf("Address : %p \n", institute);
		
	}while(institute != NULL);
	
	return selectedInstitute++;

}


