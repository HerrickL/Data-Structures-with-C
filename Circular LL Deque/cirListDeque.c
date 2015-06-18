/*********************************************************************
** Program Filename: calc.c
** Author: L. Herrick
** Date: 4/20/15
** Description: Implementation file for circular linked list deque,
titeled cirListDeque.  Includes deque functions: addBackCirListDeque,
addFrontCirListDeque, frontCirListDeque, backCirListDeque, 
removeFrontCirListDeque, removeBackCirListDeque, freeCirListDeque, 
isEmptyCirListDeque, printCirListDeque, and reverseCirListDeque.  
Corresponds to ideas taken from doubly linked list implemnation in 
worksheet 19.
** Output: --
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include "cirListDeque.h"

/* Double Link Struture */
struct DLink {
	TYPE value;/* value of the link */
	struct DLink * next;/* pointer to the next link */
	struct DLink * prev;/* pointer to the previous link */
};

# define TYPE_SENTINEL_VALUE DBL_MAX 


/* ************************************************************************
 Deque ADT based on Circularly-Doubly-Linked List WITH Sentinel
 ************************************************************************ */

struct cirListDeque {
	int size;/* number of links in the deque */
	struct DLink *Sentinel;	/* pointer to the sentinel */
};
/* internal functions prototypes */
struct DLink* _createLink (TYPE val);
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v);
void _removeLink(struct cirListDeque *q, struct DLink *lnk);



/* ************************************************************************
	Deque Functions
************************************************************************ */

/* Initialize deque.

	param: 	q		pointer to the deque
	pre:	q is not null
	post:	q->Sentinel is allocated and q->size equals zero
*/
void _initCirListDeque (struct cirListDeque *q) 
{
  	
  	/*create sentinel*/
  	q->Sentinel = (struct DLink *)malloc(sizeof(struct DLink));
  	assert(q->Sentinel != 0);

  	/*assign the sentinel next and prev*/
  	q->Sentinel->next =	 q->Sentinel;
  	q->Sentinel->prev = q->Sentinel;

  	/*set size*/
  	q->size = 0;
}

/*
 create a new circular list deque
 
 */

struct cirListDeque *createCirListDeque()
{
	struct cirListDeque *newCL = malloc(sizeof(struct cirListDeque));
	_initCirListDeque(newCL);
	return(newCL);
}


/* Create a link for a value.

	param: 	val		the value to create a link for
	pre:	none
	post:	a link to store the value
*/
struct DLink * _createLink (TYPE val)
{
	/*assign memory*/
	struct DLink *newDLink = (struct DLink *) malloc(sizeof(struct DLink));
	assert(newDLink != 0);

	newDLink->value = val;

	return newDLink; 
}

/* Adds a link after another link

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the existing link in the deque
	param: 	v		value of the new link to be added after the existing link
	pre:	q is not null
	pre: 	lnk is not null
	pre:	lnk is in the deque 
	post:	the new link is added into the deque after the existing link
*/
void _addLinkAfter(struct cirListDeque *q, struct DLink *lnk, TYPE v)
{
	/*this will be used outside of this function wth q->Sentinel->prev or
	q->Sentinel->next*/

	assert(q != 0);
	assert(lnk != 0);

	/*create a link*/
	struct DLink *linkToAdd = _createLink(v); 

	/*insert link, add after param lnk*/
	linkToAdd->next = lnk->next;
	linkToAdd->prev = lnk;

	lnk->next = linkToAdd;
	linkToAdd->next->prev = linkToAdd;

	/*increment size*/
	q->size++;

	assert(!isEmptyCirListDeque(q));
}

/* Adds a link to the back of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackCirListDeque (struct cirListDeque *q, TYPE val) 
{
	/*assert(q != 0) called in _addLinkAfter*/

	/*use _addLinkAfter*/
	_addLinkAfter(q, q->Sentinel->prev, val);

	/*check to make sure val was added in the right place*/
	assert(backCirListDeque(q) == val);

}

/* Adds a link to the front of the deque

	param: 	q		pointer to the deque
	param: 	val		value for the link to be added
	pre:	q is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontCirListDeque(struct cirListDeque *q, TYPE val)
{
	/*assert(q != 0) called in _addLinkAfter*/

	/*use _addLinkAfter*/	 	 
	_addLinkAfter(q, q->Sentinel, val);

	/*check to make sure val was added in the right place*/
	assert(frontCirListDeque(q) == val);
}

/* Get the value of the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontCirListDeque(struct cirListDeque *q) 
{
	/*return front of list*/
	return q->Sentinel->next->value;
}

/* Get the value of the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backCirListDeque(struct cirListDeque *q)
{
	/*return back of list*/
	return q->Sentinel->prev->value;
}

/* Remove a link from the deque

	param: 	q		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	q is not null and q is not empty
	post:	the link is removed from the deque
*/
void _removeLink(struct cirListDeque *q, struct DLink *lnk)
{
	assert(q != 0); 

	/*remove link from list pointers*/
	lnk->next->prev = lnk->prev;
	lnk->prev->next = lnk->next;

	/*free mem*/
	free(lnk);

	/*adjust size of list*/
	q->size--;
}

/* Remove the front of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the front is removed from the deque
*/
void removeFrontCirListDeque (struct cirListDeque *q) {
	assert(q != 0);
	assert(!isEmptyCirListDeque(q));

	_removeLink(q, q->Sentinel->next);
}


/* Remove the back of the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackCirListDeque(struct cirListDeque *q)
{
	assert(q != 0);
	assert(!isEmptyCirListDeque(q));

	_removeLink(q, q->Sentinel->prev);	 
}

/* De-allocate all links of the deque

	param: 	q		pointer to the deque
	pre:	none
	post:	All links (including Sentinel) are de-allocated
*/
void freeCirListDeque(struct cirListDeque *q)
{
	/*iterate through list, freeing nodes*/
	int index;
	struct DLink *freeThis = q->Sentinel->next;

	for(index = 0; index < q->size; index++)
	{
		free(freeThis);

		freeThis = freeThis->next;
	}

	free(q->Sentinel);
	free(q);
	
}

/* Check whether the deque is empty

	param: 	q		pointer to the deque
	pre:	q is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyCirListDeque(struct cirListDeque *q) {
  	return q->size == 0;
}

/* Print the links in the deque from front to back

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the links in the deque are printed from front to back
*/
void printCirListDeque(struct cirListDeque *q)
{
	int index = 0;
	struct DLink *printThis = q->Sentinel->next;

	/*iterate through*/
	while(index < q->size)
	{
		printf("%g  ", printThis->value);

		/*update location and iterator limit checker*/
		printThis = printThis -> next;
		index++;
	}
	printf("\n");

}

/* Reverse the deque

	param: 	q		pointer to the deque
	pre:	q is not null and q is not empty
	post: 	the deque is reversed
*/
void reverseCirListDeque(struct cirListDeque *q)
{
	assert(q != 0);
	assert(!isEmptyCirListDeque(q));

	int index;
	struct DLink *current = q->Sentinel->next;
	struct DLink *oldPrev = q->Sentinel;
	struct DLink *oldNext = q->Sentinel->next->next;

	/*iterate through the array and flip flop the next/prevs */	
	for(index = 0; index <= q->size; index++)
	{
		/*adjust current and prev*/
		current->next = oldPrev;
		current->prev = oldNext;

		/*move on to next, update next*/
		oldPrev = current;
		current = oldNext;
		oldNext = oldNext->next;
	} 

}
