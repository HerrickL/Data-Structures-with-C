/*********************************************************************
** Program Filename: calc.c
** Author: L. Herrick
** Date: 4/7/15
** Description: Calculates user input using the RPN calulation process.
** Input: program name, string for RPN calculator. Spaces are used as
whitespace between numbers, keywords, and equation symbols.  Accepted 
symbols and keywords are +, -, x, /, ^, ^2, ^3, abs, sqrt, exp, ln and 
log.
Example: ./calc 5 4 + 
** Output: Result of RPN calculation in double format
Example (to above): Final Result: 9.000000
*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dynamicArray.h"

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

#ifndef E
#define E 2.7182818284590452353602875
#endif



/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}
	else 
	{
		returnNum = strtod(s, &end);
		/* If there's anythin in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}
	}
	return 0;  //if got here, it was not a number
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their sum is pushed back onto the stack.
*/
void add (struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double num1;
	double num2;
	double result;

	/*Are there two operands after the operator?*/
	if(sizeDynArr(stack) >= 2)
	{
		/*get top number*/
		num2 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*get new top number*/
		num1 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*calculate*/
		result = num1 + num2;

		/*add sum to top of stack*/
		pushDynArr(stack, result);
	}
	/*error: not enough numbers*/
	else
	{
		printf("Error: there are not enough numbers to compute. \n");
	}

}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double num1;
	double num2;
	double result;

	/*Are there two operands after the operator?*/
	if(sizeDynArr(stack) >= 2)
	{
		/*get top number*/
		num2 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*get new top number*/
		num1 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*calculate*/
		result = num1 - num2;

		/*add sum to top of stack*/
		pushDynArr(stack, result);
	}
	/*error: not enough numbers*/
	else
	{
		printf("Error: there are not enough numbers to compute. \n");
	}

}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double num1;
	double num2;
	double result;

	/*Are there two operands after the operator?*/
	if(sizeDynArr(stack) >= 2)
	{
		/*get top number*/
		num2 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*get new top number*/
		num1 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*check for division errors*/
		if(num2 != 0)
		{
			/*calculate*/
			result = num1 / num2;

			/*add sum to top of stack*/
			pushDynArr(stack, result);
		}
		else
		{
			printf("Error: cannot divide by zero.\n");
		}
	}
	/*error: not enough numbers*/
	else
	{
		printf("Error: there are not enough numbers to compute. \n");
	}
}


/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their product is pushed back onto the stack.
*/
void multiply(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double num1;
	double num2;
	double result;

	/*Are there two operands after the operator?*/
	if(sizeDynArr(stack) >= 2)
	{
		/*get top number*/
		num2 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*get new top number*/
		num1 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*calculate*/
		result = num1 * num2;

		/*add sum to top of stack*/
		pushDynArr(stack, result);
	}
	/*error: not enough numbers*/
	else
	{
		printf("Error: there are not enough numbers to compute. \n");
	}

}


/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their power of result is pushed back onto the stack.
*/
void powerOf(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double num1;
	double num2;
	double result;

	/*Are there two operands after the operator?*/
	if(sizeDynArr(stack) >= 2)
	{
		/*get top number*/
		num2 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*get new top number*/
		num1 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*calculate using power from math.h*/
		result = pow(num2, num1);

		/*add sum to top of stack*/
		pushDynArr(stack, result);
	}
	/*error: not enough numbers*/
	else
	{
		printf("Error: there are not enough numbers to compute. \n");
	}

}


/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top element is popped and 
	the power of 2 result is pushed back onto the stack.
*/
void powerOf2(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double num1;
	double result;

	/*Are there two operands after the operator?*/
	if(sizeDynArr(stack) >= 1)
	{
		/*get new top number*/
		num1 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*calculate using power from math.h*/
		result = pow(num1, 2);

		/*add sum to top of stack*/
		pushDynArr(stack, result);
	}
	/*error: not enough numbers*/
	else
	{
		printf("Error: there are not enough numbers to compute. \n");
	}

}


/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top element is popped and 
	the power of 3 result is pushed back onto the stack.
*/
void powerOf3(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double num1;
	double result;

	/*Are there two operands after the operator?*/
	if(sizeDynArr(stack) >= 1)
	{
		/*get new top number*/
		num1 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*calculate using power from math.h*/
		result = pow(num1, 3);

		/*add sum to top of stack*/
		pushDynArr(stack, result);
	}
	/*error: not enough numbers*/
	else
	{
		printf("Error: there are not enough numbers to compute. \n");
	}

}


/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top element is popped and
	their square root result is pushed back onto the stack.
*/
void squareRoot(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double num1;
	double result;

	/*Are there two operands after the operator?*/
	if(sizeDynArr(stack) >= 1)
	{
		/*get new top number*/
		num1 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*calculate using sqrt from math.h*/
		result = sqrt(num1);

		/*add sum to top of stack*/
		pushDynArr(stack, result);
	}
	/*error: not enough numbers*/
	else
	{
		printf("Error: there are not enough numbers to compute. \n");
	}

}

/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top element is popped and 
	the absolute value is pushed back onto the stack.
*/
void absolute(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double num1;
	double result;

	/*Are there two operands after the operator?*/
	if(sizeDynArr(stack) >= 1)
	{
		/*get new top number*/
		num1 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*calculate using fabs from math.h*/
		result = fabs(num1);

		/*add sum to top of stack*/
		pushDynArr(stack, result);
	}
	/*error: not enough numbers*/
	else
	{
		printf("Error: there are not enough numbers to compute. \n");
	}

}


/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top element is popped and 
	the log value is pushed back onto the stack.
*/
void logarithm(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double num1;
	double result;

	/*Are there two operands after the operator?*/
	if(sizeDynArr(stack) >= 1)
	{
		/*get new top number*/
		num1 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*calculate using log10 from math.h*/
		result = log10(num1);

		/*add sum to top of stack*/
		pushDynArr(stack, result);
	}
	/*error: not enough numbers*/
	else
	{
		printf("Error: there are not enough numbers to compute. \n");
	}

}


/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top element is popped and 
	the natural log value is pushed back onto the stack.
*/
void naturalLog(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double num1;
	double result;

	/*Are there two operands after the operator?*/
	if(sizeDynArr(stack) >= 1)
	{
		/*get new top number*/
		num1 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*calculate using log from math.h*/
		result = log(num1);

		/*add sum to top of stack*/
		pushDynArr(stack, result);
	}
	/*error: not enough numbers*/
	else
	{
		printf("Error: there are not enough numbers to compute. \n");
	}

}

/*	param: stack the stack being manipulated
	pre: the stack contains at least 1 element
	post: the top elements is popped and 
	the exponential result is pushed back onto the stack.
*/
void exponential(struct DynArr *stack)
{
	/* FIXME: You will write this function */
	double num1;
	double result;

	/*Are there two operands after the operator?*/
	if(sizeDynArr(stack) >= 1)
	{
		/*get new top number*/
		num1 = topDynArr(stack);

		/*remove number from stack*/
		popDynArr(stack);

		/*calculate using exo from math.h*/
		result = exp(num1);

		/*add sum to top of stack*/
		pushDynArr(stack, result);
	}
	/*error: not enough numbers*/
	else
	{
		printf("Error: there are not enough numbers to compute. \n");
	}

}


/*  param: int index of string, char string
	pre: the stack contains digits, accepted chars, or accepted signs
	post: elements are calculated based of off RPN, final result
	is printed to console.
*/
double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	char *s;
	struct DynArr *stack;

	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++) 
	{
		s = inputString[i];

		// Hint: General algorithm:
		// (1) Check if the string s is in the list of operators.
		//   (1a) If it is, perform corresponding operations.
		//   (1b) Otherwise, check if s is a number.
		//     (1b - I) If s is not a number, produce an error.
		//     (1b - II) If s is a number, push it onto the stack

		if(strcmp(s, "+") == 0)
		{
			add(stack);
			/*added to match fomat below*/
			printf("Adding\n");
		}
		else if(strcmp(s,"-") == 0)
		{
			subtract(stack);
			/*added to match fomat below*/
			printf("Subtracting\n");
		}
		else if(strcmp(s, "/") == 0)
		{
			divide(stack);
			/*added to match fomat below*/
			printf("Dividing\n");
		}
		else if(strcmp(s, "x") == 0)
		{	
			multiply(stack);
			printf("Multiplying\n");
		}
		else if(strcmp(s, "^") == 0)
		{	powerOf(stack);
			printf("Power\n");
		}
		else if(strcmp(s, "^2") == 0)
		{	/* FIXME: replace printf with your own function */
			powerOf2(stack);
			printf("Squaring\n");
		}
		else if(strcmp(s, "^3") == 0)
		{
			/* FIXME: replace printf with your own function */
			powerOf3(stack);
			printf("Cubing\n");
		}
		else if(strcmp(s, "abs") == 0)
		{	/* FIXME: replace printf with your own function */
			absolute(stack);
			printf("Absolute value\n");
		}
		else if(strcmp(s, "sqrt") == 0)
		{	/* FIXME: replace printf with your own function */
			squareRoot(stack);
			printf("Square root\n");
		}
		else if(strcmp(s, "exp") == 0)
		{	/* FIXME: replace printf with your own function */
			exponential(stack);
			printf("Exponential\n");
		}
		else if(strcmp(s, "ln") == 0)
		{	/* FIXME: replace printf with your own function */
			naturalLog(stack);
			printf("Natural Log\n");
		}
		else if(strcmp(s, "log") == 0)
		{	/* FIXME: replace printf with your own function */
			logarithm(stack);
			printf("Log\n");
		}
		else if(strcmp(s, " ") == 0)
		{
			printf("Skipping space\n");
		}
		else 
		{
			// FIXME: You need to develop the code here (when s is not an operator)
			// Remember to deal with special values ("pi" and "e")

			/*Is it a number*/
			if(isNumber(s, &result))
			{
				/*add number to stack*/
				pushDynArr(stack, result);
			}
			/*Is it a special number*/
			else if(strcmp(s, "pi") == 0)
			{
				/*PI as defined in math.h*/
				result = PI;
				pushDynArr(stack, result);

			}
			else if(strcmp(s, "e") == 0)
			{
				/*Euler's number as defined in math.h*/
				result = E;
				pushDynArr(stack, result);
			}
			/*else error and end*/
			else
			{
				printf("Error: can not compute unknown/unaccepted character(s).\n");
			}
			
		}
	}	//end for 

	/* FIXME: You will write this part of the function (2 steps below) 
	 * (1) Check if everything looks OK and produce an error if needed.
	 * (2) Store the final value in result and print it out.
	 */

	 /*Is there only one value in the stack*/
	 if(sizeDynArr(stack) == 1)
	 {
	 	/*get number from top of stack*/
	 	result = topDynArr(stack);
	 	
	 	/*remove number from stack, stack is now empty*/
	 	popDynArr(stack);

	 	/*print result to console*/
	 	printf("Final Result: %f\n", result);
	 	return 0;
	 }
	 /*Else, error*/
	 else if(sizeDynArr(stack) > 1)
	 {
	 	printf("Error: there are too many numbers in the stack. Can not compute.\n");
	 	return 0;
	 }
	 else
	 {
	 	printf("Error: there are too few numbers in the stack. Can not compute.\n");
	 	return 0;
	 }
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

	calculate(argc,argv);
	return 0;
}
