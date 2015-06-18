/*********************************************************************
** Program Filename: calc.c
** Author: L. Herrick
** Date: 4/20/15
** Description: Implementation file for doubly linked list deque bag,
named linkedList.  Corresponding methods include: addFrontList, 
addBackList, frontList, backlist, removeFrontList, removeBackList, 
isEmptyList, _printList, addList, containsList, and removeList.  
Ideas for implementation taken from worksheets 19 and 22.
** Output: --
*********************************************************************/
#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList{
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
	initList
	param lst the linkedList
	pre: lst is not null
	post: lst size is 0
*/
void _initList (struct linkedList *lst) {
	/*lst is not null*/
	assert(lst != 0);

	/*create space for firstLink*/
	lst->firstLink = malloc(sizeof(struct DLink));
	assert(lst->firstLink != 0);

	/*create space for lastLink*/
	lst->lastLink = malloc(sizeof(struct DLink));
	assert(lst->lastLink);

	/*assign front and back sentinel next/prevs*/
	lst->firstLink->next = lst->lastLink;
	lst->lastLink->prev = lst->firstLink;

	lst->size = 0;
}

/*
 createList
 param: none
 pre: none
 post: firstLink and lastLink reference sentinels
 */

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
	_adDLinkBeforeBefore
	param: lst the linkedList
	param: l the  link to add before
	param: v the value to add
	pre: lst is not null
	pre: l is not null
	post: lst is not empty
*/

/* Adds Before the provided link, l */

void _adDLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
	assert(lst != 0);
	assert(l != 0);

	/*create new link*/
	struct DLink *newDLink = (struct DLink *) malloc(sizeof(struct DLink)); 
	assert(newDLink != 0);

	/*set new link’s values*/
	newDLink ->value = v;

	/*set link’s next field*/
	newDLink->next = l;

	/*set link’s prev field*/
	newDLink->prev = l->prev;

	/*set prev link to point to new as next*/
	l->prev->next = newDLink;

	/*set next link to point to new as prev*/
	newDLink->next->prev = newDLink;

	/*adjust list size*/
	lst->size++;

	assert(!isEmptyList(lst));
}


/*
	addFrontList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addFrontList(struct linkedList *lst, TYPE e)
{
	_adDLinkBefore(lst, lst->firstLink->next, e);	
}

/*
	addBackList
	param: lst the linkedList
	param: e the element to be added
	pre: lst is not null
	post: lst is not empty, increased size by 1
*/

void addBackList(struct linkedList *lst, TYPE e) {
  
	_adDLinkBefore(lst, lst->lastLink, e); 
}

/*
	frontList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: none
*/

TYPE frontList (struct linkedList *lst) {
	/*validate that list is not empty*/
	assert(!isEmptyList(lst));

	return lst->firstLink->next->value;
}

/*
	backList
	param: lst the linkedList
	pre: lst is not null
	pre: lst is not empty
	post: lst is not empty
*/

TYPE backList(struct linkedList *lst)
{
	/*validate that list is not empty*/
	assert(!isEmptyList(lst));

	return lst->lastLink->prev->value;
}

/*
	_removeLink
	param: lst the linkedList
	param: l the linke to be removed
	pre: lst is not null
	pre: l is not null
	post: lst size is reduced by 1
*/
void _removeLink(struct linkedList *lst, struct DLink *l)
{
	assert(lst != 0);
	assert(l != 0);

	/*right = l->next*/
	/*left = l->prev*/

	l->next ->prev = l->prev;

	l->prev ->next = l->next;

	/*free memory*/
	free(l);

	/*adjust size of list*/
	lst->size--;	
}

/*
	removeFrontList
	param: lst the linkedList
	pre:lst is not null
	pre: lst is not empty
	post: size is reduced by 1
*/

void removeFrontList(struct linkedList *lst) {
	/* in _removeLink: assert(lst != 0)*/
  	assert(!isEmptyList(lst));
	_removeLink (lst, lst->firstLink->next);
}

/*
	removeBackList
	param: lst the linkedList
	pre: lst is not null
	pre:lst is not empty
	post: size reduced by 1
*/
void removeBackList(struct linkedList *lst)
{	
   /* in _removeLink: assert(lst != 0)*/
   assert(!isEmptyList(lst));
   _removeLink (lst, lst->lastLink->prev);
}

/*
	isEmptyList
	param: lst the linkedList
	pre: lst is not null
	post: none
*/
int isEmptyList(struct linkedList *lst) {
 	return lst->size == 0;
}


/* Function to print list
 Pre: lst is not null
 */
void _printList(struct linkedList* lst)
{
	struct DLink *node = lst->firstLink->next;
	assert(!isEmptyList(lst));

	/*iterate through the list*/
	while(node != lst->lastLink)
	{
		printf("%d  ", node->value);

		/*on to the next one*/
		node = node->next;
	}
	printf("\n");
}

/* 
	Add an item to the bag
	param: 	lst		pointer to the bag
	param: 	v		value to be added
	pre:	lst is not null
	post:	a link storing val is added to the bag
 */
void addList(struct linkedList *lst, TYPE v)
{
	addFrontList(lst, v);
}

/*	Returns boolean (encoded as an int) demonstrating whether or not
	the specified value is in the collection
	true = 1
	false = 0

	param:	lst		pointer to the bag
	param:	e		the value to look for in the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	no changes to the bag
*/
int containsList (struct linkedList *lst, TYPE e) {
	struct DLink *node = lst->firstLink->next;

	assert(lst->firstLink->next != 0);
	assert(!isEmptyList(lst));

	/*iterate through the list*/
	while(node != lst->lastLink)
	{
		/*if found*/
		if(node->value == e)
		{
			return 1;
		}

		node = node->next;
	}
	/*if not found*/
	return 0;

}

/*	Removes the first occurrence of the specified value from the collection
	if it occurs

	param:	lst		pointer to the bag
	param:	e		the value to be removed from the bag
	pre:	lst is not null
	pre:	lst is not empty
	post:	e has been removed
	post:	size of the bag is reduced by 1
*/
void removeList (struct linkedList *lst, TYPE e) {
	struct DLink *node = lst->firstLink->next;
	
	assert(lst->firstLink->next != 0);
	assert(!isEmptyList(lst));
	assert(containsList(lst, e));

	while(node != lst->lastLink)
	{
		/*if found*/
		if(node->value == e)
		{
			_removeLink(lst, node);
		}

		node = node->next;
	}	
}