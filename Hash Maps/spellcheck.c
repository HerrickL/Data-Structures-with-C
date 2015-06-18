/*********************************************************************
** Program Filename: spellcheck.c
** Author: L. Herrick
** Date: 5/30/15
** Description: Program demonstates the use of a spellchecker through
the implementation and use of a hashmap data structure.  Program
creates map and loads words to the hashmap from a txt file.  User
is asked to input a word and the input word is checked against the
words in the hashmap.  If the word is found, the spelling is correct.
If the word is not found, the spelling is not correct and/or the word
is not in the dictionary.  Program is case-sensitive.
*********************************************************************/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hashMap.h"
#include <ctype.h>

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file);

/*
 Load the contents of file into hashmap ht
 */
void loadDictionary(FILE* file, struct hashMap* ht);

int main (int argc, const char * argv[]) {
  clock_t timer;
  struct hashMap* hashTable;
  int tableSize = 1000;
  timer = clock();
  hashTable = createMap(tableSize);
  
  FILE* dictionary;
  dictionary = fopen("dictionary.txt", "r");
  
  loadDictionary(dictionary, hashTable);
  timer = clock() - timer;
	printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
  
  char* word = (char*)malloc(256*sizeof(char));
  int quit=0;
  while(!quit){
    printf("Enter a word: ");
    scanf("%s",word);
    /*
      ... spell checker code goes here ...
      ... You write this               ...
    */

     //check if word is in dictionary
      if(containsKey(hashTable, word)){
     	//found it! - correct spelling message
      	printf("'%s' is a correctly spelled word!\n", word);
      }
     //else - incorrect spelling message
     else{
     	printf("'%s' is not a correctly spelled word or not a word in the dictionary.\n", word);
     } 
    
    /* Don't remove this. It is used for grading*/
    if(strcmp(word,"quit")==0)
      quit=!quit;
  }
  free(word);
     
  return 0;
}

void loadDictionary(FILE* file, struct hashMap* ht)
{
  /* You will write this*/
	char* word;

	//while still words to point to
	while((word = getWord(file))){
		//this shouldn't happen, but just in case txt file used has doubles
		if(containsKey(ht, word)){
			ValueType* value = atMap(ht, word);
			*value += 1;
			insertMap(ht, word, *value);
		}
		//add new
		else{
			insertMap(ht, word, 1);
		}
	}
	free(word);
	fclose(file);
}

char* getWord(FILE *file)
{
	int length = 0;
	int maxLength = 16;
	char character;
    
	char* word = (char*)malloc(sizeof(char) * maxLength);
	assert(word != NULL);
    
	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);
		}
		if((character >= '0' && character <= '9') || /*is a number*/
		   (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
		   (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
		   (character == 39)) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}
    
	if(length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}


//needed to compile with other prog
void printValue(ValueType v) {
	printf("Value:%d",(int)v);
}
