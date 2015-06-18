/*********************************************************************
** Program Filename: main.c
** Author: L. Herrick
** Date: 5/30/15
** Description: Implenation file and for hash map using dynamic array
structure. Includes functions: stringHash1, stringHash2, initMap,
createMap, _freeMap, deleteMap, _setTableSize, insertMap, atMap
containsKey, removeKey, size, capacity, emptyBuckets ,tableLoad
and printMap. Implemenations of functions developed from ideas in 
worksheets 36, 37, and 38.
*********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hashMap.h"



/*the first hashing function you can use*/
int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

/*the second hashing function you can use*/
int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between stringHash1 and stringHash2 is on this line*/
	return r;
}

/* initialize the supplied hashMap struct*/
void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

/* allocate memory and initialize a hash map*/
hashMap *createMap(int tableSize) {
	assert(tableSize > 0);
	hashMap *ht;
	ht = malloc(sizeof(hashMap));
	assert(ht != 0);
	initMap(ht, tableSize);
	return ht;
}

/*
 Free all memory used by the buckets.
 Note: Before freeing up a hashashLink, free the memory occupied by key and value
 */
void _freeMap (struct hashMap * ht)
{  
	/*write this - done*/
	int bucket;
	struct hashLink *cur, *after;

	//iterate through indecies*/
	for(bucket = 0; bucket < ht->tableSize; bucket++){

		cur = ht->table[bucket];
		/*clear all links at index*/
		while(cur != NULL){
			after = cur->next;
			free(cur);
			/*iterate*/
			cur = after;
		}
	}
	/*clear all data related to hashMap*/	
	free(ht->table);
	ht->tableSize = 0;
	ht->count = 0;
}

/* Deallocate buckets and the hash map.*/
void deleteMap(hashMap *ht) {
	assert(ht!= 0);
	/* Free all memory used by the buckets */
	_freeMap(ht);
	/* free the hashMap struct */
	free(ht);
}

/* 
Resizes the hash table to be the size newTableSize 
*/
void _setTableSize(struct hashMap * ht, int newTableSize)
{
	/*write this - done*/	
	int bucket;
	struct hashLink **oldTable = ht->table;
	int oldSize = ht->tableSize;

	initMap(ht, 2*oldSize);
	
	/*reallocate*/
	for(bucket = 0; bucket < oldSize; bucket++){
		struct hashLink *list;
		while((list = oldTable[bucket])){
			insertMap(ht, list->key, list->value);
			oldTable[bucket] = list->next;
			free(list);
		}
	}
	free(oldTable);
}

/*
 insert the following values into a hashashLink, you must create this hashashLink but
 only after you confirm that this key does not already exist in the table. For example, you
 cannot have two hashashLinks for the word "taco".
 
 if a hashashLink already exists in the table for the key provided you should
 replace that hashashLink--this requires freeing up the old memory pointed by hashashLink->value
 and then pointing hashashLink->value to value v.
 
 also, you must monitor the load factor and resize when the load factor is greater than
 or equal LOAD_FACTOR_THRESHOLD (defined in hashMap.h).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  
	/*write this*/	
	struct hashLink *cur, *link;
	int bucket;
	if(HASHING_FUNCTION == 1){
		bucket = stringHash1(k) % ht->tableSize;
	}
	else{	
		bucket = stringHash2(k) % ht->tableSize;
	}

	/* bucket is not empty */
	if(ht->table[bucket] != 0){
		cur = ht->table[bucket];
		while(cur != 0){
			/* found key- already exists */
			if(strcmp(cur->key,k) == 0){
				/*change value as per description*/
				cur->value = v;
				return;
			}
			/*iterate*/
			else{
				cur = cur->next;
			}
		}
		/*key not already in map, add at head attach body*/
		link = (struct hashLink *)malloc(sizeof(struct hashLink));
		link->key = k;
		link->value = v;
		link->next = 0;
		link->next = ht->table[bucket];
		ht->table[bucket] = link;
		ht->count++;
	}
	/*bucket is empty*/
	else{
		link = (struct hashLink *)malloc(sizeof(struct hashLink));
		link->key = k;
		link->value = v;
		link->next = 0;
		ht->table[bucket] = link;
		ht->count++;
	}

	//resize if needed
	int curLoad = tableLoad(ht);
	if(curLoad >= LOAD_FACTOR_THRESHOLD){
		_setTableSize(ht, 2*ht->tableSize);
	}

}


/*
 this returns the value (which is void*) stored in a hashashLink specified by the key k.
 
 if the user supplies the key "taco" you should find taco in the hashTable, then
 return the value member of the hashashLink that represents taco.
 
 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ 
	/*write this - done*/
	struct hashLink *cur;
	/* find correct bucket */
	int bucket;
	if(HASHING_FUNCTION == 1){
		bucket = stringHash1(k) % ht->tableSize;
	}
	else{	
		bucket = stringHash2(k) % ht->tableSize;
	}
	
	cur = ht->table[bucket];

	while(cur != NULL){	
		/*found it*/
		if(strcmp(cur->key,k) == 0){
			return &(cur->value);
		}
		cur = cur->next;
	}
	return NULL;
}

/*
 a simple yes/no if the key is in the hashtable. 
 0 is no, all other values are yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{  
	/*write this - done*/
	struct hashLink *cur;
	/* find correct bucket */
	int bucket;
	if(HASHING_FUNCTION == 1){
		bucket = stringHash1(k) % ht->tableSize;
	}
	else{	
		bucket = stringHash2(k) % ht->tableSize;
	}

	/*check to see if testElement is there*/
	cur = ht->table[bucket];

	while(cur != 0){	
		/*found it*/	
		if(strcmp(cur->key,k) == 0){
			return 1;
		}
		else{
			cur = cur->next;
		}
	}
	/*not found*/
	return 0;
}


/*
 find the hashashLink for the supplied key and remove it, also freeing the memory
 for that hashashLink. it is not an error to be unable to find the hashashLink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */
void removeKey (struct hashMap * ht, KeyType k)
{  
	/*write this - done*/	
	struct hashLink *cur;
	int bucket;
	if(HASHING_FUNCTION == 1){
		bucket = stringHash1(k) % ht->tableSize;
	}
	else{	
		bucket = stringHash2(k) % ht->tableSize;
	}
	
	/*iterate through the table*/
	cur = ht->table[bucket];
	
	if(containsKey(ht, k)){
		/*if it is the head*/
		if(strcmp(cur->key,k) == 0){
			struct hashLink *next = cur->next;
			free(cur);
			ht->table[bucket] = next;
		}
		/*if it is in the body*/
		else{
			struct hashLink *prev = cur;
			cur = cur->next;
			struct hashLink *next = cur->next;

			/*find element*/
			while(strcmp(cur->key,k) != 0){
				prev = cur;
				cur = cur->next;
				next = cur->next;
			}
			free(cur);
			prev->next = next;
		}
		ht->count--;
		printf("The key, %s, has been removed fdrom the hash map.\n", k);
	}
	else{
		/*else, not found */
		printf("Error: key '%s' could not be found in the hash map. No value removed.\n", k);
	}
}

/*
 returns the number of hashashLinks in the table
 */
int size (struct hashMap *ht)
{  
	/*write this - done*/
	return ht->count;
	
}

/*
 returns the number of buckets in the table
 */
int capacity(struct hashMap *ht)
{  
	/*write this - done*/
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashashLinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  
	/*write this - done*/
	int emptyCount = 0;
	int bucket;
	for(bucket = 0; bucket < ht->tableSize; bucket++){
		if(ht->table[bucket] == 0){
			emptyCount += 1;
		}
	}
	return emptyCount;
}

/*
 returns the ratio of: (number of hashashLinks) / (number of buckets)
 
 this value can range anywhere from zero (an empty table) to more then 1, which
 would mean that there are more hashashLinks then buckets (but remember hashashLinks
 are like linked list nodes so they can hang from each other)
 */
float tableLoad(struct hashMap *ht)
{  
	/*write this - done*/
	int hl = size(ht);
	int b = capacity(ht);
	return hl/b;
}


void printMap (struct hashMap * ht)
{
	int i;
	struct hashLink *temp;	
	for(i = 0;i < capacity(ht); i++){
		temp = ht->table[i];
		if(temp != 0) {		
			printf("\nBucket Index %d -> ", i);		
		}
		while(temp != 0){			
			printf("Key:%s|", temp->key);
			printValue(temp->value);
			printf(" -> ");
			temp=temp->next;			
		}		
	}
}


