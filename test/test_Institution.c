#include "unity.h"
#include "Institution.h"
#include "mock_LinkedList.h"
#include "mock_Stack.h"
#include "CException.h"
#include "ErrorCode.h"

void setUp(void){}

void tearDown(void){}

void test_Institution_reverse_exploration(void)
{
	int result;
	LinkedList inputList, outputList;
	Stack stack;
	Institution UTAR = {.name = "UTAR"};
	Institution USM = {.name = "USM"};

	Stack_create_ExpectAndReturn(&stack);

	List_removeHead_ExpectAndReturn(&inputList, &UTAR);
	Stack_push_Expect(&stack, &UTAR);
	List_removeHead_ExpectAndReturn(&inputList, &USM);
	Stack_push_Expect(&stack, &USM);


	List_removeHead_ExpectAndReturn(&inputList, NULL);

	Stack_pop_ExpectAndReturn(&stack, &USM);
	List_addTail_Expect(&outputList, &USM);
	Stack_pop_ExpectAndReturn(&stack, &UTAR);
	List_addTail_Expect(&outputList, &UTAR);

	Stack_pop_ExpectAndReturn(&stack, NULL);

	Institution_reverse(&inputList, &outputList);
}

void test_Institution_reverse_after_UTAR_is_pushed_should_be_able_to_pop_UTAR_out(void)
{
	LinkedList inputList, outputList;
	Stack stack;
	Institution UTAR = {.name = "UTAR"};

	Stack_create_ExpectAndReturn(&stack);

	List_removeHead_ExpectAndReturn(&inputList, &UTAR);
	Stack_push_Expect(&stack, &UTAR);

	List_removeHead_ExpectAndReturn(&inputList, NULL);

	Stack_pop_ExpectAndReturn(&stack, &UTAR);
	List_addTail_Expect(&outputList, &UTAR);

	Stack_pop_ExpectAndReturn(&stack, NULL);

	Institution_reverse(&inputList, &outputList);
}

void test_isUniversityCollege_if_it_is_UniversityCollege_then_it_will_return_1(void)
{
	Institution TARUC = {.type = UniversityCollege};
	InstitutionType type = UniversityCollege;
	int result;

	result = isUniversityCollege(&TARUC, &type);
	TEST_ASSERT_EQUAL(1, result);

}

void test_Institution_select_should_select_UTAR_out(void)
{
	InstitutionType type = University;
	LinkedList inputList, outputList;
	int result;
	Institution UTAR = {.name = "UTAR",
						.type = University};

	List_removeHead_ExpectAndReturn(&inputList, &UTAR);
	List_addTail_Expect(&outputList, &UTAR);
	List_removeHead_ExpectAndReturn(&inputList, NULL);
	
	result = Institution_select(&inputList, &outputList, &type, isUniversityCollege);
	TEST_ASSERT_EQUAL(1, result);
}

void test_Institution_select_should_select_UTAR_and_USM_out(void)
{
	InstitutionType type = University;
	LinkedList inputList, outputList;
	int result;
	Institution UTAR = {.name = "UTAR",
						.type = University};
	
	Institution USM = {.name = "USM",
					   .type = University};
					   
	List_removeHead_ExpectAndReturn(&inputList, &UTAR);
	List_addTail_Expect(&outputList, &UTAR);
	List_removeHead_ExpectAndReturn(&inputList, &USM);
	List_addTail_Expect(&outputList, &USM);
	List_removeHead_ExpectAndReturn(&inputList, NULL);
	
	result = Institution_select(&inputList, &outputList, &type, isUniversityCollege);
	TEST_ASSERT_EQUAL(2, result);
}

void test_Institution_select_should_select_UTAR_out_and_not_TARUC(void)
{
	InstitutionType type = University;
	LinkedList inputList, outputList;
	int result;
	Institution UTAR = {.name = "UTAR",
						.type = University};
	
	Institution TARUC = {.name = "TARUC",
						 .type = UniversityCollege};
	
	List_removeHead_ExpectAndReturn(&inputList, &UTAR);
	List_addTail_Expect(&outputList, &UTAR);
	List_removeHead_ExpectAndReturn(&inputList, NULL);
	
	result = Institution_select(&inputList, &outputList, &type, isUniversityCollege);
	TEST_ASSERT_EQUAL(1, result);
}

void test_wasEstablishedBefore_should_return_1_due_to_the_yearEstablished_is_less_than_2014(void)
{
	int year = 2014;
	int result;
	
	Institution UTAR = {.name = "UTAR",
						.yearEstablished = 2000};
	
	result = wasEstablishedBefore(&UTAR, &year);
	TEST_ASSERT_EQUAL(1, result);
}

void test_wasEstablishedBefore_should_throw_an_exception_due_to_the_yearEstablished_is_greater_than_2014(void)
{
	int year = 2014;
	int result;
	CEXCEPTION_T err;
	
	Institution UTAR = {.name = "UTAR",
						.yearEstablished = 2015};
	
	Try
	{
		wasEstablishedBefore(&UTAR, &year);
		TEST_FAIL_MESSAGE("Should show an exception due to the year is greater than 2014");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_WRONG_YEAR, err, "Exception was expected");
		printf("The yearEstablished is invalid, Error Code [%d] \n", err);
	}
}

void test_Institution_select_should_select_out_UTAR_due_to_the_yearEstablished_is_lesser_than_the_expected_year_that_I_have_given(void)
{
	int year = 2014;
	int result;
	LinkedList inputList, outputList;
	
	Institution UTAR = {.name = "UTAR",
						.yearEstablished = 2000};
	
	List_removeHead_ExpectAndReturn(&inputList, &UTAR);
	List_addTail_Expect(&outputList, &UTAR);
	List_removeHead_ExpectAndReturn(&inputList, NULL);

	result = Institution_select(&inputList, &outputList, &year, wasEstablishedBefore);
	TEST_ASSERT_EQUAL(1, result);
}

void test_Institution_select_should_select_out_UTAR_and_USM_due_to_the_yearEstablished_is_lesser_than_the_expected_year_that_I_have_given(void)
{
	int year = 2014;
	int result;
	LinkedList inputList, outputList;
	
	Institution UTAR = {.name = "UTAR",
						.yearEstablished = 2000};
		
	Institution USM = {.name = "USM",
					   .yearEstablished = 1998};
	
	List_removeHead_ExpectAndReturn(&inputList, &UTAR);
	List_addTail_Expect(&outputList, &UTAR);
	List_removeHead_ExpectAndReturn(&inputList, &USM);
	List_addTail_Expect(&outputList, &USM);
	List_removeHead_ExpectAndReturn(&inputList, NULL);
	

	result = Institution_select(&inputList, &outputList, &year, wasEstablishedBefore);
	TEST_ASSERT_EQUAL(2, result);
}
	
